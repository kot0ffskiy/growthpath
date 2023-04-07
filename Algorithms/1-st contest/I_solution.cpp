#include <algorithm>
#include <iostream>

int main() {
  int count, left, right, questions;
  std::cin >> count;
  auto* speeds = new int[count];
  for (int i = 0; i < count; i++) {
    std::cin >> *(speeds + i);
  }
  auto* left_arr = new int[count];
  auto* right_arr = new int[count];
  *left_arr = *speeds;
  *(right_arr + count - 1) = *(speeds + count - 1);
  for (int i = 1; i < count; i++) {
    *(left_arr + i) = std::min(*(left_arr + i - 1), *(speeds + i));
    *(right_arr + count - 1 - i) =
        std::min(*(right_arr + count - i), *(speeds + count - i - 1));
  }
  std::cin >> questions;
  for (int i = 0; i < questions; i++) {
    std::cin >> left >> right;
    if (right_arr[right - 1] > left_arr[left - 1]) {
      std::cout << left_arr[left - 1] << std::endl;
    } else {
      std::cout << right_arr[right - 1] << std::endl;
    }
  }
  delete[] speeds;
  delete[] left_arr;
  delete[] right_arr;
  return 0;
}