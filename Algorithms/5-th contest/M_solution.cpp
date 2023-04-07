#include <iostream>
#include <vector>

std::vector<std::vector<int64_t>> Input(int n) {
  std::vector<std::vector<int64_t>> out(n, std::vector<int64_t>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> out[i][j];
    }
  }
  return out;
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<std::vector<int64_t>> inp = Input(n);
  const int64_t kInf = 1e7;
  std::vector<std::vector<int64_t>> dp = std::vector<std::vector<int64_t>>(
      1 << n, std::vector<int64_t>(std::vector<int64_t>(n, kInf)));
  for (int i = 0; i < n; ++i) {
    dp[0][i] = 0;
    dp[1 << i][i] = 0;
  }

  int64_t mask = 1;
  int64_t last_town = 0;
  for (; mask < 1 << n; ++mask) {
    for (int64_t u = 0; u < n; ++u) {
      if (((mask >> u) & 1) == 1) {
        int64_t temp = mask;
        int k = 0;
        while (temp > 0) {
          if ((temp & 1) == 1) {
            int64_t other = dp[mask ^ (1 << u)][k] + inp[u][k];
            dp[mask][u] = std::min(dp[mask][u], other);
          }
          ++k;
          temp = temp >> 1;
        }
      }
    }
  }
  int64_t ans = kInf;
  for (int i = 0; i < n; ++i) {
    if (dp[(1 << n) - 1][i] <= ans) {
      ans = dp[(1 << n) - 1][i];
      last_town = i;
    }
  }
  std::vector<int64_t> answer;
  --mask;
  while (answer.size() < static_cast<size_t>(n)) {
    answer.push_back(last_town + 1);
    int64_t expected = dp[mask][last_town];
    mask = (mask | 1 << last_town) ^ (1 << last_town);
    int64_t temp = mask;
    int k = 0;
    while (temp > 0) {
      if ((temp & 1) == 1) {
        if (expected == dp[mask][k] + inp[last_town][k]) {
          last_town = k;
          break;
        }
      }
      ++k;
      temp = temp >> 1;
    }
  }
  std::cout << ans << '\n';
  for (auto& k : answer) {
    std::cout << k << ' ';
  }
}