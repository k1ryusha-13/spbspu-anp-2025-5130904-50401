#include <iostream>
#include <fstream>
#include <memory>

namespace zharov
{
  bool isArgNum(const char * arg);
  std::istream& createMatrix(std::istream& input, int* mtx, size_t rows, size_t cols);
  bool UppTriMtx(const int * mtx, size_t rows, size_t cols);
  size_t CntColNsm(const int * mtx, size_t rows, size_t cols);
}

int main(int argc, char ** argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  if (!zharov::isArgNum(argv[1])) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if ((argv[1][0] != '1' && argv[1][0] != '2') || argv[1][1] != '\0') {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  size_t rows = 0, cols = 0;
  std::ifstream input(argv[2]);
  input >> rows >> cols;
  if (!input) {
    std::cerr << "Bad read (rows and cols)\n";
    return 2;
  }

  if (argv[1][0] == '1') {
    constexpr size_t MAX_MATRIX_SIZE = 10000;
    int matrix[MAX_MATRIX_SIZE] = {};

    zharov::createMatrix(input, matrix, rows, cols);
    if (!input) {
      if (input.eof()) {
        std::cerr << "Not enough numbers\n";
      } else {
        std::cerr << "Bad read (wrong value)\n";
      }
      return 2;
    }

    input.close();
    std::ofstream output(argv[3]);
    output << zharov::UppTriMtx(matrix, rows, cols) << "\n";
    output << zharov::CntColNsm(matrix, rows, cols) << "\n";
    return 0;
  }

  int * matrix = reinterpret_cast< int * >(malloc(sizeof(int) * rows * cols));
  if (matrix == nullptr) {
    std::cerr << "Bad alloc\n";
    return 2;
  }

  zharov::createMatrix(input, matrix, rows, cols);
  if (!input) {
    if (input.eof()) {
      std::cerr << "Not enough numbers\n";
    } else {
      std::cerr << "Bad read (wrong value)\n";
    }
    free(matrix);
    return 2;
  }

  input.close();
  std::ofstream output(argv[3]);
  output << zharov::UppTriMtx(matrix, rows, cols) << "\n";
  output << zharov::CntColNsm(matrix, rows, cols) << "\n";
  free(matrix);
  return 0;
}

bool zharov::isArgNum(const char * arg)
{
  if (arg[0] == '\0') {
    return false;
  } else {
    for (int i = 0; arg[i] != '\0'; ++i) {
      if (arg[i] < '0' || arg[i] > '9') {
        return false;
      }
    }
  }
  return true;
}

std::istream& zharov::createMatrix(std::istream & input, int * mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows * cols; ++i) {
    if (!(input >> mtx[i])) {
      break;
    }
  }
  return input;
}

bool zharov::UppTriMtx(const int * mtx, size_t rows, size_t cols)
{
  if (rows != cols) {
    rows = (rows > cols) ? cols : rows;
    cols = rows;
  }

  if (rows == 0) {
    return false;
  }

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < i; ++j) {
      if (mtx[cols * i + j] != 0) {
        return false;
      }
    }
  }
  return true;
}

size_t zharov::CntColNsm(const int * mtx, size_t rows, size_t cols)
{
  if (rows == 0 || cols == 0) {
    return 0;
  }

  size_t res = cols;
  for (size_t i = 0; i < cols; ++i) {
    for (size_t j = 1; j < rows; ++j) {
      if (mtx[j * cols + i] == mtx[(j - 1) * cols + i]) {
        --res;
        break;
      }
    }
  }
  return res;
}
