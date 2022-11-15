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
//    clear(); TODO: ADD CLEAR FUNCTION
  }

  // ********************************************************************************************
  // ********************************************************************************************
  // *************************************** Member Functions ***********************************


  // Insert a new node in the tree
  node_pointer  insert(node_pointer old_node, value_type value) {
    if (old_node == NULL) {
      return new node_type(value);
    }
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
