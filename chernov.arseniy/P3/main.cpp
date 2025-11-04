#include <iostream>
#include <fstream>

namespace chernov {
  void matrix_input(std::istream & input, int ** mtx, size_t rows, size_t cols);
  void matrix_input(std::istream & input, int (&mtx)[], size_t rows, size_t cols);
  void destroy(int ** mtx, size_t created);
  int ** create(size_t rows, size_t cols);
  bool isNumber(char * word);
  void fll_inc_wav(std::ostream & output, int (&mtx)[], size_t rows, size_t cols);
}

void chernov::matrix_input(std::istream & input, int ** mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      input >> mtx[i][j];
    }
  }
}

void chernov::matrix_input(std::istream & input, int (&mtx)[] , size_t rows, size_t cols)
{
  for (size_t i; i < rows * cols; ++i) {
    input >> mtx[i];
  }
}

void chernov::destroy(int ** mtx, size_t created)
{
  for (size_t i = 0; i < created; i++) {
    delete[] mtx[i];
  }
  delete[] mtx;
}

int ** chernov::create(size_t rows, size_t cols)
{
  size_t created = 0;
  int ** mtx = new int * [rows];
  try {
    for (; created < rows; created++) {
      mtx[created] = new int[cols];
    }
  } catch (const std::bad_alloc & e) {
    chernov::destroy(mtx, created);
    throw;
  }
  return mtx;
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

void chernov::fll_inc_wav(std::ostream & output, int (&mtx)[], size_t rows, size_t cols)
{
  
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


  }
}
