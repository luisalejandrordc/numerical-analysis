#include "../../include/utils.h"
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <utility>

class BisectionMethod {
  std::function<double(double)> func;
  double lower_limit;
  double upper_limit;
  int ITER_LIMIT = 1000;
  double PRECISION = 0.0001;

public:
  BisectionMethod(std::function<double(double)> f, int a, int b)
      : func(std::move(f)), lower_limit(a), upper_limit(b) {}

  bool oppositeSigns(double a, double b) {
    return (a > 0 && b < 0) || (a < 0 && b > 0);
  }

  std::pair<bool, double> run() {
    double a = lower_limit, b = upper_limit;
    double f_a = func(a), f_b = func(b);
    if (!oppositeSigns(f_a, f_b)) {
      std::cout << "Error: f(a) and f(b) must have opposite signs" << std::endl;
      return {false, 0};
    }
    double c, f_c;
    for (int iter = 0; iter < ITER_LIMIT; iter++) {
      c = (a + b) / 2;
      f_c = func(c);
      std::cout << "Iteration " << iter + 1 << ":\t";
      std::cout << "a = " << a << "\t";
      std::cout << "b = " << b << "\t";
      std::cout << "c = " << c << "\t";
      std::cout << "f(c) = " << f_c << std::endl;
      if (std::abs(f_c) <= PRECISION)
        return {true, c};
      if (oppositeSigns(f_a, f_c))
        b = c;
      else
        a = c;
    }
    return {true, c};
  }
};

double f(double x) {
  // Real function
  return 5 * std::pow(x, 3) - 5 * std::pow(x, 2) + 6 * x - 2;
}

int main() {
  printTitle("Bisection Method");
  BisectionMethod bm(f, 0, 1);
  std::pair<bool, double> ans = bm.run();
  return 0;
}
