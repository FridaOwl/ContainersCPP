#ifndef D3_VECTOR_H_
#define D3_VECTOR_H_

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace d3 {

template <typename T>
class d3_vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  d3_vector();
  explicit d3_vector(size_type n);
  d3_vector(std::initializer_list<value_type> const &items);
  d3_vector(const d3_vector &v);
  d3_vector(d3_vector &&v) noexcept;
  ~d3_vector();

  d3_vector &operator=(d3_vector &&v);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T *data();

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(d3_vector &other);

 private:
  T *elements;
  size_type num_elements;
  size_type array_capacity;

  void copy_elements(const d3_vector &other);
  void move_elements(d3_vector &&other);
  void destroy_elements();
  void reallocate(size_type new_capacity);
};

}  // namespace d3

#endif  // D3_VECTOR_H_
