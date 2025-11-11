#include <iostream>
#include <fstream>
#include <memory>

namespace goltsov
{
  long long * create(size_t rows, size_t cols);
  void destroy(long long * mtx);
  void get_mtx(long long * mtx, size_t rows, size_t cols, std::istream & input);
  bool LWRTRIMTX(const long long * mtx, size_t n, size_t shift, size_t cols, size_t flag1, size_t flag2);
  size_t CNTLOCMAX(const long long * mtx, size_t rows, size_t cols);
}

int main(int argc, char ** argv)
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  int num = 0;
  for (size_t i = 0; argv[1][i] != '\0'; ++i)
  {
    if (argv[1][i] >= '0' && argv[1][i] <= '9')
    {
      num = num * 10 + (argv[1][i] - '0');
    }
    else
    {
      std::cerr << "First parameter is not a number\n";
      return 1;
    }
  }
  if (num != 1 && num != 2)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  size_t rows = 0;
  size_t cols = 0;
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
      dyn_mtx = goltsov::create(rows, cols);
    }
    catch (const std::bad_alloc & e)
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

  bool answear_1 = goltsov::LWRTRIMTX(
    num == 1 ? auto_mtx : dyn_mtx,
    rows < cols ? rows : cols,
    rows < cols ? (cols - rows) : (cols - rows),
    rows < cols ? rows : cols,
    rows < cols ? 0 : 1,
    rows < cols ? 1 : 0
  );

  size_t answear_2 = goltsov::CNTLOCMAX(
    num == 1 ? auto_mtx : dyn_mtx,
    rows,
    cols
  );

  std::ofstream output(argv[3]);
  output << "Expects output (return code 0): " << answear_1 << '\n';
  output << "Expects output (return code 0): " << answear_2 << '\n';

  if (num == 2)
  {
    goltsov::destroy(dyn_mtx);
  }

  return 0;
}

bool goltsov::LWRTRIMTX(const long long * mtx, size_t n, size_t shift, size_t cols, size_t flag1, size_t flag2)
{
  for (size_t sh = 0; sh <= shift; sh++)
  {
    size_t bad_rez = 0;
    size_t total = 0;
    for (size_t i = 0; i < n - 1; ++i)
    {
      for (size_t j = i + 1; j < n; ++j)
      {
        ++total;
        if (!mtx[(i + sh * flag1) * cols + j + sh * flag2])
        {
          ++bad_rez;
        }
      }
    }
    if (bad_rez == total)
    {
      return true;
    }
  }
  return false;
}

size_t goltsov::CNTLOCMAX(const long long * mtx, size_t rows, size_t cols)
{
  size_t answear = 0;
  if (rows <= 2 || cols <= 2)
  {
    return 0;
  }
  for (size_t i = 1; i < rows - 1; ++i)
  {
    for (size_t j = 1; j < cols - 1; ++j)
    {
      if (mtx[i * cols + j] > mtx[(i - 1) * cols + j] && mtx[i * cols + j] > mtx[(i + 1) * cols + j])
      {
        if (mtx[i * cols + j] > mtx[i * cols + j - 1] && mtx[i * cols + j] > mtx[i * cols + j + 1])
        {
          ++answear;
        }
      }
    }
  }
  return answear;
}

long long * goltsov::create(size_t rows, size_t cols)
{
  long long * mtx = reinterpret_cast<long long *>(malloc(sizeof(long long) * rows * cols));
  if (mtx == nullptr)
  {
    throw std::bad_alloc();
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
      input >> mtx[i * cols + j];
    }
  }
}