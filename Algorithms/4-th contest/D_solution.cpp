#include <iostream>
#include <vector>

class FenTree {
 public:
  FenTree(int size);
  void Modify(int x, int y, int z, int64_t val);
  int64_t Sum(int x1, int y1, int z1, int x2, int y2, int z2);

 private:
  std::vector<std::vector<std::vector<int64_t>>> tree_;
  int size_ = 0;
  static int F(int i) { return i & (i + 1); }
  static int G(int i) { return i | (i + 1); }
  int64_t GetPref(int x, int y, int z);
};
FenTree::FenTree(int size) {
  size_ = size;
  tree_ = std::vector<std::vector<std::vector<int64_t>>>(
      size,
      std::vector<std::vector<int64_t>>(size, std::vector<int64_t>(size, 0)));
}
void FenTree::Modify(int x, int y, int z, int64_t val) {
  for (int i = x; i < size_; i = G(i)) {
    for (int j = y; j < size_; j = G(j)) {
      for (int k = z; k < size_; k = G(k)) {
        tree_[i][j][k] += val;
      }
    }
  }
}
int64_t FenTree::GetPref(int x, int y, int z) {
  int64_t ans = 0;
  for (int i = x; i >= 0; i = F(i) - 1) {
    for (int j = y; j >= 0; j = F(j) - 1) {
      for (int k = z; k >= 0; k = F(k) - 1) {
        ans += tree_[i][j][k];
      }
    }
  }
  return ans;
}

int64_t FenTree::Sum(int x1, int y1, int z1, int x2, int y2, int z2) {
  int64_t res;
  res = GetPref(x2, y2, z2) - GetPref(x1 - 1, y2, z2) -
        GetPref(x2, y1 - 1, z2) - GetPref(x2, y2, z1 - 1) +
        GetPref(x1 - 1, y1 - 1, z2) + GetPref(x1 - 1, y2, z1 - 1) +
        GetPref(x2, y1 - 1, z1 - 1) - GetPref(x1 - 1, y1 - 1, z1 - 1);
  return res;
}

int main() {
  int input;
  std::cin >> input;
  FenTree array(input);
  int number;
  int x;
  int y;
  int z;
  while (true) {
    std::cin >> number;
    if (number == 1) {
      std::cin >> x >> y >> z >> number;
      array.Modify(x, y, z, number);
    } else if (number == 2) {
      int x_range;
      int y_range;
      int z_range;
      std::cin >> x >> y >> z >> x_range >> y_range >> z_range;
      std::cout << array.Sum(x, y, z, x_range, y_range, z_range) << '\n';
    } else if (number == 3) {
      break;
    }
  }
  return 0;
}