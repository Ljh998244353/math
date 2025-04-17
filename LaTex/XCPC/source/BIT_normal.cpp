/*树状数组(normal)
 */
#include <bits/stdc++.h>

template <class T>
struct BIT {
  int n;
  vector<T> w;
  BIT(int n, auto &in) : n(n), w(n + 1) {  // 预处理填值
    for (int i = 1; i <= n; i++) {
      add(i, in[i]);
    }
  }
  void add(int x, T v) {
    for (; x <= n; x += x & -x) {
      w[x] += v;
    }
  }
  T ask(int x) {  // 前缀和查询
    T ans = 0;
    for (; x; x -= x & -x) {
      ans += w[x];
    }
    return ans;
  }
  T ask(int l, int r) {  // 差分实现区间和查询
    return ask(r) - ask(l - 1);
  }
};

/* 食用方法
1.初始化：BIT(n,vector<Int>& a) 维护区间[1,n],初始化数组a
2.单点加：add(x,v),给x+v
3.区间和查询：ask(l,r),查询[l,r],或者ask(x),查询[1,n]
*/