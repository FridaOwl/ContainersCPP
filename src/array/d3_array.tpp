#include "d3_array.h"

namespace d3 {

// Element access
template <typename T, std::size_t N>
typename d3_array<T, N>::reference d3_array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of range");
  }
  return elements[pos];
}

template <typename T, std::size_t N>
typename d3_array<T, N>::const_reference d3_array<T, N>::at(
    size_type pos) const {
  if (pos >= N) {
    throw std::out_of_range("Index out of range");
  }
  return elements[pos];
}

template <typename T, std::size_t N>
typename d3_array<T, N>::reference d3_array<T, N>::operator[](size_type pos) {
  return elements[pos];
}

template <typename T, std::size_t N>
typename d3_array<T, N>::const_reference d3_array<T, N>::operator[](
    size_type pos) const {
  return elements[pos];
}

template <typename T, std::size_t N>
typename d3_array<T, N>::const_reference d3_array<T, N>::front() const {
  return elements[0];
}

template <typename T, std::size_t N>
typename d3_array<T, N>::const_reference d3_array<T, N>::back() const {
  return elements[N - 1];
}

// Iterators
template <typename T, std::size_t N>
typename d3_array<T, N>::iterator d3_array<T, N>::data() {
  return elements;
}

template <typename T, std::size_t N>
typename d3_array<T, N>::const_iterator d3_array<T, N>::data() const {
  return elements;
}

template <typename T, std::size_t N>
typename d3_array<T, N>::iterator d3_array<T, N>::begin() {
  return elements;
}

template <typename T, std::size_t N>
typename d3_array<T, N>::iterator d3_array<T, N>::end() {
  return elements + N;
}

template <typename T, std::size_t N>
typename d3_array<T, N>::const_iterator d3_array<T, N>::begin() const {
  return elements;
}

template <typename T, std::size_t N>
typename d3_array<T, N>::const_iterator d3_array<T, N>::end() const {
  return elements + N;
}

// Capacity
template <typename T, std::size_t N>
bool d3_array<T, N>::empty() const {
  return N == 0;
}

template <typename T, std::size_t N>
typename d3_array<T, N>::size_type d3_array<T, N>::size() const {
  return N;
}

template <typename T, std::size_t N>
typename d3_array<T, N>::size_type d3_array<T, N>::max_size() const {
  return N;
}

// Default constructor with initializer list
template <typename T, std::size_t N>
d3_array<T, N>::d3_array(std::initializer_list<value_type> const& items)
    : elements{} {
  if (items.size() > N) {
    throw std::out_of_range("Initializer list size exceeds array capacity");
  }

  auto iter = items.begin();
  for (std::size_t i = 0; i < N && iter != items.end(); ++i, ++iter) {
    elements[i] = *iter;
  }
}

// Copy constructor
template <typename T, std::size_t N>
d3_array<T, N>::d3_array(const d3_array& other) : elements{} {
  std::copy(other.elements, other.elements + N, elements);
}

//  Move constructor
template <typename T, std::size_t N>
d3_array<T, N>::d3_array(d3_array&& other) : elements{} {
  std::move(other.elements, other.elements + N, elements);
  std::fill(other.elements, other.elements + N, value_type());
}

// Destructor

template <typename T, std::size_t N>
d3_array<T, N>::~d3_array() {
  for (std::size_t i = 0; i < N; ++i) {
    elements[i] = T();
  }
}

// Copy assignment operator
template <typename T, std::size_t N>
d3_array<T, N>& d3_array<T, N>::operator=(const d3_array& other) {
  if (this != &other) {
    std::copy(other.elements, other.elements + N, elements);
  }
  return *this;
}

// Move assignment operator

template <typename T, std::size_t N>
d3_array<T, N>& d3_array<T, N>::operator=(d3_array&& other) {
  if (this != &other) {
    std::move(other.elements, other.elements + N, elements);
    std::fill(other.elements, other.elements + N, value_type());
  }
  return *this;
}

// Modifiers
template <typename T, std::size_t N>
void d3_array<T, N>::fill(const_reference value) {
  std::fill(elements, elements + N, value);
}

template <typename T, std::size_t N>
void d3_array<T, N>::swap(d3_array& other) {
  std::swap_ranges(elements, elements + N, other.elements);
}

// Non-member function
template <typename T, std::size_t N>
void swap(d3_array<T, N>& lhs, d3_array<T, N>& rhs) {
  lhs.swap(rhs);
}

}  // namespace d3
