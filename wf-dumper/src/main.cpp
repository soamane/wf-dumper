#include <print>
#include <procman/procman.hpp>
#include <scanner/scanner.hpp>

int main() {
  ProcMan proc("Game.exe");
  if (!proc.Init()) {
    std::println("[-] Failed to initialize process manager");
    return -1;
  }

  PatternScanner scanner(proc);

  uintptr_t firstadr = scanner.GetPatternAddr(
      "\x48\xBD\x00\x00\x00\x00\x00\x00\x00\x00\x49\xBE\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x48\x89\x00\x48\x89\x40\x00\x48\x89\x40\x00\x66\xC7\x40\x00\x00"
      "\x00\x48\x89\x43",
      "xx????????xx????????xxxxxx?xxx?xxx???xxx");

  uintptr_t secondadr = scanner.GetPatternAddr(
      "\x49\xBE\x00\x00\x00\x00\x00\x00\x00\x00\x48\x89\x00\x48\x89\x40\x00\x48\x89\x40\x00\x66\xC7\x40\x00\x00\x00\x48\x89\x43",
      "xx????????xxxxxx?xxx?xxx???xxx");
  
  std::println("{:016X}", scanner.GetImmediateVal<uintptr_t>(firstadr));
  std::println("{:016X}", scanner.GetImmediateVal<uintptr_t>(secondadr));
  return 0;
}