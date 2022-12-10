//
// Created by Anderson Porto on 12/4/22.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <memory>
#include <limits>
#include "ft_pair.hpp"
#include "../0-Utilities/ConstEnum.hpp"
#include "../1-Iterators/MapIterator.hpp"
#include "../ft_iterator_types.hpp"
#include "../1-Iterators/IteratorVector.hpp"
#include "../ft_algorithm.hpp"

namespace ft {

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Alloc = std::allocator<ft::pair<const Key, T> >
>
class map {
 public:
  typedef Key key_type;

  typedef T mapped_type;

  typedef ft::pair<const key_type, mapped_type> value_type;

  typedef std::size_t size_type;

  typedef ptrdiff_t difference_type;

  typedef Compare key_compare;

  typedef Alloc allocator_type;

  typedef typename allocator_type::reference reference;

  typedef typename allocator_type::const_reference const_reference;

  typedef typename allocator_type::pointer pointer;

  typedef typename allocator_type::const_pointer const_pointer;

  typedef typename ft::MapIterator<value_type, Compare, Alloc> iterator;

  typedef typename ft::MapIterator<const value_type, Compare, Alloc> const_iterator;

  typedef typename ft::reverse_iterator<iterator> reverse_iterator;

  typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;


// #############################################################################################
// ######################################### MEMBER CLASS #######################################
// #############################################################################################

  class value_compare {
    friend class map;

   protected:
    Compare comp;

    value_compare(Compare c) : comp(c) {}

   public:
    typedef bool result_type;

    typedef value_type first_argument_type;

    typedef value_type second_argument_type;

    bool operator()(const value_type &x, const value_type &y) const {
      return comp(x.first, y.first);
    }
  };

// #############################################################################################
// ######################################### MEMBER FUNCTIONS ###################################
// #############################################################################################

  explicit map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type()) {
    _comp = comp;
    _alloc = alloc;
    _size = 0;
  }

  template<class InputIt>
  map(InputIt first,
      InputIt last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type()) {
    _comp = comp;
    _alloc = alloc;
    _size = 0;
    while (first != last) {
      insert(*first);
      ++first;
    }
  }

  map(const map &other) : _comp(other._comp), _alloc(other._alloc), _size(0) {
    _size = 0;
    *this = other;
  }

  map &operator=(const map &other) {
    if (this != &other) {
      clear();
      _comp = other._comp;
      _alloc = other._alloc;
      _size = 0;
      for (const_iterator it = other.begin(); it != other.end(); ++it) {
        insert(*it);
      }
    }
    return (*this);
  }

  ~map() {
    clear();
  }

  allocator_type get_allocator() const {
    return (_alloc);
  }

  mapped_type &at(const key_type &key) {
    value_type value = ft::make_pair<key_type const, mapped_type>(key, mapped_type());
    Node<value_type, Alloc> *node = _tree.getNode(_tree.root, value);

    if (!node)
      throw (std::out_of_range("Out of Range"));
    return node->data->second;
  }

  const mapped_type &at(const key_type &key) const {
    value_type value = ft::make_pair<key_type const, mapped_type>(key, mapped_type());
    Node<value_type, Alloc> *node = _tree.getNode(_tree.root, value);

    if (!node)
      throw (std::out_of_range("Out of Range"));
    return ((const mapped_type &)_tree.getNode(_tree.root, value)->data->second);
  }

  mapped_type &operator[](const key_type &key) {
    value_type value = ft::make_pair<key_type const, mapped_type>(key, mapped_type());
    Node<value_type, Alloc> *node = _tree.getNode(_tree.root, value);

    if (!node) {
      node = _tree.insert(value);
      _size++;
      return (_tree.getNode(_tree.root, value)->data->second);
    }
    return (node->data->second);
  }

  iterator begin() {
    return (iterator(_tree.getMinNode(_tree.root) ? _tree.Min(_tree.root)->data : NULL, &_tree));
  }

  const_iterator begin() const {
    return (const_iterator(_tree.getMinNode(_tree.root) ? _tree.getMinNode(_tree.root)->data : NULL,
                           &_tree));
  }

  iterator end() {
    return (iterator(NULL, &_tree));
  }

  const_iterator end() const {
    return (const_iterator(NULL, &_tree));
  }

  reverse_iterator rbegin() {
    return (reverse_iterator(end()));
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

  // #############################################################################################
  // ######################################### CAPACITY ###########################################
  // #############################################################################################

  bool empty() const {
    return (_size == 0);
  }

  size_type size() const {
    return (_size);
  }

  size_type max_size() const {
    return (std::numeric_limits<size_type>::max() / sizeof(Node<value_type, Alloc>));
  }

  // #############################################################################################
  // ######################################### MODIFIERS ##########################################
  // #############################################################################################

  pair<iterator, bool> insert(const value_type &value) {
    Node<value_type, Alloc> *node = _tree.getNode(_tree.root, value);
    bool second = false;

    if (!node) {
      node = _tree.insert(value);
      second = true;
      _size++;
    }
    return (ft::make_pair<iterator, bool>(iterator(node->data, &_tree), second));
  }

  iterator insert(iterator hint, const value_type &value) {
    (void)hint;
    return (insert(value).first);
  }

  template<class InputIt>
  void insert(InputIt first,
              InputIt last,
              typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = 0) {
    while (first != last) {
      insert(*first);
      first++;
    }
  }

  void erase(iterator position) {
    _tree.deleteNodeByKey(position.node->data);
    _size--;
  }

  void erase(iterator first, iterator last) {
    while (first != last) {
      erase(first->first);
      first++;
    }
  }

  void clear() {
    _tree.clear();
    _size = 0;
  }

  void swap(map &other) {
    _swap(_comp, other._comp);
    _swap(_alloc, other._alloc);
    _swap(_size, other._size);
    _swap(_tree, other._tree);
  }

  // #############################################################################################
  // ######################################### LOOKUP ############################################
  // #############################################################################################

  size_type count(const key_type &key) const {
    if (_tree.find(_tree.root, ft::make_pair(key, mapped_type())) != NULL)
      return (1);
    return (0);
  }

  iterator find(const key_type &key) {
    Node<value_type, Alloc> *node = _tree.find(_tree.root, ft::make_pair(key, mapped_type()));
    return (iterator(node ? node->data : NULL, &_tree));
  }

  const_iterator find(const key_type &key) const {
    Node<value_type, Alloc> *node = _tree.find(_tree.root, ft::make_pair(key, mapped_type()));
    return (const_iterator(node ? node->data : NULL, &_tree));
  }

  pair<iterator,
       iterator> equal_range(const key_type &key) {
    return (ft::make_pair(lower_bound(key),
                          upper_bound(key)));
  }

  pair<const_iterator,
       const_iterator> equal_range(const key_type &key) const {
    return (ft::make_pair(lower_bound(key), upper_bound(key)));
  }

  iterator lower_bound(const key_type &key) {
    Node<value_type, Alloc> *node = _tree.root;
    Node<value_type, Alloc> *lower = node;

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
    Node<value_type, Alloc> *node = _tree.root;
    Node<value_type, Alloc> *lower = node;

    while (node != NULL) {
      if (!_comp(node->data->first, key)) {
        lower = node;
        node = node->left;
      } else
        node = node->right;
    }
    return (const_iterator(lower ? lower->data : NULL, &_tree));
  }

  iterator upper_bound(const key_type &key) {
    Node<value_type, Alloc> *node = _tree.root;
    Node<value_type, Alloc> *upper = node;

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
    Node<value_type, Alloc> *node = _tree.root;
    Node<value_type, Alloc> *upper = node;

    while (node != NULL) {
      if (_comp(key, node->data->first)) {
        upper = node;
        node = node->left;
      } else
        node = node->right;
    }
    return (const_iterator(upper ? upper->data : NULL, &_tree));
  }

  key_compare key_comp() const {
    return (_comp);
  }

  value_compare value_comp() const {
    return (value_compare(_comp));
  }

 private:

  Tree<value_type, Compare, Alloc> _tree;

  allocator_type _alloc;

  size_type _size;

  key_compare _comp;

// #############################################################################################
// ######################################### NON-MEMBER #########################################
// #############################################################################################

  template<typename U>
  void _swap(U &a, U &b) {
    U tmp = a;
    a = b;
    b = tmp;
  };

};

template<class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key, T, Compare, Alloc> &lhs,
                const map<Key, T, Compare, Alloc> &rhs) {
  return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key, T, Compare, Alloc> &lhs,
                const map<Key, T, Compare, Alloc> &rhs) {
  return !(ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template<class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc> &lhs,
               const map<Key, T, Compare, Alloc> &rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key, T, Compare, Alloc> &lhs,
                const map<Key, T, Compare, Alloc> &rhs) {
  return !(lhs > rhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key, T, Compare, Alloc> &lhs,
               const map<Key, T, Compare, Alloc> &rhs) {
  return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
}

template<class Key, class T, class Compare, class Alloc>
bool operator>=(const map<Key, T, Compare, Alloc> &lhs,
                const map<Key, T, Compare, Alloc> &rhs) {
  return !(lhs < rhs);
}

template<class Key, class T, class Compare, class Alloc>
void swap(map<Key, T, Compare, Alloc> &lhs, map<Key, T, Compare, Alloc> &rhs) {
  lhs.swap(rhs);
}

}
#endif //FT_CONTAINERS_MAP_HPP
