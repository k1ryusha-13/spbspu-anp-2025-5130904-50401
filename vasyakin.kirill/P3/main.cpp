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
void destroy(int ** a, size_t created)
{
  for (size_t i = 0; i < created; ++i)
  {
    delete[] a[i];
  }
  delete[] a;
}
void output_static(const int (* a) [100], size_t rows, size_t cols, std::ofstream & output)
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
void output_dynamic(const int * const * a, size_t rows, size_t cols, std::ofstream & output)
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
int quantity_static(const int (* a) [100], size_t rows, size_t cols)
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
int ** create_matrix(size_t rows, size_t cols)
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
    destroy(a, created);
    throw;
  }
  return a;
}
int quantity_dynamic(const int * const * a, size_t rows, size_t cols)
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
size_t min(size_t rows, size_t cols)
{
  if (rows >= cols)
  {
    return cols;
  }
  return rows;
}
void spiral_static(int (* a) [100], size_t rows, size_t cols)
{
  size_t circle = min(rows, cols) / 2 + min(rows, cols) % 2;
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
void spiral_dynamic(int ** a, size_t rows, size_t cols)
{
  size_t circle = min(rows, cols) / 2 + min(rows, cols) % 2;
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
int main()
{
}
