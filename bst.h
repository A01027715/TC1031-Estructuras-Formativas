#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

template <class T> 
class TreeNode {
public:
  T data;
  TreeNode *left;
  TreeNode *right;

  TreeNode(T);
};

template <class T> 
TreeNode<T>::TreeNode(T n) {
  data = n;
  left = nullptr;
  right = nullptr;
}

template <class T> 
class BST {
private:
  TreeNode<T> *root;
  TreeNode<T> *insert(TreeNode<T>, T);
  int height(TreeNode<T> *);
  void ancestors(TreeNode<T> *, T, vector<T> &);
  int whatlevelamI(TreeNode<T> *, T, int);

  void preorderTraversal(TreeNode<T> *, vector<T> &);
  void inorderTraversal(TreeNode<T> *, vector<T> &);
  void postorderTraversal(TreeNode<T> *, vector<T> &);
  void levelorderTraversal(TreeNode<T> *, vector<T> &);

  void visitHelper(stringstream &, vector<T> &);

public:
  BST();

  void add(T);

  string visit();
  int height();
  string ancestors(T);
  int whatlevelamI(T);
};

template <class T> 
TreeNode<T> BST<T>::*insert(TreeNode<T> *node, T x){
  if (node == nullptr) {return new TreeNode<T>(x);}

  if (x < node->data) {node->left = insert(node->left, x);}
  else if (x > node->data) {node->right = insert(node->right, x);}

  return node;
}

template <class T> 
BST<T>::BST() {root = nullptr;}

template <class T> 
int BST<T>::height(TreeNode<T> *node) {
  if (node == nullptr) {return 0;}

  int leftHeight = height(node->left);
  int rightHeight = height(node->right);

  return max(leftHeight, rightHeight) + 1;
}

template <class T>
void BST<T>::ancestors(TreeNode<T> *node, T target, vector<T> &result) {
  if (node == nullptr) {
    result.clear();
    return;
  }

  if (node->data == target) {return;}

  result.push_back(node->data);

  if (target < node->data) {ancestors(node->left, target, result);}
  else {ancestors(node->right, target, result);}
}

template <class T>
int BST<T>::whatlevelamI(TreeNode<T> *node, T x, int level) {
  if (node == nullptr) {return -1;}

  if (node->data == x) {return level;}

  int leftLevel = whatlevelamI(node->left, x, level + 1);
  if (leftLevel != -1) {return leftLevel;}

  return whatlevelamI(node->right, x, level + 1);
}

template <class T>
void BST<T>::preorderTraversal(TreeNode<T> *root, vector<T> &result) {
  if (root) {
    result.push_back(root->data);
    preorderTraversal(root->left, result);
    preorderTraversal(root->right, result);
  }
}

template <class T>
void BST<T>::inorderTraversal(TreeNode<T> *root, vector<T> &result) {
  if (root) {
    inorderTraversal(root->left, result);
    result.push_back(root->data);
    inorderTraversal(root->right, result);
  }
}

template <class T>
void BST<T>::postorderTraversal(TreeNode<T> *root, vector<T> &result) {
  if (root) {
    postorderTraversal(root->left, result);
    postorderTraversal(root->right, result);
    result.push_back(root->data);
  }
}

template <class T>
void BST<T>::levelorderTraversal(TreeNode<T> *root, vector<T> &result) {
  if (!root){return;}

  queue<TreeNode<T> *> q;
  q.push(root);

  while (!q.empty()) {
    TreeNode<T> *current = q.front();
    q.pop();
    result.push_back(current->data);

    if (current->left){q.push(current->left);}
    if (current->right){q.push(current->right);}
  }
}

template <class T>
void BST<T>::visitHelper(stringstream &resultStr, vector<T> &result) {
  string resultStrAux;
  resultStrAux += "[";
  for (const T &value : result) {
    resultStrAux += to_string(value) + " ";
  }
  if (!result.empty()) {
    resultStrAux.pop_back();
  }
  resultStrAux += "]";

  resultStr << resultStrAux;
  result.clear();
}

template <class T> void BST<T>::add(T x) {root = insert(root, x);}

template <class T> string BST<T>::visit() {
  vector<T> result;
  stringstream resultStr;

  preorderTraversal(root, result);
  visitHelper(resultStr, result);
  resultStr << "\n";
  inorderTraversal(root, result);
  visitHelper(resultStr, result);
  resultStr << "\n";
  postorderTraversal(root, result);
  visitHelper(resultStr, result);
  resultStr << "\n";
  levelorderTraversal(root, result);
  visitHelper(resultStr, result);

  return resultStr.str();
}

template <class T> int BST<T>::height() {return height(root);}

template <class T> string BST<T>::ancestors(T point) {
  vector<T> result;
  ancestors(root, point, result);

  string resultStr = "[";
  for (const T &value : result) {resultStr += to_string(value) + " ";}
  if (!result.empty()) {resultStr.pop_back();}
  resultStr += "]";

  return resultStr;
}

template <class T> int BST<T>::whatlevelamI(T x) {
  return whatlevelamI(root, x, 1);
}