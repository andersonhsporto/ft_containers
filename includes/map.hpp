//
// Created by Anderson Porto on 11/9/22.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <memory>
#include "ft_utility.hpp"
#include "./Tree/AVL.hpp" // TODO: Simplify this

namespace ft {
template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Alloc = std::allocator<ft::pair<const Key, T> >
>
class map {
  // ***********************************************************************************************
  // ***********************************************************************************************
  // *************************************** Member types ******************************************
 public:
  typedef Key key_type;

  typedef T mapped_type;

  typedef ft::pair<const key_type, mapped_type> value_type;

  typedef Compare key_compare;

  typedef Alloc allocator_type;

  typedef typename allocator_type::reference reference;

  typedef typename allocator_type::const_reference const_reference;

  typedef typename allocator_type::pointer pointer;

  typedef typename allocator_type::const_pointer const_pointer;

  typedef typename allocator_type::size_type size_type;

  typedef typename allocator_type::difference_type difference_type;

  // ***********************************************************************************************
  // ***********************************************************************************************
  // *************************************** Member Classes ****************************************
 public:

  // Friend class can access private and protected members
  // of other class in which it is declared as friend.
  // It is sometimes useful to allow a particular class to access private members of other class.
  class value_compare : public std::binary_function<value_type, value_type, bool> {
    friend class map;

   protected:
    Compare comp;

    explicit value_compare(Compare c) : comp(c) {}

   public:
    bool operator()(const value_type &x, const value_type &y) const {
      return comp(x.first, y.first);
    }
  };

  // ***********************************************************************************************
  // ***********************************************************************************************
  // *************************************** Member Functions **************************************
 public:

  // ***********************************************************************************************
  // ***********************************************************************************************
  // *************************************** Member Variables **************************************
 private:
  key_compare _comp;

  allocator_type _alloc;

  size_type _size;

};
}

#endif //FT_CONTAINERS_MAP_HPP
