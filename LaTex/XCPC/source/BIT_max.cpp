/*树状数组求最（大）值
单点修改（赋值）+区间最大值查询
*/
template <class T>
struct BIT {
  int n;
  vector<T> base, w;
  inline int LB(int x) { return x & -x; }
  BIT(auto &in) : n(in.size() - 1), w(in), base(in) {
    for (int i = 1; i <= n; i++) {
      update(i, in[i]);
    }
  }
  /* 可以增加并使用常规封装中的几个函数 */
  void update(int x, int v) {  // 单点修改
    base[x] = v;
    for (; x <= n; x += LB(x)) {
      w[x] = base[x];
      for (int i = 1; i < LB(x); i *= 2) {
        w[x] = max(w[x], w[x - i]);
      }
    }
  }
  T getMax(int l, int r) {  // 最值查询
    T ans = T();
    while (r >= l) {
      ans = max(base[r], ans);
      for (r--; r - LB(r) >= l; r -= LB(r)) {
        ans = max(w[r], ans);
      }
    }
    return ans;
  }
};
/*食用方法
1.初始化：BIT(vector<int>& a),[1,n],
2.单点修改：update(x,v)更新x为v
3.区间最值查询：getMax(l,r) ,[l,r]
*/