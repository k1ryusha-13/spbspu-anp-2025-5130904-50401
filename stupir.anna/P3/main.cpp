#include <iostream>
#include <fstream>

namespace stupir
{
  int * create(size_t rows, size_t cols)
  {
    int * arr = new int[rows * cols];
    return arr;
  }

  bool checkAddSnail(size_t up, size_t down, size_t left, size_t right)
  {
    return (up <= down && left <= right);
  }

  void addSnail(const int * arr1, size_t rows, size_t cols, int * arr2)
  {
    size_t sum = 1;
    size_t left = 0; 
    size_t right = cols - 1;
    size_t up = 0;
    size_t down = rows - 1;
    while (checkAddSnail(up, down, left, right))
    {
      for (size_t i = left; i < right + 1; ++i)
      {
        arr2[cols * down + i] += sum + arr1[cols * down + i];
        sum++;
      }
      down--;
      
      if (!checkAddSnail(up, down, left, right))
      {
        break;
      }

      for (size_t i = down; i > up ; --i)
      {
        arr2[cols * i + right] += sum + arr1[cols * i + right];
        sum++;
      }
      arr2[cols * up + right] += sum + arr1[cols * up + right];
      sum++;
      right--;

      if (!checkAddSnail(up, down, left, right))
      {
        break;
      }

      for (size_t i = right; i > left; --i)
      {
        arr2[up * cols + i] += sum + arr1[up * cols + i];
        sum++;
      }
      arr2[up * cols + left] += sum + arr1[up * cols + left];
      sum++;
      up++;

      if (!checkAddSnail(up, down, left, right))
      {
        break;
      }

      for (size_t i = up; i < down + 1; ++i)
      {
        arr2[cols * i + left] += sum + arr1[cols * i + left];
        sum++;
      }
      left++;
    }
  }

  int * create(int * arr, const char * firstArg, size_t rows, size_t cols)
  {
    if(firstArg == "1")
    { 
      if (rows * cols < 10000)
      {
        arr[rows * cols] = {};
      }
      else
      {
        throw std::bad_alloc();
      }
    }
    else
    {
      arr = new int[rows * cols];
    }
    return arr;
  }

  void readArr(std::ifstream& input, size_t rows, size_t cols, int * arr)
  {
    for (size_t i = 0; i < rows * cols; ++ i)
      {
        input >> arr[i];
      }
  }

  void writeArr(std::ofstream& output, size_t rows, size_t cols, int * arr)
  {
    if (!output.fail())
    {
      output << arr[0];
      for (size_t i = 1; i < rows * cols; ++ i)
      {
        output << " " << arr[i];
      }
    }
    else
    {
      std::cerr << "Сouldn't open the file for writing\n";
    }
  }
}

int main(int argc, char ** argv)
{
  if (argc < 4)
  {
    std::cerr << "Not enough argument\n";
    return 1;
  }
  else if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  else if (argv[1][0] < '0' || argv[1][0] > '9')
  {
    std::cerr << "First parametr isn't a number\n";
    return 1;
  }
  else if (argv[1][0] != '1' && argv[1][0] != '2')
  {
    std::cerr << "First parametr out of range\n";
    return 1;
  }

  const char * firstArg = argv[1];
  const char * secondArg = argv[2];
  const char * thirdArg = argv[3];
  
  std::ifstream input(secondArg);
  if (!input.is_open()) 
  {
    std::cerr << "Error when opening a file\n";
    return 2;
  }

  size_t rows = 0;
  size_t cols = 0;
  input >> rows;
  input >> cols;
  if (input.fail() || (!rows && cols) || (rows && !cols))
  {
    std::cerr << "Irregular matrix sizes\n";
    return 2;
  }
  if (!rows && !cols)
  {
    std::cout << 0;
    return 0;
  }

  int * arr = nullptr;
  int * task1 = nullptr;
  int * task2 = nullptr;
  namespace stu = stupir;
  try
  {
    arr = stu::create(arr, firstArg, rows, cols);
    stu::readArr(input, rows, cols, arr);
    if (input.fail())
    {
      std::cerr << "Non-correct values of matrix elements\n";
      return 2;
    }
    input.close();
    task1 = stu::create(rows, cols);
    stu::addSnail(arr, rows, cols, task1);
    task2 = stu::create(rows, cols);
  }
  catch (const std::bad_alloc& e)
  { 
    delete [] arr;
    delete [] task1;
    std::cerr << "Not enough memory\n";
    return 2;
  }
  std::ofstream output(thirdArg);
  stu::writeArr(output, rows, cols, task1);

  if (firstArg == "2")
  {
    delete [] arr;
  }
  delete [] task1;
  delete [] task2;
}