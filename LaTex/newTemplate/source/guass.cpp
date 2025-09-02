#include <bits/stdc++.h>
using cd = complex<long double>;
cd ar[10][10];
const double eps = 1e-8;
int gauss(int n) {
  int c, r;
  for (c = 0, r = 0; c < n; ++c) {
    int t = r;
    for (int i = r; i < n; ++i) {
      if (std::abs(ar[i][c]) > std::abs(ar[t][c])) t = i;
    }
    if (std::abs(ar[t][c]) < eps) continue;
    for (int j = c; j < n + 1; ++j) std::swap(ar[t][j], ar[r][j]);
    for (int j = n; j >= c; --j) ar[r][j] /= ar[r][c];
    for (int i = r + 1; i < n; ++i) {
      if (std::abs(ar[i][c]) > eps) {
        for (int j = n; j >= c; --j) {
          ar[i][j] -= ar[r][j] * ar[i][c];
        }
      }
    }
    r++;
  }
  if (r < n) {
    for (int i = r; i < n; ++i) {
      bool allZero = true;
      for (int j = 0; j < n; ++j) {
        if (std::abs(ar[i][j]) > eps) {
          allZero = false;
          break;
        }
      }
      if (allZero && std::abs(ar[i][n]) > eps) return 2;
    }
    return 1;
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int j = i + 1; j < n; ++j) {
      ar[i][n] -= ar[i][j] * ar[j][n];
    }
  }
  return 0;
}