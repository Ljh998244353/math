#include <bits/stdc++.h>
using namespace std;

template <class T>
struct MinCostFlow {
  struct _Edge {
    int to;
    T cap;
    T cost;
    _Edge(int to_, T cap_, T cost_) : to(to_), cap(cap_), cost(cost_) {}
  };
  int n;
  vector<_Edge> e;
  vector<vector<int>> g;
  vector<T> dis;     // 最短路距离（SPFA）
  vector<int> pre;   // 记录到某点的边索引
  vector<char> inq;  // SPFA 是否在队列中

  MinCostFlow() {}
  MinCostFlow(int n_) { init(n_); }

  void init(int n_) {
    n = n_;
    e.clear();
    g.assign(n, {});
  }

  void addEdge(int u, int v, T cap, T cost) {
    g[u].push_back((int)e.size());
    e.emplace_back(v, cap, cost);
    g[v].push_back((int)e.size());
    e.emplace_back(u, 0, -cost);
  }

  // 使用 SPFA 求 s->t 的最短路（边权为 cost，且只考虑 cap>0 的边）
  bool spfa(int s, int t) {
    // INF 取为 numeric_limits<T>::max()/4 避免加法溢出
    const T INF = numeric_limits<T>::max() / 4;
    dis.assign(n, INF);
    pre.assign(n, -1);
    inq.assign(n, 0);

    queue<int> q;
    dis[s] = 0;
    q.push(s);
    inq[s] = 1;

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      inq[u] = 0;
      for (int idx : g[u]) {
        const _Edge &ed = e[idx];
        int v = ed.to;
        T cap = ed.cap;
        T cost = ed.cost;
        if (cap > 0 && dis[v] > dis[u] + cost) {
          dis[v] = dis[u] + cost;
          pre[v] = idx;
          if (!inq[v]) {
            q.push(v);
            inq[v] = 1;
          }
        }
      }
    }
    return pre[t] != -1;  // 或者 dis[t] < INF
  }

  pair<T, T> flow(int s, int t) {
    T flow = 0;
    T cost = 0;
    // 不再使用 potentials h，直接用 SPFA
    while (spfa(s, t)) {
      // 找增广量
      T aug = numeric_limits<T>::max();
      for (int i = t; i != s; i = e[pre[i] ^ 1].to) {
        aug = min(aug, e[pre[i]].cap);
      }
      // 改变残量网络
      for (int i = t; i != s; i = e[pre[i] ^ 1].to) {
        e[pre[i]].cap -= aug;
        e[pre[i] ^ 1].cap += aug;
      }
      flow += aug;
      // dis[t] 是此次最短路径的代价
      cost += aug * dis[t];
    }
    return make_pair(flow, cost);
  }

  struct Edge {
    int from;
    int to;
    T cap;
    T cost;
    T flow;
  };

  // 返回原始图的边 (与原实现兼容)
  vector<Edge> edges() {
    vector<Edge> a;
    for (int i = 0; i < (int)e.size(); i += 2) {
      Edge x;
      x.from = e[i + 1].to;
      x.to = e[i].to;
      x.cap = e[i].cap + e[i + 1].cap;  // 原始容量（被分配前的）
      x.cost = e[i].cost;
      x.flow = e[i + 1].cap;  // 反向边的容量表示已经流过的量
      a.push_back(x);
    }
    return a;
  }
};
