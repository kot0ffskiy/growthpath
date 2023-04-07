#include <iostream>

class AVL {
 private:
  struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    std::string key;
    std::string value;
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
  Node* Insert(const std::string& key, const std::string& value, Node* curr);

 public:
  std::string Search(const std::string& key);
  std::string Find(const std::string& key);
  void Add(const std::string& key, const std::string& value);
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

void AVL::Add(const std::string& key, const std::string& value) {
  if (root_ == nullptr) {
    root_ = new Node;
    root_->height = 1;
    root_->key = key;
    root_->value = value;
    return;
  }
  root_ = Insert(key, value, root_);
}

AVL::Node* AVL::Insert(const std::string& key, const std::string& value,
                       Node* curr) {
  if (curr == nullptr) {
    Node* newnode = new Node;
    newnode->height = 1;
    newnode->key = key;
    newnode->value = value;
    return newnode;
  }
  if (key < curr->key) {
    curr->left = Insert(key, value, curr->left);
  } else if (key > curr->key) {
    curr->right = Insert(key, value, curr->right);
  } else if (key == curr->key) {
    return curr;
  }
  return Balance(curr);
}

std::string AVL::Search(const std::string& key) {  // <--> find
  std::string output = Find(key);
  if (output.empty()) {
    output = Find(key);
  }
  return output;
}

std::string AVL::Find(const std::string& key) {
  std::string ans;
  Node* curr = root_;
  while (curr != nullptr) {
    if (curr->key > key) {
      curr = curr->left;
    } else if (curr->key < key) {
      curr = curr->right;
    } else if (curr->key == key) {
      ans = curr->value;
      return ans;
    }
  }
  return ans;
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
  std::string racer;
  std::string car;
  AVL tree;
  int pairs_num;
  std::cin >> pairs_num;
  for (int i = 0; i < pairs_num; i++) {
    std::cin >> racer >> car;
    tree.Add(racer, car);
    tree.Add(car, racer);
  }
  std::cin >> pairs_num;
  std::string input;
  for (int i = 0; i < pairs_num; i++) {
    std::cin >> input;
    std::cout << tree.Search(input) << '\n';
  }
  return 0;
}