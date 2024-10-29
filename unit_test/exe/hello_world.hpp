#pragma once

#include <iostream>

#include "../sndth/swapper.hpp"

inline void
hello_world()
{
  LoadLibraryA("swapper.dll");
  std::cout << "Hello world!";
  system("pause");
}
