#pragma once

#ifndef PROCMAN_HPP
#define PROCMAN_HPP

#include <windows.h>
#include <string>

class ProcMan {
 public:
  ProcMan(const std::string& procName);
  ~ProcMan();

 public:
  bool Init();

 public:
  HANDLE GetHandle() const;
  HMODULE GetModule() const;
  std::size_t GetImageSize() const;

 private:
  bool OpenProc();
  bool GetProcId();
  bool GetProcBase();

 private:
  DWORD procId;
  HANDLE hProc;
  HMODULE hModule;
  std::string procName;
};

#endif  // !PROCMAN_HPP
