//
// Created by Anderson Porto on 11/12/22.
//

#ifndef FT_CONTAINERS_ITERATORMAP_HPP
#define FT_CONTAINERS_ITERATORMAP_HPP

#include "ft_iterator_base.hpp"
#include "Tree/Node.hpp"

namespace ft {

// Random-access iterators are iterators that can be used to access elements at an arbitrary
// offset position relative to the element they point to, offering the same functionality as pointers.
template<typename T, class compare, class allocator>
class bidirectional_iterator {
  // **********************************************************************************************
  // **********************************************************************************************
  // *************************************** Member types *****************************************
 public:

  typedef T value_type;

  typedef T *pointer;

  typedef T &reference;

  typedef std::ptrdiff_t difference_type;

  typedef std::bidirectional_iterator_tag iterator_category;

  // *********************************************************************************************
  // *********************************************************************************************
  // *************************************** Member functions ************************************
 public:
  bidirectional_iterator() : _ptr(NULL) {}


  // *********************************************************************************************
  // *********************************************************************************************
  // *************************************** Member Variables ************************************

 private:
  pointer _ptr;
};

};
}

#endif //FT_CONTAINERS_ITERATORMAP_HPP
