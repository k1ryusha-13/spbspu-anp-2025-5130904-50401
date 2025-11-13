#include <iostream>

namespace hvostov {
  bool is_number(const char * str);
}

bool hvostov::is_number(const char * str)
{
  if (*str == '\0' || !str) {
    return false;
  }
  size_t index = 0; 
  while (str[index] != '\0') {
    if (str[index] < '0' || str[index] > '9') {
      return false;
    }
    index++;
  }
  if (index > 1) {
    if (str[0] == '0') {
      return false;
    }
  }
  return true;
}

int main(int argc, char ** argv)
{
  if (argc > 4) {
    std::cerr << "Too many arguments!\n";
    return 1;
  } else if (argc < 4) {
    std::cerr << "Not enough arguments!\n";
    return 1;
  } else if (!hvostov::is_number(argv[1])) {
    std::cerr << "First parameter is not a number!\n";
    return 1; 
  } else if (argv[1][0] < '1' || argv[1][0] > '2') {
    std::cerr << "First parameter is out of range!\n";
    return 1;
  }
  std::cout << "OK!\n";
  return 0; 
}
