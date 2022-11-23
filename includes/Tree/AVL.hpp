//
// Created by Anderson Porto on 11/10/22.
//

#ifndef FT_CONTAINERS_AVL_HPP
#define FT_CONTAINERS_AVL_HPP

#include <cstddef>
#include "Node.hpp"

enum BalanceFactor {
  LEFT_HEAVY = -1,
  RIGHT_HEAVY = 1
};

namespace ft {
template<
    typename T,
    class compare,
    class allocator
>
class AVL {
 public:
  // *********************************************************************************************
  // *********************************************************************************************
  // *************************************** Member types ****************************************
  typedef T value_type;

  typedef Node<value_type, allocator> node_type;

  typedef node_type *node_pointer;

  typedef compare key_compare;

  typedef allocator allocator_type;

  // ********************************************************************************************
  // ********************************************************************************************
  // *************************************** Member functions ***********************************
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

  ~AVL() {}

  // Assigns all nodes
  void assign(const node_type &node) {
    if (node) {
      assign(node->left);
      if (node.data) {
        insert(node.data);
      }
      assign(node->right);
    }
  }

  // Insert a node
  node_type *insert(value_type value) {
    this->_root = insertNode(this->_root, value);
    return this->_root;
  }

  // Find a given value
  node_type *find(node_type *node, const value_type &value) const {
    if (node == NULL) {
      return NULL;
    }

    if (this->_comp(value, node->data)) {
      return find(node->left, value);
    } else if (this->_comp(node->data, value)) {
      return find(node->right, value);
    } else {
      return node;
    }
  }

  // Return the next of a given node
  node_type *next(node_type *node) const {
    if (node == NULL) {
      return NULL;
    }

    if (node->right != NULL) {
      return min(node->right);
    }

    node_type *parent = node->parent;

    while (parent != NULL && node == parent->right) {
      node = parent;
      parent = parent->parent;
    }
    return parent;
  }

  // Return the previous of a given node
  node_type *prev(node_type *node) const {
    if (node == NULL) {
      return NULL;
    }

    if (node->left != NULL) {
      return max(node->left);
    }

    node_type *parent = node->parent;
    while (parent != NULL && node == parent->left) {
      node = parent;
      parent = parent->parent;
    }
    return parent;
  }

  // Erase the root node
  bool eraseRoot(value_type &value) {
    if (find(this->_root, value) == NULL) {
      return false;
    } else {
      this->_root = eraseNode(this->_root, value);
      return true;
    }
  }

  // Erase a given node from last to the root node
  node_type *eraseNode(node_type *node, const value_type &value) {
    if (node == NULL) {
      return node;
    }

    if (this->_comp(value, node->data)) {
      node->left = eraseNode(node->left, value);
    } else if (this->_comp(node->data, value)) {
      node->right = eraseNode(node->right, value);
    } else {
      if (node->left == NULL || node->right == NULL) {
        node_type *temp = node->left ? node->left : node->right;

        if (temp == NULL) {
          temp = node;
          node = NULL;
        } else {
          *node = *temp;
        }
        _alloc.deallocate(temp, 1);

      } else {
        node_type *temp = min(node->right);

        node->data = temp->data;
        node->right = eraseNode(node->right, temp->data);
      }
    }
    return balance(node, value);
  }

 private:
  // ********************************************************************************************
  // ********************************************************************************************
  // *************************************** Member variables ***********************************

  key_compare _comp;

  node_type *_root;

  allocator_type _alloc;

  // ********************************************************************************************
  // ********************************************************************************************
  // *************************************** Member Functions ***********************************

  // Get the height of a given node
  int getNodeHeight(node_pointer node) {
    if (node) {
      return node->height;
    }
    return 0;
  }

  // Update the height of a given node
  void updateNodeHeight(node_pointer node) {
    node->height = 1 + max(getNodeHeight(node->left), getNodeHeight(node->right));
  }

  // Right rotation of a given node
  node_type *rotateRight(node_type *node) {
    node_type *left = node->left;
    node_type *leftRight = left->right;

    left->right = node;
    node->left = leftRight;

    updateNodeHeight(node);
    updateNodeHeight(left);

    return left;
  }

  // Left rotation of a given node
  node_type *rotateLeft(node_type *node) {
    node_type *right = node->right;
    node_type *rightLeft = right->left;

    right->left = node;
    node->right = rightLeft;

    updateNodeHeight(node);
    updateNodeHeight(right);

    return right;
  }

  // Create a new node with a given value
  node_type *fromValue(const value_type &value) {
    node_type *node = _alloc.allocate(1);

    _alloc.construct(node, value);
    return node;
  }

  // Get the balance factor of a given node
  BalanceFactor unbalancedTree(const node_pointer node) {
    if (node) {
      int leftHeight = getNodeHeight(node->left);
      int rightHeight = getNodeHeight(node->right);

      if (leftHeight - rightHeight > 1) {
        return LEFT_HEAVY;
      } else if (rightHeight - leftHeight > 1) {
        return RIGHT_HEAVY;
      }
    }
  }

  // Balance a branch of a given node
  node_type *balance(node_type *node, const value_type &value) {
    if (unbalancedTree(node) == LEFT_HEAVY) {
      if (_comp(value, node->left->value)) {
        node = rotateRight(node);
      } else {
        node->left = rotateLeft(node->left);
        node = rotateRight(node);
      }
    } else if (unbalancedTree(node) == RIGHT_HEAVY) {
      if (_comp(node->right->value, value)) {
        node = rotateLeft(node);
      } else {
        node->right = rotateRight(node->right);
        node = rotateLeft(node);
      }
    }
  }

  // Insert a new node in the tree and balance it
  node_type *insertNode(node_type *node, const value_type &value) {
    // If the tree is empty, create a new node
    if (!node) {
      return fromValue(value);
    }

    // Comp is a function object that returns true if the first argument is less than the second
    if (_comp(value, node->value)) {
      node->left = insertNode(node->left, value);
    } else if (_comp(node->value, value)) {
      node->right = insertNode(node->right, value);
    } else {
      return node;
    }

    // Update the height of the node
    updateNodeHeight(node);

    // Balance the tree if it is unbalanced
    return balance(node, value);
  }

  // Find minimum value in the tree
  // basically the left most node
  node_type *minNode(node_type *node) const {
    if (node == NULL) {
      return NULL;
    }

    if (node->left == NULL) {
      return node;
    }

    return minNode(node->left);
  }

  // Find maximum value in the tree
  // basically the right most node
  node_type *maxNode(node_type *node) const {
    if (node == NULL) {
      return NULL;
    }

    if (node->right == NULL) {
      return node;
    }

    return maxNode(node->right);
  }

};
}

#endif //FT_CONTAINERS_AVL_HPP
