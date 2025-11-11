#include <iostream>
#include <fstream>
#include <memory>

namespace goltsov
{
  long long * create(size_t rows, size_t cols);
  void destroy(long long * mtx);
  void getMtx(long long * mtx, size_t rows, size_t cols, std::istream & input);
  bool lwrTriMtx(const long long * mtx,
    size_t n,
    size_t shift,
    size_t cols,
    size_t flag1,
    size_t flag2);
  size_t cntLocMax(const long long * mtx, size_t rows, size_t cols);
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
  if (!input)
  {
    std::cerr << "Bad input\n";
    return 2;
  }

  long long * dynMtx = nullptr;
  long long autoMtx[10000];

  if (num == 1)
  {
    goltsov::getMtx(autoMtx, rows, cols, input);
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
      dynMtx = goltsov::create(rows, cols);
    }
    catch (const std::bad_alloc & e)
    {
      std::cerr << e.what() << '\n';
      return 3;
    }

    goltsov::getMtx(dynMtx, rows, cols, input);
    if (!input)
    {
      std::cerr << "Bad input\n";
      goltsov::destroy(dynMtx);
      return 2;
    }
  }

  bool answer1 = goltsov::lwrTriMtx(
    num == 1 ? autoMtx : dynMtx,
    rows < cols ? rows : cols,
    rows < cols ? (cols - rows) : (rows - cols),
    rows < cols ? rows : cols,
    rows < cols ? 0 : 1,
    rows < cols ? 1 : 0
  );

  size_t answer2 = goltsov::cntLocMax(
    num == 1 ? autoMtx : dynMtx,
    rows,
    cols
  );

  std::ofstream output(argv[3]);
  output << "Expects output (return code 0): " << answer1 << '\n';
  output << "Expects output (return code 0): " << answer2 << '\n';

  if (num == 2)
  {
    goltsov::destroy(dynMtx);
  }

  return 0;
}

bool goltsov::lwrTriMtx(const long long * mtx,
  size_t n,
  size_t shift,
  size_t cols,
  size_t flag1,
  size_t flag2)
{
  for (size_t sh = 0; sh <= shift; ++sh)
  {
    size_t badRez = 0;
    size_t total = 0;

    for (size_t i = 0; i < n - 1; ++i)
    {
      for (size_t j = i + 1; j < n; ++j)
      {
        ++total;
        if (!mtx[(i + sh * flag1) * cols + j + sh * flag2])
        {
          ++badRez;
        }
      }
    }

    if (badRez == total)
    {
      return true;
    }
  }

  return false;
}

size_t goltsov::cntLocMax(const long long * mtx, size_t rows, size_t cols)
{
  size_t answer = 0;
  if (rows <= 2 || cols <= 2)
  {
    return 0;
  }

  for (size_t i = 1; i < rows - 1; ++i)
  {
    for (size_t j = 1; j < cols - 1; ++j)
    {
      if (mtx[i * cols + j] > mtx[(i - 1) * cols + j]
        && mtx[i * cols + j] > mtx[(i + 1) * cols + j])
      {
        if (mtx[i * cols + j] > mtx[i * cols + j - 1]
          && mtx[i * cols + j] > mtx[i * cols + j + 1])
        {
          ++answer;
        }
      }
    }
  }

  return answer;
}

long long * goltsov::create(size_t rows, size_t cols)
{
  long long * mtx =
    reinterpret_cast<long long *>(malloc(sizeof(long long) * rows * cols));
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

void goltsov::getMtx(long long * mtx, size_t rows, size_t cols, std::istream & input)
{
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      input >> mtx[i * cols + j];
    }
  }
}
