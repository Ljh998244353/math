#include <bits/stdc++.h>

template <class T>
pair<vector<Point<T>>, T> maxInscribedQuadrilateral(vector<Point<T>>& p) {
  int n = (int)p.size();
  // 至少需要4个顶点
  if (n < 4) return {{}, 0};
  // 计算三角形的双倍面积（绝对值）
  auto area2 = [&](int i, int j, int k) {
    T dx1 = p[j].x - p[i].x;
    T dy1 = p[j].y - p[i].y;
    T dx2 = p[k].x - p[i].x;
    T dy2 = p[k].y - p[i].y;
    return abs(dx1 * dy2 - dy1 * dx2);
  };

  // 找最低且最左顶点 (a0)，最高且最右顶点 (c0)
  int a0 = 0, c0 = 0;
  for (int i = 1; i < n; i++) {
    if (p[i].y < p[a0].y || (p[i].y == p[a0].y && p[i].x < p[a0].x)) a0 = i;
    if (p[i].y > p[c0].y || (p[i].y == p[c0].y && p[i].x > p[c0].x)) c0 = i;
  }

  int a = a0, b = a0, c = c0, d = c0;
  T maxArea = 0;
  int bestA = a, bestB = b, bestC = c, bestD = d;

  // 旋转卡尺主循环
  while (true) {
    // 移动 b 指针，使 A-B-C 三角形面积最大
    while (true) {
      int nb = (b + 1) % n;
      if (area2(a, nb, c) > area2(a, b, c))
        b = nb;
      else
        break;
    }
    // 移动 d 指针，使 C-D-A 三角形面积最大
    while (true) {
      int nd = (d + 1) % n;
      if (area2(c, nd, a) > area2(c, d, a))
        d = nd;
      else
        break;
    }
    // 计算四边形面积（注意这里 area2 返回双倍面积）
    T areaQuad = (area2(a, b, c) + area2(a, c, d)) * T(0.5);
    if (areaQuad > maxArea) {
      maxArea = areaQuad;
      bestA = a;
      bestB = b;
      bestC = c;
      bestD = d;
    }
    // 判断旋转方向：比较移动 C 后与移动 A 后的面积
    int a_next = (a + 1) % n;
    int c_next = (c + 1) % n;
    // 如果 area2(a,a_next,c_next) <= area2(a,a_next,c)，则移动 A，否则移动 C
    if (area2(a, a_next, c_next) <= area2(a, a_next, c)) {
      a = a_next;
    } else {
      c = c_next;
    }
    // 退出条件：回到初始对换位置
    if (a == c0 && c == a0) break;
  }

  vector<Point<T>> quad = {p[bestA], p[bestB], p[bestC], p[bestD]};
  return {quad, maxArea};
}