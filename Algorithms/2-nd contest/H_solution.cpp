#include <cstdint>
#include <iostream>

uint64_t inver = 0;

void Compare(const int left_array[], int array[], const int right_array[],
             const int k_arr[]) {
  int mid = k_arr[0];
  int left = k_arr[1];
  int right = k_arr[2];
  int ind_sub_arr_one = 0;
  int ind_sub_arr_two = 0;
  int ind_merged = left;
  while (ind_sub_arr_one < mid - left + 1 && ind_sub_arr_two < right - mid) {
    if (left_array[ind_sub_arr_one] <= right_array[ind_sub_arr_two]) {
      array[ind_merged++] = left_array[ind_sub_arr_one++];
    } else {
      array[ind_merged++] = right_array[ind_sub_arr_two++];
      inver += mid - left + 1 - ind_sub_arr_one;
    }
  }
  while (ind_sub_arr_one < mid - left + 1) {
    array[ind_merged++] = left_array[ind_sub_arr_one++];
  }
  while (ind_sub_arr_two < right - mid) {
    array[ind_merged++] = right_array[ind_sub_arr_two++];
  }
}

void Merge(int array[], int const kLeft, int const kMid, int const kRight) {
  int* left_array = new int[kMid - kLeft + 1];
  int* right_array = new int[kRight - kMid];
  for (int i = 0; i < kMid - kLeft + 1; i++) {
    left_array[i] = array[kLeft + i];
  }
  for (int j = 0; j < kRight - kMid; j++) {
    right_array[j] = array[kMid + 1 + j];
  }
  int func_arg[3] = {kMid, kLeft, kRight};
  Compare(left_array, array, right_array, func_arg);
  delete[] left_array;
  delete[] right_array;
}

void MergeSort(int* a, int first, int last) {
  if (first >= last) {
    return;
  }
  int mid = (first + last) / 2;
  MergeSort(a, first, mid);
  MergeSort(a, mid + 1, last);
  Merge(a, first, mid, last);
}

int main() {
  int n;
  std::cin >> n;
  int* array = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> array[i];
  }
  MergeSort(array, 0, n - 1);
  std::cout << '\n' << inver << '\n';
  delete[] array;
  return 0;
}