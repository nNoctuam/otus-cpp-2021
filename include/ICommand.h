#pragma once

class ICommand {
public:
  virtual void run(){};
  virtual ~ICommand(){};
};
