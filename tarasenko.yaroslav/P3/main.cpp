#include <iostream>
#include <fstream>

namespace tarasenko
{
  size_t input_static(std::istream & in, int * arr, size_t n, size_t m)
  {
    for (size_t i = 0; i < n * m; ++i)
    {
      in >> arr[i];
    }
    return n * m;
  }

  std::ostream & output(std::ostream & out, const int * a, size_t n, size_t m)
  {
    for (size_t i = 0; i < n * m; ++i)
    {
      out << a[i] << ' ';
    }
    out << '\n';
    return out;
  }

  void input_processing(int argc, char ** argv)
  {
    if (argc < 4)
    {
      throw std::invalid_argument("Not enough arguments");
    }
    if (argc > 4)
    {
      throw std::invalid_argument("Too many arguments");
    }
    const char * first_arg = argv[1];
    size_t i = 0;
    while (first_arg[i] != '\0')
    {
      if (first_arg[i] > '9' || first_arg[i] < '0')
      {
        throw std::invalid_argument("First parameter is not a number");
      }
      i += 1;
    }
    if (first_arg[0] != '1' && first_arg[0] != '2')
    {
      throw std::invalid_argument("First parameter is out of range");
    }
    if (first_arg[1] != '\0')
    {
      throw std::invalid_argument("First parameter is out of range");
    }
  }

}

int main(int argc, char ** argv)
{
  try
  {
    tarasenko::input_processing(argc, argv);
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
  size_t rows = 0, cols = 0;
  input >> rows >> cols;
  int arr[10000] = {};
  tarasenko::input_static(input, arr, rows, cols);
  tarasenko::output(output, arr, rows, cols);

}
