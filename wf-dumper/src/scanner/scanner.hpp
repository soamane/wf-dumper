#pragma once

#ifndef PATTERN_SCANNER_HPP
#define PATTERN_SCANNER_HPP

#include <windows.h>
#include <string>

class ProcMan;

class PatternScanner {
 public:
  PatternScanner(ProcMan& proc);

 public:
  uintptr_t GetPatternAddr(const char* pattern, const char* mask);

  template <typename T>
  T GetImmediateVal(uintptr_t address, uint8_t opcodelen = 2);

 private:
  ProcMan& proc;
};

#include "scanner.inl"
#endif  // !PATTERN_SCANNER_HPP
