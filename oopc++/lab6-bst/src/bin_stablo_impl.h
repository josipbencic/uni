#ifndef BIN_STABLO_IMPL_H_INCLUDED
#define BIN_STABLO_IMPL_H_INCLUDED

#include <algorithm>

///// Implementacija metoda iz Node klase //////////////////////

template <typename T>
Node<T>::Node()
  : left(nullptr), right(nullptr), data() { }

template <typename T>
Node<T>::Node(T const& x)
  : left(nullptr), right(nullptr), data(x) { }


//// Implementacija metoda iz BinaryTree klase //////////////////

template <typename T>
BinarySTree<T>::BinarySTree()
  : root(nullptr) { }

template <typename T>
bool BinarySTree<T>::empty() const {
  return root == nullptr;
}

template <typename T>
int BinarySTree<T>::size() {
  return count(root);
}

template <typename T>
int BinarySTree<T>::count(Node<T>* node) {
  int cnt = 0;
  postOrder(root, [&](T const& t) {
    cnt++;
  });
  return cnt;
}

template <typename T>
bool BinarySTree<T>::isInTree(T const& t) {
  Node<T>* result = nullptr;
  auto res = find(root, t, result);
  return res;
}

template <typename T>
bool BinarySTree<T>::find(Node<T>*& node, T const& t, Node<T>*& result) {
  if (node == nullptr) {
    return false;
  }
  if (!(node->data < t || t < node->data)) {
    result = node;
    return true;
  }
  bool ret = false;
  ret = ret || find(node->left, t, result);
  ret = ret || find(node->right, t, result);
  return ret;
}

template <typename T>
ErrorCode BinarySTree<T>::insert(Node<T>*& root, T const& t) {
  if (root == nullptr) {
    root = new Node<T>{t};
    return success;
  }

  if (!(root->data < t) && !(t < root->data)) {
    return duplicate;
  }
  else if (t < root->data) {
    if (root->left) {
      return insert(root->left, t);
    }
    else {
      root->left = new Node<T>{t};
      return success;
    }
  }

  if (root->right) {
    return insert(root->right, t);
  }
  root->right = new Node<T>{t};
  return success;
}

template <typename T>
void BinarySTree<T>::clear() {
  clear_impl(root);
}

template <typename T>
void BinarySTree<T>::clear_impl(Node<T>*& node) {
  if (node == nullptr) {
    return;
  }
  if (node->left == nullptr && node->right == nullptr) {
    delete node;
    node = nullptr;
    return;
  }
  clear_impl(node->left);
  clear_impl(node->right);

  delete node;
  node = nullptr;
}

template <typename T>
ErrorCode BinarySTree<T>::remove(T const& t) {
  return remove_impl(root, t);
}

template <typename T>
ErrorCode BinarySTree<T>::remove_impl(Node<T>*& node, T const& t) {
  if (node == nullptr) {
    return notfound;
  }
  auto same = [](T const& a, T const& b) {
    return !(a < b || b < a);
  };
  if (node->left && same(node->left->data, t))  {
    remove_node(node->left);
    return success;
  }
  if (node->right && same(node->right->data, t)) {
    remove_node(node->right);
    return success;
  }
  auto l = remove_impl(node->left, t);
  if (l == success) {
    return l;
  }
  auto r = remove_impl(node->right, t);
  if (r == success) {
    return r;
  }
  return notfound;
}

template <typename T>
void BinarySTree<T>::remove_node(Node<T>*& node) {
  if (node->left == nullptr && node->right == nullptr) {
    delete node;
    node = nullptr;
    return;
  }
  if (node->left == nullptr) {
    auto* r = node->right;
    delete node;
    node = r;
    return;
  }
  if (node->right == nullptr) {
    auto* l = node->left;
    delete node;
    node = l;
    return;
  }

  /// TODO: last case: middle of the tree

  // 1) find the prev element smaller than this one
  auto* elem = node->left;
  if (elem->right == nullptr) {
    std::swap(node->data, node->left->data);
    remove_node(node->left);
    return;
  }

  while (elem->right->right != nullptr) {
    elem = elem->right;
  }
  std::swap(elem->right->data, node->data);
  remove_node(elem->right);
  return;
}

template <typename T>
ErrorCode BinarySTree<T>::remove(Node<T>*& root) {
  if (root == nullptr) {
    return notfound;
  }
  assert(root->left == nullptr && root->right == nullptr);
  delete root;
  root = nullptr;
  return success;
}

template <typename T>
template <typename Funct>
void BinarySTree<T>::preOrder(Node<T> * root, Funct visit) {
  if (root) {
    visit(root->data);
    preOrder(root->left, visit);
    preOrder(root->right, visit);
  }
}

template <typename T>
template <typename Funct>
void BinarySTree<T>::postOrder(Node<T> * root, Funct visit) {
  if (root) {
    postOrder(root->left, visit);
    postOrder(root->right, visit);
    visit(root->data);
  }
}

template <typename T>
template <typename Funct>
void BinarySTree<T>::inOrder(Node<T> * root, Funct visit) {
  if (root) {
    inOrder(root->left, visit);
    visit(root->data);
    inOrder(root->right, visit);
  }
}


#endif // BIN_STABLO_IMPL_H_INCLUDED
