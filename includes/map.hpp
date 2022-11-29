//
// Created by Anderson Porto on 11/9/22.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <memory>
#include "pair.hpp"
#include "Tree/AVL.hpp" // TODO: Simplify this
#include "Iterators/BidirectionalIterator.hpp"
#include "Iterators/IteratorVector.hpp"

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
    if (this != &source) {
      clear();
      _avl = source._avl;
      _size = source._size;
    }
    return *this;
  }

  // Destructor
  ~map() {
    clear();
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
    if (_avl.root == NULL) {
      return iterator(NULL, &_avl);
    } else {
      return iterator(_avl.minNode(_avl.root)->data, &_avl);
    }
  }

  // Returns an iterator to the first element in the container.
  const_iterator begin() const {
    if (_avl.root == NULL) {
      return const_iterator(NULL, &_avl);
    } else {
      return const_iterator(_avl.minNode(_avl.root)->data, &_avl);
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

  // Returns a reverse iterator to the element following the last element in the reversed container.
  reverse_iterator rend() {
    return reverse_iterator(begin());
  }

  // Returns a reverse iterator to the element following the last element in the reversed container.
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  // ***********************************************************************************************
  // ***********************************************************************************************
  // *************************************** Capacity **********************************************

  // Returns whether the map is empty (i.e. whether its size is 0).
  bool empty() const {
    return _size == 0;
  }

  // Returns the number of elements in the map.
  size_type size() const {
    return _size;
  }

  // Returns the maximum number of elements that the map can hold.
  size_type max_size() const {
    return _alloc.max_size();
  }

  // ***********************************************************************************************
  // ***********************************************************************************************
  // *************************************** Modifiers *********************************************

  /*  Erases all elements from the container. After this call, size() returns zero.
   * Invalidates any references, pointers, or iterators referring to contained elements.
   * Any past-the-end iterator remains valid.
  */
  void clear() {
//    _avl.eraseRoot();
    _size = 0;
  }

  ft::pair<iterator, bool> insert(const value_type &value) {
    Node<value_type, allocator_type> *node = _avl.find(_avl.root, value);

    if (node == false) {
      node = _avl.insert(value);
      _size++;
      return ft::make_pair<iterator, bool>(iterator(node->data, &_avl), true);
    } else {
      return ft::make_pair<iterator, bool>(iterator(node->data, &_avl), false);
    }
  }

  // Inserts elements from range [first, last).
  // If multiple elements in the range have keys that compare equivalent,
  // it is unspecified which element is inserted.
  template<class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    while (first != last) {
      insert(*first);
      ++first;
    }
  }

  // Removes specified elements from the container.
  // removes the element at pos.
  iterator erase(iterator position) {
    Node<value_type, allocator_type> *node = _avl.find(*position);

    if (node == NULL) {
      return iterator(NULL, &_avl);
    }

    _avl.erase(node->data);
    --_size;

    return iterator(node->data, &_avl);
  }

  // Removes the element (if one exists) with the key equivalent to key.
  size_type erase(const key_type &key) {
    value_type value = ft::make_pair(key, mapped_type());
    Node<value_type, allocator_type> *node = _avl.find(value);

    if (node == NULL) {
      return 0;
    }

    _avl.erase(node->data);
    --_size;

    return 1;
  }

  // Exchanges the contents of the container with those of another container.
  // Does not invoke any move, copy, or swap operations on individual elements.
  void swap(map &other) {
    map temp;

    temp = *this;
    *this = other;
    other = temp;

    temp.clear();
  }

  // ***********************************************************************************************
  // ***********************************************************************************************
  // *************************************** Lookup ************************************************

  // Returns the number of elements with key that compares equivalent to the specified argument.
  // This is either 1 or 0 since this container does not allow duplicates.
  size_type count(const key_type &key) const {
    value_type value = ft::make_pair(key, mapped_type());
    Node<value_type, allocator_type> *node = _avl.find(value);

    if (node == NULL) {
      return 0;
    } else {
      return 1;
    }
  }

  // Finds an element with key equivalent to key.
  iterator find(const key_type &key) {
    value_type value = ft::make_pair(key, mapped_type());
    Node<value_type, allocator_type> *node = _avl.find(value);

    if (node == NULL) {
      return iterator(NULL, &_avl);
    } else {
      return iterator(node->data, &_avl);
    }
  }

  // Finds an element with key equivalent to key.
  const_iterator find(const key_type &key) const {
    value_type value = ft::make_pair(key, mapped_type());
    Node<value_type, allocator_type> *node = _avl.find(value);

    if (node == NULL) {
      return const_iterator(NULL, &_avl);
    } else {
      return const_iterator(node->data, &_avl);
    }
  }

  // Returns a range containing all elements with the given key in the container.
  // The range is defined by two iterators, one pointing to the first element
  // that is not less than key and another pointing to the first element greater than key.
  // ( Compares the keys to key ).
  ft::pair<iterator, iterator> equal_range(const key_type &key) {
    iterator it = find(key);

    if (it == end()) {
      return ft::make_pair(it, it);
    } else {
      return ft::make_pair(it, ++it);
    }
  }

  // Returns a range containing all elements with the given key in the container.
  // The range is defined by two iterators, one pointing to the first element
  // that is not less than key and another pointing to the first element greater than key.
  // ( Compares the keys to key ).
  ft::pair<const_iterator, const_iterator> equal_range(const key_type &key) const {
    const_iterator it = find(key);

    if (it == end()) {
      return ft::make_pair(it, it);
    } else {
      return ft::make_pair(it, ++it);
    }
  }

  // Returns an iterator pointing to the first element
  // that is not less than (i.e. greater or equal to) key.
  iterator lower_bound(const key_type &key) {
    iterator it = find(key);

    if (it == end()) {
      return it;
    } else {
      return it;
    }
  }

  // Returns an iterator pointing to the first element
  // that is not less than (i.e. greater or equal to) key.
  const_iterator lower_bound(const key_type &key) const {
    const_iterator it = find(key);

    if (it == end()) {
      return it;
    } else {
      return it;
    }
  }

  // Returns an iterator pointing to the first element that is greater than key.
  iterator upper_bound(const key_type &key) {
    iterator it = find(key);

    if (it == end()) {
      return it;
    } else {
      return ++it;
    }
  }

  // Returns an iterator pointing to the first element that is greater than key.
  const_iterator upper_bound(const key_type &key) const {
    const_iterator it = find(key);

    if (it == end()) {
      return it;
    } else {
      return ++it;
    }
  }
// ***********************************************************************************************
// ***********************************************************************************************
// *************************************** Observers **********************************************

  // Returns the comparison object out of which the container was constructed.
  key_compare key_comp() const {
    return _comp;
  }

  // Returns the comparison object out of which the container was constructed.
  value_compare value_comp() const {
    return _avl.value_comp();
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

// ***********************************************************************************************
// ***********************************************************************************************
// *************************************** Non-member functions **********************************
template<class Key, class T, class Compare, class Alloc>
bool operator==(const std::map<Key, T, Compare, Alloc> &lhs,
                const std::map<Key, T, Compare, Alloc> &rhs) {
  return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<class Key, class T, class Compare, class Alloc>
bool operator!=(const std::map<Key, T, Compare, Alloc> &lhs,
                const std::map<Key, T, Compare, Alloc> &rhs) {
  return !ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<class Key, class T, class Compare, class Alloc>
bool operator<(const std::map<Key, T, Compare, Alloc> &lhs,
               const std::map<Key, T, Compare, Alloc> &rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<class Key, class T, class Compare, class Alloc>
bool operator<=(const std::map<Key, T, Compare, Alloc> &lhs,
                const std::map<Key, T, Compare, Alloc> &rhs) {
  return !(rhs < lhs);
}

template<class Key, class T, class Compare, class Alloc>

bool operator>(const std::map<Key, T, Compare, Alloc> &lhs,
               const std::map<Key, T, Compare, Alloc> &rhs) {
  return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template<class Key, class T, class Compare, class Alloc>

bool operator>=(const std::map<Key, T, Compare, Alloc> &lhs,
                const std::map<Key, T, Compare, Alloc> &rhs) {
  return !(lhs < rhs);
}

template<class Key, class T, class Compare, class Alloc>
void swap(std::map<Key, T, Compare, Alloc> &lhs,
          std::map<Key, T, Compare, Alloc> &rhs) {
  lhs.swap(rhs);
}
};

#endif //FT_CONTAINERS_MAP_HPP
