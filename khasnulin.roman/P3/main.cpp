#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>

namespace khasnulin
{
  size_t get_first_parametr(const char *num);
  std::ostream &print_output(std::ostream &output, const int *a, size_t n, size_t m);

}

int main(int argc, char **argv)
{
  if (argc == 4)
  {
    try
    {
      char *num = argv[1];
      size_t mode = khasnulin::get_first_parametr(num);

      std::ifstream input(argv[2]);
      size_t n = 0, m = 0;
      input >> n >> m;
      if (mode == 1)
      {
      }
      else if (mode == 2)
      {
      }
    }
    catch (std::runtime_error &e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  else
  {
    const char *Err_message = argc > 4 ? "Too many arguments\n" : "Not enough arguments\n";
    std::cerr << Err_message;
    return 1;
  }
}

size_t khasnulin::get_first_parametr(const char *num)
{
  size_t len = 0;
  const char *ch = num;
  while (*ch)
  {
    std::cout << *ch << " ";
    if (*ch < '0' || *ch > '9')
    {
      throw std::runtime_error("First parameter is not a number");
    }
    len++;
    ch++;
  }

  if (len == 1)
  {
    if (num[0] == '1')
    {
      return 1;
    }
    else if (num[0] == '2')
    {
      return 2;
    }
    else
    {
      throw std::runtime_error("First parameter is out of range");
    }
  }
  else
  {
    throw std::runtime_error("First parameter is out of range");
  }
}

using os_t = std::ostream;
using s_t = size_t;
os_t &khasnulin::print_output(os_t &output, const int *a, s_t n, s_t m)
{
  for (s_t i = 0; i < n; i++)
  {
    for (s_t j = 0; j < m; j++)
    {
      output << a[i * m + j] << " ";
    }
    output << "\n";
  }
  return output;
}
