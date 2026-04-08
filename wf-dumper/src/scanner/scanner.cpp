#include "scanner.hpp"

#include <procman/procman.hpp>
#include <vector>

PatternScanner::PatternScanner(ProcMan& proc) : proc(proc) {}

uintptr_t PatternScanner::GetPatternAddr(const char* pattern,
                                         const char* mask) {
  auto moduleSize = proc.GetSize();
  auto moduleBaseAddr = reinterpret_cast<uintptr_t>(proc.GetModule());

  std::vector<uint8_t> buffer(moduleSize);

  if (!ReadProcessMemory(proc.GetHandle(),
                         reinterpret_cast<LPCVOID>(moduleBaseAddr),
                         buffer.data(), moduleSize, nullptr)) {
    return 0;
  }

  size_t patternLength = std::strlen(mask);

  for (size_t i = 0; i <= moduleSize - patternLength; ++i) {
    bool found = true;

    for (size_t j = 0; j < patternLength; ++j) {
      if (mask[j] == 'x' && static_cast<uint8_t>(pattern[j]) != buffer[i + j]) {
        found = false;
        break;
      }
    }

    if (found) {
      return moduleBaseAddr + i;
    }
  }

  return 0;
}