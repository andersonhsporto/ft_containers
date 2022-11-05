//
// Created by Anderson Porto on 11/5/22.
//

#ifndef FT_CONTAINERS_FT_ITERATOR_TYPES_HPP
#define FT_CONTAINERS_FT_ITERATOR_TYPES_HPP

namespace ft {
template<class T, T v>
struct integral_constant {
  typedef T value_type;

  typedef integral_constant<T, v> type;

  static const T value = v;

  operator T() const { return value; }
};

template<class T>
struct is_integral : public integral_constant<bool, false> {};

template<>
struct is_integral<bool> : public integral_constant<bool, true> {};

template<>
struct is_integral<char> : public integral_constant<bool, true> {};

template<>
struct is_integral<signed char> : public integral_constant<bool, true> {};

template<>
struct is_integral<unsigned char> : public integral_constant<bool, true> {};

template<>
struct is_integral<wchar_t> : public integral_constant<bool, true> {};

template<>
struct is_integral<short> : public integral_constant<bool, true> {};

template<>
struct is_integral<unsigned short> : public integral_constant<bool, true> {};

template<>
struct is_integral<int> : public integral_constant<bool, true> {};

template<>
struct is_integral<unsigned int> : public integral_constant<bool, true> {};

template<>
struct is_integral<long> : public integral_constant<bool, true> {};

template<>
struct is_integral<unsigned long> : public integral_constant<bool, true> {};

template<>
struct is_integral<long long> : public integral_constant<bool, true> {};

template<>
struct is_integral<unsigned long long> : public integral_constant<bool, true> {};

};

#endif //FT_CONTAINERS_FT_ITERATOR_TYPES_HPP
