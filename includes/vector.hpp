//
// Created by Anderson Porto on 10/17/22.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "Iterators/IteratorVector.hpp"
#include "ft_iterator_types.hpp"
#include "ft_algorithm.hpp"

namespace ft {
template<class T, class Allocator = std::allocator<T> >
class vector {

  // ***********************************************************************************************
  // ***********************************************************************************************
  // *************************************** Member types ******************************************
 public:
  typedef Allocator allocator_type;

  typedef typename allocator_type::reference reference;

  typedef typename allocator_type::const_reference const_reference;

  typedef std::size_t size_type;

  typedef std::ptrdiff_t difference_type;

  typedef T value_type;

  typedef typename allocator_type::pointer pointer;

  typedef typename allocator_type::const_pointer const_pointer;

  typedef ft::random_access_iterator<value_type> iterator;

  typedef ft::random_access_iterator<const value_type> const_iterator;

  typedef ft::reverse_iterator<iterator> reverse_iterator;

  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  // ***********************************************************************************************
  // ***********************************************************************************************
  // *************************************** Member functions **************************************

 public:

  // default constructor without parameters
  vector() : _size(0), _capacity(0), _data(NULL) {
    _allocator = allocator_type();
  }

  // default constructor with allocator parameter
  explicit vector(const allocator_type &alloc) : _size(0), _capacity(0), _allocator(alloc) {
    _data = NULL;
  }

  // fill constructor
  explicit vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type())
      : _size(n), _capacity(n), _allocator(alloc) {

    _data = _allocator.allocate(_capacity);
    for (size_type i = 0; i < _size; i++) {
      _allocator.construct(_data + i, val);
    }
  }

  // destructor
  ~vector() {
    for (size_type i = 0; i < _size; i++) {
      _allocator.destroy(_data + i);
    }
    if (_data != NULL) {
      _allocator.deallocate(_data, _capacity);
    }
  }

  // copy constructor
  vector(const vector &other)
      : _size(other._size), _capacity(other._capacity), _allocator(other._allocator) {

    *this = other;
  }

  // copy assignment operator
  vector &operator=(const vector &other) {
    if (this != &other) {
      _size = other._size;
      _capacity = other._capacity;
      _allocator = other._allocator;
      _data = _allocator.allocate(_capacity);
      for (size_type i = 0; i < _size; i++) {
        _allocator.construct(_data + i, other._data[i]);
      }
    }
    return *this;
  }

  // range constructor
  template<class InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type &alloc = allocator_type())
      : _size(0), _capacity(0), _allocator(alloc) {

    _data = NULL;
    assign(first, last);
  }

  // ***********************************************************************************************
  // ***********************************************************************************************
  // *************************************** Member functions **************************************

  // Replaces the contents of the container
  void assign(size_type n, const value_type &val) {
    clear();
    _size = n;
    _capacity = n;
    _data = _allocator.allocate(_capacity);
    for (size_type i = 0; i < _size; i++) {
      _allocator.construct(_data + i, val);
    }
  }

  // Replaces the contents of the container range version
  template<class InputIterator>
  void assign(InputIterator first, InputIterator last,
              typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
    clear();
    reserve(last - first);
    for (; first != last; first++) {
      push_back(*first);
    }
  }

  // ***********************************************************************************************
  // ***********************************************************************************************
  // *************************************** Element access ****************************************

  // Access specified element with bounds checking
  reference at(size_type pos) {
    if (pos >= _size) {
      throw std::out_of_range("Out of range");
    }
    return _data[pos];
  }

  // Access specified element with bounds checking (const)
  const_reference at(size_type pos) const {
    if (pos >= _size) {
      throw std::out_of_range("Out of range");
    }
    return _data[pos];
  }

  // Access specified element
  reference operator[](size_type pos) {
    return _data[pos];
  }

  // Access specified element (const)
  const_reference operator[](size_type pos) const {
    return _data[pos];
  }

  // Access the first element
  reference front() {
    return _data[0];
  }

  // Access the first element (const)
  const_reference front() const {
    return _data[0];
  }

  // Access the last element
  reference back() {
    return _data[_size - 1];
  }

  // Access the last element (const)
  const_reference back() const {
    return _data[_size - 1];
  }

  // Direct access to the underlying array
  pointer data() {
    return _data;
  }

  // Direct access to the underlying array (const)
  const_pointer data() const {
    return _data;
  }

  // ***********************************************************************************************
  // ***********************************************************************************************
  // ****************************************** Iterators ******************************************

  // Returns an iterator to the beginning
  iterator begin() {
    return iterator(_data);
  }

  // Returns an iterator to the beginning (const)
  const_iterator begin() const {
    return const_iterator(_data);
  }

  // Returns an iterator to the end
  iterator end() {
    return iterator(_data + _size);
  }

  // Returns an iterator to the end (const)
  const_iterator end() const {
    return const_iterator(_data + _size);
  }

  // Returns a reverse iterator to the beginning
  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }

  // Returns a reverse iterator to the beginning (const)
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  // Returns a reverse iterator to the end
  reverse_iterator rend() {
    return reverse_iterator(begin());
  }

  // Returns a reverse iterator to the end (const)
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }
  // **********************************************************************************************
  // **********************************************************************************************
  // ****************************************** Capacity ******************************************

  // Checks if the container has no elements, i.e. whether begin() == end().
  bool empty() const {
    return _size == 0;
  }

  // Returns the number of elements in the container.
  size_type size() const {
    return _size;
  }

  // Returns the maximum number of elements that the container is able to hold
  // due to system or library implementation limitations.
  size_type max_size() const {
    return _allocator.max_size();
  }

  // Increase the capacity of the vector
  // (the total number of elements that the vector can hold without requiring reallocation)
  // to a value that's greater or equal to new_cap.
  void reserve(size_type new_cap) {
    if (new_cap > max_size()) {
      throw std::length_error("vector::reserve");
    }
    if (new_cap > _capacity) {
      _capacity = new_cap;
      pointer tmp = _allocator.allocate(_capacity);
      for (size_type i = 0; i < _size; i++) {
        _allocator.construct(tmp + i, _data[i]);
      }
      for (size_type i = 0; i < _size; i++) {
        _allocator.destroy(_data + i);
      }
      _allocator.deallocate(_data, _capacity);
      _data = tmp;
    }
  }

  // Returns the number of elements that can be held in currently allocated storage
  size_type capacity() const {
    return _capacity;
  }

  // **********************************************************************************************
  // **********************************************************************************************
  // ****************************************** Modifiers *****************************************

// Erases all elements from the container. After this call, size() returns zero.
  void clear() {
    for (size_type i = 0; i < _size; i++) {
      _allocator.destroy(_data + i);
    }
    _size = 0;
  }

  // Inserts elements
  iterator insert(iterator position, const value_type &value) {
    if (_size == _capacity) {
      reserve(_capacity * 2);
    }

    size_type pos = position - begin();

    for (size_type i = _size; i > pos; i--) {
      _allocator.construct(_data + i, _data[i - 1]);
      _allocator.destroy(_data + i - 1);
    }
    _allocator.construct(_data + (position - begin()), value);
    _size++;
    return position;
  }

  // Inserts n elements
  void insert(iterator position, size_type n, const value_type &value) {
    if (_size + n > _capacity) {
      reserve(_capacity * 2);
    }

    size_type pos = position - begin();

    for (size_type i = _size; i > pos; i--) {
      _allocator.construct(_data + i + n - 1, _data[i - 1]);
      _allocator.destroy(_data + i - 1);
    }
    for (size_type i = 0; i < n; i++) {
      _allocator.construct(_data + (position - begin()) + i, value);
    }
    _size += n;
  }

  // Inserts elements from range [first, last]
  template<class InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last,
              typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
    size_type n = last - first;

    if (_size + n > _capacity) {
      reserve(_capacity * 2);
    }
    for (size_type i = _size; i > position - begin(); i--) {
      _allocator.construct(_data + i + n - 1, _data[i - 1]);
      _allocator.destroy(_data + i - 1);
    }
    for (size_type i = 0; i < n; i++) {
      _allocator.construct(_data + (position - begin()) + i, *(first + i));
    }
    _size += n;
  }

  // Erases the specified elements
  iterator erase(iterator pos) {
    for (size_type i = pos - begin(); i < _size - 1; i++) {
      _allocator.construct(_data + i, _data[i + 1]);
      _allocator.destroy(_data + i + 1);
    }
    _allocator.destroy(_data + _size - 1);
    _size--;
    return pos;
  }

  // Erases the specified elements (const)
  const_iterator erase(const_iterator pos) {
    for (size_type i = pos - begin(); i < _size - 1; i++) {
      _allocator.construct(_data + i, _data[i + 1]);
      _allocator.destroy(_data + i + 1);
    }
    _allocator.destroy(_data + _size - 1);
    _size--;
    return pos;
  }

  // Erases a range of elements [first, last]
  iterator erase(iterator first, iterator last) {
    size_type n = last - first;

    for (size_type i = first - begin(); i < _size - n; i++) {
      _allocator.construct(_data + i, _data[i + n]);
      _allocator.destroy(_data + i + n);
    }
    for (size_type i = 0; i < n; i++) {
      _allocator.destroy(_data + _size - 1 - i);
    }
    _size -= n;
    return first;
  }

  //  Adds an element to the end
  void push_back(const value_type &value) {
    if (_capacity == 0) {
      reserve(1);
    }
    if (_size == _capacity) {
      reserve(_capacity * 2);
    }
    _allocator.construct(_data + _size, value);
    _size++;
  }

  // Removes the last element
  void pop_back() {
    _allocator.destroy(_data + _size - 1);
    _size--;
  }

  // Changes the number of elements stored
  void resize(size_type n, value_type value = value_type()) {
    if (n > _size) {
      if (n > _capacity) {
        reserve(n);
      }
      for (size_type i = _size; i < n; i++) {
        _allocator.construct(_data + i, value);
      }
    } else {
      for (size_type i = _size; i > n; i--) {
        _allocator.destroy(_data + i - 1);
      }
    }
    _size = n;
  }

  // Swaps the contents of the container
  void swap(vector &other) {
    std::swap(_data, other._data);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    std::swap(_allocator, other._allocator);
  }

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
 private:

  //  size of the custom vector (number of elements)
  size_type _size;

  // number of elements that the vector can hold without requiring reallocation.
  size_type _capacity;

  //  pointer to the first element of the vector
  pointer _data;

  //  allocator object
  allocator_type _allocator;
};

// ************************************* Non-member functions *************************************

template<class T, class Alloc>
bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template<class T, class Alloc>
bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return (!(ft::equal(lhs.begin(), lhs.end(), rhs.begin())));
}

template<class T, class Alloc>
bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<class T, class Alloc>
bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return !(lhs > rhs);
}

template<class T, class Alloc>
bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template<class T, class Alloc>
bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return !(lhs < rhs);
}

template<class T, class Alloc>
void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) {
  x.swap(y);
}

}  // End of namespace ft

#endif //FT_CONTAINERS_VECTOR_HPP
