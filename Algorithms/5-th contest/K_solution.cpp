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
  std::vector<std::vector<int>> dp = std::vector<std::vector<int>>(
      count, std::vector<int>(std::vector<int>(count)));
  for (int i = 0; i < count - 1; ++i) {
    if (input[i] == input[i + 1]) {
      dp[i][i + 1] = 3;
    } else {
      dp[i][i + 1] = 2;
    }
    dp[i][i] = 1;
  }
  dp[count - 1][count - 1] = 1;
  const int kMod = 1e9;
  for (int len = 2; len < count; ++len) {
    for (int left = 0; left < count - len; ++left) {
      int right = left + len;
      if (input[left] == input[right]) {
        dp[left][right] =
            (dp[left + 1][right] + dp[left][right - 1] + 1) % kMod;
      } else {
        dp[left][right] = (dp[left + 1][right] + dp[left][right - 1] -
                           dp[left + 1][right - 1]) %
                          kMod;
        if (dp[left][right] < 0) {
          dp[left][right] += kMod;
        }
      }
    }
  }
  std::cout << dp[0][count - 1];
  return 0;
}
