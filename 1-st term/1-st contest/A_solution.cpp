#include <iostream>

bool BinarySearch(int* begin, const int* end, int target) {
  int* mid;
  while (end - begin >= 0) {
    mid = begin + (end - begin) / 2;
    if (target == *mid) {
      return true;
    }
    if (target < *mid) {
      end = mid - 1;
    } else {
      begin = mid + 1;
    }
  }
  return false;
}

int* Input(int* array, int arr_len) {
  for (int i = 0; i < arr_len; ++i) {
    std::cin >> *(array + i);
  }
  return array;
}

void QueryTreatment(int* array) {
  int query_count = 0;
  int left_index = 0;
  int right_index = 0;
  int target = 0;
  std::cin >> query_count;
  for (int i = 0; i < query_count; ++i) {
    std::cin >> left_index >> right_index >> target;
    if (BinarySearch(array + left_index, array + (right_index - 1), target)) {
      std::cout << "YES" << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }
}

void Solve() {
  int arr_len = 0;
  std::cin >> arr_len;
  int* array = new int[arr_len];
  Input(array, arr_len);
  QueryTreatment(array);
  delete[] array;
}

int main() {
  Solve();
  return 0;
}