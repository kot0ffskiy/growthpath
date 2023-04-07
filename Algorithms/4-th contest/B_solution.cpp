#include <iostream>
#include <vector>

class SegTree {
 public:
  SegTree(int size, int* array, int node, int left, int right) {
    tree_ = std::vector<int>(size, 0);
    Build(array, node, left, right);
  }
  int Sum(int node, int left, int right, int lquerry, int rquerry) {
    if (lquerry > rquerry) {
      return 0;
    }
    if (lquerry == left && rquerry == right) {
      return tree_[node];
    }
    int mid = (left + right) / 2;
    int ans1 = Sum(node * 2, left, mid, lquerry, std::min(rquerry, mid));
    int ans2 =
        Sum(node * 2 + 1, mid + 1, right, std::max(lquerry, mid + 1), rquerry);
    return ans1 + ans2;
  }
  void Update(int node, int left, int right, int pos, int new_val) {
    if (left == right) {
      tree_[node] = new_val;
    } else {
      int mid = (left + right) / 2;
      if (pos <= mid) {
        Update(node * 2, left, mid, pos, new_val);
      } else {
        Update(node * 2 + 1, mid + 1, right, pos, new_val);
      }
      tree_[node] = tree_[node * 2] + tree_[node * 2 + 1];
    }
  }

 private:
  std::vector<int> tree_;
  void Build(int* a, int node, int left, int right) {
    if (left == right) {
      tree_[node] = a[left];
    } else {
      int mid = (left + right) / 2;
      Build(a, node * 2, left, mid);
      Build(a, node * 2 + 1, mid + 1, right);
      tree_[node] = tree_[node * 2] + tree_[node * 2 + 1];
    }
  }
};

int main() {
  int input;
  std::cin >> input;
  int size = 2;
  while (size < input) {
    size *= 2;
  }
  std::vector<int> even_minus(size, 0);
  std::vector<int> odd_minus(size, 0);
  int number;
  for (int i = 0; i < input; i++) {
    std::cin >> number;
    if (i % 2 == 0) {
      even_minus[i] = -number;
      odd_minus[i] = number;
    } else {
      even_minus[i] = number;
      odd_minus[i] = -number;
    }
  }
  SegTree tree_even(4 * size, even_minus.data(), 1, 0, input - 1);
  SegTree tree_odd(4 * size, odd_minus.data(), 1, 0, input - 1);
  int l;
  int r;
  int ans = 0;
  std::cin >> ans;

  for (int i = 0; i < ans; ++i) {
    std::cin >> number >> l >> r;
    if (number == 1) {
      if (l % 2 == 0) {
        std::cout << tree_even.Sum(1, 0, input - 1, l - 1, r - 1) << '\n';
      } else {
        std::cout << tree_odd.Sum(1, 0, input - 1, l - 1, r - 1) << '\n';
      }
    } else if (number == 0) {
      if (even_minus[l - 1] < 0) {
        tree_even.Update(1, 0, input - 1, l - 1, -r);
        tree_odd.Update(1, 0, input - 1, l - 1, r);
      } else {
        tree_even.Update(1, 0, input - 1, l - 1, r);
        tree_odd.Update(1, 0, input - 1, l - 1, -r);
      }
    }
  }
  return 0;
}