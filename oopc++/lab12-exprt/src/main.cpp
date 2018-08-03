#include "operations.h"
#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>

using std::cout;
using std::endl;
using namespace std::chrono;

int main() {

  // constants
  const size_t dim = 500;
  const int ITERS = 5000;
  const double C1 = 0.13337;
  const double C2 = 1555.3;

  std::array<double, dim> A1;
  std::array<double, dim> A2;
  std::array<double, dim> A3;
  std::array<std::array<double, dim>, dim> M1;

  //  fill M
  for (int i = 0; i < dim; i++) {
    M1[i][i] = 2.0;
  }
  for (int k = 1, l = 1, iter = 0; iter < dim * dim; iter++) {
    M1[k][l] = k * l * 15.57 + 3.0;
    auto tmp = k;
    k = (k % dim + l % dim) % dim;
    l = tmp;
  }
  // fill vectors
  for (auto& x : A1) {
    x = 2.3;
  }
  for (auto& x : A2) {
    x = 3.7;
  }

  auto start = system_clock::now();
  for (int c = 0; c < ITERS; ++c) {
    double coef = C1, coeff = C2;

    for (int i = 0; i < dim; ++i) {
      double tmp = 0.0;
      for (int k = 0; k < dim; ++k) {
        tmp += M1[i][k] * (coef * A1[k] + A2[k]);
      }
      A3[i] = tmp + coeff * A2[i];
    }
    coef += 0.01 + coeff;
  }
  auto end = system_clock::now();
  auto duration = duration_cast<microseconds>(system_clock::now() - start);

  cout << "C time for " << dim << " dimension and "
       << ITERS << " iterations = " << duration.count() << " microseconds.\n ";
  cout << A3[0] << endl;

  Vector<dim> B1;
  Vector<dim> B2;
  Vector<dim> B3;
  Matrix<dim, dim> H1;

  //  fill H
  for (int i = 0; i < dim; ++i) {
    H1(i, i) = 2.0;
  }
  for (int k = 1, l = 1, iter = 0; iter < dim * dim; iter++) {
    H1(k, l) = k * l * 15.57 + 3.0;
    auto tmp = k;
    k = (k % dim + l % dim) % dim;
    l = tmp;
  }

  // fill vectors
  for (int i = 0; i < dim; i++) {
    B1[i] = 2.3;
  }
  for (int i = 0; i < dim; i++) {
    B2[i] = 3.7;
  }

  start = system_clock::now();
  for (int c = 0; c < ITERS; ++c) {
    double coef = C1, coeff = C2;
    B3 = H1 * (coef * B1 + B2) + coeff * B2;
    coef += 0.01 + coeff;
  }
  end = system_clock::now();
  duration = duration_cast<microseconds>(system_clock::now() - start);

  cout << "C time for " << dim << " dimension and "
       << ITERS << " iterations = " << duration.count() << " microseconds.\n ";
  cout << B3[0] << endl;

  return 0;
}
