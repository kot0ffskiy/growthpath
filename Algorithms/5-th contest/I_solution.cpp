#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int count = 0;
  std::cin >> count;
  std::vector<int> input(count);
  for (auto& i : input) {
    std::cin >> i;
  }
  std::vector<int> first;
  first.push_back(input[0]);
  std::vector<int> second;
  second.push_back(input[0]);
  int j = 0;
  /// x1 > x2 < x3 > x4 ....
  for (int i = 1; i < static_cast<int>(input.size()); ++i) {
    if (j % 2 == 0) {
      if (first[j] > input[i]) {
        first.push_back(input[i]);
        j++;
      } else if (first[j] < input[i]) {
        first[j] = input[i];
      }
    } else {
      if (first[j] > input[i]) {
        first[j] = input[i];
      } else if (first[j] < input[i]) {
        first.push_back(input[i]);
        j++;
      }
    }
  }
  j = 0;
  for (int i = 1; i < static_cast<int>(input.size()); ++i) {
    if (j % 2 != 0) {
      if (second[j] > input[i]) {
        second.push_back(input[i]);
        j++;
      } else if (second[j] < input[i]) {
        second[j] = input[i];
      }
    } else {
      if (second[j] > input[i]) {
        second[j] = input[i];
      } else if (second[j] < input[i]) {
        second.push_back(input[i]);
        j++;
      }
    }
  }
  if (first.size() >= second.size()) {
    std::cout << first.size() << '\n';
    for (auto& i : first) {
      std::cout << i << ' ';
    }
  } else {
    std::cout << second.size() << '\n';
    for (auto& i : second) {
      std::cout << i << ' ';
    }
  }
  return 0;
}
