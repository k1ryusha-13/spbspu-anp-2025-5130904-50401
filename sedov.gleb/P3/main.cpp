#include <iostream>
#include <cstddef>
#include <limits>
#include <fstream>

namespace sedov
{
  bool checkFirstArg(const char * a);
  void destroy(int * mtx);
  int * create(size_t rows, size_t cols);
  size_t input_mtx(std::istream & input, int * mtx, size_t rows, size_t cols);
  void convertIncMatrix(int * mtx, size_t rows, size_t cols);
  size_t getNumCol(const int * mtx, size_t rows, size_t cols);
  void output_mtx(std::ostream & out, const int * mtx, size_t rows, size_t cols);
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
  std::ifstream input(argv[2]);
  if (!input.is_open())
  {
    std::cerr << "Can't open file\n";
    return 2;
  }
  input >> r >> c;
  if (!input)
  {
    std::cerr << "Bad reading\n";
    input.close();
    return 2;
  }

  if (argv[1][0] == '1')
  {
    int matrix[10000];
    size_t st = sedov::input_mtx(input, matrix, r, c);
    input.close();
    if (st == 1)
    {
      std::cerr << "Not enough arguments for matrix\n";
      return 2;
    }
    else if (st == 2)
    {
      std::cerr << "Bad reading file\n";
      return 2;
    }
    size_t res = sedov::getNumCol(matrix, r, c);
    try
    {
      sedov::convertIncMatrix(matrix, r, c);
      std::ofstream output(argv[3]);
      sedov::output_mtx(output, matrix, r, c);
      output << res << "\n";
      return 0;
    }
    catch (const std::overflow_error &e)
    {
      std::cerr << e.what() << "\n";
      return 4;
    }
  }

  int * matrix = sedov::create(r, c);
  if (matrix == nullptr)
  {
    std::cerr << "Bad alloc\n";
    return 3;
  }
  size_t st = sedov::input_mtx(input, matrix, r, c);
  input.close();
  if (st == 1)
  {
    std::cerr << "Not enough arguments for matrix\n";
    delete[] matrix;
    return 2;
  }
  else if (st == 2)
  {
    std::cerr << "Bad reading file\n";
    delete[] matrix;
    return 2;
  }
  size_t res = sedov::getNumCol(matrix, r, c);
  try
  {
    sedov::convertIncMatrix(matrix, r, c);
    std::ofstream output(argv[3]);
    sedov::output_mtx(output, matrix, r, c);
    sedov::destroy(matrix);
    output << res << "\n";
    return 0;
  }
  catch (const std::overflow_error &e)
  {
    std::cerr << e.what() << "\n";
    delete[] matrix;
    return 4;
  }
}

bool sedov::checkFirstArg(const char * a)
{
  for (size_t i = 0; a[i] != '\0'; ++i)
  {
    if (a[i] < '0' || a[i] > '9')
    {
      return false;
    }
  }
  return true;
}

void sedov::destroy(int * mtx)
{
  delete[] mtx;
}

int * sedov::create(size_t rows, size_t cols)
{
  int * mtx = nullptr;
  mtx = new int[rows * cols];
  return mtx;
}

size_t sedov::input_mtx(std::istream & input, int * mtx, size_t rows, size_t cols)
{
  size_t c = 0;
  while (input >> mtx[c])
  {
    ++c;
  }
  if (input.eof())
  {
    if (c < rows * cols)
    {
      return 1;
    }
  }
  else if (input.fail())
  {
    return 2;
  }
  return 0;
}

void sedov::convertIncMatrix(int * mtx, size_t rows, size_t cols)
{
  size_t minrc = (rows < cols) ? rows : cols;
  size_t layer = minrc / 2 + minrc % 2;
  const int MAX = std::numeric_limits<int>::max();
  for (size_t k = 0; k < layer; ++k)
  {
    for (size_t i = k; i < rows - k; ++i)
    {
      for (size_t j = k; j < cols - j; ++j)
      {
        if (mtx[i * cols + j] > MAX - 1)
        {
          throw std::overflow_error("Increment matrix overflow");
        }
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
      if (mtx[i * rows + j] == mtx[(i - 1) * rows + j])
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

void sedov::output_mtx(std::ostream & out, const int * mtx, size_t rows, size_t cols)
{
  if (rows && cols)
  {
    out << rows << " " << cols << " ";
    for (size_t i = 0; i < rows; ++i)
    {
      out << mtx[i * cols];
      for (size_t j = 1; j < cols; ++j)
      {
        out << " " << mtx[i * cols + j];
      }
      if (i == rows - 1)
      {
        out << "\n";
      }
      else
      {
        out << " ";
      }
    }
  }
  else
  {
    out << rows << " " << cols << "\n";
  }
}
