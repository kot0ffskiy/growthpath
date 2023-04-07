#include <iostream>
#include <vector>

struct Pair {
  int first;
  int second;
};

void Compare(Pair left_array[], Pair array[], Pair right_array[],
             const int k_arr[]) {
  int mid = k_arr[0];
  int left = k_arr[1];
  int right = k_arr[2];
  int ind_sub_arr_one = 0;
  int ind_sub_arr_two = 0;
  int ind_merged = left;
  while (ind_sub_arr_one < mid - left + 1 && ind_sub_arr_two < right - mid) {
    if (left_array[ind_sub_arr_one].first <=
        right_array[ind_sub_arr_two].first) {
      array[ind_merged] = left_array[ind_sub_arr_one];
      ind_sub_arr_one++;
    } else {
      array[ind_merged] = right_array[ind_sub_arr_two];
      ind_sub_arr_two++;
    }
    ind_merged++;
  }
  while (ind_sub_arr_one < mid - left + 1) {
    array[ind_merged] = left_array[ind_sub_arr_one];
    ind_sub_arr_one++;
    ind_merged++;
  }
  while (ind_sub_arr_two < right - mid) {
    array[ind_merged] = right_array[ind_sub_arr_two];
    ind_sub_arr_two++;
    ind_merged++;
  }
}

void Merge(Pair array[], int const kLeft, int const kMid, int const kRight) {
  Pair* left_array = new Pair[kMid - kLeft + 1];
  Pair* right_array = new Pair[kRight - kMid];
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

void MergeSort(Pair array[], int const kBegin, int const kEnd) {
  if (kBegin >= kEnd) {
    return;
  }
  int mid = kBegin + (kEnd - kBegin) / 2;
  MergeSort(array, kBegin, mid);
  MergeSort(array, mid + 1, kEnd);
  Merge(array, kBegin, mid, kEnd);
}

std::vector<Pair> Merge(Pair array[], int size) {
  std::vector<Pair> n_arr;
  n_arr.push_back(array[0]);
  int k = 0;
  for (int i = 1; i < size; i++) {
    if (n_arr[k].second >= array[i].first) {
      int a = n_arr[k].second;
      int b = array[i].second;
      int second = a < b ? b : a;
      n_arr[k].second = second;
    } else {
      n_arr.push_back(array[i]);
      k++;
    }
  }
  return n_arr;
}

int main() {
  int n;
  std::cin >> n;
  Pair* array = new Pair[n];
  for (int i = 0; i < n; i++) {
    std::cin >> array[i].first >> array[i].second;
  }
  MergeSort(array, 0, n - 1);
  std::vector<Pair> merged_arr;
  merged_arr = Merge(array, n);
  std::cout << merged_arr.size() << '\n';
  for (auto& i : merged_arr) {
    std::cout << i.first << ' ' << i.second << '\n';
  }
  delete[] array;
  return 0;
}