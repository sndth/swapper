#include <iostream>

#include "../sndth/swapper.hpp"

int
main()
{
  LoadLibraryA("swapper.dll");
  std::cout << "Hello world!";
  system("pause");
}
