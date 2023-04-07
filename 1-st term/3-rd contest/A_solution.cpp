#include <iostream>

struct Node {
  int key = 0;
  int priority = 0;
  int num = 0;
  Node* right = nullptr;
  Node* left = nullptr;
  Node* parent = nullptr;
};

Node* treap = nullptr;
Node* curr = treap;

void LinInsert(const Node kInpNode) {
  Node* new_node = new Node;
  *new_node = kInpNode;
  if (curr != nullptr) {  // Check if treap is empty
    while (curr->parent != nullptr && curr->priority > new_node->priority) {
      curr = curr->parent;
    }
    if (curr->parent == nullptr) {  // Case curr == treap
      if (treap->priority > new_node->priority) {
        treap->parent = new_node;
        new_node->left = treap;
        curr = new_node;
        treap = curr;
      } else {                          // Case curr != treap
        if (treap->right != nullptr) {  // Case treap has right child
          new_node->left = treap->right;
          treap->right->parent = new_node;
          treap->right = new_node;
          new_node->parent = treap;
          curr = new_node;
        } else {  // Case treap is right-childfree
          treap->right = new_node;
          new_node->parent = treap;
          curr = new_node;
        }
      }
    } else if (curr->right != nullptr) {  // Same as 35 line but not treap
      curr->right->parent = new_node;
      new_node->left = curr->right;
      new_node->parent = curr;
      curr->right = new_node;
      curr = new_node;
    } else {  // Simple insertion
      curr->right = new_node;
      curr->right->parent = curr;
      curr = curr->right;
    }
  } else {
    treap = new_node;
    curr = new_node;
  }
}

void Obhod(Node* node) {
  if (node == nullptr) {
    return;
  }
  if (node->left != nullptr) {
    Obhod(node->left);
  }
  int left = 0;
  int right = 0;
  int parent = 0;
  if (node->left != nullptr) {
    left = node->left->num;
  }
  if (node->right != nullptr) {
    right = node->right->num;
  }
  if (node->parent != nullptr) {
    parent = node->parent->num;
  }
  std::cout << parent << ' ' << left << ' ' << right << std::endl;
  if (node->right != nullptr) {
    Obhod(node->right);
  }
}

void Delete(Node* node) {
  if (node == nullptr) {
    return;
  }
  if (node->left != nullptr) {
    Delete(node->left);
  }
  if (node->right != nullptr) {
    Delete(node->right);
  }
  delete node;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int k;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    Node current;
    std::cin >> current.key >> current.priority;
    current.num = i + 1;
    LinInsert(current);
  }
  std::cout << "YES" << std::endl;
  Obhod(treap);
  Delete(treap);
  return 0;
}