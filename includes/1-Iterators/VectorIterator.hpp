#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft {

template<typename T>
class VectorIterator {
 public:
  typedef std::ptrdiff_t difference_type;

  typedef T value_type;

  typedef T *pointer;

  typedef T &reference;

  typedef std::random_access_iterator_tag iterator_category;
  /*-----------------------------------------------------------------------------------------------------------------------------*/
  /*-----[ Member Functions ]-----*/
  VectorIterator(void) : _it(NULL) {}

  explicit VectorIterator(value_type *it) : _it(it) {}

  VectorIterator(VectorIterator const &copy) { *this = copy; }

  VectorIterator &operator=(VectorIterator const &copy) {
    _it = copy._it;
    return (*this);
  }

  pointer base(void) const { return (_it); }

  ~VectorIterator(void) {}
  /*-----[ Expressions ]-----*/
  //	Equivalence operations (a == b / a != b)
  bool operator==(VectorIterator<T> const &obj) { return (_it == obj._it); }

  bool operator!=(VectorIterator<T> const &obj) { return (_it != obj._it); }

  //	Dereference as ab rvalue (*a or a->m) even as mutable iterator (*a = t)
  reference operator*() { return (*_it); }

  pointer operator->() { return (&operator*()); }

  //	increment and decrement (++a or a++ / --a or a--)
  VectorIterator &operator++() {
    _it++;
    return (*this);
  }

  VectorIterator operator++(int) {
    VectorIterator tmp = *this;
    ++(*this);
    return (tmp);
  }

  VectorIterator &operator--() {
    _it--;
    return (*this);
  }

  VectorIterator operator--(int) {
    VectorIterator tmp = *this;
    --(*this);
    return (tmp);
  }

  //	Arithmetic operations (a + b / a - b)
  VectorIterator operator+(difference_type value) const {
    return (VectorIterator(_it + value));
  }

  VectorIterator operator-(difference_type value) const {
    return (VectorIterator(_it - value));
  }

  //	Comparison operations ( a < b/ a > b / a <= b / a >= b )
  bool operator<(VectorIterator<T> const &obj) { return (_it < obj._it); }

  bool operator>(VectorIterator<T> const &obj) { return (_it > obj._it); }

  bool operator<=(VectorIterator<T> const &obj) { return (_it <= obj._it); }

  bool operator>=(VectorIterator<T> const &obj) { return (_it >= obj._it); }

  //	Compound assignment (a += b / a -= b)
  VectorIterator &operator+=(difference_type value) {
    _it += value;
    return (*this);
  }

  VectorIterator &operator-=(difference_type value) {
    _it -= value;
    return (*this);
  }

  //	Offset dereference (a[b])
  reference operator[](difference_type value) const { return (_it[value]); }
  /*-----[ Extra ]-----*/
 private:
  pointer _it;
};

/*-----[ Non Member Functions - Random Access Iterator ]-----*/
template<class Iterator>
typename VectorIterator<Iterator>::difference_type operator-(const VectorIterator<
    Iterator> &lhs,
                                                                     const VectorIterator<
                                                                         Iterator> &rhs) {
  return (lhs.base() - rhs.base());
}

template<class Iterator>
typename VectorIterator<Iterator>::difference_type operator+(typename VectorIterator<
    Iterator>::difference_type n,
                                                                     const VectorIterator<
                                                                         Iterator> &it) {
  return (VectorIterator<Iterator>(it.base() + n));
}

//	Comparison operators
template<class Iterator>
bool operator==(const VectorIterator<Iterator> &lhs,
                const VectorIterator<Iterator> &rhs) { return (lhs.base() == rhs.base()); }

template<class Iterator>
bool operator!=(const VectorIterator<Iterator> &lhs,
                const VectorIterator<Iterator> &rhs) { return (lhs.base() != rhs.base()); }

template<class Iterator>
bool operator<(const VectorIterator<Iterator> &lhs,
               const VectorIterator<Iterator> &rhs) { return (lhs.base() > rhs.base()); }

template<class Iterator>
bool operator>(const VectorIterator<Iterator> &lhs,
               const VectorIterator<Iterator> &rhs) { return (lhs.base() < rhs.base()); }

template<class Iterator>
bool operator<=(const VectorIterator<Iterator> &lhs,
                const VectorIterator<Iterator> &rhs) { return (lhs.base() >= rhs.base()); }

template<class Iterator>
bool operator>=(const VectorIterator<Iterator> &lhs,
                const VectorIterator<Iterator> &rhs) { return (lhs.base() <= rhs.base()); }

};

#endif
