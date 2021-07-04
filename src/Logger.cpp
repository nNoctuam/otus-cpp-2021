#pragma once

void Logger::set_file_name(const std::string &name) {
  if (_file.is_open()) {
    _file.flush();
    _file.close();
  }
  _file.open(name, std::ios_base::app);
}
Logger &operator<<(Logger &l, std::ostream &(*f)(std::ostream &)) {
  f(std::cout);
  f(l._file);
  return l;
}
Logger &operator<<(Logger &l, std::ostream &(*f)(std::ios &)) {
  f(std::cout);
  f(l._file);
  return l;
}
Logger &operator<<(Logger &l, std::ostream &(*f)(std::ios_base &)) {
  f(std::cout);
  f(l._file);
  return l;
}
