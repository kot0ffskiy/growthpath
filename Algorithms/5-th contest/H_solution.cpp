#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<int>>& CountLCS(std::vector<std::vector<int>>& lcs,
                                        const std::vector<int>& k_x,
                                        const std::vector<int>& k_y) {
  for (int i = 1; i <= (int)k_x.size(); ++i) {
    for (int j = 1; j <= (int)k_y.size(); ++j) {
      if (k_x[i - 1] == k_y[j - 1]) {
        lcs[i][j] = lcs[i - 1][j - 1] + 1;
      } else {
        lcs[i][j] = std::max(lcs[i - 1][j], lcs[i][j - 1]);
      }
    }
  }
  return lcs;
}

void Print(std::vector<std::vector<int>>& lcs, const std::vector<int>& k_x,
           const std::vector<int>& k_y) {
  std::vector<int> answer;
  int x_size = (int)k_x.size();
  int y_size = (int)k_y.size();
  while (x_size > 0 && y_size > 0) {
    if (k_x[x_size - 1] == k_y[y_size - 1]) {
      answer.push_back(k_y[y_size - 1]);
      x_size--;
      y_size--;
    } else if (lcs[x_size - 1][y_size] == lcs[x_size][y_size]) {
      x_size--;
    } else {
      y_size--;
    }
  }
  std::reverse(answer.begin(), answer.end());
  for (auto& i : answer) {
    std::cout << i << ' ';
  }
}

int main() {
  int first_sub;
  std::cin >> first_sub;
  std::vector<int> first_arr(first_sub);
  for (int i = 0; i < first_sub; ++i) {
    std::cin >> first_arr[i];
  }
  int second_sub;
  std::cin >> second_sub;
  std::vector<int> second_arr(second_sub);
  for (int i = 0; i < second_sub; ++i) {
    std::cin >> second_arr[i];
  }
  std::vector<std::vector<int>> lcs = std::vector<std::vector<int>>(
      first_sub + 1, std::vector<int>(second_sub + 1));
  for (int i = 1; i <= first_sub; ++i) {
    lcs[i][0] = 0;
  }
  for (int i = 0; i <= second_sub; ++i) {
    lcs[0][i] = 0;
  }
  lcs = CountLCS(lcs, first_arr, second_arr);
  Print(lcs, first_arr, second_arr);
}
