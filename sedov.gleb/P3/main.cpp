#include <iostream>
#include <cstddef>
#include <limits>

namespace sedov
{
  void destroy(int * mtx);
  int * create(size_t rows, size_t cols);
  void input(int * mtx, size_t rows, size_t cols);
  size_t min(size_t a, size_t b);
  void convertIncMatrix(int * mtx, size_t rows, size_t cols);
  size_t getNumCol(const int * mtx, size_t rows, size_t cols);
  void output(const int * mtx, size_t rows, size_t cols);
}

int main(int argc, char ** argv)
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  else if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  else if (!sedov::checkFirstArg(argv[1]))
  {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  else if ((argv[1][0] != '1' && argv[1][0] != '2') || argv[1][1] != '\0')
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  size_t r = 0, c = 0;
  std::cin >> r >> c;
  if (argv[1][0] == '1')
  {
    int matrix[10000];
    sedov::input(matrix, r, c);
    size_t res = sedov::getNumCol(matrix, r, c);
    sedov::convertIncMatrix(matrix, r, c);
    sedov::output(matrix, r, c);
    std::cout << res << "\n";
    return 0;
  }
  int * matrix = sedov::create(r, c);
  sedov::input(matrix, r, c);
  size_t res = sedov::getNumCol(matrix, r, c);
  sedov::convertIncMatrix(matrix, r, c);
  sedov::output(matrix, r, c);
  std::cout << res << "\n";
  return 0;
}

void sedov::destroy(int * mtx)
{
  delete[] mtx;
}

int * sedov::create(size_t rows, size_t cols)
{
  int * mtx = nullptr;
  try
  {
    mtx = new int[rows * cols];
  }
  catch (const std::bad_alloc &e)
  {
    destroy(mtx);
    throw;
  }
  return mtx;
}

void sedov::input(int * mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      std::cin >> mtx[i * cols + j];
    }
  }
}

size_t min(size_t a, size_t b)
{
  return a < b ? a : b;
}

void sedov::convertIncMatrix(int * mtx, size_t rows, size_t cols)
{
  size_t layer = min(rows, cols) / 2 + min(rows, cols) % 2;
  for (size_t k = 0; k < layer; ++k)
  {
    for (size_t i = k; i < rows - k; ++i)
    {
      for (size_t j = k; j < cols - j; ++j)
      {
        mtx[i * cols + j] += 1;
      }
    }
  }
}

size_t sedov::getNumCol(const int * mtx, size_t rows, size_t cols)
{
  size_t maxLength = 0, maxCol = 0;
  for (size_t j = 0; j < cols; ++j)
  {
    size_t length = 0;
    for (size_t i = 1; i < rows; ++i)
    {
      if (mtx[i * cols + j] == mtx[i * cols + j - 1])
      {
        length += 1;
        if (length > maxLength)
        {
          maxLength = length;
          maxCol = j + 1;
	}
      }
      else
      {
        length = 0;
      }
    }
  }
  return maxCol;
}

void sedov::output(const int * mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i)
  {
    std::cout << mtx[i * cols];
    for (size_t j = 1; j < cols; ++j)
    {
      std::cout << " " << mtx[i * cols + j];
    }
    std::cout << "\n";
  }
}
