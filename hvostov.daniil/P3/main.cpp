#include <iostream>
#include <fstream>

namespace hvostov {
  bool is_number(const char * str);
  void input_matrix(std::ifstream & input, int* mtx, size_t rows, size_t cols);
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
  }
  
  return 0; 
}

