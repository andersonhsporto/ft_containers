//
// Created by Anderson Porto on 10/28/22.
//

#ifndef FT_CONTAINERS_ITERATORTRAITS_HPP
#define FT_CONTAINERS_ITERATORTRAITS_HPP

#include <cstddef>
#include <iostream>

namespace ft {
template<typename Iterator>
class iterator_traits {
 public:
  typedef typename Iterator::iterator_category iterator_category;

  typedef typename Iterator::value_type value_type;

  typedef typename Iterator::difference_type difference_type;

  typedef typename Iterator::pointer pointer;

  typedef typename Iterator::reference reference;
};

// Parcial specialization for pointer types
template<class T>
class iterator_traits<T *> {
 public:
  typedef std::random_access_iterator_tag iterator_category;

  typedef T value_type;

  typedef ptrdiff_t difference_type;

  typedef T *pointer;

  typedef T &reference;
};

// Parcial specialization for const pointer types
template<class T>
class iterator_traits<const T *> {
 public:
  typedef std::random_access_iterator_tag iterator_category;

  typedef T value_type;

  typedef ptrdiff_t difference_type;

  typedef const T *pointer;

  typedef const T &reference;
};

}

#endif //FT_CONTAINERS_ITERATORTRAITS_HPP
