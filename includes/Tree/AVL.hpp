//
// Created by Anderson Porto on 11/10/22.
//

#ifndef FT_CONTAINERS_AVL_HPP
#define FT_CONTAINERS_AVL_HPP

#include <cstddef>
#include "Node.hpp"

enum BalanceFactor {
  LEFT_HEAVY = -1,
  RIGHT_HEAVY = 1,
  BALANCED = 0
};

namespace ft {
template<
    typename T,
    class compare,
    class allocator
>
class AVL {
 public:

  /* ###############################################################################################
   * #########################################  Member Types  ######################################
   * ###############################################################################################
   */

  typedef T value_type;

  typedef compare key_comparator;

  typedef allocator allocator_type;

  typedef Node<value_type, allocator_type> node_type;

  /* ###############################################################################################
   * #########################################  Public Variables  ##################################
   * ###############################################################################################
   */

  node_type *root;

  // Rebind allocator to type T -> this is used to allocate memory for the nodes
  // provides a way to obtain an allocator for a different type.
  typedef typename allocator_type::template rebind<node_type>::other node_allocator_type;

  /* ###############################################################################################
   * #########################################  Constructors  ######################################
   * ###############################################################################################
   */

  // Empty Constructor -> creates an empty AVL tree
  AVL() : root(NULL) {}

  // Copy Constructor -> creates a copy of the AVL tree
  AVL(const AVL &avl) {
    root = copy(avl.root);
  }

  // Assignment Operator -> assigns the AVL tree
  AVL &operator=(const AVL &source) {
    if (this != &source) {
      root = source.root;
      _comparator = source._comparator;
    }
    return *this;
  }

  // Destructor -> destroys the AVL tree
  ~AVL() {
//        clear();
  }

  /* ###############################################################################################
   * #########################################  Public Functions  ##################################
   * ###############################################################################################
   */

  node_type *rotateLeft(node_type *x) {
    node_type *y = x->right;
    node_type *T2 = y->left;

    // Perform rotation
    if (y->left) {
      y->left->parent = x;
    }

    // Perform rotation
    y->left = x;
    x->right = T2;

    y->parent = x->parent;
    x->parent = y;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    // Return new root
    return y;
  }

  node_type *rotateRight(node_type *y) {
    node_type *x = y->left;
    node_type *T2 = x->right;

    // Perform rotation
    if (x->right) {
      x->right->parent = y;
    }

    // Perform rotation
    x->right = y;
    y->left = T2;

    x->parent = y->parent;
    y->parent = x;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    // Return new root
    return x;
  }

  int getHeight(node_type *node) {
    return node ? node->height : 0;
  }

  BalanceFactor getBalanceFactor(node_type *node) {
    if (node) {
      int leftHeight = getHeight(node->left);
      int rightHeight = getHeight(node->right);
      int balanceFactor = leftHeight - rightHeight;

      if (balanceFactor == LEFT_HEAVY) {
        return LEFT_HEAVY;
      } else if (balanceFactor == RIGHT_HEAVY) {
        return RIGHT_HEAVY;
      }
    } else {
      return BALANCED;
    }
  }

  node_type *balance(node_type *node, value_type const &value) {
    if (getBalanceFactor(node) == LEFT_HEAVY) {
      if (getBalanceFactor(node->left) == RIGHT_HEAVY) {
        node->left = rotateLeft(node->left);
      }
      return rotateRight(node);
    } else if (getBalanceFactor(node) == RIGHT_HEAVY) {
      if (getBalanceFactor(node->right) == LEFT_HEAVY) {
        node->right = rotateRight(node->right);
      }
      return rotateLeft(node);
    }
    return node;
  }

  // Factory to create a new node
  node_type *fromValue(const value_type &value) {
    node_type *node = node_allocator_type().allocate(1);

    node_allocator_type().construct(node, node_type(value));
    return node;
  }

  node_type *insert(value_type const &value) {
    this->root = insert(this->root, value);
    return this->root;
  }

  node_type *insert(node_type *node, const value_type &value) {
    if (!node) {
      return fromValue(value);
    }

    if (_comparator(value.first, node->data->first)) {
      node->left = insert(node->left, value);
      node->left->parent = node;
    } else if (_comparator(node->data->first, value.first)) {
      node->right = insert(node->right, value);
      node->right->parent = node;
    } else {
      return node;
    }
  }

  node_type *find(node_type *node, const value_type &value) {
    if (!node) {
      return NULL;
    }

    if (_comparator(value.first, node->data->first)) {
      return find(node->left, value);
    } else if (_comparator(node->data->first, value.first)) {
      return find(node->right, value);
    } else {
      return node;
    }
  }

  node_type *minNode(node_type *node) {
    node_type *current = node;

    if (current->left == NULL) {
      return current;
    }

    return minNode(current->left);
  }

  node_type *maxNode(node_type *node) {
    node_type *current = node;

    if (current->right == NULL) {
      return current;
    }

    return maxNode(current->right);
  }

  node_type *next(value_type const &value) {
    node_type *node = find(root, value);

    if (!node) {
      return NULL;
    }

    if (node->right) {
      return minNode(node->right);
    }

    node_type *parent = node->parent;
    while (parent && node == parent->right) {
      node = parent;
      parent = parent->parent;
    }
    return parent;
  }

  node_type *prev(value_type const &value) {
    node_type *node = find(root, value);

    if (!node) {
      return NULL;
    }

    if (node->left) {
      return maxNode(node->left);
    }

    node_type *parent = node->parent;
    while (parent && node == parent->left) {
      node = parent;
      parent = parent->parent;
    }
    return parent;
  }

  bool delRoot(value_type value) {
    if (find(root, value)) {
      root = del(root, value);
      return true;
    } else {
      return false;
    }
  }

//  node_type *del(node_type *node, value_type const &value) {
//
//  }


 private:
  key_comparator _comparator;

  allocator_type _allocator;

  // Update Height of a node
  void updateHeight(node_type *node) {
    node->height = 1 + std::max(height(node->left), height(node->right));
  }

};

}

#endif //FT_CONTAINERS_AVL_HPP
