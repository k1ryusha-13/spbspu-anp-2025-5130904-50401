#include <iostream>
#include <fstream>
#include <memory>
#include <limits>

namespace zubarev
{
  int getMaxInt();
  int getMinInt();
  std::ostream& outputMatrix(std::ostream& out, const int* matrix, size_t rows, size_t cols);
  int* convertToSquare(int* matrix, size_t& rows, size_t& cols, bool dynamic);
  int* readMatrix(std::istream& in, size_t& rows, size_t& cols, int* matrix, bool dynamic);
  int solveTask9(const int* matrix, size_t rows, size_t cols);
  int solveTask14(const int* matrix, size_t rows, size_t cols);
}

int main(int argc, char const** argv)
{
  namespace zub = zubarev;
  size_t rows = 0, cols = 0;
  bool dynamic = false;
  try {
    if (argc > 4) {
      std::cerr << "Too many arguments" << "\n";
      return 1;
    } else if (argc < 4) {
      std::cerr << "Not enough arguments" << "\n";
      return 1;
    } else if (argv[1][0] < '0' || argv[1][0] > '2') {
      std::cerr << "First is out of range\n";
      return 1;
    }
  } catch (const std::invalid_argument& e) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Cannot open input file\n";
    return 1;
  }
  input >> rows >> cols;
  if (!(input)) {
    std::cerr << "Can't read the file\n";
    return 1;
  }
  int* mtx = nullptr;
  if (std::stoi(argv[1]) == 1) {
    int statMatrix[10000];
    if (rows * cols > 10000) {
      std::cerr << "Matrix too big for static allocation\n";
      return 1;
    }
    mtx = statMatrix;
    mtx = zub::readMatrix(input, rows, cols, mtx, dynamic);
  } else if (std::stoi(argv[1]) == 2) {
    mtx = reinterpret_cast<int*>(std::malloc(rows * cols * sizeof(int)));
    if (!mtx) {
      std::cerr << "Memory allocation failed\n";
      return 1;
    }
    dynamic = true;
    mtx = zub::readMatrix(input, rows, cols, mtx, dynamic);
  }

  if (!mtx) {
    return 2;
  }
  mtx = zub::convertToSquare(mtx, rows, cols, dynamic);

  std::ofstream output(argv[3]);
  output << zub::solveTask9(mtx, rows, cols) << "\n";
  output << zub::solveTask14(mtx, rows, cols) << "\n";
  if (dynamic) {
    free(mtx);
  }
}

int zubarev::getMaxInt()
{
  using namespace std;
  using int_limit = numeric_limits<int>;
  return int_limit::max();
}

int zubarev::getMinInt()
{
  using namespace std;
  using int_limit = numeric_limits<int>;
  return int_limit::min();
}

std::ostream&zubarev::outputMatrix(std::ostream& out, const int* matrix, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      out << matrix[i * cols + j] << " ";
    }
    out << "\n";
  }
  return out;
}

int* zubarev::convertToSquare(int* matrix, size_t& rows, size_t& cols, bool dynamic)
{
  if (rows == cols) {
    return matrix;
  }

  size_t sizeOfMatrix = std::min(rows, cols);
  int* square = reinterpret_cast< int* >(malloc(sizeOfMatrix * sizeOfMatrix * sizeof(int)));
  if (!square) {
    std::cerr << "Memory allocation failed for square matrix\n";
    free(square);
    return matrix;
  }

  for (size_t i = 0; i < sizeOfMatrix; ++i) {
    for (size_t j = 0; j < sizeOfMatrix; ++j) {
      square[i * sizeOfMatrix + j] = matrix[i * cols + j];
    }
  }
  if (dynamic) {
    free(matrix);
  }

  rows = cols = sizeOfMatrix;
  return square;
}

int* zubarev::readMatrix(std::istream& in, size_t& rows, size_t& cols, int* matrix, bool dynamic)
{
  for (size_t i = 0; i < rows * cols; ++i) {
    in >> matrix[i];
    if (!in) {
      std::cerr << "Can't read the file\n";
      if (dynamic) {
        free(matrix);
      }
      return nullptr;
    }
  }
  return matrix;
}

int zubarev::solveTask9(const int* matrix, size_t rows, size_t cols)
{
  size_t count = 0;
  bool equalFlag = false;

  for (size_t j = 0; j < cols; ++j) {
    for (size_t i = 0; i < rows - 1; ++i) {
      if (matrix[cols * i + j] == matrix[cols * (i + 1) + j]) {
        equalFlag = true;
        break;
      }
    }
    if (!equalFlag) {
      count++;
    } else {
      equalFlag = false;
    }
  }

  return count;
}

int zubarev::solveTask14(const int* matrix, size_t rows, size_t cols)
{
  int maxSum = getMinInt();
  int tempSum = 0;
  for (size_t s = 1; s <= (cols / 2); ++s) {
    for (size_t i = 0; i < rows - s; i++) {
      tempSum += matrix[i * cols + (i + s)];
    }
    if (tempSum > maxSum) {
      maxSum = tempSum;
    }
    tempSum = 0;
  }

  for (size_t s = 1; s <= (cols / 2); ++s) {
    for (size_t i = s; i < rows; i++) {
      tempSum += matrix[i * cols + (i - s)];
    }
    if (tempSum > maxSum) {
      maxSum = tempSum;
    }
    tempSum = 0;
  }

  return maxSum;
}
