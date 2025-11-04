#include <iostream>
#include <fstream>

bool isNumber(char * word)
{
  for (size_t i = 0; word[i] != '\0'; ++i) {
    if (word[i] < '0' || word[i] > '9') {
      return false;
    }
  }
  return (word[0] != '\0');
}

int main(int argc, char ** argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  } else if (! isNumber(argv[1])) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  } else if (! ((argv[1][0] == '1' || argv[1][0] == '2') && argv[1][1] == '\0')) {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
}
