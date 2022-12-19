//
// Created by Anderson Porto on 12/10/22.
//

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

#include <clocale>
#include <algorithm>

#include "Node.hpp"

namespace ft {

template<typename T, class Compare, class Alloc>
class Tree {
 public:
  typedef T value_type;

  typedef Compare key_compare;

  typedef Alloc allocator_type;

  typedef Node<value_type, Alloc> node_type;

  typename Alloc::template rebind<node_type>::other rebind_allocator;

  node_type *root;

  Tree() : root(NULL) {}

  Tree(Tree const &copy) { *this = copy; }

  Tree &operator=(Tree const &copy) {
    if (this == &copy)
      return (*this);
    root = copy.root;
    _comparator = copy._comparator;
    return (*this);
  }

  ~Tree() {}

  int getHeight(node_type *node) {
    if (!node)
      return (0);

    return (node->height);
  }

  void assign(const node_type *node) {
    if (!node)
      return;

    assign(node->left);
    if (node->data)
      insert(*(node->data));
    assign(node->right);
  }

  node_type *insert(value_type key) {
    this->root = this->insert(this->root, key);
    return (root);
  }

  node_type *insert(node_type *node, const value_type &key) {
    if (!node)
      return (_newNode(key));

    if (_comparator(key.first, node->data->first)) {
      node->left = insert(node->left, key);
      node->left->parent = node;
    } else if (_comparator(node->data->first, key.first)) {
      node->right = insert(node->right, key);
      node->right->parent = node;
    } else
      return (node);

    _updateHeight(node);
    return (_balanceTree(node, key));
  }

  bool del(value_type key) {
    if (find(root, key)) {
      this->root = this->del(this->root, key);
      return (true);
    }
    return (false);
  }

  node_type *del(node_type *node, value_type const &key) {
    if (!node)
      return (node);

    if (_comparator(key.first, node->data->first))
      node->left = del(node->left, key);
    else if (_comparator(node->data->first, key.first))
      node->right = del(node->right, key);
    else if (node->data->first == key.first) {
      if (!node->left || !node->right) {
        node_type *tmp = node->left ? node->left : node->right;
        if (!tmp) {
          tmp = node;
          node = NULL;
        } else {
          node_type *nodeParent = node->parent;
          *node = *tmp;
          node->parent = nodeParent;
        }
        _allocator.deallocate(tmp->data, 1);
        rebind_allocator.deallocate(tmp, 1);
      } else {
        node_type *tmp = minNode(node->right);
        _allocator.construct(node->data, *tmp->data);
        node->right = del(node->right, *tmp->data);
      }
    }
    if (!node)
      return (node);

    _updateHeight(node);
    return (_balanceTree(node, key));
  }

  node_type *find(node_type *node, value_type const &key) const {
    if (!node)
      return (NULL);

    if (node->data && node->data->first == key.first)
      return (node);

    if (_comparator(key.first, node->data->first))
      return (find(node->left, key));

    else if (_comparator(node->data->first, key.first))
      return (find(node->right, key));

    return (node);
  }

  // Return the next node:
  //  - Return NULL if there is no next;
  //  - If there is a right subtree, find the minimal node of the subtree;
  //  - If there is only a left subtree, check if the parent is not the next node, instead of the left one.
  node_type *next(value_type const &key) const {
    node_type *node = find(root, key);
    if (!node)
      return (NULL);

    if (node->right != NULL)
      return (minNode(node->right));

    node_type *next = node->parent;
    while (next != NULL && node == next->right) {
      node = next;
      next = next->parent;
    }
    node = next;
    return node;
  }

  //	Return the previous node:
  //	- Return NULL if there is no previous;
  //	- If there is a left subtree, find the maximal node of the subtree;
  //	- If there is only a right subtree, check if the parent is not the previous node, instead of the right one.
  node_type *previous(value_type const &key) const {
    node_type *node = find(root, key);
    if (!node)
      return (NULL);

    if (node->left != NULL)
      return (Max(node->left));

    node_type *previous = node->parent;
    while (previous != NULL && node == previous->left) {
      node = previous;
      previous = previous->parent;
    }
    node = previous;
    return node;
  }

  // Return the max node of the tree
  // Right most node
  node_type *Max(node_type *node) const {
    if (!node)
      return (NULL);

    node_type *max = node;
    while (max->right)
      max = max->right;
    return max;
  }

  // Return the min node of the tree
  // Left most node
  node_type *minNode(node_type *node) const {
    if (!node)
      return (NULL);

    node_type *min = node;
    while (min->left)
      min = min->left;
    return min;
  }

  void clear() {
    desaloc(root);
    root = NULL;
  }

  // Desaloca todos os nós da árvore
  // a partir do nó passado como parâmetro
  void desaloc(node_type *node) {
    if (node) {
      desaloc(node->left);
      _allocator.deallocate(node->data, 1);
      desaloc(node->right);
      rebind_allocator.deallocate(node, 1);
      node = NULL;
    }
  }

 private:
  key_compare _comparator;

  allocator_type _allocator;

  void _updateHeight(node_type *node) {
    if (node) {
      node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }
  }

  // Factory method to create a new node
  node_type *_newNode(const value_type &key) {
    node_type *node = rebind_allocator.allocate(1);
    rebind_allocator.construct(node, key);
    return (node);
  }

  node_type *_balanceTree(node_type *node, value_type const &key) {
    if ((getHeight(node->left) - getHeight(node->right)) > 1) {
      if (_comparator(key.first, node->left->data->first))
        return _rotateRight(node);
      else {
        node->left = _rotateLeft(node->left);
        return _rotateRight(node);
      }
    }
    if ((getHeight(node->left) - getHeight(node->right)) < -1) {
      if (_comparator(node->right->data->first, key.first))
        return _rotateLeft(node);
      else {
        node->left = _rotateRight(node->left);
        return _rotateLeft(node);
      }
    }
    return (node);
  }



  /*

    z                                y
   /  \                            /   \
  T1   y     Left Rotate(z)       z      x
      /  \   - - - - - - - ->    / \    / \
     T2   x                     T1  T2 T3  T4
         / \
       T3  T4

  */
  node_type *_rotateLeft(node_type *z) {
    node_type *y = z->right;        // set y
    node_type *T2 = y->left;        // save for z->left

    if (y->left != NULL)
      y->left->parent = z;                        //	y->parent is z, everything is set to rotate
    y->left = z;
    z->right = T2;
    y->parent = z->parent;
    z->parent = y;
    _updateHeight(z);
    _updateHeight(y);
    return (y);
  }

  /*
              z                                      y
             / \                                   /   \
            y   T4      Right Rotate (z)          x      z
           / \          - - - - - - - - ->      /  \    /  \
          x   T3                               T1  T2  T3  T4
         / \
       T1   T2
  */
  node_type *_rotateRight(node_type *z) {
    node_type *y = z->left;

    if (!y)
      return (z);

    node_type *T3 = y->right;
    y->parent = z->parent;
    y->right = z;
    z->left = T3;
    z->parent = y;
    _updateHeight(z);
    _updateHeight(y);
    return (y);
  }

};
}

#endif
