//
// Created by Anderson Porto on 10/20/22.
//

#ifndef FT_CONTAINERS_ITERATORVECTOR_HPP
#define FT_CONTAINERS_ITERATORVECTOR_HPP

#include "ft_iterator_base.hpp"

namespace ft {

// Random-access iterators are iterators that can be used to access elements at an arbitrary
// offset position relative to the element they point to, offering the same functionality as pointers.
template<typename T>
class random_access_iterator {
  // ****************** Member types ******************
 public:
  typedef T value_type;

  typedef T *pointer;

  typedef T &reference;

  typedef std::ptrdiff_t difference_type;

  typedef std::random_access_iterator_tag iterator_category;

  // ****************** Member functions ******************
 public:
  // Default constructor
  random_access_iterator() : _ptr(NULL) {}

  // Constructor
  explicit random_access_iterator(pointer ptr) : _ptr(ptr) {}

  // Copy constructor
  random_access_iterator(const random_access_iterator &other) : _ptr(other._ptr) {}

  // Destructor
  ~random_access_iterator() {}

  // Copy assignment operator
  random_access_iterator &operator=(const random_access_iterator &other) {
    if (this != &other) {
      _ptr = other._ptr;
    }
    return *this;
  }

  // underlying base iterator.
  pointer base() const { return _ptr; }

  // Equality operator
  bool operator==(const random_access_iterator<T> &other) const { return _ptr == other._ptr; }

  // Inequality operator
  bool operator!=(const random_access_iterator<T> &other) const { return _ptr != other._ptr; }

  // Dereference operator
  reference operator*() const { return *_ptr; }

  // Dereference operator
  pointer operator->() const { return _ptr; }

  // Prefix increment operator
  random_access_iterator &operator++() {
    ++_ptr;
    return *this;
  }

  // Postfix increment operator
  random_access_iterator operator++(int) {
    random_access_iterator tmp(*this);
    ++_ptr;
    return tmp;
  }

  // Prefix decrement operator
  random_access_iterator &operator--() {
    --_ptr;
    return *this;
  }

  // Postfix decrement operator
  random_access_iterator operator--(int) {
    random_access_iterator tmp(*this);
    --_ptr;
    return tmp;
  }

  // Addition assignment operator
  random_access_iterator &operator+=(difference_type n) {
    _ptr += n;
    return *this;
  }

  // Subtraction assignment operator
  random_access_iterator &operator-=(difference_type n) {
    _ptr -= n;
    return *this;
  }

  // Addition operator
  random_access_iterator operator+(difference_type n) const {
    random_access_iterator tmp(*this);
    tmp += n;
    return tmp;
  }

  // Subtraction operator
  random_access_iterator operator-(difference_type n) const {
    random_access_iterator tmp(*this);
    tmp -= n;
    return tmp;
  }

  // Comparison operator
  bool operator<(const random_access_iterator<T> &other) const { return _ptr < other._ptr; }

  // Comparison operator
  bool operator>(const random_access_iterator<T> &other) const { return _ptr > other._ptr; }

  // Comparison operator
  bool operator<=(const random_access_iterator<T> &other) const { return _ptr <= other._ptr; }

  // Comparison operator
  bool operator>=(const random_access_iterator<T> &other) const { return _ptr >= other._ptr; }


// ****************** Member variables ******************
 private:
  pointer _ptr;
};

// Addition operator
template<typename T>
random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n,
                                    const random_access_iterator<T> &it) {
  return it + n;
}

// Subtraction operator
template<typename T>
typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T> &lhs,
                                                              const random_access_iterator<T> &rhs) {
  return lhs.base() - rhs.base();
}

};

#endif //FT_CONTAINERS_ITERATORVECTOR_HPP
