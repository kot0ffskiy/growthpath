#include <iostream>

struct Pair {
  int elem;
  int ind;
};

void Merge(Pair* arr, int* res, int first_size, int sec_size) {
  Pair* half_arr = arr + first_size;
  Pair* tmp = new Pair[first_size + sec_size];
  int i = 0;
  int j = 0;
  while (i < first_size && j < sec_size) {
    if (arr[i].elem > half_arr[j].elem) {
      tmp[i + j] = arr[i];
      res[arr[i].ind] += sec_size - j;
      i++;
    } else {
      tmp[i + j] = half_arr[j];
      j++;
    }
  }
  while (i < first_size) {
    tmp[i + j] = arr[i];
    res[arr[i].ind] += sec_size - j;
    i++;
  }
  while (j < sec_size) {
    tmp[i + j] = half_arr[j];
    j++;
  }
  for (int k = 0; k < first_size + sec_size; k++) {
    arr[k] = tmp[k];
  }
  delete[] tmp;
}

void MergeSort(Pair* arr, int* res, int first, int last) {
  if (last > 1) {
    int mid = last / 2;
    MergeSort(arr, res, first, mid);
    MergeSort(arr, res, first + mid, last - mid);
    Merge(arr + first, res, mid, last - mid);
  }
}

int main() {
  int n;
  std::cin >> n;
  Pair* arr = new Pair[n];
  int* result = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i].elem;
    result[i] = 0;
    arr[i].ind = i;
  }
  MergeSort(arr, result, 0, n);
  for (int i = 0; i < n; i++) {
    std::cout << result[i] << ' ';
  }
  delete[] arr;
  delete[] result;
  return 0;
}