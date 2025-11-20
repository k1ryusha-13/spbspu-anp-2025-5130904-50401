#include <iostream>
#include <fstream>
#include <memory>
#include <limits>

namespace rizatdinov
{
  unsigned parseArgs(int argc, char ** argv);
  void errorHandler(unsigned parse_args);
  int * creat(size_t len, int number);
  void initial(int * array, size_t len, std::ifstream & file);
  bool willOverflow(int number, int digit, int multiplier);
  int stringToInt(const char * string);
  bool isLocalMax(const int * array, size_t cols, size_t position);
  unsigned long countLocalMax(const int * array, size_t rows, size_t cols);
  bool isLowerTriangular(const int * array, size_t rows, size_t cols);
}

int main(int argc, char ** argv)
{
  unsigned parse_args = rizatdinov::parseArgs(argc, argv);
  if (parse_args) {
    rizatdinov::errorHandler(parse_args);
    return parse_args;
  }

  std::ifstream input(argv[2]);

  size_t rows = 0, cols = 0;
  input >> rows >> cols;
  if (!input) {
    rizatdinov::errorHandler(2);
    return 2;
  }

  int * array = nullptr;
  int array_static[10000] = {};
  int number = rizatdinov::stringToInt(argv[1]);
  try {
    array = rizatdinov::creat(rows * cols, number);
    if (array == nullptr) {
      array = array_static;
    }

    rizatdinov::initial(array, rows * cols, input);
  } catch(...) {
    if (number ==2) {
      free(array);
    }
    rizatdinov::errorHandler(2);
    return 2;
  }

  input.close();

  std::ofstream output(argv[3]);

  size_t count_local_max = rizatdinov::countLocalMax(array, rows, cols);
  bool is_lower_triangular = rizatdinov::isLowerTriangular(array, rows, cols);

  output << "Expects output (return code 0): " << count_local_max << '\n';
  output << "Expects output (return code 0): " << is_lower_triangular << '\n';

  if (number == 2) {
    free(array);
  }

  return 0;
}

unsigned rizatdinov::parseArgs(int argc, char ** argv)
{
  if (argc != 4) {
    return 1;
  }

  int num = 0;
  try {
    num = rizatdinov::stringToInt(argv[1]);
  } catch (...) {
    return 1;
  }

  std::ifstream file(argv[2]);

  unsigned result = (num < 1 || num > 2) ? 1 : 0;
  result = !file ? 2 : result;

  return result;
}

void rizatdinov::errorHandler(unsigned parse_args)
{
  switch (parse_args) {
    case 1:
      std::cerr << "fatal: invalid parametr\n";
      break;
    case 2:
      std::cerr << "fatal: invalid file\n";
      break;
  }
}

int * rizatdinov::creat(size_t len, int number)
{
  int * array = nullptr;
  if (number == 2) {
    array = reinterpret_cast< int * >(malloc(sizeof(int) * len));
    if (array == nullptr) {
      throw std::bad_alloc();
    }
  }
  return array;
}

void rizatdinov::initial(int * array, size_t len, std::ifstream & file)
{
  for (size_t i = 0; i < len; ++i) {
    file >> array[i];
    if (!file) {
      throw std::invalid_argument("invalid argument");
    }
  }
}

bool rizatdinov::willOverflow(int number, int digit, int multiplier)
{
  int max_limit = std::numeric_limits< int >::max();
  int min_limit = std::numeric_limits< int >::min();

  bool result = number < min_limit + digit * multiplier;
  result = result || (result > max_limit - digit * multiplier);

  return result;
}

int rizatdinov::stringToInt(const char * string)
{
  int result = 0;
  int multiplier = 1;
  int is_negative = 1;
  int start_limit = 0;

  if (string[0] == '-') {
    is_negative = -1;
    start_limit++;
  }

  size_t len = start_limit;
  for (; string[len] != '\0'; ++len) {
    if (string[len] < '0' || string[len] > '9') {
      throw std::invalid_argument("invalid number");
    }
  }

  if (len - start_limit > 10) {
    throw std::overflow_error("overflow");
  }

  for (size_t i = len; i > 0; --i) {
    int digit = static_cast< int >(string[i - 1] - 48);

    if (rizatdinov::willOverflow(result, digit, multiplier)) {
      throw std::overflow_error("overflow");
    }

    result += digit * multiplier * is_negative;
    multiplier *= 10;
  }

  return result;
}

bool rizatdinov::isLocalMax(const int * array, size_t cols, size_t position)
{
  bool result = array[position] > array[position + 1];
  result = result && array[position] > array[position - 1];
  result = result && array[position] > array[position + cols];
  result = result && array[position] > array[position - cols];

  return result;
}

unsigned long rizatdinov::countLocalMax(const int * array, size_t rows, size_t cols)
{
  size_t count = 0;
  for (size_t i = 1; i + 1 < rows; ++i) {
    for (size_t j = 1; j + 1 < cols; ++j) {
      size_t position = i * cols + j;
      count += rizatdinov::isLocalMax(array, cols, position);
    }
  }
  return count;
}

bool rizatdinov::isLowerTriangular(const int * array, size_t rows, size_t cols)
{
  bool result = false;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = i + 1; j < cols; ++j) {
      if (array[i * cols + j] != 0) {
        return false;
      }
    }
    result = true;
  }
  return result;
}
