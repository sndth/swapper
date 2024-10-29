//  _____      ____ _ _ __  _ __   ___ _ __
// / __\ \ /\ / / _` | '_ \| '_ \ / _ \ '__|
// \__ \\ V  V / (_| | |_) | |_) |  __/ |
// |___/ \_/\_/ \__,_| .__/| .__/ \___|_|
//                   |_|   |_|

#pragma once

#ifndef SWAPPER_HPP
#define SWAPPER_HPP

#include <exception>
#include <Windows.h>
#include <unordered_map>

class swapper final : public std::exception
{
#if !_HAS_CXX17
#define VAR_PREFIX static
#else
#define VAR_PREFIX static inline
#endif

  VAR_PREFIX uint8_t lock_status_;
  VAR_PREFIX uintptr_t base_address_;
  VAR_PREFIX uintptr_t real_address_;

#undef VAR_PREFIX

public:
  static void set_lock(const uint8_t lock_status)
  {
    lock_status_ = lock_status;

    if (!lock_status_) {
      auto hExecutableInstance = (size_t)GetModuleHandle(NULL);
      IMAGE_NT_HEADERS* ntHeader =
        (IMAGE_NT_HEADERS*)(hExecutableInstance +
                            ((IMAGE_DOS_HEADER*)hExecutableInstance)->e_lfanew);
      SIZE_T size = ntHeader->OptionalHeader.SizeOfImage;
      DWORD oldProtect;
      VirtualProtect(
        (VOID*)hExecutableInstance, size, PAGE_EXECUTE_READWRITE, &oldProtect);
    } else {
      // lock (protect) application again...
    }
  }

  static void set_base(const uintptr_t base_address)
  {
    base_address_ = base_address;
  }

  static void set_real(const uintptr_t real_address)
  {
    real_address_ = real_address;
  }

  static char* get_target()
  {
    if (!base_address_) {
      throw exception("Cannot return get_target, base_address_ is 0");
    }

    if (!real_address_) {
      throw exception("Cannot return get_target, real_address_ is 0");
    }

    return reinterpret_cast<char*>(base_address_ + (real_address_ - 0x400000));
  }

  static void set_array(
    const std::unordered_map<int, std::pair<int, int>>& new_array)
  {
    for (const auto& [fst, snd] : new_array) {
      set_real(fst);
      std::memset(get_target(), snd.first, snd.second);
    }
  }
};

#if !_HAS_CXX17
uint8_t swapper::lock_status_ = 0;
uintptr_t swapper::base_address_ = 0;
uintptr_t swapper::real_address_ = 0;
#endif
#endif
