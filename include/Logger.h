#pragma once

#include "string"
#include <fstream>
#include <iostream>

class Logger {
public:
  void set_file_name(const std::string &name);

  template <typename T> friend Logger &operator<<(Logger &l, const T &value) {
    l._file << value;
    std::cout << value;
    return l;
  }

  friend Logger &operator<<(Logger &l, std::ostream &(*f)(std::ostream &));

  friend Logger &operator<<(Logger &l, std::ostream &(*f)(std::ios &));

  friend Logger &operator<<(Logger &l, std::ostream &(*f)(std::ios_base &));

  ~Logger() {
    _file.flush();
    _file.close();
  }

private:
  std::ofstream _file;
};
