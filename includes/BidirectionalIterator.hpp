//
// Created by Anderson Porto on 11/12/22.
//

#ifndef FT_CONTAINERS_BIDIRECTIONALITERATOR_HPP
#define FT_CONTAINERS_BIDIRECTIONALITERATOR_HPP

#include "ft_iterator_base.hpp"
#include "Tree/AVL.hpp"

namespace ft {

// Random-access iterators are iterators that can be used to access elements at an arbitrary
// offset position relative to the element they point to, offering the same functionality as pointers.
template<typename T, class compare, class allocator>
class BidirectionalIterator {
  // **********************************************************************************************
  // **********************************************************************************************
  // *************************************** Member types *****************************************
 public:

//  typedef std::ptrdiff_t difference_type;

//  typedef std::bidirectional_iterator_tag iterator_category;

  typedef T value_type;

  typedef T *pointer;

  typedef T &reference;

  typedef Node<value_type, allocator> node_type;

  typedef const AVL<T, compare, allocator> const_avl;

  // *********************************************************************************************
  // *********************************************************************************************
  // *************************************** Member functions ************************************
  BidirectionalIterator() : _ptr(NULL) {}

  BidirectionalIterator(pointer ptr, const_avl *avl) : _ptr(ptr), _avl(avl) {}

  BidirectionalIterator(const BidirectionalIterator &copy) : _ptr(copy._ptr), _avl(copy._avl) {}

  BidirectionalIterator &operator=(const BidirectionalIterator &other) {
    if (this != &other) {
      this->_ptr = other._ptr;
      this->_avl = other._avl;
    }
    return *this;
  }

  ~BidirectionalIterator() {}

  // *********************************************************************************************
  // *********************************************************************************************
  // *************************************** Member Operators ************************************

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
    node_type *node = this->_avl->find(this->_ptr);

    if (node) {
      _ptr = this->_avl->next(node)->data;
    }
    return *this;
  }

  BidirectionalIterator operator++(int) {
    BidirectionalIterator tmp(*this);

    ++(*this);
    return tmp;
  }

  BidirectionalIterator &operator--() { //TODO: Check if it is correct
    node_type *node = this->_avl->find(this->_ptr);

    if (node) {
      _ptr = this->_avl->prev(node)->data;
    }
    return *this;
  }

  BidirectionalIterator operator--(int) {
    BidirectionalIterator tmp(*this);

    --(*this);
    return tmp;
  }

  // *********************************************************************************************
  // *********************************************************************************************
  // *************************************** Member Variables ************************************
 private:
  pointer _ptr;

  const_avl *_avl;

};
};

#endif //FT_CONTAINERS_BIDIRECTIONALITERATOR_HPP
