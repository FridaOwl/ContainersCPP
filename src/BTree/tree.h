#ifndef D3_BINARY_TREE_H_
#define D3_BINARY_TREE_H_

#include <iostream>

namespace d3 {

template <typename Key, typename T>
class AvlTree {
 public:
  class Node;
  class AvlTreeIterator;
  class AvlTreeConstIterator;
  using key_type = Key;
  using value_type = T;
  using reference = T &;
  using const_reference = const value_type &;
  using iterator = AvlTree<Key, T>::AvlTreeIterator;
  using const_iterator = AvlTree<Key, T>::AvlTreeConstIterator;
  using size_type = std::size_t;

  class Node {
   public:
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
    value_type data;
    int height_ = 0;

    explicit Node(const value_type &data = value_type{}, Node *left = nullptr,
                  Node *right = nullptr, Node *parent = nullptr)
        : left(left), right(right), parent(parent), data(data) {}
  };

  class AvlTreeIterator {
   public:
    AvlTreeIterator() : current(nullptr) {}
    explicit AvlTreeIterator(Node *current) : current(current) {}
    AvlTreeIterator &operator++() {
      if (!current) {
        return *this;
      }

      if (current->right) {
        current = current->right;
        while (current->left) {
          current = current->left;
        }
      } else {
        while (current->parent && current->data >= current->parent->data) {
          current = current->parent;
        }
        current = current->parent;
      }
      return *this;
    }

    AvlTreeIterator &operator--() {
      if (!current) {
        return *this;
      }

      if (current->left) {
        current = current->left;
        while (current->right) {
          current = current->right;
        }
      } else {
        while (current->parent && current->data < current->parent->data) {
          current = current->parent;
        }
        current = current->parent;
      }
      return *this;
    }

    AvlTreeIterator operator++(int) {
      iterator it(*this);
      ++(*this);
      return it;
    }
    AvlTreeIterator operator--(int) {
      iterator it(*this);
      --(*this);
      return it;
    }
    bool operator==(const AvlTreeIterator &other) const {
      return current == other.current;
    }
    bool operator!=(const AvlTreeIterator &other) const {
      return current != other.current;
    }
    reference operator*() const {
      if (!current) {
        throw std::invalid_argument("wrong argument");
      }
      return current->data;
    }
    Node *getCurrent() { return current; }

   private:
    Node *current{nullptr};
  };

  class AvlTreeConstIterator : public AvlTreeIterator {
   public:
    AvlTreeConstIterator();
    explicit AvlTreeConstIterator(Node *current);
    AvlTreeConstIterator(const AvlTreeIterator &it);

    AvlTreeConstIterator &operator++();
    AvlTreeConstIterator &operator--();
    AvlTreeConstIterator operator++(int);
    AvlTreeConstIterator operator--(int);
    bool operator==(const AvlTreeConstIterator &other) const;
    bool operator!=(const AvlTreeConstIterator &other) const;
    const_reference operator*() const;

   private:
    AvlTreeIterator it;
  };

  AvlTree() : root(nullptr) {}

  AvlTree(const AvlTree<Key, T> &s) {
    root = new Node(s.root->data);
    root->parent = nullptr;
    CopyTree(root, s.root);
  }

  AvlTree(AvlTree &&s) { swap(s); }

  ~AvlTree() {
    if (root != nullptr) {
      clear();
    }
  }

  AvlTree &operator=(AvlTree &&s) {
    clear();
    swap(s);
    return *this;
  }

  iterator begin() const noexcept {
    if (!root) {
      return iterator(nullptr);
    }
    Node *tmp = root;
    while (tmp->left) {
      tmp = tmp->left;
    }
    return iterator(tmp);
  }

  iterator end() const noexcept { return iterator(nullptr); }

  bool empty() const noexcept { return (!root); }
  size_type size() const noexcept {
    size_type counter = 0;
    if (root) {
      for (auto it = begin(); it != end(); ++it) {
        ++counter;
      }
    }
    return counter;
  }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
  }

  void clear() noexcept {
    ClearTree(root);
    root = nullptr;
  }

  void Insert(value_type value, bool duplicate = false) {
    root = Insert(root, value, duplicate, nullptr);
  }

  Node *Insert(Node *node, value_type value, bool duplicate, Node *parent) {
    if (node == nullptr) {
      node = new Node(value);
      node->parent = parent;
    } else if (value < node->data) {
      node->left = Insert(node->left, value, duplicate, node);
    } else if (value > node->data || duplicate) {
      node->right = Insert(node->right, value, duplicate, node);
    }
    SetHeight(node);
    return node;
  }

  std::pair<iterator, bool> InsertOrAssign(const T &obj) {
    iterator node = FindNumByIter(obj);
    if (node != end()) {
      node.getCurrent()->data.second = obj.second;
      return {node, false};
    } else {
      Insert(obj);
      return {FindNumByIter(obj), true};
    }
  }

  std::pair<iterator, bool> InsertBool(const value_type &value,
                                       bool duplicate = false) {
    std::pair<iterator, bool> result;
    size_type begin_size = size();
    Insert(value, duplicate);
    if (size() == begin_size) {
      iterator node = FindNumByIter(value);
      result.first = node;
      result.second = false;
    } else {
      iterator node = FindNumByIter(value);
      result.first = node;
      result.second = true;
    }
    return result;
  }

  void erase(iterator pos) {
    if (pos.getCurrent() == nullptr)
      throw std::invalid_argument("Iterator points to null node");

    if (empty()) throw std::invalid_argument("Cannot erase from an empty tree");

    root = delete_node(root, *pos);
  }

  Node *delete_node(Node *&node, const value_type &value) {
    Node **current = &node;
    while (*current) {
      if (value < (*current)->data) {
        current = &((*current)->left);
      } else if (value > (*current)->data) {
        current = &((*current)->right);
      } else {
        Node *to_delete = *current;
        if ((*current)->left == nullptr) {
          *current = (*current)->right;
        } else if ((*current)->right == nullptr) {
          *current = (*current)->left;
        } else {
          Node **succ = &((*current)->right);
          while ((*succ)->left) {
            succ = &((*succ)->left);
          }
          (*current)->data = (*succ)->data;
          to_delete = *succ;
          *succ = (*succ)->right;
        }
        delete to_delete;
        return node;
      }
    }
    return node;
  }

  Node *minimum(Node *node) {
    while (node && node->left) {
      node = node->left;
    }
    return node;
  }

  void swap(AvlTree &other) { std::swap(root, other.root); }
  void merge(AvlTree &other) {
    for (auto &item : other) {
      Insert(item);
    }
  }

  iterator FindNum(const Key &key) { return iterator(FindNumByKey(root, key)); }

  iterator FindNumByIter(value_type value, bool lower = false,
                         bool upper = false) {
    iterator node = begin();
    if (!lower && !upper) {
      return iterator(FindNumByValue(root, value));
    } else if (lower) {
      while (value > node.getCurrent()->data) {
        node++;
      }
    } else if (upper) {
      while (node.getCurrent()->data <= value) {
        node++;
      }
    }
    return node;
  }

  Node *FindNumByKey(Node *node, Key value) {
    while (node != nullptr) {
      if (value < node->data) {
        node = node->left;
      } else if (value > node->data) {
        node = node->right;
      } else {
        return node;
      }
    }
    return nullptr;
  }

  Node *FindNumByValue(Node *node, value_type value) {
    while (node != nullptr && node->data != value) {
      if (value < node->data) {
        node = node->left;
      } else {
        node = node->right;
      }
    }
    return node;
  }

  void CopyTree(Node *node, Node *node_copy) {
    if (node_copy) {
      node->data = node_copy->data;
      if (node_copy->left) {
        node->left = new Node();
        node->left->parent = node;
        CopyTree(node->left, node_copy->left);
      }
      if (node_copy->right) {
        node->right = new Node();
        node->right->parent = node;
        CopyTree(node->right, node_copy->right);
      }
    }
  }

  void ClearTree(Node *node) {
    if (node) {
      ClearTree(node->left);
      ClearTree(node->right);
      if (node->parent) {
        if (node->parent->left == node) {
          node->parent->left = nullptr;
        } else if (node->parent->right == node) {
          node->parent->right = nullptr;
        }
      }
      delete node;
    }
    if (node == root) {
      root = nullptr;
    }
  }

  void SetHeight(Node *node) {
    if (node) {
      int left_height = (node->left) ? node->left->height_ : -1;
      int right_height = (node->right) ? node->right->height_ : -1;
      node->height_ = std::max(left_height, right_height) + 1;
    }
  }

 private:
  Node *root{nullptr};
};
}  // namespace d3

#endif  // D3_BINARY_TREE_H_