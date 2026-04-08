#include <print>
#include <procman/procman.hpp>
#include <scanner/scanner.hpp>

int main() {
  ProcMan proc("CrackMeEasy.exe");
  if (!proc.Init()) {
    std::println("[-] Failed to initialize process manager");
    return -1;
  }

  PatternScanner scanner(proc);
// E8 ? ? ? ? 48 8D 15 ? ? ? ? 48 83 3D
  std::print("{:016X}",
             scanner.GetPatternAddr(
                 "\xE8\x00\x00\x00\x00\x48\x8D\x15\x00\x00\x00\x00\x48\x83\x3D",
                 "x????xxx????xxx"));
  return 0;
}