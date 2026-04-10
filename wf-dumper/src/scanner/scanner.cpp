#include "scanner.hpp"

#include <procman/procman.hpp>
#include <vector>

PatternScanner::PatternScanner(ProcMan& proc) : proc(proc) {}

uintptr_t PatternScanner::GetPatternAddr(const char* pattern,
                                         const char* mask) {
  // We need only .text section for scanning
  const auto& textInfo = proc.GetTextSection();
  if (!textInfo.base || !textInfo.size) {
    return 0;
  }

  size_t textSize = textInfo.size;

  std::vector<uint8_t> buffer(textSize);
  if (!ReadProcessMemory(proc.GetHandle(),
                         reinterpret_cast<LPCVOID>(textInfo.base),
                         buffer.data(), textSize, nullptr)) {
    return 0;
  }

  size_t len = std::strlen(mask);

  for (size_t i = 0; i <= textSize - len; ++i) {
    bool found = true;

    for (size_t j = 0; j < len; ++j) {
      if (mask[j] == 'x' && static_cast<uint8_t>(pattern[j]) != buffer[i + j]) {
        found = false;
        break;
      }
    }

    if (found) {
      return textInfo.base + i;
    }
  }

  return 0;
}