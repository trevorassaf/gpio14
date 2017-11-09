#pragma once

#include <functional>
#include <utility>

namespace Utility {

template <typename T>
class ScopeGuard {
 public:
  ScopeGuard(T t, std::function<void(T&)> deleter)
    : t_(std::move(t)),
      deleter_(std::move(deleter)) {}

  ~ScopeGuard() {
    deleter_(t_);
  }

 private:
  T t_;
  std::function<void(T&)> deleter_;
};

} // namespace Utility
