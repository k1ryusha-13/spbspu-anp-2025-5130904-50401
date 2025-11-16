#include <iostream>
#include <fstream>
#include <memory>

namespace kuznetsov {
  const size_t MAX_SIZE = 10'000;
  bool isNumber(const char* str);

  int getCntColNsm(const int* mtx, size_t rows, size_t cols);
  int getCntLocMax(const int* mtx, size_t rows, size_t cols);

  int initMatr(std::istream& input, int* mtx, size_t rows, size_t cols);

  int outputRes(char* output, int res1, int res2);
}

int main(int argc, char** argv)
{
  namespace kuz = kuznetsov;
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  } else if (!kuz::isNumber(argv[1])) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  } else if ((argv[1][0] != '1' && argv[1][0] != '2') || argv[1][1] != '\0') {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  size_t rows = 0, cols = 0;
  std::ifstream input(argv[2]);

  if (!input.is_open()) {
    std::cerr << "Can't open file\n";
    return 2;
  }

  input >> rows >> cols;
  if (!input) {
    std::cerr << "Bad reading\n";
    return 2;
  }

  if (argv[1][0] == '1') {
    int mtx[kuz::MAX_SIZE] {};

    int status = kuz::initMatr(input, mtx, rows, cols);
    if (status == -1) {
      std::cerr << "Not enough elements for matrix\n";
      return 1;
    } else if (status == -2) {
      std::cerr << "Bad reading file\n";
      return 2;
    }

    int res1 = kuz::getCntColNsm(mtx, rows, cols);
    int res2 = kuz::getCntLocMax(mtx, rows, cols);

    int statusWrite = kuz::outputRes(argv[3], res1, res2);
    if (statusWrite == 2) {
      std::cerr << "Can't open output file\n";
    }
    return 0;
  }

  int* mtrx = reinterpret_cast< int* >(malloc(sizeof(int)*rows*cols));
  if (mtrx == nullptr) {
    std::cerr << "Bad alloc\n";
    return 3;
  }

  int status = kuz::initMatr(input, mtrx, rows, cols);

  if (status == -1) {
    std::cerr << "Not enough elements for matrix\n";
    free(mtrx);
    return 1;
  } else if (status == -2) {
    std::cerr << "Bad reading file\n";
    free(mtrx);
    return 2;
  }

  int res1 = kuz::getCntColNsm(mtrx, rows, cols);
  int res2 = kuz::getCntLocMax(mtrx, rows, cols);


  int statusWrite = kuz::outputRes(argv[3], res1, res2);

  if (statusWrite == 2) {
    std::cerr << "Can't open output file\n";
  }
  free(mtrx);
  return 0;
}

int kuznetsov::getCntColNsm(const int* mtx, size_t rows, size_t cols)
{
  if (rows == 0 || cols == 0) {
    return 0;
  }

  int res = 0;
  for (size_t j = 0; j < cols; ++j) {
    bool repeats = false;
    for (size_t i = 0; i < rows-1; ++i) {
      if (mtx[i * cols + j] == mtx[(i + 1) * cols + j]) {
        repeats = true;
        break;
      }
    }
    res += !repeats;
  }
  return res;
}

int kuznetsov::getCntLocMax(const int* mtx, size_t rows, size_t cols)
{
  if (rows == 0 || cols == 0) {
    return 0;
  }
  int res = 0;
  for (size_t j = 1; j < cols-1; ++j) {
    for (size_t i = 1; i < rows-1; ++i) {
      int center = mtx[i * cols + j];
      bool isLocMax = true;

      for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
          if (!(di == 0 && dj == 0)) {
            isLocMax = isLocMax && (center > mtx[(i+di) * cols + j+dj]);
          }
        }
      }

      res += isLocMax;
    }
  }
  return res;
}

int kuznetsov::initMatr(std::istream& input, int* mtx, size_t rows, size_t cols)
{
  size_t c = 0;
  while (input >> mtx[c]) {
    ++c;
  }

  if (input.eof()) {
    if (c < rows * cols) {
      return -1;
    }
  } else if (input.fail()) {
    return -2;
  }

  return 0;
}

bool kuznetsov::isNumber(const char* str)
{
  bool isNum = true;
  size_t i = 0;

  do {
    if (str[i] < '0' || str[i] > '9') {
      isNum = false;
    }
    ++i;
  } while (str[i] != '\0');

  return isNum;
}

int kuznetsov::outputRes(char* output, int res1, int res2)
{
  std::ofstream out(output);

  if (!out.is_open()) {
    return 2;
  }
  out << res1 << '\n';
  out << res2 << '\n';
  return 0;
}
