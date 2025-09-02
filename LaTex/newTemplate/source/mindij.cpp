#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int INF = 1e9;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  if (!(cin >> n >> m)) return 0;
  vector<vector<pair<int, int>>> G(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    --u;
    --v;
    G[u].push_back({v, w});
  }
  // result matrix
  vector<vector<int>> res(n, vector<int>(n, INF));
  for (int s = 0; s < n; s++) {
    // Dijkstra-like for minimax
    vector<int> dist(n, INF);
    dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;
    pq.push({0, s});
    while (!pq.empty()) {
      auto [d, u] = pq.top();
      pq.pop();
      if (d != dist[u]) continue;
      for (auto &e : G[u]) {
        int v = e.first, w = e.second;
        int cand = max(dist[u], w);
        if (cand < dist[v]) {
          dist[v] = cand;
          pq.push({dist[v], v});
        }
      }
    }
    // store
    for (int v = 0; v < n; ++v) res[s][v] = dist[v];
  }

  // 输出
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (res[i][j] == INF)
        cout << -1;
      else
        cout << res[i][j];
      if (j + 1 < n) cout << ' ';
    }
    cout << '\n';
  }
  return 0;
}
