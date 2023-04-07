#include <cmath>
#include <iomanip>
#include <iostream>

double AverageGeom(const double* left, const double* right,
                   const double* array) {
  long arr_size = right - left;
  const double kPowConstant = 100000.0;
  if (left - array > 0) {
    double product = *(right - 1) / *(left - 1);
    return static_cast<double>(pow(product, kPowConstant / ((double)arr_size)));
  }
  return static_cast<double>(
      pow(*(right - 1), kPowConstant / ((double)arr_size)));
}

void Input(int mandrug_num, double* volumes) {
  double tmp = 0;
  std::cin >> tmp;
  const double kPowConstant = 100000;
  *volumes = pow(tmp, 1.0 / kPowConstant);
  for (int i = 1; i < mandrug_num; i++) {
    std::cin >> tmp;
    tmp = pow(tmp, 1.0 / kPowConstant);
    *(volumes + i) = *(volumes + i - 1) * tmp;
  }
}

void Solve() {
  int mandrug_num = 0;
  std::cin >> mandrug_num;
  double* volumes = new double[mandrug_num];
  Input(mandrug_num, volumes);
  int request_num = 0;
  std::cin >> request_num;
  /// @brief Queries
  int left_br = 0;
  int right_br = 0;
  std::cout << std::fixed;
  for (int i = 0; i < request_num; i++) {
    std::cin >> left_br >> right_br;
    const int kPrecision = 7;
    std::cout << std::setprecision(kPrecision)
              << AverageGeom(volumes + left_br, volumes + right_br + 1, volumes)
              << std::endl;
  }
  delete[] volumes;
}

int main() {
  Solve();
  return 0;
}
