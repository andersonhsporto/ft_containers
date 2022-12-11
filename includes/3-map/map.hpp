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
#include "../vector.hpp"

#include "../includes/1-Iterators/VectorIterator.hpp"
#include "../includes/1-Iterators/ReverseIterator.hpp"
#include "../includes/1-Iterators/MapIterator.hpp"

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

  // value_compare is a function object that compares objects of type (key-value pairs)
  // by comparing of the first components of the pairs.
  class value_compare : public std::binary_function<value_type, value_type, bool> {
    friend class map<Key, T, Compare, Allocator>;

   protected:
    Compare comp;

    value_compare(Compare c) : comp(c) {}

   public:
    typedef bool result_type;

    typedef value_type first_argument_type;

    typedef value_type second_argument_type;

    bool operator()(const value_type &lhs, const value_type &rhs) const {
      return comp(lhs.first, rhs.first);
    }
  };

  // ##############################################################################################
  // ######################################### CONSTRUCTORS ########################################
  // ##############################################################################################


  // Constructs an empty container.
  explicit map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type())
      : _comp(comp), _alloc(alloc), _size(0) {}

  template<class InputIt>
  map(InputIt first, InputIt last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type()) : _comp(comp), _alloc(alloc), _size(0) {
    _size = 0;
    while (first != last) {
      insert(*first);
      first++;
    }
    _comp = comp;
    _alloc = alloc;
  }

  map(const map &other) {
    _size = 0;
    *this = other;
  }

  map &operator=(const map &other) {
    if (this != &other) {
      clear();
      _tree.copyNode(other._tree.root);
      _size = other.size();
    }
    return (*this);
  }

  ~map() { clear(); }

  // ##############################################################################################
  // ######################################### GETTERS #############################################
  // ##############################################################################################

  allocator_type get_allocator() const {
    return _alloc;
  }

  key_compare key_comp() const {
    return _comp;
  }

  value_compare value_comp() const {
    return value_compare(_comp);
  }

  // ##############################################################################################
  // ######################################### ELEMENT ACCESS ######################################
  // ##############################################################################################

  mapped_type &at(const key_type &key) {
    value_type value = ft::make_pair<key_type const, mapped_type>(key, mapped_type());
    Node<value_type, Allocator> *node = _tree.getNodeByValue(value);

    if (!node)
      throw (std::out_of_range("ft-map::at"));
    return ((mapped_type &)_tree.getNode(_tree.root, value)->data->second);
  }

  const mapped_type &at(const key_type &key) const {
    value_type value = ft::make_pair<key_type const, mapped_type>(key, mapped_type());
    Node<value_type, Allocator> *node = _tree.getNodeByValue(value);

    if (!node)
      throw (std::out_of_range("ft-map::at"));
    return ((const mapped_type &)_tree.getNode(_tree.root, value)->data->second);
  }

  mapped_type &operator[](const key_type &key) {
    value_type value = ft::make_pair<key_type const, mapped_type>(key, mapped_type());
    Node<value_type, Allocator> *node = _tree.getNodeByValue(value);

    if (!node) {
      node = _tree.insert(value);
      _size++;
      return (_tree.getNode(_tree.root, value)->data->second);
    }
    return (node->data->second);
  }

  // ##############################################################################################
  // ######################################### ITERATORS ###########################################
  // ##############################################################################################

  iterator begin() {
    return (iterator(_tree.minNode(_tree.root) ? _tree.minNode(_tree.root)->data : NULL, &_tree));
  }

  const_iterator begin() const {
    return (const_iterator(_tree.minNode(_tree.root) ? _tree.minNode(_tree.root)->data : NULL,
                           &_tree));
  }

  iterator end() {
    return (iterator(NULL, &_tree));
  }

  const_iterator end() const {
    return (const_iterator(NULL, &_tree));
  }

  reverse_iterator rbegin() {
    iterator it = end();

    return (reverse_iterator(it));
  }

  const_reverse_iterator rbegin() const {
    return (const_reverse_iterator(end()));
  }

  reverse_iterator rend() {
    return (reverse_iterator(begin()));
  }

  const_reverse_iterator rend() const {
    return (const_reverse_iterator(begin()));
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
    return _alloc.max_size() / sizeof(Node<value_type, Allocator>);
  }

  // ##############################################################################################
  // ######################################### MODIFIERS ###########################################
  // ##############################################################################################

  void clear() {
    _size = 0;
    _tree.deallocateNode(_tree.root);
    _tree.root = NULL;
  }

  // Removes the element at pos
  iterator erase(iterator pos) {
    Node<value_type, Allocator> *node = _tree.getNodeByValue(*pos);

    if (node) {
      _tree.del(_tree.root, *pos);
      _size--;
    }
    return (iterator(node ? node->data : NULL, &_tree));
  }

  iterator erase(iterator first, iterator last) {
    while (first != last) {
      erase(first);
      first++;
    }
    return (iterator(first.node, &_tree));
  }

  size_type erase(const key_type &key) {
    _size--;
    return (_tree.del(ft::make_pair(key, mapped_type())));
  }

  pair<iterator, bool> insert(const value_type &value) {
    Node<value_type, Allocator> *node = _tree.getNodeByValue(value);
    bool second = false;

    if (!node) {
      node = _tree.insert(value);
      second = true;
      _size++;
    }
    return (ft::make_pair<iterator, bool>(iterator(node->data, &_tree), second));
  }

  iterator insert(iterator pos, const value_type &value) {
    (void)pos;
    return insert(value).first;
  }

  template<class InputIt>
  void insert(InputIt first, InputIt last) {
    while (first != last) {
      insert(*first);
      first++;
    }
  }

  void swap(map &other) {
    _swap(_tree.root, other._tree.root);
    _swap(_size, other._size);
    _swap(_comp, other._comp);
    _swap(_alloc, other._alloc);
  }

  // ##############################################################################################
  // ######################################### LOOKUP ##############################################
  // ##############################################################################################

  size_type count(const key_type &key) const {
    return _tree.keyIsPresent(key) ? 1 : 0;
  }

  iterator find(const key_type &key) {
    Node<value_type, Allocator>
        *node = _tree.getNode(_tree.root, ft::make_pair(key, mapped_type()));
    return (iterator(node ? node->data : NULL, &_tree));
  }

  const_iterator find(const key_type &key) const {
    Node<value_type, Allocator>
        *node = _tree.getNode(_tree.root, ft::make_pair(key, mapped_type()));
    return (const_iterator(node ? node->data : NULL, &_tree));
  }

  pair<iterator, iterator> equal_range(const key_type &key) {
    return (ft::make_pair(lower_bound(key), upper_bound(key)));
  }

  pair<const_iterator, const_iterator> equal_range(const key_type &key) const {
    return (ft::make_pair(lower_bound(key), upper_bound(key)));
  }

  iterator lower_bound(const key_type &key) {
    Node<value_type, Allocator> *node = _tree.root;
    Node<value_type, Allocator> *lower = node;

    while (node != NULL) {
      if (!_comp(node->data->first, key)) {
        lower = node;
        node = node->left;
      } else
        node = node->right;
    }
    return (iterator(lower ? lower->data : NULL, &_tree));
  }

  const_iterator lower_bound(const key_type &key) const {
    Node<value_type, Allocator> *node = _tree.root;
    Node<value_type, Allocator> *lower = node;

    while (node != NULL) {
      if (!_comp(node->data->first, key)) {
        lower = node;
        node = node->left;
      } else
        node = node->right;
    }
    return (const_iterator(lower ? lower->data : NULL, &_tree));
  }

  //	Returns an iterator to the first element greater than the given "key"
  iterator upper_bound(const key_type &key) {
    Node<value_type, Allocator> *node = _tree.root;
    Node<value_type, Allocator> *upper = node;

    while (node != NULL) {
      if (_comp(key, node->data->first)) {
        upper = node;
        node = node->left;
      } else
        node = node->right;
    }
    return (iterator(upper ? upper->data : NULL, &_tree));
  }

  const_iterator upper_bound(const key_type &key) const {
    Node<value_type, Allocator> *node = _tree.root;
    Node<value_type, Allocator> *upper = node;

    while (node != NULL) {
      if (_comp(key, node->data->first)) {
        upper = node;
        node = node->left;
      } else
        node = node->right;
    }
    return (const_iterator(upper ? upper->data : NULL, &_tree));
  }

 private:
  Tree<value_type, key_compare, allocator_type> _tree;

  key_compare _comp;

  allocator_type _alloc;

  size_type _size;

  template<typename U>
  void _swap(U &a, U &b) {
    U tmp = a;
    a = b;
    b = tmp;
  }

};

}
#endif //FT_CONTAINERS_MAP_HPP
