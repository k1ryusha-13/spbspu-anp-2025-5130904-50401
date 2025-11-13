#include <iostream>
#include <fstream>

namespace kudaev
{
  bool inputmtx(std::ifstream&, int*, size_t, size_t);
  void lft_bot_clk(int* a, size_t m, size_t n);
  void bld_smt_mtr(int* a, size_t m, size_t n);
  void outputmtx(std::ostream& out, int* a, size_t m, size_t n);
}

int main(int argc, char** argv)
{
  try
  {
    if (argc < 4)
      throw std::exception("Not enough arguments");
    if (argc > 4)
      throw std::exception("Too many arguments");
    bool all_digits = true;
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
      if (!std::isdigit(argv[1][i]))
      {
        all_digits = false;
        break;
      }
    }
    if (!all_digits || argv[1][0] == '\0')
      throw std::exception("First parameter is not a number");
  }
  catch (std::exception ex)
  {
    std::cerr << ex.what() << '\n';
    return 1;
  }
  int choice = std::atoi(argv[1]);
  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
  int* target = nullptr;
  int a[10000] = {};
  size_t m, n;
  if (!(input >> m >> n))
  {
    std::cerr << "Error reading a file" << '\n';
    return 2;
  }
  if (m == 0 || n == 0)
  {
    output << m << n;
    return 0;
  }
  switch (choice)
  {
    case 1:
    {
      target = a;
      break;
    }
    case 2:
    {
      try 
      {
        target = new int[m * n];
      }
      catch (const std::bad_alloc& ex)
      {
        std::cerr << ex.what() << '\n';
        return 2;
      }
      break;
    }
    default:
    {
      std::cerr << "First parameter is out of range" << '\n';
      return 1;
    }
  }
  if (!kudaev::inputmtx(input, target, m, n))
  {
    std::cerr << "Error reading a file" << '\n';
    return 2;
  }
  input.close();
  kudaev::lft_bot_clk(target, m, n);
  kudaev::outputmtx(output, target, m, n);
}

bool kudaev::inputmtx(std::ifstream& input, int* a, size_t m, size_t n)
{
  for (size_t i = 0; i < m * n; ++i)
  {
    if (!(input >> a[i]))
    {
      input.close();
      return false;
    }
  }
  return true;
}

void kudaev::lft_bot_clk(int* a, size_t m, size_t n)
{
  size_t pos = (m - 1) * n;
  size_t rows = m, cols = n;
  int k = 1;
  while (rows > 0 && cols > 0)
  {
    for (size_t i = 0; i < rows; i++)
    {
      a[pos] -= k++;
      if (i < rows - 1) pos -= n;
    }
    if (--cols == 0) break;
    pos++;
    for (size_t i = 0; i < cols; i++)
    {
      a[pos] -= k++;
      if (i < cols - 1) pos++;
    }
    if (--rows == 0) break;
    pos += n;
    for (size_t i = 0; i < rows; i++)
    {
      a[pos] -= k++;
      if (i < rows - 1) pos += n;
    }
    if (--cols == 0) break;
    pos--;
    for (size_t i = 0; i < cols; i++)
    {
      a[pos] -= k++;
      if (i < cols - 1) pos--;
    }
    if (--rows == 0) break;
    pos -= n;
  }
}

void kudaev::outputmtx(std::ostream& out, int* a, size_t m, size_t n)
{
  out << m << ' ' << n << ' ';
  for (size_t i = 0; i < m * n; ++i)
  {
    out << a[i] << ' ';
  }
  out << '\n';
}

void kudaev::bld_smt_mtr(int* a, size_t m, size_t n)
{
  for (size_t i = 2; i < m * n; ++i)
  {

  }
}