#include <iostream>
#include <fstream>

namespace hvostov {
  bool is_number(const char * str);
  void input_matrix(std::ifstream & input, int* mtx, size_t rows, size_t cols);
  size_t count_local_max(int *mtx, size_t rows, size_t cols); 
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

void hvostov::input_matrix(std::ifstream & input, int *mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows * cols; i++) {
    input >> mtx[i];
  }
}

size_t hvostov::count_local_max(int* mtx, size_t rows, size_t cols)
{
  if (rows < 3 || cols < 3) {
    return 0;
  }
  size_t counter = 0;
  for (size_t i = 1; i < rows - 1; i++) {
    for (size_t j = 1; j < cols - 1; j++) { 
      bool is_local_max = mtx[i*cols + j] > mtx[i*cols + j - 1];
      is_local_max = is_local_max && mtx[i*cols + j] > mtx[i*cols + j + 1];
      is_local_max = is_local_max && mtx[i*cols + j] > mtx[i*(cols - 1) + j];
      is_local_max = is_local_max && mtx[i*cols + j] > mtx[i*(cols + 1) + j];      
      if (is_local_max) {
        counter++;
      }
    }
  }
  return counter;
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
  if (argv[1][0] == '1') {
    int mtx[10000] = {};
    hvostov::input_matrix(input, mtx, rows, cols);
    if (!input) {
      std::cerr << "Problems with input_matrix!\n";
      return 2;
    }
    size_t counter = hvostov::count_local_max(mtx, rows, cols);
    std::cout << counter << "\n";
  }  
  return 0; 
}

