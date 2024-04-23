#ifndef D3_SET_H_
#define D3_SET_H_

#include "../BTree/tree.h"

namespace d3 {
template <class Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = typename AvlTree<Key, Key>::iterator;
  using const_iterator = typename AvlTree<Key, Key>::const_iterator;

  set() : tree_() {}

  set(std::initializer_list<value_type> const &items) {
    for (auto element : items) {
      tree_.Insert(element);
    }
  }

  set(const set &s) : tree_(s.tree_){};

  set(set &&s) : tree_(std::move(s.tree_)){};

  ~set() {}

  set &operator=(set &&s) {
    tree_ = std::move(s.tree_);
    return *this;
  }

  iterator begin() const noexcept { return tree_.begin(); }

  iterator end() const noexcept { return tree_.end(); };

  bool empty() const noexcept { return tree_.empty(); };

  size_type size() const noexcept { return tree_.size(); };

  size_type max_size() const noexcept { return tree_.max_size(); }

  void clear() noexcept { tree_.clear(); };

  std::pair<iterator, bool> insert(const value_type &value) {
    return tree_.InsertBool(value);
  }
  void erase(iterator pos) { tree_.erase(pos); }

  void swap(set &other) { tree_.swap(other.tree_); };

  void merge(set &other) { tree_.merge(other.tree_); };

  iterator find(const Key &key) { return tree_.FindNum(key); }

  bool contains(const Key &key) {
    iterator node = tree_.FindNum(key);
    iterator null;
    return node != null;
  }
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> vec;
    vec.reserve(sizeof...(args));
    (vec.emplace_back(insert(std::forward<Args>(args))), ...);
    return vec;
  }

 private:
  AvlTree<Key, Key> tree_;
};
}  // namespace d3

#endif  // D3_SET_H_