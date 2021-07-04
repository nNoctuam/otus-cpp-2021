#include "memory"
#include "string"
#include "vector"

#include <fstream>
#include <iostream>
#include <chrono>

class Logger {
public:

  void set_file_name(const std::string &name) {
    if (_file.is_open()) {
      _file.flush();
      _file.close();
    }
    _file.open(name, std::ios_base::app);
  }

  template <typename T>
  friend Logger& operator << (Logger &l, const T &value) {
    l._file << value;
    std::cout << value;
    return l;
  }

  friend Logger& operator<< (Logger &l, std::ostream& (*f)(std::ostream &)) {
    f(std::cout);
    f(l._file);
    return l;
  }

  friend Logger& operator<< (Logger &l, std::ostream& (*f)(std::ios &)) {
    f(std::cout);
    f(l._file);
    return l;
  }

  friend Logger& operator<< (Logger &l, std::ostream& (*f)(std::ios_base &)) {
    f(std::cout);
    f(l._file);
    return l;
  }

  ~Logger() {
    _file.flush();
    _file.close();
  }
private:
  std::ofstream _file;
};

class ICommand {
public:
  virtual void run(){};
  virtual ~ICommand(){};
};

class Command : public ICommand {
public:
  explicit Command(std::string name, std::shared_ptr<Logger> logger)
      : _name(std::move(name)), _logger(std::move(logger)) {}
  void run() override {
    (*_logger) << _name;
  }

private:
  std::string _name;
  std::shared_ptr<Logger> _logger;
};

class Container : public ICommand {
public:
  explicit Container(std::shared_ptr<Logger> logger)
      : _logger(std::move(logger)) {}

  void push(ICommand *command) { _commands.push_back(command); }

  void run() override {
    for (size_t i = 0; i < _commands.size(); i++) {
      _commands[i]->run();
      _commands[i]->~ICommand();
      if (i < _commands.size() - 1) {
        (*_logger) << ", ";
      }
    }
    _commands.clear();
  }

protected:
  std::vector<ICommand *> _commands;
  std::shared_ptr<Logger> _logger;
  friend class Controller;
};

class Controller : public Container {
public:
  explicit Controller(size_t maxBulkLength, std::shared_ptr<Logger> logger)
      : Container(std::move(logger)), _max_bulk_size(maxBulkLength) {
    _call_stack.push_back(this);
  }

  void handleInput(std::string &cmd) {
    if (cmd == "{") {
      go_deeper();
    } else if (cmd == "}") {
      go_upper();
    } else if ((cmd.empty() || cmd == "EOF") && at_root()) {
      run();
    } else {
      if (at_root() && _commands.empty()) {
        const auto p1 = std::time(nullptr);
        _logger->set_file_name("bulk" + std::to_string(p1) + ".log");
      }
      _call_stack.at(_call_stack.size() - 1)->push(new Command(cmd, _logger));
      if (at_root() && _commands.size() >= _max_bulk_size) {
        run();
      }
    }
  }

  void run() override {
    if (_commands.empty()) {
      return;
    }
    (*_logger) << "bulk: ";
    Container::run();
    (*_logger) << std::endl;
  }

private:
  void go_deeper() {
    if (at_root()) {
      run();
    }

    auto cmd = new Container(_logger);
    _call_stack.at(_call_stack.size() - 1)->_commands.push_back(cmd);
    _call_stack.push_back(cmd);
  }

  void go_upper() {
    if (!at_root()) {
      _call_stack.pop_back();
    }
    if (at_root()) {
      run();
    }
  }

  bool at_root() const { return _call_stack.size() == 1; }

  size_t _max_bulk_size;
  std::vector<Container *> _call_stack;
};


 int main(int argc, char * argv[]) {
    if (argc < 2) {
      std::cerr << "usage: " << argv[0] << "MAX_BULK_SIZE" << std::endl;
      return 1;
    }

    size_t max_bulk_length = atoi(argv[1]);
  Controller root(max_bulk_length, std::make_shared<Logger>());

  std::string cmd;
  std::cin >> cmd;

  while (!cmd.empty()) {
    root.handleInput(cmd);
    std::cin >> cmd;
  }
  root.run();
  return 0;
}
