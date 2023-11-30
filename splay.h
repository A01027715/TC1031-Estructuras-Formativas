#ifndef Splay_H
#define Splay_H

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class T> class SplayTree;

template <class T> class Node {
private:
  T valor;
  Node *left, *right, *parent;

  Node<T> *succesor();
  Node<T> *rot_right(Node<T> *);
  Node<T> *rot_left(Node<T> *);

public:
  Node(T);
  Node(T, Node<T> *, Node<T> *, Node<T> *);
  Node<T> *add(T);
  Node<T> *find(T);
  Node<T> *remove(T);
  void removechis();
  void inorder(stringstream &) const;
  void print_tree(stringstream &) const;
  void preorder(stringstream &) const;
  Node<T> *splay(Node<T> *, Node<T> *);

  friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val){
	valor = val;
	left  = 0;
	right = 0;
	parent= 0;
}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p){
	valor = val;
	left  = le;
	right = ri;
	parent= p;
}

template <class T> Node<T> *Node<T>::add(T val) {
  if (val < valor) {
    if (left != 0) {
      return left->add(val);
    } else {
      left = new Node<T>(val);
      left->parent = this;
      return left;
    }
  } else {
    if (right != 0) {
      return right->add(val);
    } else {
      right = new Node<T>(val);
      right->parent = this;
      return right;
    }
  }
}

template <class T> Node<T> *Node<T>::find(T val) {
  if (val == valor) {
    return this;
  } else if (val < valor) {
    if (left != 0)
      return left->find(val);
    else
      return this;
  } else {
    if (right != 0)
      return right->find(val);
    else
      return this;
  }
}

template <class T> Node<T> *Node<T>::remove(T val) {
  Node<T> *succ, *old;
  if (val < valor) {
    if (left != 0) {
      if (left->valor == val) {
        old = left;
        if (old->left != 0 && old->right != 0) {
          succ = left->succesor();
          if (succ != 0) {
            succ->left = old->left;
            succ->right = old->right;
            succ->parent = old->parent;
            if (succ->left)
              succ->left->parent = succ;
            if (succ->right)
              succ->right->parent = succ;
          }
          left = succ;
        } else if (old->right != 0) {
          old->right->parent = left->parent;
          left = old->right;

        } else if (old->left != 0) {
          old->left->parent = left->parent;
          left = old->left;
        } else {
          left = 0;
        }
        delete old;
        return this;
      } else {
        return left->remove(val);
      }
    }
  } else if (val > valor) {
    if (right != 0) {
      if (right->valor == val) {
        old = right;
        if (old->left != 0 && old->right != 0) { 
          succ = right->succesor();
          if (succ != 0) {
            succ->left = old->left;
            succ->right = old->right;
            succ->parent = old->parent;
            if (succ->left)
              succ->left->parent = succ;
            if (succ->right)
              succ->right->parent = succ;
          }
          right = succ;
        } else if (old->right != 0) {
          old->right->parent = right->parent;
          right = old->right;

        } else if (old->left != 0) {
          old->left->parent = right->parent;
          right = old->left;
        } else {
          right = 0;
        }
        delete old;
        return this;
      } else {
        return right->remove(val);
      }
    }
  }
  return this;
}

template <class T> Node<T> *Node<T>::succesor() {
  Node<T> *l, *r;

  l = left;
  r = right;

  if (right->left == 0) {
    right = right->right;
    r->right = 0;
    return r;
  }

  Node<T> *parent, *chi;
  parent = right;
  chi = right->left;
  while (chi->left != 0) {
    parent = chi;
    chi = chi->left;
  }
  parent->left = chi->right;
  chi->right = 0;
  return chi;
}

template <class T> void Node<T>::removechis() {
  if (left != 0) {
    left->removechis();
    delete left;
    left = 0;
  }
  if (right != 0) {
    right->removechis();
    delete right;
    right = 0;
  }
}

template <class T> Node<T> *Node<T>::rot_right(Node<T> *n) {
  Node<T> *r = n->left;
  n->left = r->right;
  if (r->right){r->right->parent = n;}
  r->right = n;
  r->parent = n->parent;
  n->parent = r;
  if (r->parent) {
    if (r->parent->left && r->parent->left->valor == n->valor){r->parent->left = r;}
    else{r->parent->right = r;}
  }
  return r;
}

template <class T> Node<T> *Node<T>::rot_left(Node<T> *n) {
  Node<T> *r = n->right; 
  n->right = r->left;
  if (r->left){r->left->parent = n;}
  r->left = n;
  r->parent = n->parent;
  n->parent = r;
  if (r->parent) {
    if (r->parent->left && r->parent->left->valor == n->valor){r->parent->left = r;}
    else {r->parent->right = r;}
  }
  return r;
}

template <class T> Node<T> *Node<T>::splay(Node<T> *root, Node<T> *n) {
  while (n->parent != 0) {

    if (n->parent->valor == root->valor) {
      if (n->parent->left && n->parent->left->valor == n->valor) {rot_right(n->parent);}
	  else {rot_left(n->parent);}
    }
	else {
      Node<T> *x = n->parent;
      Node<T> *y = x->parent;
      if (x->left && y->left && n->valor == x->left->valor 
	  	  && x->valor == y->left->valor) {
    	rot_right(y);
        rot_right(x);
      }
	  else if (x->right && y->right && n->valor == x->right->valor && 
	  		   x->valor == y->right->valor) {
        rot_left(y);
        rot_left(x);
      }
	  else if (x->left && y->right && n->valor == x->left->valor &&
	  		   x->valor == y->right->valor) {
        rot_right(x);
        rot_left(y);
      }
	  else {
        rot_left(x);
        rot_right(y);
      }
    }
  }
  return n;
}

template <class T> void Node<T>::inorder(stringstream &aux) const {
  if (left != 0) {
    left->inorder(aux);
  }
  if (aux.tellp() != 1){
    aux << " ";
  }
  aux << valor;
  if (right != 0) {
    right->inorder(aux);
  }
}

template <class T> void Node<T>::print_tree(stringstream &aux) const {
  if (parent != 0) {
    aux << "\n node " << valor;
    aux << " parent " << parent->valor;
  }
  else{aux << "\n root " << valor;}
  if (left != 0){aux << " left " << left->valor;}
  if (right != 0){aux << " right " << right->valor;}
  aux << "\n";

  if (left != 0) {left->print_tree(aux);}
  if (right != 0) {right->print_tree(aux);}
}

template <class T> void Node<T>::preorder(stringstream &aux) const {
  aux << valor;
  if (left != 0) {
    aux << " ";
    left->preorder(aux);
  }
  if (right != 0) {
    aux << " ";
    right->preorder(aux);
  }
}

template <class T> class SplayTree {
private:
  Node<T> *root;
  int size = 0;

public:
  SplayTree();
  bool empty() const;
  void add(T);
  bool find(T);
  void remove(T);
  string inorder() const;
  string preorder() const;
};

template <class T> SplayTree<T>::SplayTree() {root = 0;}

template <class T> bool SplayTree<T>::empty() const { return (root == 0); }

template <class T> void SplayTree<T>::add(T val) {

  if (root != 0) {
    Node<T> *added = root->add(val);
    root = root->splay(root, added);
  }
  else {root = new Node<T>(val);}
  size++;
}

template <class T> void SplayTree<T>::remove(T val) {
  if (root != 0) {
    if (val == root->valor) {
      Node<T> *succ = root->succesor();
      if (succ != 0) {
        succ->left = root->left;
        succ->right = root->right;
        succ->parent = 0;
        if (succ->left){succ->left->parent = succ;}
        if (succ->right){succ->right->parent = succ;}
      }
      delete root;
      root = succ;
    }
	else {
      Node<T> *p = root->remove(val);
      root = root->splay(root, p);
    }
  }
  size--;
}

template <class T> bool SplayTree<T>::find(T val) {
  if (root != 0){
    Node<T> *found = root->find(val);
    root = root->splay(root, found);
    return (root->valor == val);
  } 
  else{return false;}
}

template <class T> string SplayTree<T>::inorder() const {
  stringstream aux;

  aux << "[";
  if (!empty()) {root->inorder(aux);}
  aux << "]";
  return aux.str();
}

template <class T> string SplayTree<T>::preorder() const {
  stringstream aux;

  aux << "[";
  if (!empty()) {root->preorder(aux);}
  aux << "]";
  return aux.str();
}

#endif