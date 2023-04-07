#include <iostream>
#include <string>

struct Node {
  int elem = 0;
  int size = 0;
  int min = 0;
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
  std::cout << "ok" << std::endl;
}

void Push(int n) {
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
  std::cout << "ok" << std::endl;
}

int Pop() {
  int tmp = head->elem;
  DeleteNode();
  return tmp;
}

void ExecBack() {
  if (!IsEmpty()) {
    std::cout << head->elem << std::endl;
  } else {
    std::cout << "error" << std::endl;
  }
}

void ExecPop() {
  if (!IsEmpty()) {
    std::cout << Pop() << std::endl;
  } else {
    std::cout << "error" << std::endl;
  }
}

void ExecMin() {
  if (!IsEmpty()) {
    std::cout << head->min << std::endl;
  } else {
    std::cout << "error" << std::endl;
  }
}

void ExecSize() {
  if (!IsEmpty()) {
    std::cout << head->size << std::endl;
  } else {
    std::cout << 0 << std::endl;
  }
}

void ExecPush() {
  int n = 0;
  std::cin >> n;
  Push(n);
}

int main() {
  int iter_count;
  std::cin >> iter_count;
  for (int i = 0; i < iter_count; i++) {
    std::string inp_stream;
    std::cin >> inp_stream;
    if (inp_stream == "push") {
      ExecPush();
    }
    if (inp_stream == "pop") {
      ExecPop();
    }
    if (inp_stream == "back") {
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