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

  char* getLine(std::istream& in)
  {
    const bool isSkipws = in.flags() & std::ios_base::skipws;
    if (isSkipws) {
      in >> std::noskipws;
    }

    size_t i = 0;
    size_t size = 8;
    char sym = 0;
    char* str = createStr(size);
    if (!str) {
      return nullptr;
    }

    while (in >> sym && sym != '\n') {
      if (i == size - 1) {
        str = updateStr(str, size);
        if (!str) {
          return nullptr;
        }
        size *= 2;
      }
      str[i++] = sym;
    }
    str[i++] = '\0';

    if (isSkipws) {
      in >> std::skipws;
    }

    return str;
  }

  int removeLatinLetters(const char* str, char* result, const int resultSize)
  {
    if (str == nullptr || result == nullptr || resultSize <= 0) {
      return -1;
    }

    int pos = 0;
    for (size_t i = 0; str[i] != '\0'; ++i) {
      const unsigned char c = str[i];
      if (!std::isalpha(c)) {
        if (pos + 1 >= resultSize) {
          return -1;
        }
        result[pos++] = str[i];
      }
    }

    result[pos] = '\0';
    return pos;
  }
}

int main()
{
  namespace luk = lukashevich;
  return 0;
}
