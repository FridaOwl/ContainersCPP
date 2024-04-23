#ifndef D3_ARRAY_H_
#define D3_ARRAY_H_

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
namespace d3 {

template <typename T, std::size_t N>
class d3_array {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = std::size_t;

  // Constructors
  d3_array() = default;
  d3_array(std::initializer_list<value_type> const& items);
  d3_array(const d3_array& other);
  d3_array(d3_array&& other);

  // Destructor
  ~d3_array();

  // Assignment operators
  d3_array& operator=(const d3_array& other);
  d3_array& operator=(d3_array&& other);

  // Element access
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  iterator data();
  const_iterator data() const;

  // Iterators
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // Capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // Modifiers
  void fill(const_reference value);
  void swap(d3_array& other);

 private:
  value_type elements[N];
};

// Non-member functions
template <typename T, std::size_t N>
void swap(d3_array<T, N>& lhs, d3_array<T, N>& rhs);

}  // namespace d3

#include "d3_array.tpp"

#endif  // D3_ARRAY_H_
