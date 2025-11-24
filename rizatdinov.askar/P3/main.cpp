#include <iostream>
#include <fstream>
#include <memory>

namespace rizatdinov
{
  int * creat(size_t len, int number);
  bool initial(int * array, size_t len, std::ifstream & file);
  bool isLocalMax(const int * array, size_t cols, size_t position);
  unsigned long countLocalMax(const int * array, size_t rows, size_t cols);
  bool isLowerTriangular(const int * array, size_t rows, size_t cols);
}

int main(int argc, char ** argv)
{
  if (argc < 4 || argc > 4) {
    std::cerr << "fatal: invalid parameters\n";
    return 1;
  }

  int number = static_cast< int >(argv[1][0]) - 48;
  if (number < 1 || number > 2 || argv[1][1] != '\0') {
    std::cerr << "fatal: invalid parameters\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "fatal: file not found\n";
    return 2;
  }

  size_t rows = 0, cols = 0;
  input >> rows >> cols;
  if (!input) {
    std::cerr << "fatal: failed to read data from the file\n";
    return 2;
  }

  int * array = nullptr;
  int array_static[10000] = {};
  try {
    array = rizatdinov::creat(rows * cols, number);
    if (array == nullptr) {
      array = array_static;
    }

    if (rizatdinov::initial(array, rows * cols, input)) {
      throw std::invalid_argument("invalid argument");
    }
  } catch(...) {
    if (number ==2) {
      free(array);
    }
    std::cerr << "fatal: failed to read data from the file\n";
    return 2;
  }

  input.close();

  std::ofstream output(argv[3]);

  size_t count_local_max = rizatdinov::countLocalMax(array, rows, cols);
  bool is_lower_triangular = rizatdinov::isLowerTriangular(array, rows, cols);

  output << "Expects output (return code 0): " << count_local_max << '\n';
  output << "Expects output (return code 0): " << is_lower_triangular << '\n';

  if (number == 2) {
    free(array);
  }

  return 0;
}

int * rizatdinov::creat(size_t len, int number)
{
  int * array = nullptr;
  if (number == 2) {
    array = reinterpret_cast< int * >(malloc(sizeof(int) * len));
    if (array == nullptr) {
      throw std::bad_alloc();
    }
  }
  return array;
}

bool rizatdinov::initial(int * array, size_t len, std::ifstream & file)
{
  for (size_t i = 0; i < len; ++i) {
    file >> array[i];
    if (!file) {
      return 1;
    }
  }
  return 0;
}

bool rizatdinov::isLocalMax(const int * array, size_t cols, size_t position)
{
  if (array[position] < array[position + 1]) {
    return false;
  } else if (array[position] < array[position - 1]) {
    return false;
  } else if (array[position] < array[position + cols]) {
    return false;
  } else if (array[position] < array[position - cols]) {
    return false;
  }

  return true;
}

unsigned long rizatdinov::countLocalMax(const int * array, size_t rows, size_t cols)
{
  size_t count = 0;
  for (size_t i = 1; i + 1 < rows; ++i) {
    for (size_t j = 1; j + 1 < cols; ++j) {
      size_t position = i * cols + j;
      count += rizatdinov::isLocalMax(array, cols, position);
    }
  }
  return count;
}

bool rizatdinov::isLowerTriangular(const int * array, size_t rows, size_t cols)
{
  bool result = false;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = i + 1; j < cols; ++j) {
      if (array[i * cols + j] != 0) {
        return false;
      }
    }
    result = true;
  }
  return result;
}
