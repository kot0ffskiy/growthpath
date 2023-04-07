#include <iostream>

struct Node {
  char elem = ' ';
  struct Node* next = nullptr;
};

Node* head = nullptr;

bool IsEmpty() { return head == nullptr; }

void DeleteNode() {
  Node* del_node = head;
  head = head->next;
  delete del_node;
}

void Clear() {
  while (!IsEmpty()) {
    DeleteNode();
  }
}

void Push(char n) {
  Node* temp = new Node();
  temp->elem = n;
  temp->next = head;
  head = temp;
}

char Pop() {
  char tmp = head->elem;
  DeleteNode();
  return tmp;
}

int main() {
  char n;
  std::cin.get(n);
  while (n > 30) {
    if (IsEmpty()) {
      Push(n);
    } else {
      if ((head->elem == '(' && n == ')') || (head->elem == '{' && n == '}') ||
          (head->elem == '[' && n == ']')) {
        Pop();
      } else {
        Push(n);
      }
    }
    std::cin.get(n);
  }
  if (IsEmpty()) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
  Clear();
  return 0;
}