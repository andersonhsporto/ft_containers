//
// Created by Anderson Porto on 11/10/22.
//

#ifndef FT_CONTAINERS_AVL_HPP
#define FT_CONTAINERS_AVL_HPP

namespace ft {
template<typename T, class allocator>
struct Node {
  Node *left;

  Node *right;

  Node *parent;

  T *data;

  int height;

  allocator alloc;

  Node() : left(0), right(0), parent(0), data(0), height(0) {}

  Node(const T &data) : left(0), right(0), parent(0), data(0), height(0) {
    this->data = alloc.allocate(1);
    alloc.construct(this->data, data);
  }

  Node &operator=(const Node &other) {
    if (this != &other) {
      this->left = other.left;
      this->right = other.right;
      this->parent = other.parent;
      this->data = other.data;
      this->height = other.height;
    }
    return *this;
  }

  ~Node() {
    alloc.destroy(data); // TODO: check if this is correct
    alloc.deallocate(data, 1);
  }

};
}

#endif //FT_CONTAINERS_AVL_HPP
