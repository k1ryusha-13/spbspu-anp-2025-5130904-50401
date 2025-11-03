// my variant
// memory: malloc/free
// tasks: 9, 14

#include <iostream>
#include <fstream> //for ofstream/ifstream
#include <memory>  //for malloc/free
#include <cmath>   //for std::ceil()
using s_t = size_t;

int max_int()
{
  using namespace std;
  using int_limit = numeric_limits<int>;
  return int_limit::max();
}
int min_int()
{
  using namespace std;
  using int_limit = numeric_limits<int>;
  return int_limit::min();
}

std::ostream& outputMatrix(std::ostream& out, int* matrix, s_t rows, s_t cols)
{
  for (s_t i = 0; i < rows; ++i) {
    for (s_t j = 0; j < cols; ++j) {
      out << matrix[i * cols + j] << " ";
    }
    out << "\n";
  }
  return out;
}
int* convertToSquare(int* matrix, s_t& rows, s_t& cols)
{

  if (rows == cols) {
    return matrix;
  }

  s_t sizeOfMatrix = std::min(rows, cols);
  int* square = reinterpret_cast<int*>(malloc(sizeOfMatrix * sizeOfMatrix * sizeof(int)));
  if (!square) {
    std::cerr << "Memory allocation failed for square matrix\n";
    free(square);
    return matrix;
  }

  for (s_t i = 0; i < sizeOfMatrix; ++i) {
    for (s_t j = 0; j < sizeOfMatrix; ++j) {
      square[i * sizeOfMatrix + j] = matrix[i * cols + j];
    }
  }

  free(matrix);
  rows = cols = sizeOfMatrix;
  return square;
}
int* readMatrix(std::istream& in, s_t& rows, s_t& cols)
{
  in >> rows >> cols;
  if (!in) {
    std::cerr << "Can't read the file\n";
    return nullptr;
  }

  int* matrix = reinterpret_cast<int*>(malloc(rows * cols * sizeof(int)));
  if (!matrix) {
    std::cerr << "Memory allocation failed\n";
    return nullptr;
  }

  for (s_t i = 0; i < rows * cols; ++i) {
    in >> matrix[i];
    if (!in) {
      std::cerr << "Can't read the file\n";
      free(matrix);
      return nullptr;
    }
  }
  return matrix;
}
int task9(int* matrix, s_t rows, s_t cols)
{
  s_t count = 0;
  bool equalFlag = false;
  for (s_t j = 0; j < cols; ++j) {
    for (s_t i = 0; i < rows - 1; ++i) {
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
int task14(int* matrix, s_t rows, s_t cols)
{
  int num = 0;
  int maxSum = min_int();
  int tempSum = 0;
  // over main diagonal
  for (s_t s = 1; s <= (cols / 2.0); ++s) { // because i want floating point division
    for (s_t i = 0; i < rows - s; i++) {
      tempSum += matrix[i * cols + (i + s)];
    }
    if (tempSum > maxSum) {
      maxSum = tempSum;
    }
    tempSum = 0;
  }
  // under main diagonal
  for (s_t s = 1; s <= (cols / 2.0); ++s) {
    for (s_t i = s; i < rows; i++) {
      tempSum += matrix[i * cols + (i + s)];
    }
    if (tempSum > maxSum) {
      maxSum = tempSum;
    }
    tempSum = 0;
  }
  return maxSum;
}
int main(int argc, char const** argv)
{
  s_t rows = 0, cols = 0;
  try {
    if (argc != 4 || std::stoi(argv[1]) != 2 && std::stoi(argv[1]) != 1) {
      std::cerr << "Wrong arguments" << "\n";
      return 1;
    }
  } catch (const std::invalid_argument& e) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }

  // input matrix
  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Cannot open input file\n";
    return 1;
  }

  // initialize matrix
  int* mtx = readMatrix(input, rows, cols);

  input.close();
  if (!mtx) {

    return 2;
  }
  mtx = convertToSquare(mtx, rows, cols);

  // output matrix
  std::ofstream output(argv[3]);
  output << task9(mtx, rows, cols) << "\n";
  output << task14(mtx, rows, cols) << "\n";
  free(mtx);
}
