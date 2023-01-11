//
// Created by Anderson Porto on 10/17/22.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "../1-Iterators/VectorIterator.hpp"
#include "../1-Iterators/ReverseIterator.hpp"
#include "../ft_iterator_types.hpp"
#include "../ft_algorithm.hpp"

namespace ft {
template<class T, class Allocator = std::allocator<T> >
class vector {
  // ***********************************************************************************************
  // *************************************** Member types ******************************************
  // ***********************************************************************************************
 public:
  typedef T value_type;

  typedef Allocator allocator_type;

  typedef std::size_t size_type;

  typedef std::ptrdiff_t difference_type;

  typedef typename allocator_type::reference reference;

  typedef typename allocator_type::const_reference const_reference;

  typedef typename allocator_type::pointer pointer;

  typedef typename allocator_type::const_pointer const_pointer;

  typedef ft::VectorIterator<value_type> iterator;

  typedef ft::VectorIterator<const value_type> const_iterator;

  typedef ft::ReverseIterator<iterator> reverse_iterator;

  typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;

  // ***********************************************************************************************
  // *************************************** Constructors ******************************************
  // ***********************************************************************************************

  vector() : _size(0), _storageSpace(0), _data(NULL) {}

  explicit vector(const allocator_type &alloc)
      : _allocator(alloc), _size(0), _storageSpace(0), _data(NULL) {}

  explicit vector(size_type count,
                  const value_type &value = value_type(),
                  const allocator_type &alloc = allocator_type()) {
    _size = count;
    _storageSpace = count;
    _allocator = alloc;
    _data = _allocator.allocate(count);
    for (size_type i = 0; i < count; i++)
      _allocator.construct(_data + i, value);
  }

  template<class Interator>
  vector(Interator first,
         Interator last,
         const allocator_type &alloc = allocator_type(),
         typename ft::enable_if<!ft::is_integral<Interator>::value,
                                Interator>::type = Interator()) {
    size_type temp = last - first;
    _deallocate();
    _data = _allocator.allocate(temp);
    for (size_type i = 0; i < temp; i++) {
      _allocator.construct(_data + i, *first);
      first++;
    }
    _size = last - first;
    _storageSpace = last - first;
    _allocator = alloc;
  }

  vector(const vector &other) {
    _size = 0;
    _storageSpace = 0;
    *this = other;
  }

  vector &operator=(const vector &other) {
    if (this != &other) {
      clear();
      _deallocate();
      _size = other._size;
      _storageSpace = other._storageSpace;
      _allocator = other._allocator;
      if (_storageSpace)
        _data = _allocator.allocate(_storageSpace);
      for (size_type i = 0; i < _size; i++)
        _allocator.construct(_data + i, other._data[i]);
    }
    return *this;
  }

  ~vector() {
    for (size_type i = 0; i < _size; i++)
      _allocator.destroy(_data + i);
    _deallocate();
  }

  // ***********************************************************************************************
  // *************************************** Member functions **************************************
  // ***********************************************************************************************

  void assign(size_type count, const value_type &value) {
    _size = 0;
    reserve(count);
    for (size_type i = 0; i < count; i++)
      push_back(value);
  }

  template<class Interator>
  void assign(Interator first,
              Interator last,
              typename ft::enable_if<!ft::is_integral<Interator>::value,
                                     Interator>::type = Interator()) {
    clear();
    reserve(last - first);
    while (first != last)
      push_back(*first++);
  }

  // ***********************************************************************************************
  // *************************************** SIZE FUNCTIONS ****************************************
  // ***********************************************************************************************

  bool empty() const {
    return _size == 0;
  }

  size_type size() const {
    return _size;
  }

  size_type max_size() const {
    return (_allocator.max_size());
  }

  // ***********************************************************************************************
  // *************************************** ELEMENT ACCESS ****************************************
  // ***********************************************************************************************

  allocator_type get_allocator() const {
    return (_allocator);
  }

  reference at(size_type pos) {
    if (pos >= this->size())
      throw (std::out_of_range("ft::vector::out-of-range"));
    return (_data[pos]);
  }

  const_reference at(size_type pos) const {
    if (pos >= this->size())
      throw (std::out_of_range("ft::vector::out-of-range"));
    return (_data[pos]);
  }

  reference operator[](size_type pos) {
    return (_data[pos]);
  }

  const_reference operator[](size_type pos) const {
    return (_data[pos]);
  }

  reference front() {
    return (_data[0]);
  }

  const_reference front() const {
    return (_data[0]);
  }

  reference back() {
    return (_data[_size - 1]);
  }

  const_reference back() const {
    return (_data[_size - 1]);
  }

// ***********************************************************************************************
// *************************************** ITERATORS *********************************************
// ***********************************************************************************************

  value_type *data() {
    return _data;
  }

  const value_type *data() const {
    return _data;
  }

  iterator begin() {
    return iterator(_data);
  }

  const_iterator begin() const {
    return const_iterator(_data);
  }

  iterator end() {
    return iterator(_data + _size);
  }

  const_iterator end() const {
    return const_iterator(_data + _size);
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

  // ***********************************************************************************************
  // *************************************** MODIFIERS *********************************************
  // ***********************************************************************************************

  void reserve(size_type new_cap) {
    if (new_cap > max_size())
      throw std::length_error("ft::vector::length_error");

    if (new_cap > _storageSpace) {
      pointer ptr2 = _allocator.allocate(new_cap);
      for (size_type i = 0; i < _size; i++)
        _allocator.construct(ptr2 + i, _data[i]);
      _deallocate();
      _swap(ptr2, _data);
      _storageSpace = new_cap;
    }
  }

  size_type capacity() const {
    return _storageSpace;
  }

  void clear() {
    for (size_type i = 0; i < _size; i++)
      _allocator.destroy(_data + i);
    _size = 0;
  }

  iterator insert(iterator pos, const value_type &value) {
    vector tmp;
    size_type index = pos - begin();
    size_type tmp_end = end() - pos;

    tmp.assign(pos, end());
    _size = index;
    push_back(value);
    for (size_type i = 0; i < tmp_end; i++)
      push_back(tmp[i]);
    return (begin() + index);
  }

  void insert(iterator pos, size_type count, const value_type &value) {
    vector tmp;
    size_type index = pos - begin();
    size_type tmp_end = end() - pos;

    tmp.assign(pos, end());
    if ((count + _storageSpace) > (_storageSpace * 2))
      reserve(_size + count);
    else if (!_size)
      reserve(count);
    _size = index;
    for (size_type i = 0; i < count; i++)
      push_back(value);
    for (size_type i = 0; i < tmp_end; i++)
      push_back(tmp[i]);
  }

  template<class Interator>
  void insert(iterator pos,
              Interator first,
              Interator last,
              typename ft::enable_if<!ft::is_integral<Interator>::value,
                                     Interator>::type = Interator()) {
    vector tmp;
    size_type index = pos - begin();
    size_type tmp_end = end() - pos;
    difference_type diference = last - first;

    tmp.assign(pos, end());
    if ((diference + _storageSpace) > (_storageSpace * 2))
      reserve(_size + diference);
    else if (!_size)
      reserve(diference);
    _size = index;
    do {
      push_back(*first++);
    } while (first != last);
    for (size_type i = 0; i < tmp_end; i++)
      push_back(tmp[i]);
  }

  iterator erase(iterator pos) {
    if (_size > 0)
      _allocator.destroy(&*pos);
    for (iterator it = pos; it != end(); it++) {
      _allocator.construct(&*it, *(it + 1));
      _allocator.destroy(&*(it + 1));
    }
    _size--;
    return pos;
  }

  iterator erase(iterator first, iterator last) {
    iterator tmp = first;
    do {
      *tmp = *last;
      tmp++;
      last++;
    } while (last != end());
    _size -= last - first;
    return tmp;
  }

  void push_back(const value_type &value) {
    if (_storageSpace == 0)
      reserve(1);
    else if (_size + 1 > _storageSpace)
      reserve(_storageSpace * 2);
    _allocator.construct(_data + _size, value);
    _size++;
  }

  void pop_back() {
    if (_size > 0) {
      _allocator.destroy(_data + _size);
      _size--;
    }
  }

  void resize(size_type count, value_type value = value_type()) {
    if (count < _size) {
      while (_size > count) {
        _allocator.destroy(_data + _size);
        _size--;
      }
    } else if (count > _size) {
      reserve(count);
      for (size_type i = _size; i < count; i++) {
        _allocator.construct(_data + i, value);
        _size++;
      }
    }
  }

  void swap(vector &other) {
    _swap(_size, other._size);
    _swap(_storageSpace, other._storageSpace);
    _swap(_data, other._data);
  }

  // ***********************************************************************************************
  // ***********************************************************************************************
  // ***********************************************************************************************
  // ***********************************************************************************************
  // ***********************************************************************************************
  // ***********************************************************************************************
  // ***********************************************************************************************
  // ***********************************************************************************************
  // ***********************************************************************************************

 private:
  size_type _size;

  size_type _storageSpace;

  pointer _data;

  allocator_type _allocator;

  void _deallocate() {
    if (_storageSpace)
      _allocator.deallocate(_data, _storageSpace);
  }

  template<typename U>
  void _swap(U &a, U &b) {
    U tmp = a;
    a = b;
    b = tmp;
  }
};

template<class T, class Allocator>
void swap(vector<T, Allocator> &lhs, vector<T, Allocator> &rhs) {
  lhs.swap(rhs);
}

template<class T, class Allocator>
bool operator==(const vector<T, Allocator> &lhs,
                const vector<T, Allocator> &rhs) {
  return (
      ft::equal(lhs.begin(),
                lhs.end(),
                rhs.begin()));
}

template<class T, class Allocator>
bool operator!=(const vector<T, Allocator> &lhs,
                const vector<T, Allocator> &rhs) {
  return (
      !(ft::equal(lhs.begin(),
                  lhs.end(),
                  rhs.begin())));
}

template<class T, class Allocator>
bool operator<(const vector<T, Allocator> &lhs,
               const vector<T, Allocator> &rhs) {
  return (
      ft::lexicographical_compare(lhs.begin(),
                                  lhs.end(),
                                  rhs.begin(),
                                  rhs.end()));
}

template<class T, class Allocator>
bool operator<=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs) {
  return !(lhs > rhs);
}

template<class T, class Allocator>
bool operator>(const vector<T, Allocator> &lhs,
               const vector<T, Allocator> &rhs) {
  return (
      ft::lexicographical_compare(rhs.begin(),
                                  rhs.end(),
                                  lhs.begin(),
                                  lhs.end()));
}

template<class T, class Allocator>
bool operator>=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs) {
  return !(lhs < rhs);
}
}

#endif //FT_CONTAINERS_VECTOR_HPP
