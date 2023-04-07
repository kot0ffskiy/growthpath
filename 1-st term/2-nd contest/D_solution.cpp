#include <cstdint>
#include <iostream>
#include <vector>

class Heap {
 public:
  void SiftDown(int64_t ind);
  void MinSiftDown(int64_t ind);
  void MinHeapify();
  void SiftUp(int64_t ind);
  void Insert(int64_t elem);
  int64_t ExtractMax();
  uint64_t ExtractMin();
  void PrintSortedHeap();
  int64_t Top() const { return heap_[0]; }
  int64_t HeapSize() const { return heap_size_; }

 private:
  int64_t heap_size_ = 0;
  std::vector<int64_t> heap_;
};
void Heap::SiftDown(int64_t ind) {
  while ((2 * ind + 1) < heap_size_) {
    int64_t left = 2 * ind + 1;
    int64_t right = 2 * ind + 2;
    int64_t max = left;
    if (right < heap_size_ && heap_[right] > heap_[left]) {
      max = right;
    }
    if (heap_[ind] >= heap_[max]) {
      break;
    }
    std::swap(heap_[ind], heap_[max]);
    ind = max;
  }
}

void Heap::MinSiftDown(int64_t ind) {
  while ((2 * ind + 1) < heap_size_) {
    int64_t left = 2 * ind + 1;
    int64_t right = 2 * ind + 2;
    int64_t min = left;
    if (right < heap_size_ && heap_[right] < heap_[left]) {
      min = right;
    }
    if (heap_[ind] <= heap_[min]) {
      break;
    }
    std::swap(heap_[ind], heap_[min]);
    ind = min;
  }
}

void Heap::MinHeapify() {
  for (int64_t i = heap_size_ - 1; i >= 0; i--) {
    MinSiftDown(i);
  }
}

void Heap::SiftUp(int64_t ind) {
  if (ind - 1 > 0) {
    while (heap_[ind] > heap_[(ind - 1) / 2] && ind > 0) {
      std::swap(heap_[ind], heap_[(ind - 1) / 2]);
      ind = (ind - 1) / 2;
    }
  }
}

void Heap::Insert(int64_t elem) {
  heap_size_++;
  heap_.push_back(elem);
  SiftUp(heap_size_ - 1);
}

int64_t Heap::ExtractMax() {
  std::swap(heap_.back(), heap_[0]);
  int64_t max = heap_.back();
  heap_.pop_back();
  heap_size_--;
  SiftDown(0);
  return max;
}

uint64_t Heap::ExtractMin() {
  std::swap(heap_.back(), heap_[0]);
  uint64_t min = heap_.back();
  heap_.pop_back();
  heap_size_--;
  MinSiftDown(0);
  return min;
}

void Heap::PrintSortedHeap() {
  while (heap_size_ != 0) {
    std::cout << ExtractMin() << ' ';
  }
}

int main() {
  int64_t n = 0;
  int64_t k = 0;
  std::cin >> n >> k;
  int64_t a_0 = 0;
  int64_t x = 0;
  int64_t y = 0;
  std::cin >> a_0 >> x >> y;
  Heap heap;
  int64_t tmp = a_0;
  const int kShift = 30;
  for (int64_t i = 0; i < n; i++) {
    tmp = (x * tmp + y) % (1LL << kShift);
    if (heap.HeapSize() < k) {
      heap.Insert(tmp);
    } else if (heap.Top() > tmp) {
      heap.ExtractMax();
      heap.Insert(tmp);
    }
  }
  heap.MinHeapify();
  heap.PrintSortedHeap();
  return 0;
}