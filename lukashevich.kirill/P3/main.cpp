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

  std::istream& readMtx(std::istream& in, int* nums, size_t rows, size_t cols)
  {
    for (size_t i = 0; i < rows * cols; ++i)
    {
      if (!(in >> nums[i]))
      {
        return in;
      }
    }
    return in;
  }

  void fll_inc_wav(int* mtx, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return;
    }

    size_t layers = (std::min(rows, cols) + 1) / 2;

    for (size_t layer = 0; layer < layers; ++layer)
    {
      int increment = layer + 1;
      size_t start_row = layer;
      size_t end_row = rows - layer - 1;
      size_t start_col = layer;
      size_t end_col = cols - layer - 1;

      for (size_t j = start_col; j <= end_col; ++j)
      {
        mtx[start_row * cols + j] += increment;
        if (start_row != end_row)
        {
          mtx[end_row * cols + j] += increment;
        }
      }

      for (size_t i = start_row + 1; i < end_row; ++i)
      {
        mtx[i * cols + start_col] += increment;
        mtx[i * cols + end_col] += increment;
      }
    }
  }

  int max_sum_mdg(const int* mtx, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return 0;
    }

    int max_sum = 0;

    for (size_t d = 0; d < rows; ++d)
    {
      int sum = 0;
      size_t i = d;
      size_t j = 0;
      while (i < rows && j < cols)
      {
        sum += mtx[i * cols + j];
        ++i;
        ++j;
      }
      if (sum > max_sum)
      {
        max_sum = sum;
      }
    }

    for (size_t d = 1; d < cols; ++d)
    {
      int sum = 0;
      size_t i = 0;
      size_t j = d;
      while (i < rows && j < cols)
      {
        sum += mtx[i * cols + j];
        ++i;
        ++j;
      }
      if (sum > max_sum)
      {
        max_sum = sum;
      }
    }

    return max_sum;
  }
}
  
int main(int argc, char ** argv){

}
