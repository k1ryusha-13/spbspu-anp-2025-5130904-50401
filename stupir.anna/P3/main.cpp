#include <iostream>
#include <fstream>

int * create(int * arr, const char * firstArg, size_t rows, size_t cols)
{
  if(firstArg == "1")
  {
    arr[rows * cols] = {};
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
  try
  {
    arr = create(arr, firstArg, rows, cols);
    readArr(input, rows, cols, arr);
    if (input.fail())
    {
      std::cerr << "Non-correct values of matrix elements\n";
      return 2;
    }
    input.close();
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "Not enough memory\n";
    return 2;
  }
  
  std::ofstream output(thirdArg);
  writeArr(output, rows, cols, arr);

  if (firstArg == "2")
  {
    delete [] arr;
  }
}