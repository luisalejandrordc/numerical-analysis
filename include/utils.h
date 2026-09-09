#include <iostream>
#include <string>

inline void printTitle(const std::string &title) {
  std::string dashes(title.length() + 10, '-');
  std::cout << dashes << std::endl;
  std::cout << "|    " << title << "    |" << std::endl;
  std::cout << dashes << std::endl;
}
