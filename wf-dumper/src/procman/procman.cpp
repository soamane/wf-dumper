#include "procman.hpp"

#include <TlHelp32.h>
#include <windows.h>
#include <print>

ProcMan::ProcMan(const std::string& procName)
    : procId(0), hProc(0), hModule(0), imageSize(0), procName(procName) {}

ProcMan::~ProcMan() {
  if (hProc) {
    CloseHandle(hProc);
  }
}

bool ProcMan::Init() {
  if (!GetProcId()) {
    std::println("[-] Failed to get procId for '{}'", procName);
    return false;
  }

  if (!GetProcBase()) {
    std::println("[-] Failed to get procBase for '{}'", procName);
    return false;
  }

  if (!OpenProc()) {
    std::println("[-] Failed to open process '{}' with procId [{}]", procName,
                 procId);
    return false;
  }

  if (!GetImageSize()) {
    std::println("[-] Failed to get image size for '{}'", procName);
    return false;
  }

  return true;
}

HANDLE ProcMan::GetHandle() const {
  return hProc;
}

HMODULE ProcMan::GetModule() const {
  return hModule;
}

std::size_t ProcMan::GetSize() const {
  return imageSize;
}

TextSectionInfo ProcMan::GetTextSectionInfo() const {
  return TextSectionInfo();
}

bool ProcMan::OpenProc() {
  hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
  return hProc != NULL;
}

bool ProcMan::GetProcId() {
  auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (snapshot == INVALID_HANDLE_VALUE) {
    return false;
  }

  PROCESSENTRY32 procEntry;
  procEntry.dwSize = sizeof(PROCESSENTRY32);

  if (Process32First(snapshot, &procEntry)) {
    do {
      if (procName == procEntry.szExeFile) {
        procId = procEntry.th32ProcessID;
        CloseHandle(snapshot);
        return true;
      }
    } while (Process32Next(snapshot, &procEntry));
  }

  CloseHandle(snapshot);
  return false;
}

bool ProcMan::GetProcBase() {
  auto snapshot =
      CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
  if (snapshot == INVALID_HANDLE_VALUE) {
    return false;
  }

  MODULEENTRY32 modEntry;
  modEntry.dwSize = sizeof(MODULEENTRY32);

  if (Module32First(snapshot, &modEntry)) {
    hModule = modEntry.hModule;
    return true;
  }

  return false;
}

bool ProcMan::GetImageSize() {
  IMAGE_DOS_HEADER dos;
  if (!ReadProcessMemory(hProc, hModule, &dos, sizeof(dos), nullptr)) {
    return false;
  }

  IMAGE_NT_HEADERS nt;
  if (!ReadProcessMemory(
          hProc, reinterpret_cast<std::uint8_t*>(hModule) + dos.e_lfanew, &nt,
          sizeof(nt), nullptr)) {
    return false;
  }

  imageSize = nt.OptionalHeader.SizeOfImage;
  return true;
}
