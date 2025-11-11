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
void output_static(const int (* a) [100], size_t rows, size_t cols, std::ofstream & output)
{
  for (size_t i = 0; i < rows; ++i)
  {
    output << a[i][0];
    for (size_t j = 1; j < cols; ++j)
    {
      output << ' ' << a[i][j];
    }
    output << '\n';
  }
}
int main()
{
}
