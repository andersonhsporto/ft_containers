//
// Created by Anderson Porto on 11/9/22.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <memory>
#include "pair.hpp"
#include "./Tree/AVL.hpp" // TODO: Simplify this
#include "BidirectionalIterator.hpp"
#include "IteratorVector.hpp"

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

  typedef std::size_t size_type;

  typedef std::ptrdiff_t difference_type;

  typedef Compare key_compare;

  typedef Alloc allocator_type;

  typedef value_type &reference;

  typedef const value_type &const_reference;

  typedef typename allocator_type::pointer pointer;

  typedef typename allocator_type::const_pointer const_pointer;

  typedef ft::BidirectionalIterator<value_type, key_compare, allocator_type> iterator;

  typedef ft::BidirectionalIterator<const value_type, key_compare, allocator_type> const_iterator;

  typedef ft::reverse_iterator<iterator> reverse_iterator;

  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  // ***********************************************************************************************
  // ***********************************************************************************************
  // *************************************** Member Classes ****************************************

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
  // *************************************  Member Constructors  ***********************************

  // Default Constructor ( empty container )
  explicit map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type()) :
      _alloc(alloc),
      _comp(comp),
      _size(0) {

  }

  // Range Constructor ( constructs container with as copies of elements from range [first,last) )
  template<class InputIterator>
  map(InputIterator first,
      InputIterator last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type()) :
      _avl(comp, alloc),
      _comp(comp),
      _size(0) {
    while (first != last) {
      insert(*first);
      ++first;
    }
  }

  // Copy Constructor ( constructs container with a copy of each of the elements in x )
  map(const map &source) : _size(0) {
    *this = source;
  }

  // Assignment Operator ( assigns new contents to container, replacing its current contents )
  map &operator=(const map &source) {
    // TODO: Use member functions
    return *this;
  }

  // Destructor
  ~map() {
    // TODO: Use member functions
  }

  // Returns the associated allocator
  allocator_type get_allocator() const {
    return _alloc;
  }

  // ***********************************************************************************************
  // ***********************************************************************************************
  // *************************************** Element access ****************************************

  /*  Returns a reference to the mapped value of the element with key equivalent to key.
  *   If no such element exists, an exception to type std::out_of_range is thrown.
  */
  mapped_type &at(const key_type &key) {
    value_type value = ft::make_pair(key, mapped_type());
    Node<value_type, allocator_type> *node = _avl.find(value);

    if (node == NULL) {
      throw std::out_of_range("map::at");
    }

    return node->data->second;
  }

  /*  Returns a reference to the mapped value of the element with key equivalent to key.
  *   If no such element exists, an exception to type std::out_of_range is thrown.
  */
  const mapped_type &at(const key_type &key) const {
    value_type value = ft::make_pair(key, mapped_type());
    Node<value_type, allocator_type> *node = _avl.find(value);

    if (node == NULL) {
      throw std::out_of_range("map::at");
    }

    return node->data->second;
  }

  /*  Returns a reference to the value that is mapped to a key equivalent to key,
  *   performing an insertion if such key does not already exist.
  */
  mapped_type &operator[](const key_type &key) {
    value_type value = ft::make_pair(key, mapped_type());
    Node<value_type, allocator_type> *node = _avl.find(value);

    if (node == NULL) {
      insert(value);
      node = _avl.find(value);
    }

    return node->data->second;
  }

  // ***********************************************************************************************
  // ***********************************************************************************************
  // *************************************** Iterators *********************************************

  // Returns an iterator to the first element in the container.
  iterator begin() {
    if (_avl._root == NULL) {
      return iterator(NULL, &_avl);
    } else {
      return iterator(_avl.minNode(_avl._root)->data, &_avl);
    }
  }

  // Returns an iterator to the first element in the container.
  const_iterator begin() const {
    if (_avl._root == NULL) {
      return const_iterator(NULL, &_avl);
    } else {
      return const_iterator(_avl.minNode(_avl._root)->data, &_avl);
    }
  }

  // Returns an iterator to the element following the last element in the container.
  iterator end() {
    return iterator(NULL, &_avl);
  }

  // Returns an iterator to the element following the last element in the container.
  const_iterator end() const {
    return const_iterator(NULL, &_avl);
  }

  // Returns a reverse iterator to the first element in the reversed container.
  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }

  // Returns a reverse iterator to the first element in the reversed container.
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }





// ***********************************************************************************************
// ***********************************************************************************************
// *************************************** Member Variables **************************************
 private:

  AVL<value_type, key_compare, allocator_type> _avl;

  allocator_type _alloc;

  key_compare _comp;

  size_type _size;

};
}

#endif //FT_CONTAINERS_MAP_HPP
