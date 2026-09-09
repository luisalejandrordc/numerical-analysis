#include "../../include/utils.h"
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>

struct Result {
  bool success;
  double root;
  int iterations;
};

class BisectionMethod {
public:
  int MAX_ITERATIONS;
  double PRECISION;

  BisectionMethod() : MAX_ITERATIONS(1000), PRECISION(0.0001) {}

  bool oppositeSigns(double a, double b) {
    return (a > 0 && b < 0) || (a < 0 && b > 0);
  }

  Result run(std::function<double(double)> f, double a, double b,
             bool printIterations = true) {
    double f_a = f(a), f_b = f(b);
    if (!oppositeSigns(f_a, f_b)) {
      std::cout << "Error: f(a) and f(b) must have opposite signs" << std::endl;
      return {false, 0, 0};
    }
    double c, f_c;
    for (int iter = 1; iter <= MAX_ITERATIONS; iter++) {
      c = (a + b) / 2;
      f_c = f(c);
      if (printIterations) {
        std::cout << "Iteration " << iter << ":\t";
        std::cout << "a = " << a << "\t";
        std::cout << "b = " << b << "\t";
        std::cout << "c = " << c << "\t";
        std::cout << "f(c) = " << f_c << std::endl;
      }
      if (std::abs(f_c) <= PRECISION)
        return {true, c, iter};
      if (oppositeSigns(f_a, f_c))
        b = c;
      else
        a = c;
    }
    return {true, c, MAX_ITERATIONS};
  }
};

double f(double x) {
  // Real function
  return 5 * std::pow(x, 3) - 5 * std::pow(x, 2) + 6 * x - 2;
}

int main() {
  printTitle("Bisection Method");
  BisectionMethod bm;
  bm.run(f, 0, 1);
  std::cout << std::endl;
  bm.run(f, -1, 5);
  return 0;
}
