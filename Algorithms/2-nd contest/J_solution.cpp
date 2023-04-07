#include <iostream>
#include <vector>

struct Pair {
  int elem;
  int ind;
};

class Heap {
 public:
  void SiftDown(int ind);
  void SiftUp(int ind);
  void Insert(int elem, int ind);
  void Heapify();
  Pair ExtractMin();
  int HeapSize() const { return heap_size_; }

 private:
  int heap_size_ = 0;
  std::vector<Pair> heap_;
};

void Heap::SiftDown(int ind) {
  while ((2 * ind + 1) < heap_size_) {
    int left = 2 * ind + 1;
    int right = 2 * ind + 2;
    int min = left;
    if (right < heap_size_ && heap_[right].elem < heap_[left].elem) {
      min = right;
    }
    if (heap_[ind].elem <= heap_[min].elem) {
      break;
    }
    std::swap(heap_[ind], heap_[min]);
    ind = min;
  }
}

Pair Heap::ExtractMin() {
  if (heap_size_ > 0) {
    Pair min = heap_[0];
    heap_[0] = heap_[heap_size_ - 1];
    heap_size_--;
    SiftDown(0);
    return min;
  }
  return {-1, -1};
}

void Heap::SiftUp(int ind) {
  if (ind - 1 >= 0) {
    while (heap_[ind].elem < heap_[(ind - 1) / 2].elem) {
      std::swap(heap_[ind], heap_[(ind - 1) / 2]);
      ind = (ind - 1) / 2;
    }
  }
}

void Heap::Heapify() {
  for (int i = heap_size_ / 2; i >= 0; i--) {
    SiftDown(i);
  }
}

void Heap::Insert(int elem, int ind) {
  heap_size_++;
  Pair tmp{elem, ind};
  heap_.push_back(tmp);
  heap_[heap_size_ - 1].elem = elem;
  heap_[heap_size_ - 1].ind = ind;
  SiftUp(heap_size_ - 1);
}

int main() {
  int arr_number;
  std::cin >> arr_number;
  std::vector<std::vector<int>> arrays(arr_number);
  std::vector<int> index(arr_number, 0);
  for (int i = 0; i < arr_number; i++) {
    int size;
    std::cin >> size;
    for (int j = 0; j < size; j++) {
      int elem;
      std::cin >> elem;
      arrays[i].push_back(elem);
    }
  }
  Heap heap;
  for (int i = 0; i < arr_number; i++) {
    heap.Insert(arrays[i][0], i);
  }
  heap.Heapify();
  while (heap.HeapSize() != 0) {
    Pair top = heap.ExtractMin();
    std::cout << top.elem << ' ';
    if (index[top.ind] < (int)arrays[top.ind].size() - 1) {
      heap.Insert(arrays[top.ind][++index[top.ind]], top.ind);
    }
  }
  return 0;
}