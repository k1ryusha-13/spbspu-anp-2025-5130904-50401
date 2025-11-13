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

  size_t get_first_parameter(const char *num);
  void check_argc_validity(int argc);

  std::istream &read_matrix(std::istream &input, int *arr, size_t n, size_t m);

  void LFT_BOT_CLK(int *arr, size_t n, size_t m);

  size_t min(size_t a, size_t b);
  bool LWR_TRI_MTX(const int *arr, size_t n, size_t m);

  std::ostream &print_matrix(std::ostream &output, const int *a, size_t n, size_t m);
  std::ostream &print_bool(std::ostream &output, bool val);
}

int main(int argc, char **argv)
{
  try
  {
    khasnulin::check_argc_validity(argc);

    char *num = argv[1];
    size_t mode = khasnulin::get_first_parameter(num);

    std::ifstream input(argv[2]);
    size_t n = 1, m = 1;

    int arr[10000] = {};
    int *currArr = nullptr;

    input >> n >> m;
    try
    {
      currArr = mode == 1 ? arr : new int[n * m];

      khasnulin::read_matrix(input, currArr, n, m);
      input.close();

      bool isLWR_TRI_MTX = khasnulin::LWR_TRI_MTX(currArr, n, m);
      khasnulin::LFT_BOT_CLK(currArr, n, m);

      std::ofstream output(argv[3]);

      khasnulin::print_matrix(output, currArr, n, m);
      khasnulin::print_bool(output, isLWR_TRI_MTX);

      if (mode == 2)
      {
        delete[] currArr;
      }
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

size_t khasnulin::get_first_parameter(const char *num)
{
  size_t len = 0;
  const char *ch = num;
  while (*ch)
  {
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
  }
  throw std::runtime_error(ErrMessages::FP_out_of_range);
}

void khasnulin::check_argc_validity(int argc)
{
  if (argc != 4)
  {
    const char *message = argc > 4 ? ErrMessages::manyArgs : ErrMessages::notEnoughArgs;
    throw std::runtime_error(message);
  }
}

void khasnulin::LFT_BOT_CLK(int *arr, size_t n, size_t m)
{
  if (n > 0 && m > 0)
  {
    size_t currI = (n - 1) * m;

    int directionI = -1;
    int directionJ = 0;
    int factor = 1;
    size_t spiral_circle = 0;
    size_t elem_counter = 0;
    for (size_t i = 0; i < n * m; i++)
    {
      arr[currI] -= factor;
      factor++;
      elem_counter++;
      if (directionI && elem_counter == (n - spiral_circle))
      {
        if (directionI == -1)
        {
          directionJ = 1;
        }
        else
        {
          directionJ = -1;
        }
        spiral_circle++;
        elem_counter = 0;
        directionI = 0;
      }
      else if (directionJ && elem_counter == (m - spiral_circle))
      {
        if (directionJ == -1)
        {
          directionI = -1;
        }
        else
        {
          directionI = 1;
        }
        elem_counter = 0;
        directionJ = 0;
      }
      currI += directionI * m + directionJ;
    }
  }
}

size_t khasnulin::min(size_t a, size_t b)
{
  return a < b ? a : b;
}

bool khasnulin::LWR_TRI_MTX(const int *arr, size_t n, size_t m)
{
  size_t minSide = min(n, m);
  if (minSide == 0)
  {
    return false;
  }
  for (size_t i = 0; i < minSide; i++)
  {
    for (size_t j = i + 1; j < m; j++)
    {
      if (arr[i * m + j] != 0)
      {
        return false;
      }
    }
  }

  return true;
}

using is_t = std::istream;
is_t &khasnulin::read_matrix(is_t &input, int *arr, size_t n, size_t m)
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
os_t &khasnulin::print_matrix(os_t &output, const int *a, size_t n, size_t m)
{
  output << n << " " << m << " ";
  if (n > 0 && n > 0)
  {
    for (size_t i = 0; i < n * m - 1; i++)
    {
      output << a[i] << " ";
    }
    output << a[m * n - 1];
  }
  output << "\n";
  return output;
}

os_t &khasnulin::print_bool(os_t &output, bool val)
{
  return output << (val ? "true\n" : "false\n");
}
