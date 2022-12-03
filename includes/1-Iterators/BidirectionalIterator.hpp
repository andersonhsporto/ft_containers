//
// Created by Anderson Porto on 11/12/22.
//

#ifndef FT_CONTAINERS_BIDIRECTIONALITERATOR_HPP
#define FT_CONTAINERS_BIDIRECTIONALITERATOR_HPP

#include "../2-Tree/Tree.hpp"
#include "../ft_iterator_base.hpp"

namespace ft {

// Random-access iterators are iterators that can be used to access elements at an arbitrary
// offset position relative to the element they point to, offering the same functionality as pointers.
template<typename T, class compare, class allocator>
class BidirectionalIterator {
  // **********************************************************************************************
  // **********************************************************************************************
  // *************************************** Member types *****************************************
 public:

  typedef std::ptrdiff_t difference_type;

  typedef T value_type;

  typedef T *pointer;

  typedef T &reference;

  typedef Node<value_type, allocator> node_type;

  typedef std::bidirectional_iterator_tag iterator_category;

  typedef const Tree<T, compare, allocator> const_tree;

  // *********************************************************************************************
  // *********************************************************************************************
  // *************************************** Member functions ************************************
  BidirectionalIterator() : _ptr(NULL) {}

  explicit BidirectionalIterator(pointer ptr, const_tree *avl = NULL) : _ptr(ptr), _tree(avl) {}

  BidirectionalIterator(const BidirectionalIterator &copy) {
    *this = copy;
  }

  BidirectionalIterator &operator=(const BidirectionalIterator &other) {
    if (this != &other) {
      this->_ptr = other._ptr;
      this->_tree = other._tree;
    }
    return *this;
  }

  ~BidirectionalIterator() {}

  // *********************************************************************************************
  // *********************************************************************************************
  // *************************************** Member Operators ************************************

  operator BidirectionalIterator<const T, compare, allocator>(void) const {
    return BidirectionalIterator<const T, compare, allocator>(_ptr, reinterpret_cast<Tree<const value_type,
                                                              compare,
                                                              allocator> const*>(_tree));
  }

  bool operator==(const BidirectionalIterator &other) const {
    return this->_ptr == other._ptr;
  }

  bool operator!=(const BidirectionalIterator &other) const {
    return this->_ptr != other._ptr;
  }

  reference operator*() const {
    return *this->_ptr;
  }

  pointer operator->() const {
    return this->_ptr;
  }

  BidirectionalIterator &operator++() {
    node_type *node = _tree->find(_tree->root, *_ptr);

    if (node) {
      _ptr = _tree->next(*_ptr)->data;
    }
    return *this;
  }

  BidirectionalIterator operator++(int) {
    BidirectionalIterator temp(*this);

    ++(*this);
    return temp;
  }

  BidirectionalIterator &operator--() {
    node_type *node = _tree->find(_tree->root, *_ptr);

    if (node) {
      _ptr = _tree->previous(*_ptr)->data;
    }
    return *this;
  }

  BidirectionalIterator operator--(int) {
    BidirectionalIterator temp(*this);

    --(*this);
    return temp;
  }

  // *********************************************************************************************
  // *********************************************************************************************
  // *************************************** Member Variables ************************************
 private:
  pointer _ptr;

  const_tree *_tree;

};
};

#endif //FT_CONTAINERS_BIDIRECTIONALITERATOR_HPP
