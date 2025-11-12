#include <cstddef>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <stdexcept>

namespace khasnulin
{
  namespace ErrMessages
  {
    const char *manyArgs = "Too many arguments\n";
    const char *notEnoughArgs = "Not enough arguments\n";
    const char *FP_out_of_range = "First parameter is out of range\n";
    const char *FP_not_a_number = "First parameter is not a number\n";
    const char *input_file_not_valid = "Error while reading input file data, can't read as matrix\n";
    const char *memory_bad_alloc = "Error memory allocation\n";
    const char *unknown = "Error during task execution, something went wrong\n";
  };

  size_t get_first_parametr(const char *num);
  void check_argc_validity(int argc);

  std::istream &read_matrix(std::istream &input, int *arr, size_t n, size_t m);

  std::ostream &print_output(std::ostream &output, const int *a, size_t n, size_t m);
}

int main(int argc, char **argv)
{
  try
  {
    khasnulin::check_argc_validity(argc);

    char *num = argv[1];
    size_t mode = khasnulin::get_first_parametr(num);

    std::ifstream input(argv[2]);
    size_t n = 0, m = 0;

    int arr[10000] = {};
    int *currArr = nullptr;

    input >> n >> m;
    try
    {
      currArr = mode == 1 ? arr : new int[n * m];
      khasnulin::read_matrix(input, currArr, n, m);

      std::ofstream output(argv[3]);
      khasnulin::print_output(output, currArr, n, m);
    }
    catch (std::runtime_error &e)
    {
      std::cerr << e.what() << "\n";
      if (mode == 2)
      {
        delete[] currArr;
      }
      return 2;
    }
    catch (std::bad_alloc &e)
    {
      std::cerr << khasnulin::ErrMessages::memory_bad_alloc;
      return 2;
    }
    catch (...)
    {
      std::cerr << khasnulin::ErrMessages::unknown;
      if (mode == 2)
      {
        delete[] currArr;
      }
      return 2;
    }
  }
  catch (std::runtime_error &e)
  {
    std::cerr << e.what() << "\n";
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
      throw std::runtime_error(ErrMessages::FP_not_a_number);
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
      throw std::runtime_error(ErrMessages::FP_out_of_range);
    }
  }
  else
  {
    throw std::runtime_error(ErrMessages::FP_out_of_range);
  }
}

void khasnulin::check_argc_validity(int argc)
{
  if (argc != 4)
  {
    const char *message = argc > 4 ? ErrMessages::manyArgs : ErrMessages::notEnoughArgs;
    throw std::runtime_error(message);
  }
}

std::istream &khasnulin::read_matrix(std::istream &input, int *arr, size_t n, size_t m)
{
  size_t i = 0;
  while (input >> arr[i] && i < n * m)
  {
    i++;
  }
  if ((!input.eof() && input.fail()) || i != n * m)
  {
    throw std::runtime_error(ErrMessages::input_file_not_valid);
  }
  return input;
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
