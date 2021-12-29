// Authors: summivox@gmail.com

#pragma once

#include <optional>
#include <variant>

#include "common/macros.hpp"

template <typename TInner>
class RustIter {
 public:
  using Item = typename TInner::Item;

  template <typename... T>
  explicit RustIter(T&&... arg) : inner_{std::forward<T>(arg)...}, curr_(inner_.Next()) {}

  ~RustIter() = default;

  operator bool() const { return !!curr_; }

  const Item& operator*() const { return *curr_; }
  const Item* operator->() const { return &*curr_; }
  RustIter<TInner>& operator++() {
    curr_ = inner_.Next();
    return *this;
  }

  // ranged-for proxying

  class Proxy {
   public:
    operator bool() const { return !!*iter_; }
    const Item& operator*() const { return **iter_; }
    const Item* operator->() const { return &**iter_; }
    Proxy& operator++() {
      ++(*iter_);
      return *this;
    }

   private:
    RustIter<TInner>* iter_;
    Proxy(RustIter* iter) : iter_(iter) {}

    friend class RustIter<TInner>;
  };

  Proxy begin() noexcept { return {this}; }
  std::monostate end() const noexcept { return {}; }
  friend bool operator!=(const Proxy& lhs, const std::monostate& rhs) { return lhs; }

  NOT_COPYABLE_NOR_MOVABLE(RustIter<TInner>)

 private:
  TInner inner_;
  std::optional<Item> curr_;
};

template <typename TInner>
bool operator==(const RustIter<TInner>& lhs, const RustIter<TInner>& rhs) {
  return !lhs && !rhs;  // only for comparing to end
}

#if 0  // example

class MyNext {
 public:
  using Item = int;
  MyNext() = default;
  MyNext(int begin, int end) : now_(begin), end_(end) {}
  std::optional<int> Next() {
    if (now_ < end_) {
      return now_++;
    }
    return {};
  }

 private:
  int now_;
  int end_;
};

#endif
