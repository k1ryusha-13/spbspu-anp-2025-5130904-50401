#include <iostream>
#include <fstream>
#include <memory>

namespace goltsov
{
  long long * create(size_t rows, size_t cols);
  void destroy(long long * mtx, size_t created);
  void get_mtx(long long * mtx, size_t rows, size_t cols, std::istream & input);
}

int main(int argc, char ** argv)
{
  //Получение параметров из командной строки
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4)
  {
    std::cerr << "Too many argiments\n";
  }

  int num = 0;
  for (int i = 0; argv[1][i] != '\0'; ++i)
  {
    if (argv[1][i] >= '0' && argv[1][i] <= '9')
    {
      num = num*10 + (argv[1][i] - '0');
    }
    else
    {
      std::cerr << "First parametr is not a number\n";
      return 1;
    }
  }
  if (num != 1 && num != 2)
  {
    std::cerr << "First parametr is out of range\n";
    return 1;
  }
  //

  char * outp = argv[3];

  //Получение матрицы
  std::ifstream input(argv[2]);
  size_t rows = 0, cols = 0;
  input >> rows >> cols;
  long long * dyn_mtx = nullptr;
  long long auto_mtx[10000];
  if (num == 1)
  {
    goltsov::get_mtx(auto_mtx, rows, cols, input);
    if (!input)
    {
      std::cerr << "Bad input\n";
      return 2;
    }
  }
  else
  {
    try
    {
      dyn_mtx = goltsov::create(rows,cols);
    }
    catch(const std::bad_alloc &e)
    {
      std::cerr << "Bad alloc" << e.what() << '\n';
      return 3;
    }   
    goltsov::get_mtx(dyn_mtx, rows, cols, input);
    if (!input)
    {
      std::cerr << "Bad input\n";
      goltsov::destroy(dyn_mtx);
      return 2;
    }
  }
  //
}

long long * goltsov::create(size_t rows, size_t cols)
{
  long long * mtx = reinterpret_cast< long long * >(malloc(sizeof(long long *) * rows * cols));
  if (mtx == nullptr)
  {
    throw 
      std::bad_alloc();
  }
  return mtx;
}

void goltsov::destroy(long long * mtx)
{
  free(mtx);
}

void goltsov::get_mtx(long long * mtx, size_t rows, size_t cols, std::istream & input)
{
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      input >> mtx[i*cols + j];
    }
  }
}

