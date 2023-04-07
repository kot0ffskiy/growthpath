#include <algorithm>
#include <iostream>
#include <string>

struct Node {
  int elem = 0;
  int size = 0;
  int min = 0;
  struct Node* next = nullptr;
};

Node* head_straight = nullptr;
Node* head_reversed = nullptr;

bool IsEmpty(Node* head) { return head == nullptr; }

Node* DeleteNode(Node* head) {
  Node* del_node = head;
  head = head->next;
  delete del_node;
  return head;
}

void Clear() {
  while (!IsEmpty(head_straight)) {
    head_straight = DeleteNode(head_straight);
  }
  while (!IsEmpty(head_reversed)) {
    head_reversed = DeleteNode(head_reversed);
  }
  std::cout << "ok" << std::endl;
}

Node* Push(Node* head, int n) {
  Node* temp = new Node();
  temp->elem = n;
  temp->next = head;
  head = temp;
  head->min = n;
  if (head->next != nullptr) {
    head->size = head->next->size + 1;
    if (head->min > head->next->min) {
      head->min = head->next->min;
    }
  } else {
    head->size = 1;
  }
  return head;
}

void Reverse() {
  while (head_straight != nullptr) {
    head_reversed = Push(head_reversed, head_straight->elem);
    head_straight = DeleteNode(head_straight);
  }
}

void ExecPop() {
  if (!IsEmpty(head_reversed)) {
    std::cout << head_reversed->elem << std::endl;
    head_reversed = DeleteNode(head_reversed);
  } else if (!IsEmpty(head_straight)) {
    Reverse();
    ExecPop();
  } else {
    std::cout << "error" << std::endl;
  }
}

void ExecBack() {
  if (!IsEmpty(head_reversed)) {
    std::cout << head_reversed->elem << std::endl;
  } else if (!IsEmpty(head_straight)) {
    Reverse();
    ExecBack();
  } else {
    std::cout << "error" << std::endl;
  }
}

void ExecMin() {
  if (!IsEmpty(head_reversed) && !(IsEmpty(head_straight))) {
    std::cout << std::min(head_reversed->min, head_straight->min) << std::endl;
  } else if (!IsEmpty(head_straight)) {
    std::cout << head_straight->min << std::endl;
  } else if (!IsEmpty(head_reversed)) {
    std::cout << head_reversed->min << std::endl;
  } else {
    std::cout << "error" << std::endl;
  }
}

void ExecSize() {
  if (!IsEmpty(head_reversed) && !(IsEmpty(head_straight))) {
    std::cout << head_reversed->size + head_straight->size << std::endl;
  } else if (!IsEmpty(head_straight)) {
    std::cout << head_straight->size << std::endl;
  } else if (!IsEmpty(head_reversed)) {
    std::cout << head_reversed->size << std::endl;
  } else {
    std::cout << 0 << std::endl;
  }
}

void ExecPush() {
  int n = 0;
  std::cin >> n;
  head_straight = Push(head_straight, n);
  std::cout << "ok" << std::endl;
}

int main() {
  int iter_count;
  std::cin >> iter_count;
  for (int i = 0; i < iter_count; i++) {
    std::string inp_stream;
    std::cin >> inp_stream;
    if (inp_stream == "enqueue") {
      ExecPush();
    }
    if (inp_stream == "dequeue") {
      ExecPop();
    }
    if (inp_stream == "front") {
      ExecBack();
    }
    if (inp_stream == "min") {
      ExecMin();
    }
    if (inp_stream == "size") {
      ExecSize();
    }
    if (inp_stream == "clear") {
      Clear();
    }
  }
  return 0;
}