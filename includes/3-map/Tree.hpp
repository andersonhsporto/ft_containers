//
// Created by Anderson Porto on 12/10/22.
//

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

#include "Node.hpp"

namespace ft {

template<typename T, class Compare, class Alloc>
struct Tree {
  typedef T value_type;

  typedef Compare key_compare;

  typedef Alloc allocator_type;

  typedef Node<value_type, Alloc> node_type;

  typename Alloc::template rebind<node_type>::other rebind_alloc;

  node_type *root;

  Tree() : root(NULL) {}

  Tree(const Tree &copy) : root(NULL) {
    *this = copy;
  }

  Tree &operator=(const Tree &copy) {
    if (this != &copy) {
      root = copy.root;
      _comp = copy._comp;
    }
    return *this;
  }

  ~Tree() {}

  void assign(const node_type *node) {
    if (node) {
      assign(node->left);
      if (node->data)
        insert(*node->data);
      assign(node->right);
    }
  }

  node_type *insert(value_type key) {
    return insert(root, key);
  }

  node_type *insert(node_type *node, const value_type &key) {
    if (node == NULL) {
      return (_makeNode(key));
    }

    if (_comp(key.first, node->data->first)) {
      node->left = insert(node->left, key);
      node->left->parent = node;
    } else if (_comp(node->data->first, key.first)) {
      node->right = insert(node->right, key);
      node->right->parent = node;
    } else
      return (node);
    _updateHeight(node);
    return (_balance(node, key));
  }

  node_type *getNode(node_type *node, value_type const &key) const {
    if (!node)
      return (NULL);

    if (node->data && node->data->first == key.first)
      return (node);

    if (_comp(key.first, node->data->first))
      return (getNode(node->left, key));
    else if (_comp(node->data->first, key.first))
      return (getNode(node->right, key));
    return (node);
  }

  node_type *getMinNode(node_type *node) const {
    if (!node)
      return (NULL);
    if (!node->left)
      return (node);
    return (getMinNode(node->left));
  }

  node_type *getMaxNode(node_type *node) const {
    if (!node)
      return (NULL);
    if (!node->right)
      return (node);
    return (getMaxNode(node->right));
  }

  bool deleteNodeByKey(value_type const &key) {
    if (getNode(root, key)) {
      root = deleteNode(root, key);
      return true;
    } else
      return false;
  }

  node_type *getNextNode(value_type const &key) const {
    node_type *node = getNode(root, key);
    if (!node)
      return (NULL);
    if (node->right)
      return (getMinNode(node->right));

    node_type *parent = node->parent;
    while (parent && node == parent->right) {
      node = parent;
      parent = parent->parent;
    }
    return (parent);
  }

  node_type *getPrevNode(value_type const &key) const {
    node_type *node = getNode(root, key);
    if (!node)
      return (NULL);
    if (node->left)
      return (getMaxNode(node->left));

    node_type *parent = node->parent;
    while (parent && node == parent->left) {
      node = parent;
      parent = parent->parent;
    }
    return (parent);
  }

  void clear() {
    clear(root);
  }

 private:

  key_compare _comp;

  allocator_type _alloc;


// #############################################################################################
// ######################################### PRIVATE METHODS ####################################
// #############################################################################################

  node_type *_makeNode(const value_type &key) {
    node_type *newNode = rebind_alloc.allocate(1);

    rebind_alloc.construct(newNode, key);
    return newNode;
  }

  node_type *_balance(node_type *node, value_type const &key) {
    if ((node->left->getHeight() - node->right->getHeight()) > 1) {
      if (_comp(key.first, node->left->data->first))
        return (_rotateRight(node));
      else {
        node->left = _rotateLeft(node->left);
        return (_rotateRight(node));
      }
    }
    if (node->left->getHeight() - node->right->getHeight() < -1) {
      if (_comp(node->right->data->first, key.first))
        return (_rotateLeft(node));
      else {
        node->left = _rotateRight(node->left);
        return (_rotateLeft(node));
      }
    }
    return (node);
  }

  node_type *_rotateRight(node_type *z) {
    node_type *y = z->left;    // set y

    if (!y)
      return (z);
    node_type *T3 = y->right;    // save for z->left

    if (y->right != NULL)
      y->right->parent = z;        //	y->parent is z, everything is set to rotate
    y->right = z;
    z->left = T3;
    y->parent = z->parent;
    z->parent = y;
    _updateHeight(z);
    _updateHeight(y);
    return (y);
  }

  node_type *_rotateLeft(node_type *z) {
    node_type *y = z->right;    // set y

    if (!y)
      return (z);
    node_type *T2 = y->left;    // save for z->left

    if (y->left != NULL)
      y->left->parent = z;        //	y->parent is z, everything is set to rotate
    y->left = z;
    z->right = T2;
    y->parent = z->parent;
    z->parent = y;
    _updateHeight(z);
    _updateHeight(y);
    return (y);
  }

  void _updateHeight(node_type *node) {
    node->height = std::max(node->left->getHeight(), node->right->getHeight()) + 1;
  }

  void _deallocNode(node_type *node) {
    if (node) {
      _alloc.deallocate(node->data, 1);
      rebind_alloc.deallocate(node, 1);
    }
  }

  node_type *deleteNode(node_type *node, value_type const &key) {
    if (node == NULL)
      return (NULL);

    if (_comp(key.first, node->data->first))
      node->left = deleteNode(node->left, key);
    else if (_comp(node->data->first, key.first))
      node->right = deleteNode(node->right, key);
    else if (node->data->first == key.first) {
      if (!node->left || !node->right) {
        node_type *child = node->left ? node->left : node->right;

        if (!child) {
          child = node;
          node = NULL;
        } else {
          node_type *nodeParent = node->parent;
          *node = *child;
          node->parent = nodeParent;
        }
        _deallocNode(child);
      } else {
        node_type *minNode = getMinNode(node->right);                //(3)
        _alloc.construct(node->data, *minNode->data);
        node->right = del(node->right, *minNode->data);
      }

      if (!node)
        return (node);

      _updateHeight(node);
      return _balance(node, key);
    }

  }

  void clear(node_type *node) {
    if (node) {
      clear(node->left);
      clear(node->right);
      _deallocNode(node);
      node = NULL;
    }
  }

};
}

#endif //FT_CONTAINERS_TREE_HPP
