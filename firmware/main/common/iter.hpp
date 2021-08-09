// Authors: summivox@gmail.com

#pragma once

#include <optional>

template <typename TInner>
class RustIter {
 public:
  using Item = typename TInner::Item;

  template <typename... T>
  explicit RustIter(T&&... arg) : inner_{std::forward<T>(arg)...}, curr_(inner_.Next()) {}

  RustIter(const RustIter<TInner>& rhs) = default;
  RustIter(RustIter<TInner>&& rhs) noexcept = default;
  RustIter<TInner>& operator=(const RustIter<TInner>& rhs) = default;
  RustIter<TInner>& operator=(RustIter<TInner>&& rhs) noexcept = default;
  ~RustIter() = default;

  operator bool() const { return !!curr_; }

  const Item& operator*() const { return *curr_; }
  const Item* operator->() const { return &*curr_; }
  RustIter<TInner>& operator++() {
    curr_ = inner_.Next();
    return *this;
  }

  friend RustIter<TInner> begin(RustIter<TInner> iter) noexcept { return iter; }
  friend RustIter<TInner> end(const RustIter<TInner>& iter) noexcept {
    return RustIter<TInner>{(typename RustIter<TInner>::Marker){}};
  }

 private:
  struct Marker {};
  RustIter(Marker) : curr_{} {}

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
