#include <iostream>
#include <fstream>
#include <memory>
#include <limits>

namespace rizatdinov
{
  bool willOverflow(int result, int digit, int multiplier);
  int stringToInt(const char * string);
  unsigned parseArgs(const char * const * argv, int argc);
  void errorHandler(unsigned parse_args);
  bool isLocalMax(const int * matrix, size_t cols, unsigned position);
  unsigned countLocalMax(const int * matrix, size_t rows, size_t cols);
  bool isTriangularMatrix(const int * matrix, size_t rows, size_t cols);
}

int main(int argc, char ** argv)
{
  namespace riz = rizatdinov;
  unsigned parse_args = riz::parseArgs(argv, argc);
  if (parse_args)
  {
    riz::errorHandler(parse_args);
    return 1;
  }
  int number = riz::stringToInt(argv[1]);
  std::ifstream input(argv[2]);
  size_t rows = 0, cols = 0;
  int * matrix = nullptr;
  input >> rows >> cols;
  if (input.fail())
  {
    std::cerr << "fatal: failed to read the file\n";
    return 2;
  }
  int static_matrix[rows * cols];
  if (number == 1)
  {
    matrix = static_matrix;
  }
  else
  {
    matrix = reinterpret_cast< int * >(malloc(sizeof(int) * rows * cols));
    if (matrix == nullptr)
    {
      std::cerr << "Bad alloc\n";
      return 3;
    }
  }
  for (size_t i = 0; i < cols * rows; ++i)
  {
    input >> matrix[i];
    if (input.fail())
    {
      if (number == 2)
      {
        free(matrix);
      }
      std::cerr << "fatal: failed to read the file\n";
      return 2;
    }
  }

  input.close();

  unsigned count_lmax = riz::countLocalMax(matrix, rows, cols);
  bool is_triangular = riz::isTriangularMatrix(matrix, rows, cols);

  std::ofstream output(argv[3]);
  output << "Expects output (retrun code 0): " << count_lmax;
  output << ' ' << (is_triangular ? "true" : "false");

  if (number == 2)
  {
    free(matrix);
  }

  return 0;
}

bool rizatdinov::isLocalMax(const int * matrix, size_t cols, unsigned position)
{
  bool result = matrix[position] > matrix[position - 1];
  result = result && matrix[position] > matrix[position + 1];
  result = result && matrix[position] > matrix[position - cols];
  result = result && matrix[position] > matrix[position + cols];

  return result;
}

unsigned rizatdinov::countLocalMax(const int * matrix, size_t rows, size_t cols)
{
  unsigned count = 0;
  for (size_t i = cols + 1; i < rows * (cols - 1); ++i)
  {
    if (i % cols == 0)
    {
      i++;
      continue;
    }
    count += rizatdinov::isLocalMax(matrix, cols, i);
  }
  return count;
}

bool rizatdinov::isTriangularMatrix(const int * matrix, size_t rows, size_t cols)
{
  bool result = true;
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      result = i > j ? matrix[i * j + j] == 0 : true;
    }
  }
  return result;
}

bool rizatdinov::willOverflow(int number, int digit, int multiplier)
{
  int max_limit = std::numeric_limits<int>::max();
  int min_limit = std::numeric_limits<int>::min();

  bool result = number < min_limit + digit * multiplier;
  result = result || (result > max_limit - digit * multiplier);

  return result;
}

int rizatdinov::stringToInt(const char * string)
{
  int result = 0;
  int digit = 0;
  int multiplier = 1;
  int count = 0;
  int start_limit = 0;
  int is_negative = 1;

  namespace riz = rizatdinov;

  if (string[0] == '-')
  {
    is_negative = -1;
    start_limit++;
    count++;
  }
  for (; string[count] != '\0'; ++count)
  {
    if (string[count] < '0' || string[count] > '9')
    {
      throw std::invalid_argument("invalid number");
    }
  }
  if (count - start_limit > 10)
  {
    throw std::overflow_error("overflow");
  }
  for (int i = count - 1; i >= start_limit; --i)
  {
    digit = ((int)string[i]) - 48;
    if (riz::willOverflow(result, digit, multiplier))
    {
      throw std::overflow_error("overflow");
    }
    result += digit * multiplier * is_negative;
    multiplier *= 10;
  }

  return result;
}

unsigned rizatdinov::parseArgs(const char * const * argv, int argc)
{
  int num = 0;
  unsigned result = argc < 4 || argc > 4;
  if (result)
  {
    return 1;
  }
  try
  {
    num = rizatdinov::stringToInt(argv[1]);
  }
  catch (...)
  {
    return 2;
  }
  std::ifstream input(argv[2]);
  result = (num < 1 || num > 2) ? 2 : 0;
  result = !input.is_open() ? 3 : result;

  return result;
}

void rizatdinov::errorHandler(unsigned parse_args)
{
  switch (parse_args)
  {
    case 1:
      std::cerr << "fatal: invalid number of arguments\n";
      break;
    case 2:
      std::cerr << "fatal: invalid parameter\n";
      break;
    case 3:
      std::cerr << "fatal: cannot open file\n";
      break;
  }
}
