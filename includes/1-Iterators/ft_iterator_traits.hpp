//
// Created by Anderson Porto on 10/28/22.
//

#ifndef FT_CONTAINERS_ITERATORTRAITS_HPP
#define FT_CONTAINERS_ITERATORTRAITS_HPP

#include <cstddef>
#include <iostream>

namespace ft {
template<typename Iterator>
struct iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;

  typedef typename Iterator::value_type value_type;

  typedef typename Iterator::difference_type difference_type;

  typedef typename Iterator::pointer pointer;

  typedef typename Iterator::reference reference;
};

// Interface class for iterator
template<class T>
struct iterator_traits<T *> {
  typedef std::random_access_iterator_tag iterator_category;

  typedef T value_type;

  typedef ptrdiff_t difference_type;

  typedef T *pointer;

  typedef T &reference;
};

// Parcial specialization for const pointer types
template<class T>
struct iterator_traits<const T *> {
  typedef std::random_access_iterator_tag iterator_category;

  typedef T value_type;

  typedef ptrdiff_t difference_type;

  typedef const T *pointer;

  typedef const T &reference;
};

}

#endif //FT_CONTAINERS_ITERATORTRAITS_HPP
