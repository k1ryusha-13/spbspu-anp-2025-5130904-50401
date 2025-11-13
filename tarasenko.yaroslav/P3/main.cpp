#include <iostream>
#include <fstream>

namespace tarasenko
{
  size_t input(std::istream & in, int * arr, size_t n, size_t m)
  {
    for (size_t i = 0; i < n * m; ++i)
    {
      in >> arr[i];
      if (!in)
      {
        throw i;
      }
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

  size_t cnt_loc_extremum(int const * arr, int type, size_t n, size_t m)
  // type 1 for max and 0 for min
  {
    if (n * m == 0)
    {
      return 0;
    }
    size_t count = 0;
    for (size_t i = 1; i < n - 1; ++i)
    {
      for (size_t k = 1; k < m - 1; ++k)
      {
        bool is_extremum = true;
        const int num = arr[i * m + k];
        for (int near_i = -1; near_i < 2; ++near_i)
        {
          for (int near_k = -1; near_k < 2; ++near_k)
          {
            if (!(near_i == 0 && near_k == 0))
            {
              const int near_num = arr[(i + near_i) * m + (k + near_k)];
              if (type)
              {
                if (num <= near_num)
                {
                  is_extremum = false;
                }
              }
              else
              {
                if (num >= near_num)
                {
                  is_extremum = false;
                }
              }
            }
          }
        }
        count += (is_extremum ? 1 : 0);
      }
    }
    return count;
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
  if (!input)
  {
    std::cerr << "Incorrect file" << '\n';
    return 2;
  }
  if (*argv[1] == '1')
  {
    int arr[10000] = {};
    try
    {
      tarasenko::input(input, arr, rows, cols);
    }
    catch (size_t e)
    {
      std::cerr << "Managed to read "<< e << " numbers from file" << '\n';
      return 2;
    }
    int max = tarasenko::cnt_loc_extremum(arr, 1, rows, cols);
    int min = tarasenko::cnt_loc_extremum(arr, 0, rows, cols);
    output << max << '\n';
    output << min << '\n';
  }
  else
  {
    int * arr = reinterpret_cast< int * >(malloc(sizeof(int) * rows * cols));
    if (!arr)
    {
      std::cerr << "failed to allocate memory" << '\n';
      return 1;
    }
    try
    {
      tarasenko::input(input, arr, rows, cols);
    }
    catch (size_t e)
    {
      std::cerr << "Managed to read "<< e << " numbers from file" << '\n';
      free(arr);
      return 2;
    }
    int max = tarasenko::cnt_loc_extremum(arr, 1, rows, cols);
    int min = tarasenko::cnt_loc_extremum(arr, 0, rows, cols);
    output << max << '\n';
    output << min << '\n';
    free(arr);
  }
}
