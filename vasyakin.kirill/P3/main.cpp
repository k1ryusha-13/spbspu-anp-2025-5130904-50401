#include <iostream>
#include <cstddef>
#include <limits>
#include <fstream>
namespace vasyakin
{
  void destroy(int * a);
  void output_static_dynamic(const int * a, size_t rows, size_t cols, std::ofstream & output);
  int quantity_static_dynamic(const int * a, size_t rows, size_t cols);
  int * create_matrix(size_t rows, size_t cols);
  size_t min(size_t rows, size_t cols);
  void spiral_static_dynamic(int * a, size_t rows, size_t cols);
}
void vasyakin::destroy(int * a)
{
  delete[] a;
}
void vasyakin::output_static_dynamic(const int * a, size_t rows, size_t cols, std::ofstream & output)
{
  output << rows << ' ' << cols << '\n';
  if (rows != 0 && cols != 0)
  {
    for (size_t i = 0; i < rows; ++i)
    {
      output << a[i * cols + 0];
      for (size_t j = 1; j < cols; ++j)
      {
        output << ' ' << a[i * cols + j];
      }
      output << '\n';
    }
  }
}
int vasyakin::quantity_static_dynamic(const int * a, size_t rows, size_t cols)
{
  int count = 0;
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      int current = a[i * cols + j];
      bool is_min_in_row = true;
      bool is_max_in_col = true;
      for (size_t f = 0; f < cols; ++f)
      {
        if (a[i * cols + f]< current)
        {
          is_min_in_row = false;
          break;
        }
      }
      for (size_t f = 0; f < rows; ++f)
      {
        if (a[f * cols + j] > current)
        {
          is_max_in_col = false;
          break;
        }
      }
      if (is_min_in_row && is_max_in_col)
      {
        count++;
      }
    }
  }
  return count;
}
int * vasyakin::create_matrix(size_t rows, size_t cols)
{
  int * a = nullptr;
  a = new int [rows * cols];
  return a;
}
size_t vasyakin::min(size_t rows, size_t cols)
{
  if (rows >= cols)
  {
    return cols;
  }
  return rows;
}
void vasyakin::spiral_static_dynamic(int * a, size_t rows, size_t cols)
{
  size_t circle = vasyakin::min(rows, cols) / 2 + vasyakin::min(rows, cols) % 2;
  size_t subtrahend = 1;
  for (size_t k = 0; k < circle; ++k)
  {
    for (size_t i = k; i < cols - k; ++i)
    {
      a[k * cols + i] -= subtrahend;
      subtrahend++;
    }
    for (size_t i = k + 1; i < rows - k; ++i)
    {
      a[i * cols + (cols - 1 - k)] -= subtrahend;
      subtrahend++;
    }
    if (k < rows - k - 1)
    {
      for (size_t i = cols - k - 2; i + 1 > k; --i)
      {
        a[(rows - 1 - k) * cols + i] -= subtrahend;
        subtrahend++;
      }
    }
    if (k < cols - k - 1)
    {
      for (size_t i = rows - k - 2; i > k; --i)
      {
        a[i * cols + k] -= subtrahend;
        subtrahend++;
      }
    }
  }
}
int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Error:" << " ";
    if (argc < 4)
    {
      std::cerr << "Not enough arguments" << "\n";
      return 1;
    }
    else
    {
      std::cerr << "Too many arguments" << "\n";
      return 1;
    }
  }
  if (*argv[1] != '1' && *argv[1] != '2')
  {
    std::cerr << "First parameter is out of range" << "\n";
    return 1;
  }
  else if (argv[1][1] != '\0')
  {
    std::cerr << "First parameter is not number" << "\n";
    return 1;
  }
  int num = *argv[1] - '0';
  std::ifstream input (argv[2]);
  std::ofstream output (argv[3]);
  if (!input)
  {
    std::cerr << "file not open" << "\n";
    return 1;
  }
  if (!output)
  {
    std::cerr << "cannot create output file" << "\n";
    return 1;
  }
  try
  {
    size_t rows = 0, cols = 0;
    if (!(input >> rows >> cols))
    {
      std::cerr << "cannot read matrix dimensions" << "\n";
      return 2;
    }
    if (rows == 0 && cols == 0)
    {
      output << "0 0" << "\n";
      return 0;
    }
    if (num == 1)
    {
      if (rows * cols > 10000)
      {
        std::cerr << "too much" << "\n";
        return 2;
      }
      int matrix[10000];
      for (size_t i = 0; i < rows; ++i)
      {
        for (size_t j = 0; j < cols; ++j)
        {
          long long int temp = 0;
          if (!(input >> temp))
          {
            if (input.eof())
            {
              std::cerr << "Not enough elements for matrix" << '\n';
              return 2;
            }
            else if (input.fail())
            {
              input.clear();
              std::cerr << "Unexpected input" << '\n';
              return 2;
            }
          }
          using lim_int = std::numeric_limits< int >;
          const long long int MAX = static_cast< long long int > (lim_int::max());
          const long long int MIN = static_cast< long long int > (lim_int::min());
          if (temp > MAX || temp < MIN)
          {
            std::cerr << "number out of int range" << '\n';
            return 2;
          }
          matrix[i * cols + j] = static_cast< int >(temp);
        }
      }
      int result = vasyakin::quantity_static_dynamic(matrix, rows, cols);
      output << result << '\n';
      int matrix_copy[10000];
      for (size_t i = 0; i < rows; ++i)
      {
        matrix_copy[i] = matrix[i];
      }
      vasyakin::spiral_static_dynamic(matrix_copy, rows, cols);
      vasyakin::output_static_dynamic(matrix_copy, rows, cols, output);
    }
    else
    {
      int * matrix = vasyakin::create_matrix(rows, cols);
      for (size_t i = 0; i < rows; ++i)
      {
        for (size_t j = 0; j < cols; ++j)
        {
          long long int temp = 0;
          if (!(input >> temp))
          {
            if (input.eof())
            {
              vasyakin::destroy(matrix);
              std::cerr << "Not enough elements for matrix" << '\n';
              return 2;
            }
            else if (input.fail())
            {
              input.clear();
              vasyakin::destroy(matrix);
              std::cerr << "Unexpected input" << '\n';
              return 2;
            }
          }
          using lim_int = std::numeric_limits< int >;
          const long long int MAX = static_cast< long long int > (lim_int::max());
          const long long int MIN = static_cast< long long int > (lim_int::min());
          if (temp > MAX || temp < MIN)
          {
            vasyakin::destroy(matrix);
            std::cerr << "number out of int range" << '\n';
            return 2;
          }
          matrix[i * cols + j] = static_cast< int >(temp);
        }
      }
      int result = vasyakin::quantity_static_dynamic(matrix, rows, cols);
      output << result << '\n';
      int * matrix_copy = vasyakin::create_matrix(rows, cols);
      for (size_t i = 0; i < rows; ++i)
      {
        matrix_copy[i] = matrix[i];
      }
      vasyakin::spiral_static_dynamic(matrix_copy, rows, cols);
      vasyakin::output_static_dynamic(matrix_copy, rows, cols, output);
      vasyakin::destroy(matrix);
      vasyakin::destroy(matrix_copy);
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  return 0;
}
