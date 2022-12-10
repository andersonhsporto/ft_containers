//
// Created by Anderson Porto on 12/4/22.
//

#ifndef FT_CONTAINERS_MAPITERATOR_HPP
#define FT_CONTAINERS_MAPITERATOR_HPP

#include <cstddef>
#include <iterator>
#include "../0-Utilities/ConstEnum.hpp"
#include "../3-map/ft_pair.hpp"
#include "../3-map/Tree.hpp"

namespace ft {

template<typename T, typename Compare, typename Alloc>
class MapIterator {
 public:
  typedef T value_type;

  typedef T *pointer;

  typedef T &reference;

  typedef std::bidirectional_iterator_tag iterator_category;

  typedef Node<value_type, Alloc> node_type;
  /*-----------------------------------------------------------------------------------------------------------------------------*/
  /*-----[ Member Functions ]-----*/
  MapIterator() : _it(NULL) {}

  explicit MapIterator(pointer it, const Tree<value_type, Compare, Alloc> *avl = NULL)
      : _it(it), _avl(avl) {}

  MapIterator(MapIterator const &copy) { *this = copy; }

  MapIterator &operator=(MapIterator const &copy) {
    _it = copy._it;
    _avl = copy._avl;
    return (*this);
  }

  ~MapIterator() {}

  operator MapIterator<const T, Compare, Alloc>() const {
    return (MapIterator<const T, Compare, Alloc>(_it,
                                                            reinterpret_cast<Tree<const value_type,
                                                                                 Compare,
                                                                                 Alloc> const *>(_avl)));
  }
  /*-----[ Expressions ]-----*/
  //	Equivalence operations (a == b / a != b)
  bool operator==(MapIterator const &obj) { return (_it == obj._it); }

  bool operator!=(MapIterator const &obj) { return (_it != obj._it); }

  //	Dereference as ab value (*a or a->m) even as mutable iterator (*a = t)
  reference operator*() { return (*_it); }

  pointer operator->() { return (&operator*()); }

  // increment and decrement (++a or a++ / --a or a--)
  MapIterator &operator++() {
    node_type *node = _avl->getNode(_avl->root, *_it);
    if (node) {
      node_type *tmp = _avl->getNextNode(*_it);

      if (tmp)
        _it = tmp->data;
      else
        _it = NULL;
    }
    return (*this);
  }

  MapIterator operator++(int) {
    MapIterator tmp = *this;
    ++(*this);
    return (tmp);
  }

  MapIterator &operator--() {
    node_type *node = NULL;

    if (!_it) {
      node = _avl->getMaxNode(_avl->root);
      if (node) _it = node->data;
      return (*this);
    }
    node = _avl->getNode(_avl->root, *_it);
    if (node) {
      node_type *tmp = _avl->previous(*_it);
      if (tmp) _it = tmp->data;
      else _it = NULL;
    }
    return (*this);
  }

  MapIterator operator--(int) {
    MapIterator tmp = *this;
    --(*this);
    return (tmp);
  }

 private:
  pointer _it;

  const Tree<value_type, Compare, Alloc> *_avl;
};

}

#endif //FT_CONTAINERS_MAPITERATOR_HPP
