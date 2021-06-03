#pragma once
#include <memory>
#include <vector>

namespace core {

class Observer;

class Observable {
  void Subscribe(std::weak_ptr<Observer>);
  virtual ~Observable();

private:
  void NotifyObservers();
  std::vector<std::weak_ptr<Observer>> _observers;
};

class Observer {
  virtual void HandleObservableUpdate();

private:
  std::shared_ptr<Observable> _observable;
};

} // namespace core