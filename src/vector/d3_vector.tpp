#include <algorithm>
#include <stdexcept>
#include <utility>

#include "d3_vector.h"

namespace d3 {

// Default constructor
template <typename T>
d3_vector<T>::d3_vector()
    : elements(nullptr), num_elements(0), array_capacity(0) {}

// Parameterized constructor
template <typename T>
d3_vector<T>::d3_vector(size_type n)
    : elements(new T[n]), num_elements(n), array_capacity(n) {}

// Initializer list constructor
template <typename T>
d3_vector<T>::d3_vector(std::initializer_list<value_type> const &items)
    : elements(new T[items.size()]),
      num_elements(items.size()),
      array_capacity(items.size()) {
  std::copy(items.begin(), items.end(), elements);
}

// Copy constructor
template <typename T>
d3_vector<T>::d3_vector(const d3_vector &v)
    : num_elements(v.num_elements), array_capacity(v.array_capacity) {
  elements = new T[array_capacity];
  std::copy(v.elements, v.elements + num_elements, elements);
}

// Move constructor
template <typename T>
d3_vector<T>::d3_vector(d3_vector &&v) noexcept
    : elements(v.elements),
      num_elements(v.num_elements),
      array_capacity(v.array_capacity) {
  v.elements = nullptr;
  v.num_elements = 0;
  v.array_capacity = 0;
}

// Destructor
template <typename T>
d3_vector<T>::~d3_vector() {
  delete[] elements;
}

// Move assignment operator
template <typename T>
d3_vector<T> &d3_vector<T>::operator=(d3_vector &&v) {
  if (this != &v) {
    delete[] elements;
    elements = v.elements;
    num_elements = v.num_elements;
    array_capacity = v.array_capacity;

    v.elements = nullptr;
    v.num_elements = 0;
    v.array_capacity = 0;
  }
  return *this;
}

// Access specified element with bounds checking
template <typename T>
typename d3_vector<T>::reference d3_vector<T>::at(size_type pos) {
  if (pos >= num_elements) {
    throw std::out_of_range("Index out of range");
  }
  return elements[pos];
}

// Access specified element
template <typename T>
typename d3_vector<T>::reference d3_vector<T>::operator[](size_type pos) {
  return elements[pos];
}

// Access the first element
template <typename T>
typename d3_vector<T>::const_reference d3_vector<T>::front() {
  if (num_elements == 0) {
    throw std::out_of_range("d3_vector is empty");
  }
  return elements[0];
}

// Access the last element
template <typename T>
typename d3_vector<T>::const_reference d3_vector<T>::back() {
  if (num_elements == 0) {
    throw std::out_of_range("d3_vector is empty");
  }
  return elements[num_elements - 1];
}

// Direct access to the underlying array
template <typename T>
T *d3_vector<T>::data() {
  return elements;
}

// Returns an iterator to the beginning
template <typename T>
typename d3_vector<T>::iterator d3_vector<T>::begin() {
  return elements;
}

// Returns an iterator to the end
template <typename T>
typename d3_vector<T>::iterator d3_vector<T>::end() {
  return elements + num_elements;
}

// Checks whether the container is empty
template <typename T>
bool d3_vector<T>::empty() {
  return num_elements == 0;
}

// Returns the number of elements
template <typename T>
typename d3_vector<T>::size_type d3_vector<T>::size() {
  return num_elements;
}

// Returns the maximum possible number of elements
template <typename T>
typename d3_vector<T>::size_type d3_vector<T>::max_size() {
  return std::numeric_limits<size_type>::max();
}

// Allocate storage of size elements and copies current array elements to a
template <typename T>
void d3_vector<T>::reserve(size_type size) {
  if (size <= array_capacity) {
    return;
  }
  T *new_elements = new T[size];
  std::copy(elements, elements + num_elements, new_elements);
  delete[] elements;
  elements = new_elements;
  array_capacity = size;
}

// Returns the number of elements that can be held in currently allocated
template <typename T>
typename d3_vector<T>::size_type d3_vector<T>::capacity() {
  return array_capacity;
}

// Reduces memory usage by freeing unused memory
template <typename T>
void d3_vector<T>::shrink_to_fit() {
  if (num_elements < array_capacity) {
    T *new_elements = new T[num_elements];
    std::copy(elements, elements + num_elements, new_elements);
    delete[] elements;
    elements = new_elements;
    array_capacity = num_elements;
  }
}

// Clears the contents
template <typename T>
void d3_vector<T>::clear() {
  delete[] elements;
  elements = nullptr;
  num_elements = 0;
  array_capacity = 0;
}

// Inserts elements into concrete pos and returns the iterator that points to
template <typename T>
typename d3_vector<T>::iterator d3_vector<T>::insert(iterator pos,
                                                     const_reference value) {
  size_type index = pos - elements;
  if (num_elements == array_capacity) {
    reserve(array_capacity == 0 ? 1 : array_capacity * 2);
  }
  std::copy_backward(elements + index, elements + num_elements,
                     elements + num_elements + 1);
  elements[index] = value;
  ++num_elements;
  return elements + index;
}

// Erases element at pos
template <typename T>
void d3_vector<T>::erase(iterator pos) {
  size_type index = pos - elements;
  std::copy(elements + index + 1, elements + num_elements, elements + index);
  --num_elements;
}

// Adds an element to the end
template <typename T>
void d3_vector<T>::push_back(const_reference value) {
  if (num_elements == array_capacity) {
    reserve(array_capacity == 0 ? 1 : array_capacity * 2);
  }
  elements[num_elements++] = value;
}

// Removes the last elementм
template <typename T>
void d3_vector<T>::pop_back() {
  if (num_elements > 0) {
    --num_elements;
  }
}

// Swaps the contents
template <typename T>
void d3_vector<T>::swap(d3_vector &other) {
  std::swap(elements, other.elements);
  std::swap(num_elements, other.num_elements);
  std::swap(array_capacity, other.array_capacity);
}

}  // namespace d3
