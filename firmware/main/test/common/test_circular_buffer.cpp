// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "common/circular_buffer.hpp"

#include "fmt/core.h"

#include "unity.h"  // must be included last

using fmt::print;

TEST_CASE("CircularBuffer - basic integer", "[common]") {
  CircularBuffer<int> q(5);
  q.Dump();
  q.push_back(1);
  q.push_back(2);
  q.Dump();
  q.push_back(3);
  q.push_back(4);
  q.Dump();
  q.push_back(5);
  q.Dump();
  TEST_ASSERT(q.full());
  q.push_back(6);
  q.Dump();
  TEST_ASSERT(q.full());
  TEST_ASSERT(q.front() == 2);
  TEST_ASSERT(q.back() == 6);
  TEST_ASSERT(q[0] == 2);
  TEST_ASSERT(q[1] == 3);
  TEST_ASSERT(q[2] == 4);
  TEST_ASSERT(q[3] == 5);
  TEST_ASSERT(q[4] == 6);
  TEST_ASSERT(q[-1] == 6);
  TEST_ASSERT(q[-2] == 5);
  TEST_ASSERT(q[-3] == 4);
  TEST_ASSERT(q[-4] == 3);
  TEST_ASSERT(q[-5] == 2);

  q.emplace_back(7);
  q.Dump();
  TEST_ASSERT(q[-1] == 7);

  auto& z = q.recycle_back();
  z = 8;
  q.Dump();
  TEST_ASSERT(q[-1] == 8);

  TEST_ASSERT(q.pop_front() == 4);
  q.Dump();
  TEST_ASSERT(q.size() == 4);
  TEST_ASSERT(q.pop_front() == 5);
  q.Dump();
  TEST_ASSERT(q.size() == 3);

  q.push_back(9);
  q.Dump();
  TEST_ASSERT(q.size() == 4);
  q.push_back(10);
  q.Dump();
  TEST_ASSERT(q.size() == 5);
  q.push_back(11);
  q.Dump();
  TEST_ASSERT(q.size() == 5);
  TEST_ASSERT(q.front() == 7);
}

class A {
 public:
  A() { print("A() -- {}\n", x_); }
  explicit A(double x) : x_(x) { print("A(double) -- {}\n", x_); }
  A(const A& other) : x_(other.x_) { print("A(const A&) -- {}\n", x_); }
  A(A&& other) : x_(other.x_) {
    other.x_ = 1e100;
    print("A(A&&) -- {}\n", x_);
  }
  virtual ~A() { print("~A -- {}\n", x_); }
  A& operator=(const A& other) {
    x_ = other.x_;
    print("A& operator=(const A&) -- {}\n", x_);
    return *this;
  }
  A& operator=(A&& other) {
    x_ = other.x_;
    other.x_ = 2e100;
    print("A& operator=(A&& other) -- {}\n", x_);
    return *this;
  }

  static A FromDouble(double x) { return A{x}; }

  operator double() const { return x_; }

 private:
  double x_;
};

TEST_CASE("CircularBuffer - ctor & dtor", "[common]") {
  CircularBuffer<A> q(3);
  print("--- ready ---\n");
  q.Dump();

  q.emplace_back(1.1);
  q.Dump();
  q.emplace_back(1.2);
  q.Dump();
  q.emplace_back(1.3);
  q.Dump();
  q.emplace_back(2.1);
  q.Dump();
  print("--- push_back ---\n");
  q.push_back(A::FromDouble(2.2));
  q.Dump();
  print("-----\n");
  A popped = q.pop_front();
  q.Dump();
  TEST_ASSERT(double(popped) == 1.3);
  popped = q.pop_front();
  q.Dump();
  TEST_ASSERT(double(popped) == 2.1);
}
