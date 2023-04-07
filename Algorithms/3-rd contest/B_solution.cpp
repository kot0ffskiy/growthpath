#include <iostream>

class AVL {
 private:
  struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    int key = -1;
    int height = 0;
  };
  Node* root_ = nullptr;
  static int Height(Node* node);
  static int DeltaH(Node* node);
  static void CountH(Node* node);
  static Node* RightRotate(Node* node);
  static Node* LeftRotate(Node* node);
  static Node* Balance(Node* node);
  void Clean(Node* node);
  AVL::Node* Insert(int key, Node* curr);

 public:
  void Add(int key);
  int Next(int key);
  ~AVL() { Clean(root_); }
};

int AVL::Height(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

int AVL::DeltaH(Node* node) { return Height(node->right) - Height(node->left); }

void AVL::CountH(Node* node) {
  int left = Height(node->left);
  int right = Height(node->right);
  if (left > right) {
    node->height = left + 1;
  } else {
    node->height = right + 1;
  }
}

AVL::Node* AVL::Balance(AVL::Node* node) {
  CountH(node);
  if (DeltaH(node) == -2) {
    if (DeltaH(node->left) > 0) {
      node->left = LeftRotate(node->left);
    }
    return RightRotate(node);
  }
  if (DeltaH(node) == 2) {
    if (DeltaH(node->right) < 0) {
      node->right = RightRotate(node->right);
    }
    return LeftRotate(node);
  }
  return node;
}

AVL::Node* AVL::RightRotate(Node* node) {
  Node* tmp = node->left;
  node->left = tmp->right;
  tmp->right = node;
  CountH(node);
  CountH(tmp);
  return tmp;
}

AVL::Node* AVL::LeftRotate(Node* node) {
  Node* tmp = node->right;
  node->right = tmp->left;
  tmp->left = node;
  CountH(node);
  CountH(tmp);
  return tmp;
}

void AVL::Add(int key) {
  if (root_ == nullptr) {
    root_ = new Node;
    root_->height = 1;
    root_->key = key;
    return;
  }
  root_ = Insert(key, root_);
}

AVL::Node* AVL::Insert(int key, Node* curr) {
  if (curr == nullptr) {
    Node* newnode = new Node;
    newnode->height = 1;
    newnode->key = key;
    return newnode;
  }
  if (key < curr->key) {
    curr->left = Insert(key, curr->left);
  } else if (key > curr->key) {
    curr->right = Insert(key, curr->right);
  } else if (key == curr->key) {
    return curr;
  }
  return Balance(curr);
}

int AVL::Next(int key) {  // <--> find
  int rem_key = -1;
  Node* curr = root_;
  while (curr != nullptr) {
    if (curr->key > key) {
      rem_key = curr->key;
      curr = curr->left;
    } else if (curr->key < key) {
      curr = curr->right;
    } else if (curr->key == key) {
      return curr->key;
    }
  }
  return rem_key;
}

void AVL::Clean(Node* node) {
  if (node == nullptr) {
    return;
  }
  if (node->left != nullptr) {
    Clean(node->left);
  }
  if (node->right != nullptr) {
    Clean(node->right);
  }
  delete node;
}

int main() {
  int n;
  std::cin >> n;
  char op;
  int key;
  bool plus = false;
  AVL tree;
  int rem_mem = 0;  // remember key after '?'
  const int kModule = 1000000000;
  for (int i = 0; i < n; i++) {
    std::cin >> op >> key;
    if (op == '+' && !plus) {
      tree.Add(key);
    } else if (op == '+' && plus) {
      tree.Add((key + rem_mem) % kModule);
      plus = false;
    }
    if (op == '?') {
      rem_mem = tree.Next(key);
      std::cout << rem_mem << '\n';
      plus = true;
    }
  }
  return 0;
}