#include <iostream>
#include <vector>

int64_t Log(int64_t x);

class SparseTable {
 public:
  SparseTable(int64_t size, const std::vector<int64_t>& k_input);
  void Out();
  int64_t FindSecStat(int64_t left, int64_t right);

 private:
  struct Pair {
    int64_t index;
    int64_t elem;
  };
  std::vector<std::vector<Pair>> ST_;
  int64_t log_ = 0;
  int64_t size_ = 0;
  void Create(const std::vector<int64_t>& k_input);
  Pair FindMin(int64_t left, int64_t right);
};

int64_t Log(int64_t x) {
  int64_t ans = 0;
  while (x / 2 > 0) {
    x /= 2;
    ans++;
  }
  return ans;
}

SparseTable::SparseTable(int64_t size, const std::vector<int64_t>& k_input) {
  log_ = Log(size) + 1;
  size_ = size;
  ST_ = std::vector<std::vector<Pair>>(log_, std::vector<Pair>(size, {0, 0}));
  Create(k_input);
}

SparseTable::Pair SparseTable::FindMin(int64_t left, int64_t right) {
  size_t deg = Log(right - left + 1);
  Pair a = ST_[deg][left];
  Pair b = ST_[deg][right - (1 << deg) + 1];
  Pair res = a.elem < b.elem ? a : b;
  return res;
}

void SparseTable::Create(const std::vector<int64_t>& k_input) {
  for (int64_t x = 0; x < size_; ++x) {
    ST_[0][x].elem = k_input[x];
    ST_[0][x].index = x;
  }
  for (int64_t i = 0; i < log_ - 1; ++i) {
    for (int64_t k = 0; k + (2 << i) <= size_; ++k) {
      Pair a = ST_[i][k];
      Pair b = ST_[i][k + (1 << i)];
      Pair res = a.elem < b.elem ? a : b;
      ST_[i + 1][k] = res;
    }
  }
}

int64_t SparseTable::FindSecStat(int64_t left, int64_t right) {
  Pair pivot = FindMin(left, right);
  Pair minleft = FindMin(left, (pivot.index - 1) < 0 ? 0 : pivot.index - 1);
  Pair minright =
      FindMin((pivot.index + 1) > right ? right : pivot.index + 1, right);
  if (pivot.index == left) {
    return minright.elem;
  }
  if (pivot.index == right) {
    return minleft.elem;
  }
  return minleft.elem < minright.elem ? minleft.elem : minright.elem;
}

void SparseTable::Out() {
  for (auto& i : ST_) {
    for (auto& k : i) {
      std::cout << k.elem << ' ';
    }
    std::cout << '\n';
  }
  std::cout << '\n' << "Check indexes: \n";
  for (auto& i : ST_) {
    for (auto& k : i) {
      std::cout << k.index << ' ';
    }
    std::cout << '\n';
  }
}

int main() {
  int64_t size;
  size_t query_num;
  std::cin >> size >> query_num;
  std::vector<int64_t> array(size, 0);
  for (auto& i : array) {
    std::cin >> i;
  }
  SparseTable table(size, array);
  int64_t left;
  int64_t right;
  while (query_num != 0) {
    std::cin >> left >> right;
    std::cout << table.FindSecStat(left - 1, right - 1) << '\n';
    --query_num;
  }

  return 0;
}