#include <bits/stdc++.h>

vector<int> g[N];
int len[N], dep[N], mxs[N], eord[N << 1], fp[N], idx, fa[N];
void dfs(int x, int pre) {
  fa[x] = pre;
  dep[x] = dep[pre] + 1;
  mxs[x] = 1;
  eord[++idx] = x;
  if (fp[x] == 0) fp[x] = idx;
  for (auto& y : g[x]) {
    if (y == pre) continue;
    dfs(y, x);
    eord[++idx] = x;
    mxs[x] = max(mxs[x], mxs[y] + 1);
  }
}
int f[N << 1][35];
void init() {
  for (int i = 1; i <= idx; ++i) f[i][0] = eord[i];
  for (int len = 1; len < 30; ++len) {
    for (int l = 1; l <= idx; ++l) {
      int r = l + (1ll << len) - 1;
      if (r > idx) break;
      f[l][len] =
          min(f[l][len - 1], f[l + (1ll << len - 1)][len - 1],
              [&](const int& x, const int& y) { return dep[x] < dep[y]; });
    }
  }
}
int lca(int x, int y) {
  int L = fp[x], R = fp[y];
  if (L > R) swap(L, R);
  int len = __lg(R - L + 1);
  // cout<<L<<" "<<R<<"\n" ;
  return min(f[L][len], f[R - (1 << len) + 1][len],
             [&](const int& x, const int& y) { return dep[x] < dep[y]; });
}