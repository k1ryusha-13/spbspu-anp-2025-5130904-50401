#include <iostream>

int main(int argc, char ** argv)
{

  if (argc < 4)
  {
    std::cerr << "Not enough arguments";
    return 1;
  }
  if (argc > 4)
  {
    std::cerr << "Too many argiments";
  }

  int num = 0;
  for (int i = 0; argv[1][i] != '\0'; ++i)
  {
    if (argv[1][i] >= '0' && argv[1][i] <= '9')
    {
      num = num*10 + (argv[1][i] - '0');
    }
    else
    {
      std::cerr << "First parametr is not a number\n";
      return 1;
    }
  }
  if (num != 1 && num != 2)
  {
    std::cerr << "First parametr is out of range\n";
    return 1;
  }

  char * inp = argv[2];
  char * outp = argv[3]; 
  std::cout << num << ' '<< inp << ' ' << outp << '\n';
}