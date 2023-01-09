//
// Created by Anderson Porto on 12/4/22.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <functional>
#include <stdexcept>

#include "ft_pair.hpp"
#include "../ft_iterator_types.hpp"
#include "../ft_algorithm.hpp"
#include "../2-vector/vector.hpp"

#include "../1-Iterators/VectorIterator.hpp"
#include "../1-Iterators/ReverseIterator.hpp"
#include "../1-Iterators/MapIterator.hpp"

#include <vector>
#include <iostream>

namespace ft {

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> >
>
class map {
 public:
  typedef Key key_type;

  typedef T mapped_type;

  typedef ft::pair<const key_type, mapped_type> value_type;

  typedef std::size_t size_type;

  typedef ptrdiff_t difference_type;

  typedef Compare key_compare;

  typedef Allocator allocator_type;

  typedef typename allocator_type::reference reference;

  typedef typename allocator_type::const_reference const_reference;

  typedef typename allocator_type::pointer pointer;

  typedef typename allocator_type::const_pointer const_pointer;

  typedef typename ft::MapIterator<value_type, Compare, Allocator> iterator;

  typedef typename ft::MapIterator<value_type, Compare, Allocator> const_iterator;

  typedef typename ft::ReverseIterator<iterator> reverse_iterator;

  typedef typename ft::ReverseIterator<const_iterator> const_reverse_iterator;

  // ##############################################################################################
  // ######################################### COMPARE CLASS #######################################
  // ##############################################################################################

  class value_compare : public std::binary_function<value_type, value_type, bool> {
    friend class map;

   protected:
    Compare comp;

    explicit value_compare(Compare c) : comp(c) {}

   public:
    typedef bool result_type;

    typedef value_type first_argument_type;

    typedef value_type second_argument_type;

    bool operator()(const value_type &lhs, const value_type &rhs) const {
      return (comp(lhs.first, rhs.first));
    }
  };

  // ##############################################################################################
  // ######################################### CONSTRUCTORS ########################################
  // ##############################################################################################

  explicit map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type())
      : _comparator(comp), _allocator(alloc), _size(0) {}

  template<class InputIt>
  map(InputIt first,
      InputIt last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type())
      : _comparator(comp), _allocator(alloc) {
    _size = 0;
    do {
      insert(*first);
      first++;
    }
    while (first != last);
    _comparator = comp;
    _allocator = alloc;
  }

  map(const map &other) {
    _size = 0;
    *this = other;
  }

  map &operator=(const map &other) {
    clear();
    _tree.assign(other._tree.root);
    _size = other.size();
    return (*this);
  }

  ~map() {
    clear();
  }

  mapped_type &at(const key_type &key) {
    value_type value = ft::make_pair<key_type const, mapped_type>(key, mapped_type());
    Node<value_type, Allocator> *node = _tree.find(_tree.root, value);

    if (!node)
      throw (std::out_of_range("ft-map::out_of_range"));
    return ((mapped_type &)_tree.find(_tree.root, value)->data->second);
  }

  const mapped_type &at(const key_type &key) const {
    value_type value = ft::make_pair<key_type const, mapped_type>(key, mapped_type());
    Node<value_type, Allocator> *node = _tree.find(_tree.root, value);

    if (!node)
      throw (std::out_of_range("ft-map::out_of_range"));
    return ((const mapped_type &)_tree.find(_tree.root, value)->data->second);
  }

  mapped_type &operator[](const key_type &key) {
    value_type value = ft::make_pair<key_type const, mapped_type>(key, mapped_type());
    Node<value_type, Allocator> *node = _tree.find(_tree.root, value);

    if (!node) {
      node = _tree.insert(value);
      _size++;
      return (_tree.find(_tree.root, value)->data->second);
    }
    return (node->data->second);
  }

  // ##############################################################################################
  // ######################################### GETTERS #############################################
  // ##############################################################################################

  allocator_type get_allocator() const {
    return (_allocator);
  }

  key_compare key_comp() const {
    return (_comparator);
  }

  value_compare value_comp() const {
    return (value_compare(_comparator));
  }

  // ##############################################################################################
  // ######################################### ITERATORS ###########################################
  // ##############################################################################################

  iterator begin() {
    if (_tree.minNode(_tree.root))
      return (iterator(_tree.minNode(_tree.root)->data, &_tree));
    else
      return (iterator(NULL, &_tree));
  }

  const_iterator begin() const {
    return (const_iterator(
        _tree.minNode(_tree.root) ? _tree.minNode(_tree.root)->data : NULL, &_tree)
    );
  }

  iterator end() {
      return (iterator(NULL, &_tree));
  }

  const_iterator end() const {
    return const_iterator(NULL, &_tree);
  }

  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() {
    return reverse_iterator(begin());
  }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  // ##############################################################################################
  // ######################################### CAPACITY ############################################
  // ##############################################################################################

  bool empty() const {
    return _size == 0;
  }

  size_type size() const {
    return _size;
  }

  size_type max_size() const {
    return _allocator.max_size();
  }

  void clear() {
    _tree.clear();
    _tree.root = NULL;
    _size = 0;
  }

    // This function inserts a value into a data structure
  pair<iterator, bool> insert(const value_type &value) {
    // Search the tree for the value
    Node<value_type, Allocator> *node = _tree.find(_tree.root, value);
    // If the value is not found
    if (!node) {
      // Insert the value into the data structure
      node = _tree.insert(value);
      // Increase size
      _size++;
      // Return an iterator pointing to the new node and true (indicating the value was successfully inserted)
      return (ft::make_pair<iterator, bool>(iterator(node->data, &_tree), true));
    }
    // Otherwise, return an iterator pointing to the node and false (indicating the value already exists)
    return (ft::make_pair<iterator, bool>(iterator(node->data, &_tree), false));
  }

  iterator insert(iterator pos, const value_type &value) {
    (void)pos;

    return (insert(value).first);
  }

  template<class InputIt>
  void insert(InputIt first, InputIt last) {
    while (first != last) {
      insert(*first);
      first++;
    }
  }

  void erase(iterator pos) {
    _tree.del(*pos);
    _size--;
  }

  void erase(iterator first, iterator last) {
    ft::vector<key_type> keys;

    while (first != last) {
      keys.push_back(first->first);
      first++;
    }
    for (size_t i = 0; i < keys.size(); i++)
      erase(keys[i]);
  }

  size_type erase(const key_type &key) {
    _size--;
    return _tree.del(ft::make_pair(key, mapped_type()));
  }

  void swap(map &other) {
    _swap(_tree.root, other._tree.root);
    _swap(_size, other._size);
    _swap(_comparator, other._comparator);
    _swap(_allocator, other._allocator);
  }

  // ##############################################################################################
  // ######################################### LOOKUP ##############################################
  // ##############################################################################################

  size_type count(const key_type &key) const {
    if (_tree.find(_tree.root, ft::make_pair(key, mapped_type())) != NULL)
      return (1);
    return (0);
  }

  iterator find(const key_type &key) {
    Node<value_type, Allocator> *node = _tree.find(_tree.root, ft::make_pair(key, mapped_type()));

    return iterator(node ? node->data : NULL, &_tree);
  }

  const_iterator find(const key_type &key) const {
    Node<value_type, Allocator> *node = _tree.find(_tree.root, ft::make_pair(key, mapped_type()));

    return const_iterator(node ? node->data : NULL, &_tree);
  }

  pair<iterator, iterator> equal_range(const key_type &key) {
    return ft::make_pair(lower_bound(key), upper_bound(key));
  }

  pair<const_iterator, const_iterator> equal_range(const key_type &key) const {
    return ft::make_pair(lower_bound(key), upper_bound(key));
  }

  iterator lower_bound(const key_type &key) {
    Node<value_type, Allocator> *node = _tree.root;
    Node<value_type, Allocator> *lower = node;

    while (node != NULL) {
      if (!_comparator(node->data->first, key)) {
        lower = node;
        node = node->left;
      } else
        node = node->right;
    }
    return iterator(lower ? lower->data : NULL, &_tree);
  }

  const_iterator lower_bound(const key_type &key) const {
    Node<value_type, Allocator> *node = _tree.root;
    Node<value_type, Allocator> *lower = node;

    while (node != NULL) {
      if (!_comparator(node->data->first, key)) {
        lower = node;
        node = node->left;
      } else
        node = node->right;
    }
    return const_iterator(lower ? lower->data : NULL, &_tree);
  }

  iterator upper_bound(const key_type &key) {
    Node<value_type, Allocator> *node = _tree.root;
    Node<value_type, Allocator> *upper = node;

    while (node != NULL) {
      if (_comparator(key, node->data->first)) {
        upper = node;
        node = node->left;
      } else
        node = node->right;
    }
    return iterator(upper ? upper->data : NULL, &_tree);
  }

  const_iterator upper_bound(const key_type &key) const {
    Node<value_type, Allocator> *node = _tree.root;
    Node<value_type, Allocator> *upper = node;

    while (node != NULL) {
      if (_comparator(key, node->data->first)) {
        upper = node;
        node = node->left;
      } else
        node = node->right;
    }
    return const_iterator(upper ? upper->data : NULL, &_tree);
  }

 private:
  key_compare _comparator;

  allocator_type _allocator;

  size_type _size;

  Tree<value_type, key_compare, allocator_type> _tree;

// ##############################################################################################
// ######################################### UTILITIES ###########################################
// ##############################################################################################

  template<typename U>
  void _swap(U &a, U &b) {
    U tmp = a;
    a = b;
    b = tmp;
  }

};

template<class Key, class T, class Compare, class Allocator>
bool operator==(const map<Key, T, Compare, Allocator> &lhs,
                const map<Key, T, Compare, Allocator> &rhs) {
  return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<class Key, class T, class Compare, class Allocator>
bool operator!=(const map<Key, T, Compare, Allocator> &lhs,
                const map<Key, T, Compare, Allocator> &rhs) {
  return !(ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template<class Key, class T, class Compare, class Allocator>
bool operator<(const map<Key, T, Compare, Allocator> &lhs,
               const map<Key, T, Compare, Allocator> &rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<class Key, class T, class Compare, class Allocator>
bool operator<=(const map<Key, T, Compare, Allocator> &lhs,
                const map<Key, T, Compare, Allocator> &rhs) {
  return !(lhs > rhs);
}

template<class Key, class T, class Compare, class Allocator>
bool operator>(const map<Key, T, Compare, Allocator> &lhs,
               const map<Key, T, Compare, Allocator> &rhs) {
  return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template<class Key, class T, class Compare, class Allocator>
bool operator>=(const map<Key, T, Compare, Allocator> &lhs,
                const map<Key, T, Compare, Allocator> &rhs) {
  return !(lhs < rhs);
}

template<class Key, class T, class Compare, class Allocator>
void swap(map<Key, T, Compare, Allocator> &lhs,
          map<Key, T, Compare, Allocator> &rhs) {
  lhs.swap(rhs);
}

}

#endif
