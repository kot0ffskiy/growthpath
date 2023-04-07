#include <cstdint>
#include <iostream>

class AVL {
 private:
  struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    int64_t sum = 0;
    int64_t minleft = 0;
    int64_t maxright = 0;
    int64_t key = -1;
    int64_t height = 0;
  };
  Node* root_ = nullptr;
  int64_t Height(Node* node);
  int64_t DeltaH(Node* node);
  void CountH(Node* node);
  Node* RightRotate(Node* node);
  Node* LeftRotate(Node* node);
  Node* Balance(Node* node);
  void Clean(Node* node);
  AVL::Node* Insert(int64_t key, Node* curr);
  int64_t Find(int64_t k_left, int64_t k_right, Node* curr);

 public:
  void Add(int64_t key);
  int64_t Sum(int64_t k_left, int64_t k_right);
  ~AVL() { Clean(root_); }
};

int64_t AVL::Height(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

int64_t AVL::DeltaH(Node* node) {
  return Height(node->right) - Height(node->left);
}

void AVL::CountH(Node* node) {
  int64_t left = Height(node->left);
  int64_t right = Height(node->right);
  if (left > right) {
    node->height = left + 1;
  } else {
    node->height = right + 1;
  }
  node->sum = 0;
  if (node->right != nullptr) {
    node->sum = node->right->sum + node->right->key;
  }
  if (node->left != nullptr) {
    node->sum += node->left->sum + node->left->key;
  }
  node->minleft = (node->left == nullptr) ? node->key : node->left->minleft;
  node->maxright = (node->right == nullptr) ? node->key : node->right->maxright;
}

AVL::Node* AVL::Balance(AVL::Node* node) {
  CountH(node);
  if (DeltaH(node) == -2LL) {
    if (DeltaH(node->left) > 0LL) {
      node->left = LeftRotate(node->left);
    }
    return RightRotate(node);
  }
  if (DeltaH(node) == 2LL) {
    if (DeltaH(node->right) < 0LL) {
      node->right = RightRotate(node->right);
    }
    return LeftRotate(node);
  }
  CountH(node);
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

void AVL::Add(int64_t key) {
  if (root_ == nullptr) {
    root_ = new Node;
    root_->height = 1;
    root_->key = key;
    root_->minleft = key;
    root_->maxright = key;
    return;
  }
  root_ = Insert(key, root_);
}

AVL::Node* AVL::Insert(int64_t key, Node* curr) {
  if (curr == nullptr) {
    Node* newnode = new Node;
    newnode->height = 1;
    newnode->key = key;
    newnode->minleft = key;
    newnode->maxright = key;
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

int64_t AVL::Sum(int64_t k_left, int64_t k_right) {  // <--> find
  int64_t rem_key;
  rem_key = Find(k_left, k_right, root_);
  return rem_key;
}

int64_t AVL::Find(int64_t k_left, int64_t k_right, Node* curr) {
  if (curr == nullptr) {
    return 0;
  }
  int64_t res;
  if (curr->minleft >= k_left && curr->maxright <= k_right) {
    return curr->sum + curr->key;
  }
  if (curr->minleft > k_right || curr->maxright < k_left) {
    return 0;
  }
  if (curr->key <= k_right && curr->key >= k_left) {
    res = Find(k_left, k_right, curr->left);
    res += Find(k_left, k_right, curr->right);
    res += curr->key;
    return res;
  }
  res = Find(k_left, k_right, curr->left);
  res += Find(k_left, k_right, curr->right);
  return res;
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
  int64_t n;
  std::cin >> n;
  bool plus = false;
  AVL tree;
  int64_t rem_mem = 0;  // remember key after '?'
  for (int64_t i = 0; i < n; i++) {
    char op;
    std::cin >> op;
    if (op == '+') {
      int64_t key;
      std::cin >> key;
      if (!plus) {
        tree.Add(key);
      } else {
        tree.Add((key + rem_mem) % 1000000000);
        plus = false;
      }
    } else if (op == '?') {
      int64_t left;
      int64_t right;
      std::cin >> left >> right;
      rem_mem = tree.Sum(left, right);
      std::cout << rem_mem << '\n';
      plus = true;
    }
  }
  return 0;
}