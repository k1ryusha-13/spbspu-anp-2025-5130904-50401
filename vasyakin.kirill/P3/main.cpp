#include <iostream>
#include <cstddef>
#include <limits>
#include <fstream>
void destroy(int ** a, size_t created)
{
  for (size_t i = 0; i < created; ++i)
  {
    delete[] a[i];
  }
  delete[] a;
}
int main()
{
}
