//
// Created by Anderson Porto on 12/11/22.
//

#ifndef FT_CONTAINERS_REVERSEITERATOR_HPP
#define FT_CONTAINERS_REVERSEITERATOR_HPP

#include "ft_iterator_traits.hpp"

namespace ft {

template<class Iterator>
class ReverseIterator {
 public:

  typedef Iterator iterator_type;

  typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;

  typedef typename ft::iterator_traits<Iterator>::value_type value_type;

  typedef typename ft::iterator_traits<Iterator>::pointer pointer;

  typedef typename ft::iterator_traits<Iterator>::reference reference;

  typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;

  ReverseIterator() {}

  ~ReverseIterator() {}

  explicit ReverseIterator(iterator_type it) : _it(it) {}

  template<class iterator>
  ReverseIterator(ReverseIterator<iterator> const &rev_it) {
    _it = rev_it.base();
  }

  iterator_type base() const {
    return (_it);
  }

  reference operator*() const {
    return *(--Iterator(_it));
  }

  ReverseIterator &operator+(difference_type value) {
    return (ReverseIterator(_it - value));
  }

  ReverseIterator &operator++() {
    _it--;
    return (*this);
  }

  ReverseIterator operator++(int) {
    ReverseIterator tmp = *this;
    ++(*this);
    return (tmp);
  }

  ReverseIterator &operator+=(difference_type value) {
    _it -= value;
    return (*this);
  }

  ReverseIterator &operator-(difference_type value) {
    return (ReverseIterator(_it + value));
  }

  ReverseIterator &operator--() {
    _it++;
    return (*this);
  }

  ReverseIterator operator--(int) {
    ReverseIterator tmp = *this;
    --(*this);
    return (tmp);
  }

  ReverseIterator &operator-=(difference_type value) {
    _it += value;
    return (*this);
  }

  pointer operator->() const {
    return &(operator*());
  }

  reference operator[](difference_type n) const {
    return (base()[-n - 1]);
  }

 private:
  iterator_type _it;
};

template<class Iterator>
typename ReverseIterator<Iterator>::difference_type operator-(const ReverseIterator<Iterator> &lhs,
                                                              const ReverseIterator<Iterator> &rhs) {
  return (rhs.base() + lhs.base());
}

template<class Iterator>
typename ReverseIterator<Iterator>::difference_type operator+(typename ReverseIterator<Iterator>::difference_type n,
                                                              const ReverseIterator<Iterator> &rev_it) {
  return (ReverseIterator<Iterator>(rev_it.base() - n));
}

template<class Iterator>
bool operator==(const ReverseIterator<Iterator> &lhs,
                const ReverseIterator<Iterator> &rhs) {
  return (lhs.base() == rhs.base());
}

template<class Iterator>
bool operator!=(const ReverseIterator<Iterator> &lhs,
                const ReverseIterator<Iterator> &rhs) {
  return (lhs.base() != rhs.base());
}

template<class Iterator>
bool operator<(const ReverseIterator<Iterator> &lhs,
               const ReverseIterator<Iterator> &rhs) {
  return (lhs.base() > rhs.base());
}

template<class Iterator>
bool operator>(const ReverseIterator<Iterator> &lhs,
               const ReverseIterator<Iterator> &rhs) {
  return (lhs.base() < rhs.base());
}

template<class Iterator>
bool operator<=(const ReverseIterator<Iterator> &lhs,
                const ReverseIterator<Iterator> &rhs) {
  return (lhs.base() >= rhs.base());
}

template<class Iterator>
bool operator>=(const ReverseIterator<Iterator> &lhs,
                const ReverseIterator<Iterator> &rhs) {
  return (lhs.base() <= rhs.base());
}

}

#endif //FT_CONTAINERS_REVERSEITERATOR_HPP
