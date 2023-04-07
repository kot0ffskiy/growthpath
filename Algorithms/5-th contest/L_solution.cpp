#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
  int count = 0;
  std::cin >> count;
  std::vector<int> input(count);
  for (auto& i : input) {
    std::cin >> i;
  }
  std::vector<std::vector<double>> dp = std::vector<std::vector<double>>(
      count, std::vector<double>(std::vector<double>(count)));
  for (int i = 0; i < count; ++i) {
    dp[i][i] = static_cast<double>(input[i]);
  }
  for (int len = 1; len < count; ++len) {
    for (int left = 0; left < count - len; ++left) {
      int right = len + left;
      double rem = 0;
      for (int i = left; i < right; ++i) {
        rem = std::max(rem, (dp[left][i] + dp[i + 1][right]) / 2);
      }
      dp[left][right] = rem;
    }
  }
  std::cout << std::setprecision(10) << dp[0][count - 1];
  return 0;
}
