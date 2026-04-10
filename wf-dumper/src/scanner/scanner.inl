#ifndef SCANNER_INL
#define SCANNER_INL

#include <procman/procman.hpp>

template <typename T>
inline T PatternScanner::GetImmediateVal(uintptr_t address, uint8_t opcodelen) {
  T offset;
  uintptr_t readAddr = address + opcodelen;

  ReadProcessMemory(proc.GetHandle(), reinterpret_cast<LPCVOID>(readAddr),
                    &offset, sizeof(offset), nullptr);

  return offset;
}

#endif  // !SCANNER_INL
