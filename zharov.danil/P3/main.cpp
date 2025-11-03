#include <iostream>
#include <fstream>

namespace zharov 
{
  bool isArgNum(const char * arg);
  int createMatrix(std::istream & input, int * mtx, size_t rows, size_t cols);
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
    std::cerr << "Bad read (rows and cols)";
    return 2;
  }
  if (argv[1][0] == '1') {
    int arr[10000] = {};
    int code = zharov::createMatrix(input, arr, rows, cols);
    if (code == 1) {
      std::cerr << "Not enough numbers";
      return 2;
    }
    if (code == 2) {
      std::cerr << "Bad read (wrong value)";
      return 2;
    }
    std::cout << "Read is ok";
  } 
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

int zharov::createMatrix(std::istream & input, int * mtx, size_t rows, size_t cols)
{
  size_t count = 0;
  while (input >> mtx[count]) {
    ++count;
  }
  if (input.eof()) {
    if (count < (rows * cols)) {
      return 1;
    }
  } else if (input.fail()) {
    return 2;
  }
  return 0;
}
