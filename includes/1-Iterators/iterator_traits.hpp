//
// Created by Anderson Porto on 10/28/22.
//

#ifndef FT_CONTAINERS_ITERATORTRAITS_HPP
#define FT_CONTAINERS_ITERATORTRAITS_HPP

#include <cstddef>
#include <iterator>

namespace ft {

template<class Iterator>
class iterator_traits {
 public:
  typedef typename Iterator::difference_type difference_type;

  typedef typename Iterator::value_type value_type;

  typedef typename Iterator::pointer pointer;

  typedef typename Iterator::reference reference;

  typedef typename Iterator::iterator_category iterator_category;
};

template<class T>
class iterator_traits<T *> {
 public:
  typedef ptrdiff_t difference_type;

  typedef T value_type;

  typedef T *pointer;

  typedef T &reference;

  typedef std::random_access_iterator_tag iterator_category;
};

template<class T>
class iterator_traits<const T *> {
 public:
  typedef ptrdiff_t difference_type;

  typedef T value_type;

  typedef T *pointer;

  typedef T &reference;

  typedef std::random_access_iterator_tag iterator_category;
};

}

#endif //FT_CONTAINERS_ITERATORTRAITS_HPP
