#include <iostream>
#include <fstream>
#include <limits>
#include <cctype>

namespace chernov {
  std::istream & matrixInput(std::istream & input, int * mtx, size_t rows, size_t cols);
  bool isNumber(const char * word);
  void fllIncWav(std::ostream & output, int * mtx, size_t rows, size_t cols);
  int minSumMdg(std::ostream & output, const int * mtx, size_t rows, size_t cols);
  int getSumAntiDiagonal(const int * mtx, size_t x, size_t y, size_t rows, size_t cols);
  int processMatrix(std::istream & input, std::ostream & output, int * matrix, char type, size_t rows, size_t cols);
}

std::istream & chernov::matrixInput(std::istream & input, int * mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows * cols; ++i) {
    input >> mtx[i];
  }
  return input;
}

bool chernov::isNumber(const char * word)
{
  if (!word || *word == '\0') {
    return false;
  }
  size_t i = 0;
  if (word[0] == '-') {
    ++i;
  }
  for (; word[i] != '\0'; ++i) {
    if (!std::isdigit(word[i])) {
      return false;
    }
  }
  return true;
}

void chernov::fllIncWav(std::ostream & output, int * mtx, size_t rows, size_t cols)
{
  size_t add = 1;
  size_t x = 0, y = 0, count = 0;
  while (count++ < rows * cols) {
    mtx[cols * y + x] += static_cast<int>(add);
    if (y == add - 1 && x != cols - add) {
      ++x;
    }
    else if (x == cols - add && y != rows - add) {
      ++y;
    }
    else if (y == rows - add && x != add - 1) {
      --x;
    }
    else if (x == add - 1) {
      if (y == add) {
        add++;
        x++;
      }
      else {
        --y;
      }
    }
  }
}

int chernov::getSumAntiDiagonal(const int * mtx, size_t x, size_t y, size_t rows, size_t cols)
{
  int sum = 0;
  do {
    sum += mtx[y * cols + x];
  } while (x-- > 0 && ++y < rows);
  return sum;
}

int chernov::minSumMdg(std::ostream & output, const int * mtx, size_t rows, size_t cols)
{
  if (rows * cols == 0) {
    return 0;
  }
  int min_sum = std::numeric_limits< int >::max(), sum = 0;

  for (size_t x = 0; x < cols; ++x) {
    sum = getSumAntiDiagonal(mtx, x, 0, rows, cols);
    if (sum < min_sum) {
      min_sum = sum;
    }
  }
  for (size_t y = 1; y < rows; ++y) {
    sum = getSumAntiDiagonal(mtx, cols - 1, y, rows, cols);
    if (sum < min_sum) {
      min_sum = sum;
    }
  }
  return min_sum;
}

int chernov::processMatrix(std::istream & input, std::ostream & output, int * matrix, char type, size_t rows, size_t cols)
{
  if (!chernov::matrixInput(input, matrix, rows, cols)) {
    std::cerr << "Incorrect input\n";
    if (type == '2') {
      delete [] matrix;
    }
    return 2;
  }

  output << chernov::minSumMdg(output, matrix, rows, cols) << "\n";

  chernov::fllIncWav(output, matrix, rows, cols);
  output << rows << " " << cols;
  for (size_t i = 0; i < rows * cols; ++i) {
    output << " " << matrix[i];
  }
  output << "\n";

  if (type == '2') {
    delete [] matrix;
  }

  return 0;
}

int main(int argc, char ** argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  } else if (!chernov::isNumber(argv[1])) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  } else if (!((argv[1][0] == '1' || argv[1][0] == '2') && argv[1][1] == '\0')) {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
  size_t rows = 0, cols = 0;
  input >> rows >> cols;
  if (!input) {
    std::cerr << "Incorrect input\n";
    return 2;
  }

  char type = argv[1][0];
  if (type == '1') {
    constexpr size_t MAX_STATIC_MATRIX_SIZE = 10000;
    int matrix[MAX_STATIC_MATRIX_SIZE] = {};
    return chernov::processMatrix(input, output, matrix, type, rows, cols);
  }

  int * matrix = nullptr;
  try {
    matrix = new int[rows * cols];
  } catch (const std::bad_alloc & e) {
    std::cerr << "Bad alloc\n";
    return 2;
  }
  return chernov::processMatrix(input, output, matrix, type, rows, cols);
}
