//
// Created by Anderson Porto on 10/17/22.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "IteratorVector.hpp"

namespace ft {
template<class T, class Allocator = std::allocator<T> >
class vector {
// ****************** Member types ******************

 public:
  typedef typename Allocator::reference reference;

  typedef typename Allocator::const_reference const_reference;

  typedef std::size_t size_type;

  typedef std::ptrdiff_t difference_type;

  typedef T value_type;

  typedef Allocator allocator_type;

  typedef typename Allocator::pointer pointer;

  typedef typename Allocator::const_pointer const_pointer;

  typedef ft::random_access_iterator<value_type> iterator;

  typedef ft::random_access_iterator<const value_type> const_iterator;

  // TODO: Implement iterator
  //  typedef std::reverse_iterator<iterator> reverse_iterator;
  //  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

// ****************** Member functions ******************
 public:

  // default constructor without parameters
  vector() : _size(0), _capacity(0), _allocator(Allocator()) {
    _data = NULL;
  }

  // default constructor with allocator parameter
  explicit vector(const allocator_type &alloc) : _size(0), _capacity(0), _allocator(alloc) {
    _data = NULL;
  }

  // fill constructor
  explicit vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type())
      : _size(n), _capacity(n), _allocator(alloc) {

    _data = _allocator.allocate(_capacity);
    for (size_type i = 0; i < _size; i++) {
      _allocator.construct(_data + i, val);
    }
  }



// ***********************************************************************************************//
// ***********************************************************************************************//
// ***********************************************************************************************//
// ***********************************************************************************************//
 private:

  //  size of the custom vector (number of elements)
  size_type _size;

  // number of elements that the vector can hold without requiring reallocation.
  size_type _capacity;

  //  pointer to the first element of the vector
  pointer _data;

  //  allocator object
  allocator_type _allocator;
};

}

#endif //FT_CONTAINERS_VECTOR_HPP
