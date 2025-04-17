/*并查集(启发式合并)
 */
#include <bits/stdc++.h>

struct DSU {
  vector<int> fa, p, e, f;
  DSU(int n) {
    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    p.resize(n + 1, 1);
    e.resize(n + 1);
    f.resize(n + 1);
  }
  int get(int x) {
    while (x != fa[x]) {
      x = fa[x] = fa[fa[x]];
    }
    return x;
  }
  bool merge(int x, int y) {  // 设x是y的祖先
    if (x == y) f[get(x)] = 1;
    x = get(x), y = get(y);
    e[x]++;
    if (x == y) return false;
    if (x < y) swap(x, y);
    fa[y] = x;
    f[x] |= f[y], p[x] += p[y], e[x] += e[y];
    return true;
  }
  bool same(int x, int y) { return get(x) == get(y); }
  bool F(int x) { return f[get(x)]; }
  int size(int x) { return p[get(x)]; }
  int E(int x) { return e[get(x)]; }
};
/*食用方法：
1.初始化: DSU s(n),维护节点[1,n]
2.找根: get(x)
3.合并: merge(x,y) 将编号小的合并到大的上
4.判断是否连通: bool same(x,y)
5.判断连通块内是否存在自环: F(x)
6.输出连通块中点的数量:size(x)
7.输出连通块中边的数量:E(x)
*/