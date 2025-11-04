#include <iostream>
#include <fstream>

namespace chernov {
  void matrix_input(std::istream & input, int * mtx, size_t rows, size_t cols);
  bool isNumber(char * word);
  void fll_inc_wav(std::ostream & output, int mtx[], size_t rows, size_t cols);
}

void chernov::matrix_input(std::istream & input, int * mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows * cols; ++i) {
    input >> mtx[i];
  }
}

bool chernov::isNumber(char * word)
{
  for (size_t i = 0; word[i] != '\0'; ++i) {
    if (word[i] < '0' || word[i] > '9') {
      return false;
    }
  }
  return (word[0] != '\0');
}

void chernov::fll_inc_wav(std::ostream & output, int mtx[], size_t rows, size_t cols)
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

  output << rows << " " << cols;
  for (size_t i = 0; i < rows * cols; ++i) {
    output << " " << mtx[i];
  }
  output << "\n";
}

int main(int argc, char ** argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  } else if (! chernov::isNumber(argv[1])) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  } else if (! ((argv[1][0] == '1' || argv[1][0] == '2') && argv[1][1] == '\0')) {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  //std::istream& input = std::cin;
  std::ofstream output(argv[3]);
  //std::ostream& output = std::cout;
  size_t rows = 0, cols = 0;
  input >> rows >> cols;
  if (! input) {
    std::cerr << "Incorrect input\n";
    return 2;
  }

  if (argv[1][0] == '1') {
    int matrix[10000] = {};
    chernov::matrix_input(input, matrix, rows, cols);
    if (! input) {
      std::cerr << "Incorrect input\n";
      return 2;
    }

    chernov::fll_inc_wav(output, matrix, rows, cols);
    return 0;
  }

  int * matrix = new int [rows * cols];
  chernov::matrix_input(input, matrix, rows, cols);
  if (! input) {
    std::cerr << "Incorrect input\n";
    delete [] matrix;
    return 2;
  }

  try {
    chernov::fll_inc_wav(output, matrix, rows, cols);
  } catch (const std::exception & e) {
    delete [] matrix;
    throw;
  }
}
