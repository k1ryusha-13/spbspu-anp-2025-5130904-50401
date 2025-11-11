#include <iostream>
#include <cstddef>
#include <limits>
#include <fstream>
namespace vasyakin
{
  void destroy(int ** a, size_t created);
  void output_static(const int (* a) [100], size_t rows, size_t cols, std::ofstream & output);
  void output_dynamic(const int * const * a, size_t rows, size_t cols, std::ofstream & output);
  int quantity_static(const int (* a) [100], size_t rows, size_t cols);
  int ** create_matrix(size_t rows, size_t cols);
  int quantity_dynamic(const int * const * a, size_t rows, size_t cols);
  size_t min(size_t rows, size_t cols);
  void spiral_dynamic(int ** a, size_t rows, size_t cols);
  void spiral_static(int (* a) [100], size_t rows, size_t cols);
}
void vasyakin::destroy(int ** a, size_t created)
{
  for (size_t i = 0; i < created; ++i)
  {
    delete[] a[i];
  }
  delete[] a;
}
void vasyakin::output_static(const int (* a) [100], size_t rows, size_t cols, std::ofstream & output)
{
  for (size_t i = 0; i < rows; ++i)
  {
    output << a[i][0];
    for (size_t j = 1; j < cols; ++j)
    {
      output << ' ' << a[i][j];
    }
    output << '\n';
  }
}
void vasyakin::output_dynamic(const int * const * a, size_t rows, size_t cols, std::ofstream & output)
{
  for (size_t i = 0; i < rows; ++i)
  {
    output << a[i][0];
    for (size_t j = 1; j < cols; ++j)
    {
      output << ' ' << a[i][j];
    }
    output << '\n';
  }
}
int vasyakin::quantity_static(const int (* a) [100], size_t rows, size_t cols)
{
  int count = 0;
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      int current = a[i][j];
      bool is_min_in_row = true;
      bool is_max_in_col = true;
      for (size_t f = 0; f < cols; ++f)
      {
        if (a[i][f] < current)
        {
          is_min_in_row = false;
          break;
        }
      }
      for (size_t f = 0; f < rows; ++f)
      {
        if (a[f][j] > current)
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
int ** vasyakin::create_matrix(size_t rows, size_t cols)
{
  int ** a = new int * [rows];
  size_t created = 0;
  try
  {
    for (; created < rows; created++)
    {
      a[created] = new int [cols];
    }
  }
  catch (const std::bad_alloc &e)
  {
    vasyakin::destroy(a, created);
    throw;
  }
  return a;
}
int vasyakin::quantity_dynamic(const int * const * a, size_t rows, size_t cols)
{
  int count = 0;
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      int current = a[i][j];
      bool is_min_in_row = true;
      bool is_max_in_col = true;
      for (size_t f = 0; f < cols; ++f)
      {
        if (a[i][f] < current)
        {
          is_min_in_row = false;
          break;
        }
      }
      for (size_t f = 0; f < rows; ++f)
      {
        if (a[f][j] > current)
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
size_t vasyakin::min(size_t rows, size_t cols)
{
  if (rows >= cols)
  {
    return cols;
  }
  return rows;
}
void vasyakin::spiral_static(int (* a) [100], size_t rows, size_t cols)
{
  size_t circle = vasyakin::min(rows, cols) / 2 + vasyakin::min(rows, cols) % 2;
  size_t subtrahend = 1;
  for (size_t k = 0; k < circle; ++k)
  {
    for (size_t i = k; i < cols - k; ++i)
    {
      a[k][i] -= subtrahend;
      subtrahend++;
    }
    for (size_t i = k + 1; i < rows - k; ++i)
    {
      a[i][cols - 1 - k] -= subtrahend;
      subtrahend++;
    }
    if (k < rows - k - 1)
    {
      for (size_t i = cols - k - 2; i + 1 > k; --i)
      {
        a[rows - 1 - k][i] -= subtrahend;
        subtrahend++;
      }
    }
    if (k < cols - k - 1)
    {
      for (size_t i = rows - k - 2; i > k; --i)
      {
        a[i][k] -= subtrahend;
        subtrahend++;
      }
    }
  }
}
void vasyakin::spiral_dynamic(int ** a, size_t rows, size_t cols)
{
  size_t circle = vasyakin::min(rows, cols) / 2 + vasyakin::min(rows, cols) % 2;
  size_t subtrahend = 1;
  for (size_t k = 0; k < circle; ++k)
  {
    for (size_t i = k; i < cols - k; ++i)
    {
      a[k][i] -= subtrahend;
      subtrahend++;
    }
    for (size_t i = k + 1; i < rows - k; ++i)
    {
      a[i][cols - 1 - k] -= subtrahend;
      subtrahend++;
    }
    if (k < rows - k - 1)
    {
      for (size_t i = cols - k - 2; i + 1 > k; --i)
      {
        a[rows - 1 - k][i] -= subtrahend;
        subtrahend++;
      }
    }
    if (k < cols - k - 1)
    {
      for (size_t i = rows - k - 2; i > k; --i)
      {
        a[i][k] -= subtrahend;
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
      int matrix[100][100];
      for (size_t i = 0; i < rows; ++i)
      {
        for (size_t j = 0; j < cols; ++j)
        {
          long long int temp = 0;
}
