#include "../../sndth/swapper.hpp"

BOOL APIENTRY
DllMain(HMODULE /* hModule */,
        DWORD ul_reason_for_call,
        LPVOID /* lpReserved */)
{
  if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
    // 1. Get application handle
    auto handle = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));

    // 2. Unprotect (unlock) application
    swapper::set_lock(0);

    // 3. Set base address (handle as uintptr_t)
    swapper::set_base(handle);

    // 4. Set real address (from debugger like IDA)
    swapper::set_real(0x403160);

    // 5. Prepare some things like text to swap and target address.
    auto target_text = "Hello would!";
    auto target_address = swapper::get_target();

    // 6. At this point, we should have target address and text, so we can swap!
    strcpy_s(target_address, strlen(target_text) + 1, target_text);

    swapper::set_real(0x401031);
    target_address = swapper::get_target();
    
    memset(target_address, 0x90, 5);

    swapper::set_real(0x40103b);
    target_address = swapper::get_target();

    memset(target_address, 0x90, 6);
  }

  return TRUE;
}
