//
// Created by Anderson Porto on 10/17/22.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <iostream>

namespace ft {
template<class T, class Allocator = std::allocator<T> >
class vector {
 public:
  typedef typename Allocator::reference reference;

  typedef typename Allocator::const_reference const_reference;

  typedef std::size_t size_type;

  typedef std::ptrdiff_t difference_type;

  typedef T value_type;

  typedef Allocator allocator_type;

  typedef typename Allocator::pointer pointer;

  typedef typename Allocator::const_pointer const_pointer;

  // TODO: Implement iterator

  //  typedef implementation defined iterator;
  //  typedef implementation defined const_iterator;
//  typedef std::reverse_iterator<iterator> reverse_iterator;
//  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

// ***********************************************************************************************//
// ***********************************************************************************************//
// ***********************************************************************************************//
// ***********************************************************************************************//
 public:

  // construct / copy / destroy:
  vector() : _size(0), _capacity(0), _allocator(Allocator()) {
    _data = NULL;
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
