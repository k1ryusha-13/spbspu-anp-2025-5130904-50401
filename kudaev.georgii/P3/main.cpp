#include <cmath>
#include <iostream>
#include <fstream>
#include <limits>

namespace kudaev
{
  void inputmtx(std::ifstream &, int *, size_t, size_t);
  void lft_bot_clk(int *, size_t, size_t);
  void bld_smt_mtr(std::ostream &, int *, size_t, size_t);
  void outputmtx(std::ostream &, int *, size_t, size_t);
}

int main(int argc, char **argv)
{
  try
  {
    if (argc < 4)
      throw std::invalid_argument("Not enough arguments");
    if (argc > 4)
      throw std::out_of_range("Too many arguments");
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
      throw std::invalid_argument("First parameter is not a number");
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what() << '\n';
    return 1;
  }
  int choice = std::atoi(argv[1]);
  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
  if (!input.is_open())
  {
    std::cerr << "Cannot open input file\n";
    return 2;
  }
  if (!output.is_open())
  {
    std::cerr << "Cannot open output file\n";
    return 2;
  }
  int *target = nullptr;
  int a[10000] = {};
  size_t m, n;
  if (!(input >> m >> n))
  {
    std::cerr << "Error reading a file" << '\n';
    return 2;
  }
  if (m == 0 || n == 0)
    output << m << ' ' << n << '\n';
  else
  {
    switch (choice)
    {
    case 1:
    {
      if (m * n <= 10000)
        target = a;
      else
      {
        std::cerr << "Too many elements for static array" << '\n';
        return 2;
      }
      break;
    }
    case 2:
    {
      try
      {
        target = new int[m * n];
      }
      catch (const std::exception& ex)
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
  }
  try
  {
    kudaev::inputmtx(input, target, m, n);
    kudaev::lft_bot_clk(target, m, n);
    kudaev::outputmtx(output, target, m, n);
    kudaev::bld_smt_mtr(output, target, m, n);
  }
  catch (const std::exception& ex)
  {
    if (choice == 2) delete[] target;
    std::cerr << ex.what() << '\n';
    return 2;
  }
  if (choice == 2 && target != nullptr)
  {
    delete[] target;
  }
}

void kudaev::inputmtx(std::ifstream &input, int *a, size_t m, size_t n)
{
  for (size_t i = 0; i < m * n; ++i)
  {
    if (!(input >> a[i]))
      throw std::invalid_argument("Incorrect input");
  }
}

void kudaev::lft_bot_clk(int *a, size_t m, size_t n)
{
  size_t pos = (m - 1) * n;
  size_t rows = m, cols = n;
  int k = 1;
  while (rows > 0 && cols > 0)
  {
    for (size_t i = 0; i < rows; i++)
    {
      a[pos] -= k++;
      if (i < rows - 1)
        pos -= n;
    }
    if (--cols == 0)
      break;
    pos++;
    for (size_t i = 0; i < cols; i++)
    {
      a[pos] -= k++;
      if (i < cols - 1)
        pos++;
    }
    if (--rows == 0)
      break;
    pos += n;
    for (size_t i = 0; i < rows; i++)
    {
      a[pos] -= k++;
      if (i < rows - 1)
        pos += n;
    }
    if (--cols == 0)
      break;
    pos--;
    for (size_t i = 0; i < cols; i++)
    {
      a[pos] -= k++;
      if (i < cols - 1)
        pos--;
    }
    if (--rows == 0)
      break;
    pos -= n;
  }
}

void kudaev::outputmtx(std::ostream &out, int *a, size_t m, size_t n)
{
  out << m << ' ' << n << ' ';
  for (size_t i = 0; i < m * n; ++i)
  {
    out << a[i] << ' ';
  }
  out << '\n';
}

void kudaev::bld_smt_mtr(std::ostream &out, int *a, size_t m, size_t n)
{
  int *tmp = nullptr;
  float *res_mas = nullptr;
  try
  {
    tmp = new int[m * n];
    try
    {
      res_mas = new float[m * n];
    }
    catch (...)
    {
      delete[] tmp;
      throw;
    }
  }
  catch (const std::exception& ex)
  {
    delete[] tmp;
    throw;
  }
  for (size_t i = 0; i < m * n; ++i)
    tmp[i] = a[i];
  for (size_t i = 0; i < m * n; ++i)
  {
    int sum = 0;
    int k = 0;
    int higherrow = i - n;
    size_t lowerrow = i + n;
    if (higherrow >= 0)
    {
      sum += tmp[higherrow];
      k++;
      if (higherrow % n != 0)
      {
        sum += tmp[higherrow - 1];
        k++;
      }
      if ((higherrow + 1) % n != 0)
      {
        sum += tmp[higherrow + 1];
        k++;
      }
    }
    if (lowerrow < m * n)
    {
      sum += tmp[lowerrow];
      k++;
      if (lowerrow % n != 0)
      {
        sum += tmp[lowerrow - 1];
        k++;
      }
      if ((lowerrow + 1) % n != 0)
      {
        sum += tmp[lowerrow + 1];
        k++;
      }
    }
    if (i % n != 0)
    {
      sum += tmp[i - 1];
      k++;
    }
    if ((i + 1) % n != 0)
    {
      sum += tmp[i + 1];
      k++;
    }
    float res = static_cast<float>(sum) / k;
    res_mas[i] = res;
  }
  delete[] tmp;
  out << m << ' ' << n << ' ';
  for (size_t i = 0; i < m * n; ++i)
  {
    out << floor(10 * res_mas[i] + 0.5f) / 10 << ' ';
  }
  delete[] res_mas;
}
