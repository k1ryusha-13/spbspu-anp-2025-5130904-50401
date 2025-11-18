#include <iostream>
#include <fstream>
#include <memory>

namespace goltsov
{
  long long * create(size_t rows, size_t cols);
  void getMtx(long long * mtx, size_t rows, size_t cols, std::istream & input);
  bool lwrTriMtx(const long long * mtx, size_t n, size_t shift, size_t cols, size_t flag1, size_t flag2);
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
    if (isdigit(argv[1][i]))
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

  if (num == 1)
  {
    long long autoMtx[10000];
    goltsov::getMtx(autoMtx, rows, cols, input);

    if (!input)
    {
      std::cerr << "Bad input\n";
      return 2;
    }

    bool answer1;

    if (rows < cols)
    {
      answer1 = goltsov::lwrTriMtx(autoMtx, rows, cols - rows, cols, 0, 1);
    }
    else
    {
      answer1 = goltsov::lwrTriMtx(autoMtx, cols, rows - cols, cols, 1, 0);
    }

    size_t answer2 = goltsov::cntLocMax(autoMtx, rows, cols);

    std::ofstream output(argv[3]);
    output << "Expects output (return code 0): " << answer1 << '\n';
    output << "Expects output (return code 0): " << answer2 << '\n';

    return 0;
  }
  else
  {
    long long * dynMtx = nullptr;

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
      free(dynMtx);
      return 2;
    }

    bool answer1;

    if (rows < cols)
    {
      answer1 = goltsov::lwrTriMtx(dynMtx, rows, cols - rows, cols, 0, 1);
    }
    else
    {
      answer1 = goltsov::lwrTriMtx(dynMtx, cols, rows - cols, cols, 1, 0);
    }

    size_t answer2 = goltsov::cntLocMax(dynMtx, rows, cols);

    std::ofstream output(argv[3]);
    output << "Expects output (return code 0): " << answer1 << '\n';
    output << "Expects output (return code 0): " << answer2 << '\n';

    free(dynMtx);

    return 0;
  }
}

bool goltsov::lwrTriMtx(const long long * mtx,
  size_t n,
  size_t shift,
  size_t cols,
  size_t flag1,
  size_t flag2)
{
  if (n == 0)
  {
    return true;
  }

  for (size_t sh = 0; sh <= shift; ++sh)
  {
    bool flag = false;

    for (size_t i = 0; i < n - 1; ++i)
    {
      for (size_t j = i + 1; j < n; ++j)
      {
        if (mtx[(i + sh * flag1) * cols + j + sh * flag2])
        {
          flag = true;
          break;
        }
      }

      if (flag)
      {
        break;
      }
    }

    if (!flag)
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
  long long * mtx = reinterpret_cast<long long *>(malloc(sizeof(long long) * rows * cols));
  if (mtx == nullptr)
  {
    throw std::bad_alloc();
  }

  return mtx;
}

void goltsov::getMtx(long long * mtx, size_t rows, size_t cols, std::istream & input)
{
  if (rows == 0 || cols == 0)
  {
    return;
  }

  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      input >> mtx[i * cols + j];
      if (!input)
      {
        return;
      }
    }
  }
}
