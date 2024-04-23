#ifndef D3_MULTISET_H_
#define D3_MULTISET_H_

#include "../BTree/tree.h"

namespace d3 {
template <class Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = typename AvlTree<Key, Key>::iterator;
  using const_iterator = typename AvlTree<Key, Key>::const_iterator;

  multiset() : tree_(){};

  multiset(std::initializer_list<value_type> const &items) {
    for (auto element : items) {
      tree_.Insert(element, true);
    }
  }

  multiset(const multiset &ms) : tree_(ms.tree_){};

  multiset(multiset &&ms) : tree_(std::move(ms.tree_)){};

  ~multiset(){};

  multiset &operator=(multiset &&ms) {
    tree_ = std::move(ms.tree_);
    return *this;
  }

  iterator begin() const noexcept { return tree_.begin(); }

  iterator end() const noexcept { return tree_.end(); };

  bool empty() const noexcept { return tree_.empty(); };

  size_type size() const noexcept { return tree_.size(); };

  size_type max_size() const noexcept { return tree_.max_size(); }

  void clear() noexcept { tree_.clear(); };

  std::pair<iterator, bool> insert(const value_type &value) {
    return tree_.InsertBool(value, true);
  }

  void erase(iterator pos) { tree_.erase(pos); }

  void swap(multiset &other) { tree_.swap(other.tree_); };

  void merge(multiset &other) { tree_.merge(other.tree_); };

  size_type count(const Key &key) {
    size_type counter = 0;
    for (auto it = begin(); it != end(); ++it) {
      if (*it == key) {
        ++counter;
      }
    }
    return counter;
  }

  iterator find(const Key &key) { return tree_.FindNum(key); }
  bool contains(const Key &key) {
    iterator node = tree_.FindNum(key);
    iterator null;
    return node != null;
  }

  iterator lower_bound(const Key &key) {
    return tree_.FindNumByIter(key, true);
  }

  iterator upper_bound(const Key &key) {
    return tree_.FindNumByIter(key, false, true);
  }

  std::pair<iterator, iterator> equal_range(const Key &key) {
    std::pair<iterator, iterator> result = {lower_bound(key), upper_bound(key)};
    return result;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> vec;
    for (const auto &arg : {args...}) {
      vec.push_back(insert(arg));
    }
    return vec;
  }

 private:
  AvlTree<Key, Key> tree_;
};
}  // namespace d3

#endif  // D3_MULTISET_H_