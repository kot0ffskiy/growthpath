#include <iostream>

int main() {
  int range;
  std::cin >> range;
  int* array = new int[range];
  for (int i = 0; i < range; i++) {
    std::cin >> *(array + i);
  }
  int* left_br = array;
  int* right_br = array + range;
  int* mid = left_br + (right_br - left_br) / 2;
  while (left_br != mid) {
    if (*mid < *left_br) {
      right_br = mid;
      mid = left_br + (right_br - left_br) / 2;
    } else {
      left_br = mid;
      mid = left_br + (right_br - left_br) / 2;
    }
  }
  std::cout << (right_br - array) % range;
  delete[] array;
  return 0;
}
