#include <iostream>

#include "../../sndth/swapper.hpp"

BOOL APIENTRY
DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
      auto handle = reinterpret_cast<size_t>(GetModuleHandle(nullptr));

      swapper::set_lock(0);
      swapper::set_base(handle);
      swapper::set_real(0x40313C);

      auto target_text = "Hello would!";
      auto target_address = swapper::get_target();

      strcpy_s(target_address, strlen(target_text) + 1, target_text);
    } break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}
