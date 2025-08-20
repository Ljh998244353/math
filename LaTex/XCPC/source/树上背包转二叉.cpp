#include <bits/stdc++.h>
#define NO 100009
using namespace std;
int n, m, v[100010], lc[100010], rc[100010];
int siz[100010];
vector<int> G[100010], f[100010];
void dfs(int pos) {
  if (pos == NO) return;
  dfs(lc[pos]);
  dfs(rc[pos]);
  for (int i = 1; i <= min(m, siz[pos]); i++) {
    f[pos][i] = f[rc[pos]][i];
    // 不需要  ...][i]  =>  ...][min(i,siz[rc[pos]])]
    // 原因是如果i>siz[rc[pos]]，就说明把右节点分配满，
    // 也有剩余的课程可以加到pos和pos的左子节点
    // 这个语句就相当于没用了
    int lj, rj;
    rj = min(i - 1, siz[lc[pos]]);
    // 左节点最多分配siz[lc[pos]]个
    lj = max(0, i - 1 - siz[rc[pos]]);
    // 右节点最多分配siz[rc[pos]]个
    // 而右节点个数是i-1-j，
    // 所以j最大枚举到i-1-siz[rc[pos]]
    for (int j = lj; j <= rj; j++) {
      // 左 j个    右 i-1-j个
      int l = f[lc[pos]][j];
      int r = f[rc[pos]][i - 1 - j];
      f[pos][i] = max(f[pos][i], l + r + v[pos]);
    }
  }
}
void conv(int pos) {
  siz[pos] = 1;
  int prei = -1;
  for (auto i : G[pos]) {
    if (prei == -1)
      lc[pos] = i;
    else
      rc[prei] = i;
    prei = i;
    conv(i);
  }
}
void cntsiz(int pos) {
  if (pos == NO) return;
  cntsiz(lc[pos]);
  cntsiz(rc[pos]);
  siz[pos] = 1 + siz[lc[pos]] + siz[rc[pos]];
}
int main() {
  cin >> n >> m;
  m++;
  for (int i = 1; i <= n; i++) {
    int u;
    cin >> u >> v[i];
    G[u].emplace_back(i);
  }
  for (int i = 0; i <= n; i++) f[i].resize(m + 1), lc[i] = rc[i] = NO;
  f[NO].resize(m + 1);
  conv(0);    // 转二叉
  cntsiz(0);  // 计算大小
  dfs(0);
  cout << f[0][m];
  return 0;
}