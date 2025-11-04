#include <iostream>
#include <fstream>
#include <limits>

namespace rizatdinov
{
  int stringToInt(char * string);
  unsigned parseArgs(int argc, char ** argv);
  void errorHandler(unsigned parse_args);
}

int main(int argc, char ** argv)
{
  namespace riz = rizatdinov;

  unsigned parse_args = riz::parseArgs(argc, argv);
  if (parse_args)
  {
    riz::errorHandler(parse_args);
    return 1;
  }
}

int rizatdinov::stringToInt(char * string)
{
  int result = 0;
  int digit = 0;
  int multiplier = 1;
  int count = 0;
  int start_limit = 0;
  int max_limit = std::numeric_limits<int>::max();
  int min_limit = std::numeric_limits<int>::min();
  int is_negative = 1;

  if (string[0] == '-')
  {
    is_negative = -1;
    start_limit++;
  }

  for (; string[count] != '\0'; ++count);

  if (count - start_limit > 10)
  {
    throw std::overflow_error("Number too large");
  }

  for (int i = count - 1; i >= start_limit; --i)
  {
    if (string[i] < '0' || string[i] > '9')
    {
      throw std::invalid_argument("Invalid Character");
    }

    digit = ((int)string[i]) - 48;
  
    if (result < (min_limit + digit * multiplier))
    {
      throw std::overflow_error("Number too large");
    } 
    else  if (result > (max_limit - digit * multiplier))
    {
      throw std::overflow_error("Number too large");
    }

    result += digit * multiplier * is_negative;

    multiplier *= 10;
  }

  return result;
}

unsigned rizatdinov::parseArgs(int argc, char ** argv)
{
  int num = 0;
  unsigned result = argc < 4 || argc > 4;
  
  if (result)
  {
    return 1;
  }

  try
  {
    num = rizatdinov::stringToInt(argv[1]);
  }
  catch (...)
  {
    return 2;
  }

  std::ifstream input(argv[2]);

  result = (num < 1 || num > 2) * 2;
  result += (!input.is_open()) * 3;

  return result;
}

void rizatdinov::errorHandler(unsigned parse_args)
{
  switch (parse_args)
  {
    case 1:
      std::cerr << "fatal: invalid number of arguments\n";
      break;
    case 2:
      std::cerr << "fatal: invalid parameter\n";
      break;
    case 3:
      std::cerr << "fatal: cannot open file\n";
      break;
    default:
      std::cerr << "fatal: invalid parameter\n";
  }
}
