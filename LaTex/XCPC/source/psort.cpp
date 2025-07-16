#include <bits/stdc++.h>
using ld = long double;
const ld PI = acos(-1);
const ld EPS = 1e-7;
const ld INF = numeric_limits<ld>::max();
#define cc(x) cout << fixed << setprecision(x);

template <class T>
struct Point {  // 在C++17下使用 emplace_back 绑定可能会导致CE！
  T x, y;
  Point(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}  // 初始化
  template <class U>
  operator Point<U>() {  // 自动类型匹配
    return Point<U>(U(x), U(y));
  }
  Point &operator+=(Point p) & { return x += p.x, y += p.y, *this; }
  Point &operator+=(T t) & { return x += t, y += t, *this; }
  Point &operator-=(Point p) & { return x -= p.x, y -= p.y, *this; }
  Point &operator-=(T t) & { return x -= t, y -= t, *this; }
  Point &operator*=(T t) & { return x *= t, y *= t, *this; }
  Point &operator/=(T t) & { return x /= t, y /= t, *this; }
  Point operator-() const { return Point(-x, -y); }
  friend Point operator+(Point a, Point b) { return a += b; }
  friend Point operator+(Point a, T b) { return a += b; }
  friend Point operator-(Point a, Point b) { return a -= b; }
  friend Point operator-(Point a, T b) { return a -= b; }
  friend Point operator*(Point a, T b) { return a *= b; }
  friend Point operator*(T a, Point b) { return b *= a; }
  friend Point operator/(Point a, T b) { return a /= b; }
  friend bool operator<(Point a, Point b) {
    return equal(a.x, b.x) ? a.y < b.y - EPS : a.x < b.x - EPS;
  }
  friend bool operator>(Point a, Point b) { return b < a; }
  friend bool operator==(Point a, Point b) { return !(a < b) && !(b < a); }
  friend bool operator!=(Point a, Point b) { return a < b || b < a; }
  friend auto &operator>>(istream &is, Point &p) { return is >> p.x >> p.y; }
  friend auto &operator<<(ostream &os, Point p) {
    return os << "(" << p.x << ", " << p.y << ")";
  }
};

using Points = vector<Point<int>>;

double theta(auto p) { return atan2(p.y, p.x); }
void psort(Points &ps, Point<int> c = {0, 0}) {
  sort(ps.begin(), ps.end(),
       [&](auto p1, auto p2) { return lt(theta(p1 - c), theta(p2 - c)); });
}