#include <bits/stdc++.h>
using namespace std;
int n, m, v[100010];
vector<int> G[100010], f[100010];
int siz[100010], awa[100010], len;
void dfs(int pos) {
  siz[pos] = 1;
  for (auto i : G[pos]) {
    dfs(i);
    siz[pos] += siz[i];
  }
  awa[++len] = pos;
}
// 前i个点，代价j，最大价值。
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    int u;
    cin >> u >> v[i];
    G[u].emplace_back(i);
  }
  dfs(0);
  f[0].resize(m + 1);
  for (int i = 1; i <= n; i++) {
    f[i].resize(m + 1);
    for (int j = 1; j <= m; j++) {
      f[i][j] = max(f[i - 1][j - 1] + v[awa[i]], f[i - siz[awa[i]]][j]);
    }
  }
  cout << f[n][m];
  return 0;
}