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

 private:
  ProcMan& proc;
};

#endif  // !PATTERN_SCANNER_HPP
