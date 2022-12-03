//
// Created by Anderson Porto on 11/10/22.
//

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

#include "Node.hpp"

enum BalanceFactor {
  LEFT_HEAVY = -1,
  RIGHT_HEAVY = 1,
  BALANCED = 0
};

namespace ft {
template<
    typename T,
    class Compare,
    class Allocator
>
class Tree {

 public:

  /* ###############################################################################################
   * #########################################  Member Types  ######################################
   * ###############################################################################################
   */

  typedef T value_type;

  typedef Compare key_comparator;

  typedef Allocator allocator_type;

  typedef Node<value_type, allocator_type> node_type;

  /* ###############################################################################################
   * #########################################  Public Variables  ##################################
   * ###############################################################################################
   */

  node_type *root;

  // A structure that enables an allocator for objects of one type to allocate storage
  // for objects of another type.
  // This structure is useful for allocating memory for
  // type that differs from the element type of the container being implemented.
  typename allocator_type::template rebind<node_type>::other node_allocator_type;

  /* ###############################################################################################
   * #########################################  Constructors  ######################################
   * ###############################################################################################
   */

  // Empty Constructor -> creates an empty tree
  Tree() : root(NULL) {}

  // Copy Constructor -> creates a copy of the tree
  Tree(const Tree &avl) {
    *this = avl;
  }

  // Assignment Operator -> assigns the tree
  Tree &operator=(const Tree &source) {
    if (this != &source) {
      root = source.root;
      _comparator = source._comparator;
    }
    return *this;
  }

  // Destructor
  ~Tree() {}

  /* ###############################################################################################
   * #########################################  Public Functions  ##################################
   * ###############################################################################################
   */

  // Node height getter
  int getHeight(node_type *node) {
    if (node) {
      return node->height;
    }
    return 0;
  }

  // Recursive assign all node of a given tree to another tree
  void assign(node_type const *node) {
    if (node) {
      assign(node->left);
      if (node->data) {
        insert(node->data);
      }
      assign(node->right);
    }
  }

  // Insert a new node in the root Avl tree node
  node_type *insert(value_type key) {
    this->root = this->insert(this->root, key);
    return root;
  }

  node_type *insert(node_type *node, const value_type &key) {
    if (!node)
      return (createNode(key));

    if (_comparator(key.first, node->data->first)) {
      node->left = insert(node->left, key);
      node->left->parent = node;
    } else if (_comparator(node->data->first, key.first)) {
      node->right = insert(node->right, key);
      node->right->parent = node;
    } else
      return (node);

    updateHeight(node);
    return (balance(node, key));
  }

  bool erase(value_type key) {
    if (find(root, key)) {
      this->root = this->eraseNode(this->root, key);
      return (true);
    }
    return (false);
  }

  node_type *eraseNode(node_type *node, value_type const &key) {
    // If the root is NULL, then return root (Base case)
    if (node == NULL)
      return (node);

    // If the key to be deleted is
    // smaller than the root's
    // key, then it lies in left subtree
    if (_comparator(key.first, node->data->first))
      node->left = eraseNode(node->left, key);

      // If the key to be deleted is
      // greater than the root's
      // key, then it lies in right subtree
    else if (_comparator(node->data->first, key.first))
      node->right = eraseNode(node->right, key);

      // if key is same as root's key,
      // then This is the node to be deleted
    else if (node->data->first == key.first) {
      if (isChildPresent(node)) {
        node_type *childNode = getChild(node);

        // node has no child
        if (childNode == NULL) {
          childNode = node;
          node = NULL;
        } else {
          // node with only one child
          node_type *parent = node->parent;

          *node = *childNode;
          node->parent = parent;
        }
        deallocate(childNode);
      } else {
        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        node_type *tmp = minNode(node->right);                //(3)

        // Copy the inorder successor's content to this node
        _allocator.construct(node->data, *tmp->data);

        // Delete the inorder successor
        node->right = eraseNode(node->right, *tmp->data);
      }
    }

    // Fix invalid read
    if (!node)
      return (node);

    // Update height
    updateHeight(node);

    // Balance the tree
    return (balance(node, key));
  }

  node_type *find(value_type const &key) {
    return (find(this->root, key));
  }

  node_type *find(node_type *node, value_type const &key) const {
    if (!node)
      return (NULL);

    if (node->data && node->data->first == key.first)
      return (node);

    if (_comparator(key.first, node->data->first))
      return (find(node->left, key));

    else if (_comparator(node->data->first, key.first))
      return (find(node->right, key));

    return (node);
  }

  node_type *next(value_type const &key) const {
    node_type *node = find(root, key);

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

  node_type *previous(value_type const &key) const {
    node_type *node = find(root, key);

    if (!node)
      return NULL;

    if (node->left != NULL)
      return maxNode(node->left);

    node_type *previous = node->parent;
    while (previous != NULL && node == previous->left) {
      node = previous;
      previous = previous->parent;
    }
    node = previous;
    return (node);
  }

  // Recursive function to find the maximum value in the tree
  node_type *maxNode(node_type *node) const {
    if (node == NULL) {
      return NULL;
    }

    if (node->right == NULL) {
      return node;
    }

    return maxNode(node->right);
  }

  // Recursive function to find the minimum node in the tree
  node_type *minNode(node_type *node) const {
    if (node == NULL) {
      return NULL;
    }

    if (node->left == NULL) {
      return node;
    }

    return minNode(node->left);
  }

  void destroyRoot() {
    if (root) {
      destroyNode(root);
      root = NULL;
    }
  }

  std::size_t max_size() const {
    return _allocator.max_size();
  }

 private:

  /* ###############################################################################################
   * #########################################  PRIVATE ATTRIBUTES  ################################
   * ###############################################################################################
   */

  key_comparator _comparator;

  allocator_type _allocator;

  /* ###############################################################################################
   * #########################################  PRIVATE METHODS  ###################################
   * ###############################################################################################
   */

  // Update the height of the node
  void updateHeight(node_type *node) {
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
  }

  // Factory method to create a new node
  node_type *createNode(const value_type &data) {
    node_type *node = node_allocator_type.allocate(1);

    node_allocator_type.construct(node, node_type(data));
    return node;
  }

  /* ###############################################################################################
   * #########################################  BALANCE METHODS  ###################################
   * ###############################################################################################
   */

  // Return the balance factor of the node
  BalanceFactor getBalanceFactor(node_type *node) {
    if (node == NULL) {
      return BALANCED;
    }

    if (getHeight(node->left) - getHeight(node->right) > 1) {
      return LEFT_HEAVY;
    } else if (getHeight(node->left) - getHeight(node->right) < -1) {
      return RIGHT_HEAVY;
    }
    return BALANCED;
  }

  // Balance the tree
  node_type *balance(node_type *node, value_type const &key) {
    // If the tree is left heavy unbalance it
    if (getBalanceFactor(node) == LEFT_HEAVY) {
      return leftHeavyBalance(node, key);
    }

    // If the tree is right heavy unbalance it
    if (getBalanceFactor(node) == RIGHT_HEAVY) {
      return rightHeavyBalance(node, key);
    }

    // If the tree is balanced, return the node
    return (node);
  }

  // Balance the tree if it is left heavy
  node_type *leftHeavyBalance(node_type *node, value_type const &key) {
    if (_comparator(key.first, node->left->data->first))
      return (rotateRight(node));
    else {
      node->left = rotateLeft(node->left);
      return (rotateRight(node));
    }
  }

  // Balance the tree if it is right heavy
  node_type *rightHeavyBalance(node_type *node, value_type const &key) {
    if (_comparator(node->right->data->first, key.first))
      return (rotateLeft(node));
    else {
      node->left = rotateRight(node->left);
      return (rotateLeft(node));
    }
  }

  // Right Rotation
  node_type *rotateRight(node_type *z) {
    node_type *y = z->left;

    if (y == NULL) {
      return z;
    }

    // Temporary pointer to the right child of y
    node_type *T3 = y->right;

    if (y->right != NULL)
      y->right->parent = z;

    y->right = z;
    z->left = T3;
    y->parent = z->parent;
    z->parent = y;

    // Update heights
    updateHeight(z);
    updateHeight(y);
    return (y);
  }

  node_type *rotateLeft(node_type *z) {
    node_type *y = z->right;        // set y
    node_type *T2 = y->left;        // save for z->left

    if (y->left != NULL)
      y->left->parent = z;

    //	y->parent is z, everything is set to rotate
    y->left = z;
    z->right = T2;
    y->parent = z->parent;
    z->parent = y;

    // Update heights
    updateHeight(z);
    updateHeight(y);
    return (y);
  }

  // Recursive destroy node and all its children
  void destroyNode(node_type *node) {
    if (node) {
      destroyNode(node->left);
      destroyNode(node->right);
      deallocate(node);
    }
  }

  void deallocate(node_type *node) {
    _allocator.deallocate(node->data, 1);
    node_allocator_type.deallocate(node, 1);
    node = NULL;
  }

  /* ###############################################################################################
   * #########################################  UTILS METHODS  #####################################
   * ###############################################################################################
   */

  // Check if there is a child in the node
  bool isChildPresent(node_type *node) {
    return (node->left == NULL || node->right == NULL);
  }

  node_type *getChild(node_type *node) {
    if (node->left != NULL) {
      return node->left;
    } else {
      return node->right;
    }
  }

};

}

#endif //FT_CONTAINERS_TREE_HPP
