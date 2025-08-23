// compile: g++ -O2 -std=c++17 bucket_allpairs_discrete.cpp -o bucket_allpairs
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int INF = 1e9;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  if (!(cin >> n >> m)) return 0;
  struct Edge {
    int u, v;
    long long w;
  };
  vector<Edge> edges;
  edges.reserve(m);
  vector<long long> vals;
  for (int i = 0; i < m; ++i) {
    int u, v;
    long long w;
    cin >> u >> v >> w;
    --u;
    --v;
    edges.push_back({u, v, w});
    vals.push_back(w);
  }
  if (n == 0) return 0;
  // special: if no edges
  if (m == 0) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j)
          cout << 0;
        else
          cout << -1;
        if (j + 1 < n) cout << ' ';
      }
      cout << '\n';
    }
    return 0;
  }

  // 离散化权值到 rank [1..K]
  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  int K = (int)vals.size();
  // map weight -> rank (1..K)
  auto rank_of = [&](long long w) -> int {
    int idx = int(lower_bound(vals.begin(), vals.end(), w) - vals.begin());
    return idx + 1;  // ranks start from 1
  };

  // build graph with ranked weights
  vector<vector<pair<int, int>>> G(n);
  for (auto &e : edges) {
    int r = rank_of(e.w);
    G[e.u].push_back({e.v, r});
  }

  // bucketed (Dial-like) single-source minimax Dijkstra
  auto bottleneck_from = [&](int s) {
    // dist in [0..K], where 0 means source itself (no edges)
    vector<int> dist(n, INT_MAX);
    dist[s] = 0;
    vector<vector<int>> buckets(K + 1);  // 0..K
    vector<int> head(K + 1, 0);
    buckets[0].push_back(s);
    int cur = 0;
    while (true) {
      while (cur <= K && head[cur] >= (int)buckets[cur].size()) ++cur;
      if (cur > K) break;
      int u = buckets[cur][head[cur]++];
      if (dist[u] != cur) continue;  // lazy skip
      for (auto &ed : G[u]) {
        int v = ed.first, wr = ed.second;
        int cand = max(dist[u], wr);
        if (cand < dist[v]) {
          dist[v] = cand;
          if (cand <= K) buckets[cand].push_back(v);
          // cand should always be <=K (weights ranks are within 1..K)
        }
      }
    }
    return dist;
  };

  // 全源求解并输出（输出原始权值；dist==0 且 i==s 表示 0；dist==INF
  // 表示不可达）
  vector<int> dist;
  for (int s = 0; s < n; ++s) {
    dist = bottleneck_from(s);
    for (int t = 0; t < n; ++t) {
      if (s == t)
        cout << 0;
      else if (dist[t] == INT_MAX)
        cout << -1;
      else {
        int r = dist[t];
        // r in 1..K
        cout << vals[r - 1];
      }
      if (t + 1 < n) cout << ' ';
    }
    cout << '\n';
  }
  return 0;
}
