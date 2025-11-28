#include <iostream>
#include <cstddef>
#include <limits>
#include <fstream>

namespace lukashevich
{
  std::ostream& outMtx(std::ostream& out, const int* matrix, size_t rows, size_t cols)
  {
    out << rows << " " << cols;
    if (rows > 0 && cols > 0)
    {
      out << " ";
      for (size_t i = 0; i < rows; ++i)
      {
        out << matrix[i * cols];
        for (size_t j = 1; j < cols; ++j)
        {
          out << " " << matrix[i * cols + j];
        }
      }
    }
    out << "\n";
    return out;
  }

  int* createMtx(size_t rows, size_t cols)
  {
    int* nums = nullptr;
    nums = reinterpret_cast<int*>(malloc(rows * cols * sizeof(int)));
    return nums;
  }

  
int main(int argc, char ** argv){

}
