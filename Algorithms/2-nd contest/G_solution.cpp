#include <iostream>

void QSort(int array[], int first, int last) {
  int left = first;
  int right = last;
  int mid = array[(right + left) / 2];
  while (left <= right) {
    while (array[left] < mid) {
      left++;
    }
    while (array[right] > mid) {
      right--;
    }
    if (left <= right) {
      std::swap(array[left], array[right]);
      left++;
      right--;
    }
  }
  if (right > first) {
    QSort(array, first, right);
  }
  if (left < last) {
    QSort(array, left, last);
  }
}

int main() {
  int n;
  std::cin >> n;
  int* array = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> array[i];
  }
  QSort(array, 0, n - 1);
  for (int i = 0; i < n; ++i) {
    std::cout << array[i] << ' ';
  }
  delete[] array;
  return 0;
}