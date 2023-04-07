#include <iostream>
#include <vector>

int main() {
  const int kInf = 1e6;
  int count;
  std::cin >> count;
  std::vector<int> input_array;
  int arr_elem;
  for (int i = 0; i < count; ++i) {
    std::cin >> arr_elem;
    input_array.push_back(arr_elem);
  }
  std::vector<int> output(count, kInf);
  output[0] = -kInf;
  for (int i = 0; i < count; ++i) {
    int left = 0;
    int right = count;
    int middle;
    while (right - left > 1) {
      middle = (right + left) / 2;
      if (output[middle] >= input_array[i]) {
        right = middle;
      } else {
        left = middle;
      }
    }
    output[right] = input_array[i];
  }
  int length = 0;
  for (auto& i : output) {
    if (i != kInf && i != -kInf) {
      length++;
    }
  }
  std::cout << length;
}