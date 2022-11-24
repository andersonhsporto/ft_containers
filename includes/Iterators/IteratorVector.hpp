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

// *************************************************************************************************
// *************************************************************************************************
// *************************************************************************************************
// *************************************************************************************************


// Iterator adapter that reverses the order the direction of a given iterator.
template<class Iterator>
class reverse_iterator {
  // ****************** Member types ******************
 public:
  typedef Iterator iterator_type;

  typedef typename iterator_traits<Iterator>::iterator_category iterator_category;

  typedef typename iterator_traits<Iterator>::value_type value_type;

  typedef typename iterator_traits<Iterator>::difference_type difference_type;

  typedef typename iterator_traits<Iterator>::pointer pointer;

  typedef typename iterator_traits<Iterator>::reference reference;

  // ****************** Member functions ******************
 public:
  // Default constructor
  reverse_iterator() {}

  // Parametric constructor
  reverse_iterator(iterator_type it) : _it(it) {}

  // Copy constructor
  reverse_iterator(const reverse_iterator &other) : _it(other._it) {}

  // Destructor
  ~reverse_iterator() {}

  template<class Iter>
  reverse_iterator(const reverse_iterator<Iter> &other) : _it(other.base()) {}

  iterator_type base() const { return _it; }

  reference operator*() const {
    iterator_type tmp = _it;
    return *--tmp;
  }

  pointer operator->() const { return &(operator*()); }

  reference operator[](difference_type n) const { return *(*this + n); }

  reverse_iterator &operator++() {
    --_it;
    return *this;
  }

  reverse_iterator operator++(int) {
    reverse_iterator tmp(*this);
    --_it;
    return tmp;
  }

  reverse_iterator &operator+=(difference_type n) {
    _it -= n;
    return *this;
  }

  reverse_iterator &operator+(difference_type n) {
    reverse_iterator tmp(*this);
    tmp += n;
    return tmp;
  }

  reverse_iterator &operator--() {
    ++_it;
    return *this;
  }

  reverse_iterator operator--(int) {
    reverse_iterator tmp(*this);
    ++_it;
    return tmp;
  }

  reverse_iterator &operator-=(difference_type n) {
    _it += n;
    return *this;
  }

  reverse_iterator &operator-(difference_type n) {
    reverse_iterator tmp(*this);
    tmp -= n;
    return tmp;
  }

  // ****************** Member variables ******************
 private:
  iterator_type _it;
};

// *************************************************************************************************
template<class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
                                     const reverse_iterator<Iterator> &it) {
  return it + n;
}

template<class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs,
                                                               const reverse_iterator<Iterator> &rhs) {
  return rhs.base() - lhs.base();
}

template<class Iterator>
bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
  return lhs.base() == rhs.base();
}

template<class Iterator>
bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
  return !(lhs == rhs);
}

template<class Iterator>
bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
  return lhs.base() > rhs.base();
}

template<class Iterator>
bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
  return lhs <= rhs;
}

template<class Iterator>
bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
  return lhs.base() < rhs.base();
}

template<class Iterator>
bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
  return lhs.base() <= rhs.base();
}

};

#endif //FT_CONTAINERS_ITERATORVECTOR_HPP
