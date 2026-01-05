#include <iostream>
#include <cstddef>
#include <cctype>
#include <iomanip>

namespace lukashevich {
  char* createStr(const size_t size)
  {
    char* str = nullptr;
    try {
      str = new char[size];
    } catch (const std::bad_alloc& e) {
      std::cerr << "bad alloc\n";
      return nullptr;
    }
    return str;
  }

  size_t strLen(const char* str)
  {
    size_t l = 0;
    while (str[l] != '\0') {
      l++;
    }
    return l;
  }

  char* updateStr(char* oldStr, const size_t oldSize)
  {
    char* newStr = createStr(oldSize * 2);
    if (!newStr) {
      delete[] oldStr;
      return nullptr;
    }
    for (size_t i = 0; i < oldSize; ++i) {
      newStr[i] = oldStr[i];
    }
    delete[] oldStr;
    return newStr;
  }
}

int main()
{
  return 0;
}
