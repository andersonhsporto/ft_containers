//
// Created by Anderson Porto on 11/5/22.
//

#ifndef FT_CONTAINERS_PAIR_HPP
#define FT_CONTAINERS_PAIR_HPP

namespace ft {
template<class T1, class T2>
struct pair {
  typedef T1 first_type;

  typedef T2 second_type;

  T1 first;

  T2 second;

  pair() : first(T1()), second(T2()) {}

  pair(const T1 &x, const T2 &y) : first(x), second(y) {}

  template<class U, class V>
  pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}

  pair &operator=(pair const &pr) {
    first = pr.first;
    second = pr.second;
    return *this;
  }

  template<class first_type, class second_type>
  void swap(pair<first_type, second_type> &x, pair<first_type, second_type> &y) {
    first_type tmp = x.first;
    x.first = y.first;
    y.first = tmp;
    second_type tmp2 = x.second;
    x.second = y.second;
    y.second = tmp2;
  };

};

template<class T1, class T2>
bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

template<class T1, class T2>
bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
  return !(lhs == rhs);
}

template<class T1, class T2>
bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
  return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template<class T1, class T2>
bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
  return !(rhs < lhs);
}

template<class T1, class T2>
bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
  return rhs < lhs;
}

template<class T1, class T2>
bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
  return !(lhs < rhs);
}

template<class T1, class T2>
pair<T1, T2> make_pair(T1 x, T2 y) {
  return pair<T1, T2>(x, y);
}

}

#endif //FT_CONTAINERS_PAIR_HPP
