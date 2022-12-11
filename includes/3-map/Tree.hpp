//
// Created by Anderson Porto on 12/10/22.
//

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

#include "Node.hpp"

namespace ft {

template<typename T, class Compare, class Allocator>
class Tree {
 public:
  typedef T value_type;

  typedef Node<value_type, Allocator> node_type;

  typedef Compare key_compare;

  typedef Allocator allocator_type;

  // ##############################################################################################
  // ######################################### ROOT ################################################
  // ##############################################################################################

  node_type *root;

  // ##############################################################################################
  // ######################################### CONSTRUCTORS ########################################
  // ##############################################################################################

  Tree() : root(NULL) {}

  Tree(Tree const &copy) {
    *this = copy;
  }

  Tree &operator=(Tree const &copy) {
    if (this == &copy) {
      root = copy.root;
      _comp = copy._comp;
    }
    return (*this);
  }

  ~Tree() {}

  int getHeight(node_type *node) {
    if (node)
      return node->height;
    return (0);
  }

  void copyNode(const node_type *node) {
    if (node) {
      copyNode(node->left);
      if (node->data)
        insert(*(node->data));
      copyNode(node->right);
    }
  }
  
  node_type *insert(value_type key) {
    this->root = this->insert(this->root, key);
    return (root);
  }

  //	Insert a node to the tree and re_balance if needed.
  //	The insertion will be on the right node, if the current key is greater than the root key, or in the left node if the current key is lower than the root key.
  //	_comp is TRUE if less, FALSE if greater or equal
  node_type *insert(node_type *node, const value_type &key) {
    if (!node)
      return (_newNode(key));

    if (_comp(key.first, node->data->first)) {
      node->left = insert(node->left, key);
      node->left->parent = node;
    } else if (_comp(node->data->first, key.first)) {
      node->right = insert(node->right, key);
      node->right->parent = node;
    } else
      return (node);
    _updateHeight(node);
    return (_balance(node, key));
  }
  /*-----------------------------------------------------------------------------------------------------------------------------*/
  /*-----[ Delete ]-----*/
  //	Delete the root node, if there is one.
  bool del(value_type key) {
    if (getNode(root, key)) {
      this->root = this->del(this->root, key);
      return (true);
    }
    return (false);
  }

  //	Delete a node recursively form the last node to the root node:
  //	- (1) Child Nodes receives a NULL;
  //	- (2) In case of one Child node, the parent of the node, will become the parent of the child.
  //	- (3) If thre is 2 child nodes, You should getNode the next child (minNode of the right child) rotate the node and delete the child.
  //	_comp is TRUE if less, FALSE if greater or equal
  node_type *del(node_type *node, value_type const &key) {
    if (!node)
      return (node);                        //(1)

    if (_comp(key.first, node->data->first))
      node->left = del(node->left, key);
    else if (_comp(node->data->first, key.first))
      node->right = del(node->right, key);
    else if (node->data->first == key.first) {
      if (!node->left || !node->right) {
        node_type *tmp = node->left ? node->left : node->right;
        if (!tmp) {
          tmp = node;
          node = NULL;
        } else {
          node_type *nodeParent = node->parent;        //(2)
          *node = *tmp;
          node->parent = nodeParent;
        }
        _alloc.deallocate(tmp->data, 1);
        rebind_allocator.deallocate(tmp, 1);
      } else {
        node_type *tmp = minNode(node->right);                //(3)
        _alloc.construct(node->data, *tmp->data);
        node->right = del(node->right, *tmp->data);
      }
    }
    if (!node)
      return (node);                                            //After onde deletion, it updates the height and return the node.
      
    _updateHeight(node);
    return (_balance(node, key));
  }

  node_type *getNode(node_type *node, value_type const &key) const {
    if (!node)
      return (NULL);

    if (node->data && node->data->first == key.first)
      return (node);

    if (_comp(key.first, node->data->first))
      return (getNode(node->left, key));

    else if (_comp(node->data->first, key.first))
      return (getNode(node->right, key));
    return (node);
  }

  node_type *getNodeByValue(value_type const &key) const {
    return getNode(root, key);
  }

  // Search a given key in the tree and return the node if found, otherwise NULL
  bool keyIsPresent(value_type const &key) const {
    return (getNode(root, key) != NULL);
  }

  /*	Return the next node:
              - Return NULL if there is no next;
              - If there is a right subtree, getNode the minimal node of the subtree;
              - If there is only a left subtree, check if the parent is not the next node, instead of the left one.
  */
  node_type *next(value_type const &key) const {
    node_type *node = getNode(root, key);
    if (!node)
      return (NULL);

    if (node->right != NULL)
      return (minNode(node->right));

    node_type *next = node->parent;
    while (next != NULL && node == next->right) {
      node = next;
      next = next->parent;
    }
    node = next;
    return (node);
  }

  /*	Return the next node:
              - Return NULL if there is no next;
              - If there is a left subtree, getNode the minimal node of the subtree;
              - If there is only a right subtree, check if the parent is not the next node, instead of the right one.
  */
  node_type *previous(value_type const &key) const {
    node_type *node = getNode(root, key);
    if (!node)
      return (NULL);

    if (node->left != NULL)
      return (maxNode(node->left));

    node_type *previous = node->parent;
    while (previous != NULL && node == previous->left) {
      node = previous;
      previous = previous->parent;
    }
    node = previous;
    return (node);
  }
  /*-----------------------------------------------------------------------------------------------------------------------------*/
  /*-----[ Utility ]-----*/
  //	Return the maxNode Node Element of the Tree tree
  node_type *maxNode(node_type *node) const {
    if (!node)
      return (NULL);

    node_type *max = node;
    while (max->right)
      max = max->right;
    return (max);
  }

  //	Return the Minimal Node Element of the Tree tree
  node_type *minNode(node_type *node) const {
    if (!node)
      return (NULL);

    node_type *min = node;
    while (min->left)
      min = min->left;
    return (min);
  }

  //	Recursively deallocate the tree from
  // the last node to the root node
  void deallocateNode(node_type *node) {
    if (node) {
      deallocateNode(node->left);
      _alloc.deallocate(node->data, 1);
      deallocateNode(node->right);
      rebind_allocator.deallocate(node, 1);
      node = NULL;
    }
  }

 private:
  key_compare _comp;

  allocator_type _alloc;

  typename Allocator::template rebind<node_type>::other rebind_allocator;

  void _updateHeight(node_type *node) {
    if (node)
      node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
  }

  /*-----------------------------------------------------------------------------------------------------------------------------*/
  /*-----[ Rotation ]-----*/
  /*	RIGHT ROTATION
      -> z, y, x will be the branch members being rotated. x - y - z
      -> T1, T2, T3 and T4 are subtrees.
              z                                      y
             / \                                   /   \
            y   T4      Right Rotate (z)          x      z
           / \          - - - - - - - - ->      /  \    /  \
          x   T3                               T1  T2  T3  T4
         / \
       T1   T2
      Generaly, it is like a swap exchange of pointers.
  */
  node_type *_rotateRight(node_type *z) {
    node_type *y = z->left;    // set y

    if (!y)
      return (z);

    node_type *T3 = y->right;    // save for z->left

    if (y->right != NULL)
      y->right->parent = z;        //	y->parent is z, everything is set to rotate
    y->right = z;
    z->left = T3;
    y->parent = z->parent;
    z->parent = y;
    _updateHeight(z);
    _updateHeight(y);
    return (y);
  }

  /*	LEFT ROTATION
      -> z, y, x will be the branch members being rotated. x - y - z
      -> T1, T2, T3 and T4 are subtrees.
            z                                y
           /  \                            /   \
          T1   y     Left Rotate(z)       z      x
              /  \   - - - - - - - ->    / \    / \
             T2   x                     T1  T2 T3  T4
                  / \
                 T3  T4
      Generaly, it is like a swap exchange of pointers.
  */
  node_type *_rotateLeft(node_type *z) {
    node_type *y = z->right;        // set y
    node_type *T2 = y->left;        // save for z->left

    if (y->left != NULL)
      y->left->parent = z;                        //	y->parent is z, everything is set to rotate
    y->left = z;
    z->right = T2;
    y->parent = z->parent;
    z->parent = y;
    _updateHeight(z);
    _updateHeight(y);
    return (y);
  }


  // Factory method to create a new node
  node_type *_newNode(const value_type &key) {
    node_type *node = rebind_allocator.allocate(1);

    rebind_allocator.construct(node, key);
    return (node);
  }


  //	Balance the current branch, if needed it will rotate the  nodes, to return to an Tree status.
  //	The range of height of the Tree nodes should be between "-1 to 1", if higher it will right rotate and if it is lower than -1, left rotate it.
  //	_comp is TRUE if less, FALSE if greater or equal
  node_type *_balance(node_type *node, value_type const &key) {
    if ((getHeight(node->left) - getHeight(node->right)) > 1) {
      if (_comp(key.first, node->left->data->first)) return (_rotateRight(node));
      else {
        node->left = _rotateLeft(node->left);
        return (_rotateRight(node));
      }
    }
    if ((getHeight(node->left) - getHeight(node->right)) < -1) {
      if (_comp(node->right->data->first, key.first)) return (_rotateLeft(node));
      else {
        node->left = _rotateRight(node->left);
        return (_rotateLeft(node));
      }
    }
    return (node);
  }
};
}

#endif //FT_CONTAINERS_TREE_HPP
