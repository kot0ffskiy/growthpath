#include <algorithm>
#include <iostream>
#include <vector>

struct Pair {
  int weight = 0;
  int cost = 0;
};

int main() {
  int items = 0;
  int max_weight = 0;
  std::cin >> items >> max_weight;
  std::vector<Pair> input(items + 1);
  std::vector<std::vector<int>> dp = std::vector<std::vector<int>>(
      items + 1, std::vector<int>(std::vector<int>(max_weight + 1)));
  /// @brief ////////INPUT////////
  for (int i = 1; i <= items; ++i) {
    std::cin >> input[i].weight;
  }
  for (int i = 1; i <= items; ++i) {
    std::cin >> input[i].cost;
  }
  /// @brief ////////END_INPUT////////
  for (int i = 1; i <= items; ++i) {
    for (int j = 0; j <= max_weight; ++j) {
      if (input[i].weight > j) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = std::max(dp[i - 1][j],
                            dp[i - 1][j - input[i].weight] + input[i].cost);
      }
    }
  }
  std::vector<int> answer;
  int j = max_weight;
  for (int vert = items; vert > 0; --vert) {
    if (input[vert].weight <= j &&
        dp[vert][j] ==
            dp[vert - 1][j - input[vert].weight] + input[vert].cost) {
      answer.push_back(vert);
      j = j - input[vert].weight;
    }
  }
  std::reverse(answer.begin(), answer.end());
  for (auto& i : answer) {
    std::cout << i << '\n';
  }
  return 0;
}
