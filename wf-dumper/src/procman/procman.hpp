#pragma once

#ifndef PROCMAN_HPP
#define PROCMAN_HPP

#include <windows.h>
#include <string>

struct TextSectionInfo {
  uintptr_t base;
  std::size_t size;
};

class ProcMan {
 public:
  ProcMan(const std::string& procName);
  ~ProcMan();

 public:
  bool Init();

 public:
  HANDLE GetHandle() const;
  HMODULE GetModule() const;
  SIZE_T GetSize() const;
  TextSectionInfo GetTextSection() const;

 private:
  bool OpenProc();
  bool GetProcId();
  bool GetProcBase();
  bool GetImageSize();
  bool GetTextSectionInfo();

 private:
  DWORD procId;
  HANDLE hProc;
  HMODULE hModule;
  SIZE_T imageSize;

  std::string procName;
  TextSectionInfo textSectionInfo;
};

#endif  // !PROCMAN_HPP