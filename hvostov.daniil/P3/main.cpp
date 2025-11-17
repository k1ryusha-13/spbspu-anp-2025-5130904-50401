#include <iostream>
#include <fstream>

namespace hvostov {
  bool is_number(const char * str);
  void input_matrix(std::ifstream & input, int * matrix, size_t rows, size_t cols);
  size_t count_local_max(int * matrix, size_t rows, size_t cols);
  void modify_matrix(int * matrix, size_t rows, size_t cols);
  void output_matrix(std::ofstream & output, int * matrix, size_t rows, size_t cols);
  void task_execution(std::ofstream & output, int * matrix, size_t rows, size_t cols);
}

int main(int argc, char ** argv)
{
  if (argc > 4) {
    std::cerr << "Too many arguments!\n";
    return 1;
  } else if (argc < 4) {
    std::cerr << "Not enough arguments!\n";
    return 1;
  } else if (!hvostov::is_number(argv[1])) {
    std::cerr << "First parameter is not a number!\n";
    return 1;
  } else if (argv[1][0] < '1' || argv[1][0] > '2') {
    std::cerr << "First parameter is out of range!\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
  size_t rows = 0, cols = 0;
  input >> rows >> cols;
  if (!input) {
    std::cerr << "Problems with input_matrix!\n";
    return 2;
  }
  if (rows == 0 && cols == 0) {
    output << 0 << "\n" << 0 << " " << 0 << "\n";
    return 0;
  }
  if (argv[1][0] == '1') {
    constexpr size_t MATRIX_SIZE = 10000;
    int matrix[MATRIX_SIZE] = {};
    hvostov::input_matrix(input, matrix, rows, cols);
    if (!input) {
      std::cerr << "Problems with input_matrix!\n";
      return 2;
    }
    input.close();
    hvostov::task_execution(output, matrix, rows, cols);
    return 0;
  }

  int * matrix = reinterpret_cast<int *>(malloc(sizeof(int) * rows * cols));
  if (matrix == nullptr) {
    std::cerr << "Bad alloc!\n";
    return 3;
  }
  hvostov::input_matrix(input, matrix, rows, cols);
  if (!input) {
    std::cerr << "Problems with input_matrix!\n";
    free(matrix);
    return 2;
  }
  input.close();
  hvostov::task_execution(output, matrix, rows, cols);
  free(matrix);
  return 0;
}

void hvostov::task_execution(std::ofstream & output, int * matrix, size_t rows, size_t cols)
{
  size_t counter = hvostov::count_local_max(matrix, rows, cols);
  output << counter << "\n";
  hvostov::modify_matrix(matrix, rows, cols);
  hvostov::output_matrix(output, matrix, rows, cols);
}

bool hvostov::is_number(const char * str)
{
  if (*str == '\0' || !str) {
    return false;
  }
  size_t index = 0;
  while (str[index] != '\0') {
    if (str[index] < '0' || str[index] > '9') {
      return false;
    }
    index++;
  }
  if (index > 1) {
    if (str[0] == '0') {
      return false;
    }
  }
  return true;
}

void hvostov::input_matrix(std::ifstream & input, int * matrix, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows * cols; i++) {
    input >> matrix[i];
  }
}

size_t hvostov::count_local_max(int * matrix, size_t rows, size_t cols)
{
  if (rows < 3 || cols < 3) {
    return 0;
  }
  size_t counter = 0;
  for (size_t i = 1; i < rows - 1; i++) {
    for (size_t j = 1; j < cols - 1; j++) {
      bool is_local_max = matrix[i*cols + j] > matrix[i*cols + j - 1];
      is_local_max = is_local_max && matrix[i*cols + j] > matrix[i*cols + j + 1];
      is_local_max = is_local_max && matrix[i*cols + j] > matrix[i*(cols - 1) + j];
      is_local_max = is_local_max && matrix[i*cols + j] > matrix[i*(cols + 1) + j];
      if (is_local_max) {
        counter++;
      }
    }
  }
  return counter;
}

void hvostov::output_matrix(std::ofstream & output, int * matrix, size_t rows, size_t cols)
{
  output << rows << " " << cols;
  for (size_t i = 0; i < rows * cols; i++) {
    output << " " << matrix[i];
  }
  output << "\n";
}

void hvostov::modify_matrix(int * matrix, size_t rows, size_t cols)
{
  size_t top = 0, right = cols - 1, bot = rows - 1, left = 0, decrease_by = 1;
  while (top <= bot && left <= right) {
    for (size_t i = bot; i > top; i--) {
      matrix[i*cols+left] -= decrease_by;
      decrease_by++;
    }
    for (size_t j = left; j < right; j++) {
      matrix[j+top*cols] -= decrease_by;
      decrease_by++;
    }
    for (size_t i = top; i < bot; i++) {
      matrix[i*cols + right] -= decrease_by;
      decrease_by++;
    }
    for (size_t j = right; j > left; j--) {
      matrix[bot*cols + j] -= decrease_by;
      decrease_by++;
    }
    top++;
    right--;
    bot--;
    left++;
  }
}
