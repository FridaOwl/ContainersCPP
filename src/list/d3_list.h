#ifndef D3_LIST_H_
#define D3_LIST_H_

#include <limits>
#include <new>
#include <stdexcept>

namespace d3 {

template <typename T>
class list {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  list() noexcept;
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l) noexcept;
  ~list() noexcept;
  list &operator=(const list &l);
  list operator=(list &&l) noexcept;
  const_reference front() const noexcept;
  const_reference back() const noexcept;
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void clear() noexcept;
  void push_back(const_reference value);
  void pop_back() noexcept;
  void push_front(const_reference value);
  void pop_front() noexcept;
  void swap(list &other) noexcept;
  void reverse() noexcept;
  void sort() noexcept;

 private:
  void MoveListContents(list &&l);
  void CopyListContents(const list &l);
  void CreateEndNode();
  struct Node {
    value_type value;
    Node *next;
    Node *prev;
    Node(const_reference value) : value(value), next(nullptr), prev(nullptr){};
  };
  Node *head;
  Node *tail;
  Node *endMarker;
  size_type size_;

  class ConstListIterator {
    friend class list<T>;

   public:
    ConstListIterator() noexcept;
    ConstListIterator(Node *n) noexcept;
    ConstListIterator(Node *n, Node *end) noexcept;
    ConstListIterator(const ConstListIterator &other) noexcept;
    ConstListIterator(ConstListIterator &&other) noexcept;
    ~ConstListIterator() = default;
    ConstListIterator &operator=(const ConstListIterator &other) noexcept;
    ConstListIterator operator=(ConstListIterator &&other) noexcept;
    const_reference operator*() const noexcept;
    ConstListIterator operator++() noexcept;
    ConstListIterator operator--() noexcept;
    ConstListIterator operator+(const size_type step) noexcept;
    ConstListIterator operator-(const size_type step) noexcept;
    bool operator==(const ConstListIterator &other) const noexcept;
    bool operator!=(const ConstListIterator &other) const noexcept;

   private:
    Node *itr_;
    Node *itr_end_;
  };

 public:
  class ListIterator : public ConstListIterator {
   public:
    ListIterator() noexcept : ConstListIterator(){};
    ListIterator(Node *n) noexcept : ConstListIterator(n){};
    ListIterator(Node *n, Node *end) noexcept : ConstListIterator(n, end){};
    ListIterator(const ConstListIterator &other) noexcept
        : ConstListIterator(other){};
    ListIterator(ConstListIterator &&other) noexcept
        : ConstListIterator(std::move(other)){};
    ~ListIterator() = default;
    ListIterator &operator=(const ConstListIterator &other) noexcept;
    ListIterator operator=(ConstListIterator &&other) noexcept;
    reference operator*() const noexcept;
    ListIterator operator++() noexcept;
    ListIterator operator--() noexcept;
    ListIterator operator+(const size_type step) noexcept;
    ListIterator operator-(const size_type step) noexcept;
  };

  using iterator = ListIterator;
  using const_iterator = ConstListIterator;

  iterator begin();
  iterator end();
  iterator insert(iterator position, const_reference value);
  void erase(iterator position);
  void splice(const_iterator position, list &other);
  void unique();
  void merge(list &other);

  template <class... Args>
  iterator insert_many(const_iterator position, Args &&...args);

  template <class... Args>
  void insert_many_back(Args &&...args);

  template <class... Args>
  void insert_many_front(Args &&...args);
};
}  // namespace d3
#include "d3_list.tpp"
#endif  // D3_LIST_H_
