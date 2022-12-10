//
// Created by Anderson Porto on 12/10/22.
//

#ifndef FT_CONTAINERS_NODE_HPP
#define FT_CONTAINERS_NODE_HPP

#include <clocale>

namespace ft {

template<typename T, class Alloc>
struct Node {
  Node *parent;

  Node *left;

  Node *right;

  T *data;

  Alloc alloc;

  int height;

  Node() : left(NULL), right(NULL), parent(NULL), data(NULL), height(0) {}

  Node(T const &copy) : left(NULL), right(NULL), parent(NULL), height(1) {
    data = alloc.allocate(1);
    alloc.construct(data, copy);
  }

  Node &operator=(Node const &copy) {
    if (this == &copy)
      return (*this);
    if (data)
      alloc.deallocate(data, 1);
    left = copy.left;
    right = copy.right;
    parent = copy.parent;
    height = copy.height;
    data = alloc.allocate(1);
    alloc.construct(data, *copy.data);
    return (*this);
  }

  ~Node() {}

  int getHeight() {
    return (height);
  }
};
}

#endif //FT_CONTAINERS_NODE_HPP
