#ifndef D3_STACK_H_
#define D3_STACK_H_

#include "../list/d3_list.h"

namespace d3 {
template <typename T, class Container = list<T>>
class stack {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  stack() noexcept : list_() {}
  stack(std::initializer_list<value_type> const &items) : list_(items) {}
  stack(const stack &s) : list_(s.list_) {}
  stack(stack &&s) noexcept : list_(std::move(s.list_)) {}
  ~stack() noexcept {}
  stack &operator=(const stack &s) {
    list_ = s.list_;
    return *this;
  }
  stack operator=(stack &&s) noexcept {
    list_ = std::move(s.list_);
    return *this;
  }
  const_reference top() const noexcept { return list_.back(); }
  bool empty() const noexcept { return list_.empty(); }
  size_type size() const noexcept { return list_.size(); }
  void push(const_reference value) { list_.push_back(value); }
  void pop() noexcept { list_.pop_back(); }
  void swap(stack &other) noexcept { list_.swap(other.list_); }
  template <class... Args>
  void insert_many_front(Args &&...args) {
    list_.insert_many_front(std::forward<Args>(args)...);
  }

 private:
  Container list_;
};
}  // namespace d3

#endif  // D3_STACK_H_
