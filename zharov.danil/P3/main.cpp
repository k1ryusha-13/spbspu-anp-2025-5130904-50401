#include <iostream>

bool isArgNum(char * arg);

int main(int argc, char ** argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  if (!isArgNum(argv[1])) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if ((argv[1][0] != '1' && argv[1][0] != '2') || argv[1][1] != '\0') {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  std::cout << "All is good\n";
}

bool isArgNum(const char * arg)
{
  if (arg[0] == '\0') {
    return false;
  } else {
    for (int i = 0; arg[i] != '\0'; ++i) {
      if (arg[i] < '0' || arg[i] > '9') {
        return false;
      }
    }
  }
  return true;
}
