//
// Created by Anderson Porto on 11/10/22.
//

#ifndef FT_CONTAINERS_AVL_HPP
#define FT_CONTAINERS_AVL_HPP

#include <cstddef>
#include "Node.hpp"

namespace ft {
template<typename T, class compare, class allocator>
class AVL {
  // *********************************************************************************************
  // *********************************************************************************************
  // *************************************** Member types ****************************************
 public:
  typedef T value_type;

  typedef Node<value_type, allocator> node_type;

  typedef node_type *node_pointer;

  typedef compare key_compare;

  typedef allocator allocator_type;

  // ********************************************************************************************
  // ********************************************************************************************
  // *************************************** Member functions ***********************************
 public:
  AVL() : _root(NULL) {}

  AVL(AVL &other) : _root(NULL) {
    *this = other;
  }

  AVL &operator=(const AVL &other) {
    if (this != &other) {
      this->_root = other._root;
      this->_comp = other._comp;
    }
    return *this;
  }

  ~AVL() {
    clear();
  }

  // ********************************************************************************************
  // ********************************************************************************************
  // *************************************** Member Functions ***********************************

// TODO:: ?? PRIVATE
  node_type *newNode(const value_type &data) {
    node_type *node = _alloc.allocate(1);

    _alloc.construct(node, data);
    return node;
  }

  node_type *insert(node_type *n1, const value_type &data) {
//    if (n1 == NULL) {
//      return newNode(data);
//    } else if (data < n1->data) {

  }

//  node_type *balance(node_type *n1) {
//    int balance = getBalance(n1);
//
//    if (balance > 1) {
//      if (getBalance(n1->left) < 0) {
//        n1->left = rotateLeft(n1->left);
//      }
//      return rotateRight(n1);
//    } else if (balance < -1) {
//      if (getBalance(n1->right) > 0) {
//        n1->right = rotateRight(n1->right);
//      }
//      return rotateLeft(n1);
//    }
//    return n1;
//  }

  // TODO:: ?? PRIVATE
  node_type *singleRightRotate(node_type *k2) {
    node_type *k1 = k2->left;

    k2->left = k1->right;
    k1->right = k2;
    updateNodeHeight(k2);
    updateNodeHeight(k1);
    return k1;
  }

  // TODO:: ?? PRIVATE
  node_type *singleLeftRotate(node_type *k2) {
    node_type *k1 = k2->right;

    k2->right = k1->left;
    k1->left = k2;
    updateNodeHeight(k2);
    updateNodeHeight(k1);
    return k1;
  }

  // TODO: ?? PRIVATE
  void updateNodeHeight(node_type *node) {
    node->height = max(height(node->left), height(node->right)) + 1;
  }

  // TODO: ?? PRIVATE
  node_type *doubleLeftRotate(node_type *k3) {
    k3->right = singleRightRotate(k3->right);
    return singleLeftRotate(k3);
  }

  // TODO: ?? PRIVATE
  node_type *doubleRightRotate(node_type *k3) {
    k3->left = singleLeftRotate(k3->left);
    return singleRightRotate(k3);
  }

  // Recursive member function to return the minimum node in the tree
  // This function simply return the leftmost node in the tree
  node_type *findMin(node_type *node) {
    if (node == NULL)
      return NULL;
    else if (node->left == NULL)
      return node;
    else
      return findMin(node->left);
  }

  // Recursive member function to return the maximum node in the tree
  // This function simply returns the rightmost node in the tree
  node_type *findMax(node_type *node) {
    if (node == NULL)
      return NULL;
    else if (node->right == NULL)
      return node;
    else
      return findMax(node->right);
  }

  // Recursive deallocate all nodes in the tree
  void clear(node_type *node) {
    if (node != NULL) {
      clear(node->left);
      clear(node->right);
      _alloc.deallocate(node, 1);
    }
  }

  // Return the height of node
  int height(node_type *node) {
    return (node == NULL ? -1 : node->height);
  }

  // Return the balance factor of node
  int getBalance(node_type *node) {
    if (node == NULL)
      return 0;
    else
      return height(node->left) - height(node->right);
  }







// ********************************************************************************************
// ********************************************************************************************
// *************************************** Member variables ***********************************
 private:

  key_compare _comp;

  node_type *_root;

  allocator_type _alloc;

// ********************************************************************************************
// ********************************************************************************************
// *************************************** Member Functions ***********************************

};
}

#endif //FT_CONTAINERS_AVL_HPP
