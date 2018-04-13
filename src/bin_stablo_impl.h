#ifndef BIN_STABLO_IMPL_H_INCLUDED
#define BIN_STABLO_IMPL_H_INCLUDED

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
  /// TODO ================================================
}

template <typename T>
ErrorCode BinarySTree<T>::remove(T const& t) {
  return remove_impl(root, t);
}

template <typename T>
ErrorCode BinarySTree<T>::remove_impl(Node<T>*& node, T const& t) {
  /// TODO ================================================
  auto same = [](T const& a, T const& b) {
    return !(a < b || b < a);
  };
  if (same(node->left->data, t))  {}

  // ZA dodatne bodove, TODO!
  return success;
}

template <typename T>
ErrorCode BinarySTree<T>::remove(Node<T>*& root) {
  /// TODO ================================================
  if (root == nullptr) {
    return notfound;
  }
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
