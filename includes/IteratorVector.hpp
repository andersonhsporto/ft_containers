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

};
};

#endif //FT_CONTAINERS_ITERATORVECTOR_HPP
