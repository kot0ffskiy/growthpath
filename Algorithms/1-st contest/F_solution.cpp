#include <iostream>

struct Node {
  int elem = ' ';
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

void Push(int n) {
  Node* temp = new Node();
  temp->elem = n;
  temp->next = head;
  head = temp;
}

int Pop() {
  int tmp = head->elem;
  DeleteNode();
  return tmp;
}

int main() {
  int n;
  n = std::cin.get();
  while (n > 30) {
    if (n >= '0' && n <= '9') {
      Push(n - '0');
    } else {
      if (n == '+') {
        int a = Pop();
        int b = Pop();
        Push(b + a);
      } else if (n == '-') {
        int a = Pop();
        int b = Pop();
        Push(b - a);
      } else if (n == '*') {
        int a = Pop();
        int b = Pop();
        Push(b * a);
      }
    }
    n = std::cin.get();
  }
  std::cout << Pop() << std::endl;
  Clear();
  return 0;
}