#include "d3_list.h"

namespace d3 {

template <typename T>
list<T>::list() noexcept
    : head(nullptr), tail(nullptr), endMarker(nullptr), size_(0){};

template <typename T>
list<T>::list(size_type n) : list() {
  if (n < max_size()) {
    for (size_type i = 0; i < n; ++i) {
      push_back(value_type());
    }
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) : list() {
  for (auto i : items) {
    push_back(i);
  }
}

template <typename T>
list<T>::list(const list &l) : list() {
  *this = l;
}

template <typename T>
list<T>::list(list &&l) noexcept : list() {
  *this = std::move(l);
}

template <typename T>
list<T>::~list() noexcept {
  clear();
}

template <typename T>
list<T> &list<T>::operator=(const list &l) {
  if (this != &l) {
    clear();
    CopyListContents(l);
  }
  return *this;
}

template <typename T>
list<T> list<T>::operator=(list &&l) noexcept {
  if (this != &l) {
    clear();
    MoveListContents(std::move(l));
  }
  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::front() const noexcept {
  const_reference customDefault = value_type();
  return empty() ? customDefault : head->value;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const noexcept {
  const_reference customDefault = value_type();
  return empty() ? customDefault : tail->value;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  if (endMarker == nullptr) {
    CreateEndNode();
  }
  return iterator(head, endMarker);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  if (endMarker == nullptr) {
    CreateEndNode();
  }
  return iterator(endMarker, endMarker);
}

template <typename T>
bool list<T>::empty() const noexcept {
  return head == nullptr;
}

template <typename T>
typename list<T>::size_type list<T>::size() const noexcept {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const noexcept {
  return std::numeric_limits<size_t>::max() / sizeof(typename list<T>::Node) /
         2;
}

template <typename T>
void list<T>::clear() noexcept {
  while (!empty()) {
    pop_back();
  }
  delete endMarker;
  endMarker = nullptr;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator position,
                                           const_reference value) {
  if (position == head) {
    push_front(value);
    position.itr_ = head;
  } else if (position == end()) {
    push_back(value);
    position.itr_ = tail;
  } else {
    Node *temp = nullptr;
    try {
      temp = new Node(value);
    } catch (const std::bad_alloc &e) {
      clear();
      throw e;
    }
    Node *itr = position.itr_;
    if (position.itr_ == nullptr) {
      Node *tmp = tail->next;
      temp->prev = tail;
      tail->next = temp;
      tail = temp;
      tail->next = tmp;
      itr = tail;
    } else {
      temp->next = itr;
      temp->prev = itr->prev;
      if (temp->prev != nullptr) temp->prev->next = temp;
      itr->prev = temp;
    }
    ++size_;
    endMarker->value++;
    position = iterator(temp);
  }
  return position;
}

template <typename T>
void list<T>::erase(iterator position) {
  if (position == begin()) {
    pop_front();
  } else if (position == tail) {
    pop_back();
  } else if (!empty() && position != end()) {
    iterator prevPos = position - 1;
    iterator nextPos = position + 1;
    Node *temp = position.itr_;
    temp->next->prev = temp->prev;
    temp->prev->next = temp->next;
    delete temp;
    size_--;
  }
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node *temp = nullptr;
  try {
    temp = new Node(value);
  } catch (const std::bad_alloc &e) {
    clear();
    throw e;
  }
  if (head == nullptr) head = temp;
  if (tail == nullptr)
    tail = temp;
  else {
    if (tail->next == nullptr) {
      tail->next = temp;
      temp->next = nullptr;
      temp->prev = tail;
      tail = temp;
    }
  }
  ++size_;
}

template <typename T>
void list<T>::pop_back() noexcept {
  if (tail != nullptr) {
    Node *temp = tail;
    if (temp == head) {
      delete temp;
      head = nullptr;
      tail = nullptr;
    } else {
      tail = temp->prev;
      tail->next = nullptr;
      delete temp;
    }
    --size_;
  }
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node *temp = nullptr;
  try {
    temp = new Node(value);
  } catch (const std::bad_alloc &e) {
    clear();
    throw e;
  }
  if (tail == nullptr) {
    tail = temp;
  }
  if (head == nullptr)
    head = temp;
  else {
    head->prev = temp;
    temp->prev = nullptr;
    temp->next = head;
    head = temp;
  }
  ++size_;
}

template <typename T>
void list<T>::pop_front() noexcept {
  if (tail != nullptr) {
    Node *temp = head;
    if (temp == tail) {
      delete temp;
      head = nullptr;
      tail = nullptr;
    } else {
      head = temp->next;
      head->prev = nullptr;
      delete temp;
    }
    --size_;
  }
}

template <typename T>
void list<T>::swap(list &other) noexcept {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(endMarker, other.endMarker);
  std::swap(size_, other.size_);
}

template <typename T>
void list<T>::merge(list &other) {
  if (empty() && !other.empty()) {
    CopyListContents(other);
  } else if (!empty() && !other.empty()) {
    iterator it = begin();
    iterator it_other = other.begin();
    while (it != end() && it_other != other.end()) {
      if (it.itr_->value >= it_other.itr_->value) {
        insert(it, it_other.itr_->value);
        ++it_other;
      } else {
        ++it;
      }
    }
    while (it_other != other.end()) {
      insert(it, it_other.itr_->value);
      ++it_other;
    }
  }
  other.clear();
}

template <typename T>
void list<T>::splice(const_iterator position, list &other) {
  if (!other.empty()) {
    iterator our_it;
    our_it.itr_ = position.itr_;
    for (iterator it = other.begin(); it != other.end(); ++it) {
      insert(our_it, *it);
    }
    other.clear();
  }
}

template <typename T>
void list<T>::reverse() noexcept {
  Node *itr = head;
  for (size_type i = 0; i < size_; ++i) {
    std::swap(itr->next, itr->prev);
    itr = itr->prev;
  }
  std::swap(tail, head);
}

template <typename T>
void list<T>::unique() {
  if (head != nullptr) {
    Node *current = head;
    Node *next = head->next;
    list<T> uniqueList;
    for (size_type i = 0; i < size_ - 1; ++i) {
      if (current->value != next->value) {
        uniqueList.push_back(current->value);
      }
      current = current->next;
      next = next->next;
    }
    uniqueList.push_back(current->value);
    *this = std::move(uniqueList);
  }
}

template <typename T>
void list<T>::sort() noexcept {
  for (size_type i = 0; i < size_ - 1; ++i) {
    Node *node = head;
    for (size_type j = 0; j < size_ - i - 1; ++j) {
      if (node->value >= node->next->value) {
        T temp = node->value;
        node->value = node->next->value;
        node->next->value = temp;
      }
      node = node->next;
    }
  }
}

template <typename T>
void list<T>::MoveListContents(list &&l) {
  std::swap(head, l.head);
  std::swap(tail, l.tail);
  std::swap(endMarker, l.endMarker);
  std::swap(size_, l.size_);
}

template <typename T>
void list<T>::CopyListContents(const list &l) {
  Node *temp = l.head;
  if (l.tail) {
    while (temp != l.tail->next) {
      push_back(temp->value);
      temp = temp->next;
    }
  }
}

template <typename T>
void list<T>::CreateEndNode() {
  try {
    endMarker = new Node(value_type());
    endMarker->prev = tail;
    endMarker->value = size_;
    endMarker->next = head;
  } catch (const std::bad_alloc &e) {
    clear();
    throw e;
  }
}

template <typename T>
list<T>::const_iterator::ConstListIterator() noexcept {
  itr_ = nullptr;
}

template <typename T>
list<T>::const_iterator::ConstListIterator(Node *n) noexcept {
  itr_ = n;
}

template <typename T>
list<T>::const_iterator::ConstListIterator(Node *n, Node *end) noexcept {
  itr_ = n;
  itr_end_ = end;
}

template <typename T>
list<T>::const_iterator::ConstListIterator(
    const ConstListIterator &other) noexcept {
  *this = other;
}
template <typename T>
list<T>::const_iterator::ConstListIterator(ConstListIterator &&other) noexcept {
  *this = std::move(other);
}

template <typename T>
typename list<T>::const_iterator &list<T>::const_iterator::operator=(
    const ConstListIterator &other) noexcept {
  itr_ = other.itr_;
  itr_end_ = other.itr_end_;
  return *this;
}

template <typename T>
typename list<T>::const_iterator list<T>::const_iterator::operator=(
    ConstListIterator &&other) noexcept {
  itr_ = other.itr_;
  itr_end_ = other.itr_end_;
  other.itr_ = nullptr;
  other.itr_end_ = nullptr;
  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::const_iterator::operator*()
    const noexcept {
  value_type customDefault = value_type();
  return itr_ == nullptr ? customDefault : itr_->value;
}

template <typename T>
typename list<T>::const_iterator
list<T>::const_iterator::operator++() noexcept {
  if (itr_->next)
    itr_ = itr_->next;
  else
    itr_ = itr_end_;
  return itr_;
}

template <typename T>
typename list<T>::const_iterator
list<T>::const_iterator::operator--() noexcept {
  if (itr_->prev)
    itr_ = itr_->prev;
  else
    itr_ = itr_end_;
  return itr_;
}

template <typename T>
typename list<T>::const_iterator list<T>::const_iterator::operator+(
    const size_type step) noexcept {
  for (size_type i = 0; i < step; ++i) {
    ++*this;
  }
  return *this;
}

template <typename T>
typename list<T>::const_iterator list<T>::const_iterator::operator-(
    const size_type step) noexcept {
  for (size_type i = 0; i < step; ++i) {
    --*this;
  }
  return *this;
}

template <typename T>
bool list<T>::const_iterator::operator==(
    const ConstListIterator &other) const noexcept {
  return itr_ == other.itr_;
}

template <typename T>
bool list<T>::const_iterator::operator!=(
    const ConstListIterator &other) const noexcept {
  return itr_ != other.itr_;
}

template <typename T>
typename list<T>::iterator &list<T>::iterator::operator=(
    const ConstListIterator &other) noexcept {
  *this = other;
  return *this;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator=(
    ConstListIterator &&other) noexcept {
  *this = std::move(other);
  return *this;
}

template <typename T>
typename list<T>::reference list<T>::iterator::operator*() const noexcept {
  value_type customDefault = value_type();
  return this->itr_ == nullptr ? customDefault : this->itr_->value;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator++() noexcept {
  if (this->itr_) {
    if (this->itr_->next)
      this->itr_ = this->itr_->next;
    else
      this->itr_ = this->itr_end_;
  } else
    this->itr_ = this->itr_end_;
  return this->itr_;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator--() noexcept {
  if (this->itr_) {
    if (this->itr_->prev)
      this->itr_ = this->itr_->prev;
    else
      this->itr_ = this->itr_end_;
  } else
    this->itr_ = this->itr_end_;
  return this->itr_;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator+(
    const size_type step) noexcept {
  iterator res = this->itr_;
  for (size_type i = 0; i < step; ++i) {
    ++res;
  }
  return res;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator-(
    const size_type step) noexcept {
  iterator res = this->itr_;
  for (size_type i = 0; i < step; ++i) {
    --res;
  }
  return res;
}

template <class T>
template <class... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator position,
                                                Args &&...args) {
  iterator it;
  it.itr_ = position.itr_;
  for (auto &i : {args...}) {
    insert(it, i);
  }
  return it;
}

template <class T>
template <class... Args>
void list<T>::insert_many_back(Args &&...args) {
  for (auto &i : {args...}) {
    push_back(i);
  }
}

template <class T>
template <class... Args>
void list<T>::insert_many_front(Args &&...args) {
  for (auto &i : {args...}) {
    push_front(i);
  }
}

}  // namespace d3
