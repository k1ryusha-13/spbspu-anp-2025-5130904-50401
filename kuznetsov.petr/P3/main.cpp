#include <iostream>
#include <fstream>
#include <memory>
namespace kuznetsov {
  bool isNumber(const char* str)
  {
    bool isNum = true;
    size_t i = 0;

    do {
      if (str[i] < '0' || str[i] > '9') {
        isNum = false;
      }
      ++i;
    } while (str[i] != '\0');

    return isNum;
  }


}

int main(int argc, char** argv)
{
  namespace kuz = kuznetsov;
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  } else if (!kuz::isNumber(argv[1])) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  } else if (argv[1][0] != '1' && argv[1][0] != '2') {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

}