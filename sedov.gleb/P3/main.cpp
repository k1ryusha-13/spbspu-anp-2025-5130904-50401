#include <iostream>
#include <cstddef>
#include <limits>

void destroy(int * mtx);
int * create(size_t rows, size_t cols);
void input(int * mtx, size_t rows, size_t cols);
size_t min(size_t a, size_t b);
void convertIncMatrix(int * mtx, size_t rows, size_t cols);
size_t getNumCol(const int * mtx, size_t rows, size_t cols);
void output(const int * mtx, size_t rows, size_t cols);

int main()
{
  size_t a1 = 0, r = 0, c = 0;
  std::cin >> r >> c;
  if (a1 == 1)
  {
    int matrix[10000];
    input(matrix, r, c);
    size_t res = getNumCol(matrix, r, c);
    convertIncMatrix(matrix, r, c);
    output(matrix, r, c);
    std::cout << res << "\n";
    return 0;
  }
  else if (a1 == 2)
  {
    int * matrix = create(r, c);
    input(matrix, r, c);
    size_t res = getNumCol(matrix, r, c);
    convertIncMatrix(matrix, r, c);
    output(matrix, r, c);
    std::cout << res << "\n";
    return 0;
  }
}

void destroy(int * mtx)
{
  delete[] mtx;
}

int * create(size_t rows, size_t cols)
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

void input(int * mtx, size_t rows, size_t cols)
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

void convertIncMatrix(int * mtx, size_t rows, size_t cols)
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

size_t getNumCol(const int * mtx, size_t rows, size_t cols)
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

void output(const int * mtx, size_t rows, size_t cols)
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
