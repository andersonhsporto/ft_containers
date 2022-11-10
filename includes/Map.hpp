//
// Created by Anderson Porto on 11/9/22.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <memory>
#include "ft_utility.hpp"

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
};
}

#endif //FT_CONTAINERS_MAP_HPP
