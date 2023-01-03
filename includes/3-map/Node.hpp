//
// Created by Anderson Porto on 12/10/22.
//

#ifndef FT_CONTAINERS_NODE_HPP
#define FT_CONTAINERS_NODE_HPP

namespace ft {

template<typename T, class Alloc>
struct Node {
  T *data;

  Node *left;

  Node *right;

  Node *parent;

  int height;

  Alloc _alloc;

  Node() : left(NULL), right(NULL), parent(NULL), data(NULL), height(0) {}

  Node(T const &copy) : left(NULL), right(NULL), parent(NULL), height(1) {
    data = _alloc.allocate(1);
    _alloc.construct(data, copy);
  }

  Node &operator=(Node const &copy) {
    if (this != &copy) {
      if (data)
        _alloc.deallocate(data, 1);
      left = copy.left;
      right = copy.right;
      parent = copy.parent;
      height = copy.height;
      data = _alloc.allocate(1);
      _alloc.construct(data, *copy.data);
    }
    return (*this);
  }

  ~Node() {}
};
}

#endif //FT_CONTAINERS_NODE_HPP
