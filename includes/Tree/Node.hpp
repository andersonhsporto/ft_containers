//
// Created by Anderson Porto on 11/10/22.
//

#ifndef FT_CONTAINERS_NODE_HPP
#define FT_CONTAINERS_NODE_HPP

namespace ft {
template<typename T, class allocator>
struct Node {
  allocator default_allocator;

  Node *left;

  Node *right;

  Node *parent;

  T *data;

  int height;

  // Default Constructor
  Node() : left(0), right(0), parent(0), data(0), height(0) {}

  // Copy Constructor
  explicit Node(const T &value) : left(0), right(0), parent(0), data(0), height(1) {
    data = default_allocator.allocate(1);
    default_allocator.construct(data, value);
  }

  // Assignment Operator
  Node &operator=(const Node &other) {
    if (this != &other) {
      this->left = other.left;
      this->right = other.right;
      this->parent = other.parent;
      this->data = default_allocator.allocate(1);
      default_allocator.construct(this->data, *other.data);
    }
    return *this;
  }

  // Destructor
  ~Node() {  }

};
}

#endif //FT_CONTAINERS_NODE_HPP
