#include "memory"
#include "string"
#include "vector"

#include <iostream>

class ICommand {
public:
  virtual void run(){};
  virtual ~ICommand(){};
};

class Command : public ICommand {
public:
  explicit Command(std::string name) : _name(std::move(name)) {}
  void run() override { std::cout << _name; }

private:
  std::string _name;
};

class Container : public ICommand {
public:
  void push(ICommand *command) { _commands.push_back(command); }

  void run() override {
    for (size_t i = 0; i < _commands.size(); i++) {
      _commands[i]->run();
      _commands[i]->~ICommand();
      if (i < _commands.size() - 1) {
        std::cout << ", ";
      }
    }
    _commands.clear();
  }

  std::vector<ICommand *> _commands;
};

class Controller : public Container {
public:
  explicit Controller(size_t maxBulkLength) : _max_bulk_length(maxBulkLength) {
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
      _call_stack.at(_call_stack.size() - 1)->push(new Command(cmd));
      if (at_root() && _commands.size() >= _max_bulk_length) {
        run();
      }
    }
  }

  void run() override {
    if (_commands.empty()) {
      return;
    }
    std::cout << "bulk: ";
    Container::run();
    std::cout << std::endl;
  }

private:
  void go_deeper() {
    if (at_root()) {
      run();
    }

    auto cmd = new Container();
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

  size_t _max_bulk_length;
  std::vector<Container *> _call_stack;
};

// todo read length as argument
// todo logger

int main(int, char **) {
  std::string cmd;
  size_t max_bulk_length = 3;
  //  std::cin >> _max_bulk_length;

  Controller root(max_bulk_length);

  std::cin >> cmd;
  while (!cmd.empty()) {
    root.handleInput(cmd);
    std::cin >> cmd;
  }
  root.run();
  return 0;
}
