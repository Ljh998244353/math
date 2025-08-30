#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

/**
 * @brief 网络流封装
 *
 * 使用原始对偶算法 (Primal-Dual)，配合 Dijkstra 和势函数。
 * 同时集成一个普通的最大流（Dinic）用于不带费用的最大流场景，
 * 并把所有“没有 cost 的最大流接口”改为使用普通最大流以获得更好常数与简洁性。
 *
 * @tparam T 容量和费用的数据类型 (例如 int, long long)。
 */
template <class T>
struct MinCostFlow {
  // ----- 内部最小费用边结构（保留用于带费用的算法） -----
  struct _Edge {
    int to;  // 终点
    T cap;   // 容量 / 当前残量
    T cost;  // 费用（最大流算法忽略）
    _Edge(int to_ = 0, T cap_ = 0, T cost_ = 0)
        : to(to_), cap(cap_), cost(cost_) {}
  };

  // 对外返回的边信息
  struct Edge {
    int from, to;
    T cap, cost, flow;
  };

  // 方便的参数结构体
  struct E_Cap {
    int u, v;
    T cap;
  };  // 仅有容量的边
  struct E_Cost {
    int u, v;
    T cap, cost;
  };  // 有容量和费用的边
  struct E_Bound {
    int u, v;
    T low, cap;
  };  // 有流量下界的边
  struct E_Full {
    int u, v;
    T low, cap, cost;
  };  // 完整信息的边

  int n;
  vector<_Edge> e;        // 用于最小费用流（也被最大流复用：仅 cap 字段）
  vector<vector<int>> g;  // 邻接表：存储边在 e 中的索引（成对出现：正向、反向）
  vector<T> h, dis;       // 势函数 / Dijkstra 距离
  vector<int> pre;        // Dijkstra 的前驱（存储边索引）

  // 为 Dinic 复用的结构体（减少重复分配）
  vector<int> level;
  vector<int> it_ptr;

  const T INF = numeric_limits<T>::max() / 4;

 public:
  MinCostFlow() : n(0) {}
  MinCostFlow(int n_) { init(n_); }

  // init 支持期望边数以便预分配
  void init(int n_, size_t expected_edges = 0) {
    n = n_;
    e.clear();
    if (expected_edges) e.reserve(expected_edges * 2 + 4);
    g.assign(n, {});
    if (expected_edges && n > 0) {
      size_t avg = max<size_t>(1, expected_edges / (size_t)n);
      for (int i = 0; i < n; ++i) g[i].reserve(avg + 1);
    }
    h.assign(n, 0);
    dis.assign(n, 0);
    pre.assign(n, -1);
    level.assign(n, -1);
    it_ptr.assign(n, 0);
  }

  // 加边 (u->v, 容量 cap, 费用 cost)
  inline void addEdge(int u, int v, T cap, T cost) {
    g[u].push_back((int)e.size());
    e.emplace_back(v, cap, cost);
    g[v].push_back((int)e.size());
    e.emplace_back(u, (T)0, -cost);  // 反向边（初始 cap=0）
  }

  // ---------------- 最小费用流部分（与之前保持兼容） ----------------

  // SPFA 初始化势函数 h，用于处理负权边
  bool spfa_init_h(int s) {
    T localINF = INF;
    std::fill(h.begin(), h.end(), localINF);
    vector<char> inq(n, 0);
    vector<int> cnt(n, 0);
    vector<int> q;
    q.reserve(n * 2 + 4);
    int qh = 0;
    q.push_back(s);
    inq[s] = 1;
    cnt[s] = 1;
    h[s] = 0;
    while (qh < (int)q.size()) {
      int u = q[qh++];
      inq[u] = 0;
      for (int idx : g[u]) {
        const _Edge& ed = e[idx];
        if (ed.cap > 0) {
          T nv = h[u] + ed.cost;
          if (h[ed.to] > nv) {
            h[ed.to] = nv;
            if (!inq[ed.to]) {
              inq[ed.to] = 1;
              q.push_back(ed.to);
              if (++cnt[ed.to] > n) return false;  // 检测到负环
            }
          }
        }
      }
    }
    return true;
  }

  // Dijkstra 寻找最短增广路（使用势函数）
  bool dijkstra(int s, int t) {
    T localINF = INF;
    std::fill(dis.begin(), dis.end(), localINF);
    std::fill(pre.begin(), pre.end(), -1);
    using P = pair<T, int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    dis[s] = 0;
    pq.emplace((T)0, s);
    while (!pq.empty()) {
      auto [d, u] = pq.top();
      pq.pop();
      if (d != dis[u]) continue;
      for (int i : g[u]) {
        const _Edge& ed = e[i];
        if (ed.cap <= 0) continue;
        T nd = d + h[u] - h[ed.to] + ed.cost;
        if (dis[ed.to] > nd) {
          dis[ed.to] = nd;
          pre[ed.to] = i;
          pq.emplace(nd, ed.to);
        }
      }
    }
    return dis[t] != localINF;
  }

  // 求解最小费用最大流 (默认版本，边权非负)
  pair<T, T> flow(int s, int t) {
    T flow_val = 0;
    T cost_val = 0;
    std::fill(h.begin(), h.end(), (T)0);
    while (dijkstra(s, t)) {
      for (int i = 0; i < n; ++i) {
        if (dis[i] != INF) h[i] += dis[i];
      }
      T aug = INF;
      for (int i = t; i != s; i = e[pre[i] ^ 1].to) {
        aug = min(aug, e[pre[i]].cap);
      }
      for (int i = t; i != s; i = e[pre[i] ^ 1].to) {
        e[pre[i]].cap -= aug;
        e[pre[i] ^ 1].cap += aug;
      }
      flow_val += aug;
      cost_val += aug * h[t];
    }
    return {flow_val, cost_val};
  }

  // 可处理负权边的 flow（警告：图中不能有从源点可达的负费用环）
  pair<T, T> flow_neg(int s, int t) {
    if (!spfa_init_h(s)) {
      return {0, -INF};  // 有从源可达的负环，费用无下界
    }
    return flow(s, t);
  }

  // 获取最终的流网络信息（基于 e/g：假定边以成对方式存储）
  vector<Edge> edges() {
    vector<Edge> res;
    res.reserve(e.size() / 2);
    for (size_t i = 0; i + 1 < e.size(); i += 2) {
      // forward edge is at i, reverse at i+1
      res.push_back({e[i + 1].to, e[i].to, e[i].cap + e[i + 1].cap, e[i].cost,
                     e[i + 1].cap});
    }
    return res;
  }

  // ---------------- 普通最大流（Dinic）实现（复用 e/g 的 cap 字段）
  // ----------------

  // 为兼容性：在当前已使用 addEdge 构建好的图上运行 Dinic，修改 e 中的 cap &
  // 反向 cap
  T maxflow_on_current_graph(int s, int t) {
    // level / it_ptr 已在 init 时分配
    auto bfs = [&](void) -> bool {
      std::fill(level.begin(), level.end(), -1);
      vector<int> q;
      q.reserve(n);
      int qh = 0;
      q.push_back(s);
      level[s] = 0;
      while (qh < (int)q.size()) {
        int u = q[qh++];
        for (int idx : g[u]) {
          if (e[idx].cap > 0 && level[e[idx].to] == -1) {
            level[e[idx].to] = level[u] + 1;
            q.push_back(e[idx].to);
          }
        }
      }
      return level[t] != -1;
    };

    function<T(int, T)> dfs = [&](int u, T pushed) -> T {
      if (u == t || pushed == 0) return pushed;
      for (int& cid = it_ptr[u]; cid < (int)g[u].size(); ++cid) {
        int ei = g[u][cid];
        _Edge& ed = e[ei];
        if (ed.cap > 0 && level[ed.to] == level[u] + 1) {
          T tr = dfs(ed.to, min(pushed, ed.cap));
          if (tr > 0) {
            ed.cap -= tr;
            e[ei ^ 1].cap += tr;
            return tr;
          }
        }
      }
      return (T)0;
    };

    T flow = 0;
    while (bfs()) {
      std::fill(it_ptr.begin(), it_ptr.end(), 0);
      while (true) {
        T pushed = dfs(s, INF);
        if (pushed == 0) break;
        flow += pushed;
      }
    }
    return flow;
  }

  // 一个便捷的接口：根据传入的边列表构建图并求最大流（与旧接口保持相同签名）
  T max_flow(int _n, int s, int t, const vector<E_Cap>& es) {
    init(_n, es.size());
    for (const auto& edge : es) addEdge(edge.u, edge.v, edge.cap, 0);
    return maxflow_on_current_graph(s, t);
  }

  // ---------------- 封装接口（把“无费用最大流”相关操作改为使用 Dinic）
  // ----------------

  // 1. 无源汇可行流 (循环流)
  // 使用 Dinic 来判断可行性并且保留 e/g 中的流量信息，便于后续读取 edges()
  bool feasible_circulation(int _n, const vector<E_Bound>& es) {
    // 仍然在 this (mcf 对象) 上构建图，以便 edges() 能反映流
    init(_n + 2, es.size());
    int SS = _n, ST = _n + 1;
    vector<T> diff(_n, 0);

    for (const auto& edge : es) {
      diff[edge.u] -= edge.low;
      diff[edge.v] += edge.low;
      addEdge(edge.u, edge.v, edge.cap - edge.low, 0);
    }

    T sup_sum = 0;
    for (int i = 0; i < _n; ++i) {
      if (diff[i] > 0) {
        addEdge(SS, i, diff[i], 0);
        sup_sum += diff[i];
      } else if (diff[i] < 0) {
        addEdge(i, ST, -diff[i], 0);
      }
    }

    T flow_val = maxflow_on_current_graph(SS, ST);
    return flow_val == sup_sum;
  }

  // 2. 有源汇可行流
  // 返回 {是否存在, 一个可行的流值}
  pair<bool, T> feasible_flow(int _n, int s, int t, const vector<E_Bound>& es) {
    vector<E_Bound> circ_es = es;
    circ_es.push_back({t, s, 0, INF});
    if (feasible_circulation(_n, circ_es)) {
      T res = 0;
      // 流值为 t->s 的反向边的流量（edges() 中的 flow 值）
      for (const auto& ed : this->edges()) {
        if (ed.from == t && ed.to == s) {
          res = ed.flow;
          break;
        }
      }
      return {true, res};
    }
    return {false, 0};
  }

  // 3. 有源汇上下界最大流
  // 返回 {是否存在可行流, 最大流值}
  // 说明：先判断是否存在满足上下界的可行流（添加 t->s 无限边），若存在则读取
  // t->s 的流量 flow1， 然后在残量图（去掉人工 t->s 边）上用 Dinic 再增广得到
  // flow2，最终最大流为 flow1 + flow2。
  pair<bool, T> bounded_max_flow(int _n, int s, int t,
                                 const vector<E_Bound>& es) {
    // 在一个临时 mcf1 对象上构造并判断可行性（但为了方便后续读取
    // edges()，这里直接用当前对象）
    MinCostFlow<T> mcf1;
    vector<E_Bound> circ_es = es;
    circ_es.push_back({t, s, 0, INF});
    // 使用 mcf1 的 feasible_circulation（其内部会 init 并运行 Dinic，并保留
    // e/g）
    if (!mcf1.feasible_circulation(_n, circ_es)) {
      return {false, 0};
    }

    // 找到 t->s 边的流量（作为初始 s->t 流）
    T flow1 = 0;
    for (const auto& ed : mcf1.edges()) {
      if (ed.from == t && ed.to == s) {
        flow1 = ed.flow;
        break;
      }
    }

    // 构建残量图：将 mcf1 中剩余容量 >0 的边作为 residual_edges（跳过人工 t->s
    // 边）
    vector<E_Cap> residual_edges;
    residual_edges.reserve(mcf1.e.size() / 2);
    for (const auto& ed : mcf1.edges()) {
      if (ed.from < _n && ed.to < _n) {
        if (ed.from == t && ed.to == s) continue;  // 跳过人工边
        T rem_cap = ed.cap - ed.flow;              // 剩余容量
        if (rem_cap > 0) residual_edges.push_back({ed.from, ed.to, rem_cap});
      }
    }

    // 在新图上用 Dinic 再跑一次最大流（增广 s->t）
    MinCostFlow<T> mcf2;
    T flow2 = mcf2.max_flow(_n, s, t, residual_edges);

    return {true, flow1 + flow2};
  }

  // 4. 有源汇最小流
  // 返回 {是否存在, 最小流值}
  pair<bool, T> min_flow(int _n, int s, int t, const vector<E_Bound>& es) {
    MinCostFlow<T> mcf1;
    vector<E_Bound> circ_es = es;
    circ_es.push_back({t, s, 0, INF});  // 添加 t->s 的边构成循环

    bool ok = mcf1.feasible_circulation(_n, circ_es);
    if (!ok) return {false, 0};

    T flow1 = 0;  // 初始可行流 (t->s)
    for (const auto& ed : mcf1.edges()) {
      if (ed.from == t && ed.to == s) {
        flow1 = ed.flow;
        break;
      }
    }

    // 在残量图上，从 t 到 s 跑最大流，即可退回最多的流
    MinCostFlow<T> mcf2;
    mcf2.init(_n, mcf1.e.size() / 2);

    for (const auto& ed : mcf1.edges()) {
      // 只考虑原始节点范围内的边
      if (ed.from < _n && ed.to < _n) {
        // 跳过我们人为加入的 t->s 边（否则会误导增广）
        if (ed.from == t && ed.to == s) continue;

        T forward_rem = ed.cap - ed.flow;  // 前向剩余容量 = C - f
        T backward_rem = ed.flow;          // 反向剩余容量 = f (可以退回的流)

        if (forward_rem > 0) mcf2.addEdge(ed.from, ed.to, forward_rem, 0);
        if (backward_rem > 0) mcf2.addEdge(ed.to, ed.from, backward_rem, 0);
      }
    }

    T flow2 = mcf2.maxflow_on_current_graph(t, s);
    return {true, flow1 - flow2};
  }

  // 5. 有源汇上下界最小费用可行流
  // 返回 {是否存在, 流值, 费用值}，如果有负环则费用为 -INF 表示无下界
  tuple<bool, T, T> min_cost_feasible_flow(int _n, int s, int t,
                                           const vector<E_Full>& es) {
    vector<E_Full> circ_es = es;
    circ_es.push_back({t, s, (T)0, INF, (T)0});
    auto [ok, cost] = min_cost_circulation(_n, circ_es);
    if (!ok) return {false, (T)0, (T)0};
    T f = 0;
    for (const auto& ed : edges()) {
      if (ed.from == t && ed.to == s) {
        f = ed.flow;
        break;
      }
    }
    return {true, f, cost};
  }

  // 6. 无源汇上下界最小费用可行流
  // 返回 {是否存在, 费用值}，如果有负环则费用为 -INF 表示无下界
  pair<bool, T> min_cost_circulation(int _n, const vector<E_Full>& es) {
    init(_n + 2, es.size());
    int SS = _n, ST = _n + 1;
    vector<T> diff(_n, 0);
    T base_cost = 0;
    bool has_neg = false;
    for (const auto& edge : es) {
      if (edge.low > edge.cap) return {false, (T)0};
      diff[edge.u] -= edge.low;
      diff[edge.v] += edge.low;
      base_cost += edge.low * edge.cost;
      if (edge.cap > edge.low) {
        addEdge(edge.u, edge.v, edge.cap - edge.low, edge.cost);
        if (edge.cost < 0) has_neg = true;
      }
    }
    T sup_sum = 0;
    for (int i = 0; i < _n; ++i) {
      if (diff[i] > 0) {
        addEdge(SS, i, diff[i], (T)0);
        sup_sum += diff[i];
      } else if (diff[i] < 0) {
        addEdge(i, ST, -diff[i], (T)0);
      }
    }
    pair<T, T> res{(T)0, (T)0};
    if (has_neg) {
      res = flow_neg(SS, ST);
      if (res.second == -INF) return {false, -INF};
    } else {
      res = flow(SS, ST);
    }
    if (res.first < sup_sum) return {false, (T)0};
    return {true, base_cost + res.second};
  }

  // 7. 有负环的费用流（最小费用最大流，支持负费用，可能有负环时计算有限费用）
  // 返回 {是否存在解, 流值,
  // 费用值}，如果无法平衡（可能由于负环导致无界）则不存在解
  tuple<bool, T, T> min_cost_max_flow_neg(int _n, int s, int t,
                                          const vector<E_Cost>& es) {
    init(_n + 2, es.size());
    int SS = _n, ST = _n + 1;
    vector<T> diff(_n, 0);
    T base_cost = 0;
    for (const auto& edge : es) {
      if (edge.cost >= 0) {
        addEdge(edge.u, edge.v, edge.cap, edge.cost);
      } else {
        if (edge.cap == 0) continue;
        diff[edge.u] -= edge.cap;
        diff[edge.v] += edge.cap;
        base_cost += edge.cap * edge.cost;
        addEdge(edge.v, edge.u, edge.cap, -edge.cost);
      }
    }
    T sup_sum = 0;
    for (int i = 0; i < _n; ++i) {
      if (diff[i] > 0) {
        addEdge(SS, i, diff[i], (T)0);
        sup_sum += diff[i];
      } else if (diff[i] < 0) {
        addEdge(i, ST, -diff[i], (T)0);
      }
    }
    addEdge(t, s, INF, (T)0);
    pair<T, T> res1 = flow(SS, ST);
    if (res1.first < sup_sum) {
      return {false, (T)0, (T)0};
    }
    size_t last_rev = e.size() - 1;
    T flow_back = e[last_rev].cap;
    // 禁用超级源汇相关边
    for (int idx : g[SS]) {
      e[idx].cap = 0;
      e[idx ^ 1].cap = 0;
    }
    for (int idx : g[ST]) {
      e[idx].cap = 0;
      e[idx ^ 1].cap = 0;
    }
    // 禁用 t->s 边
    size_t ts_fwd = e.size() - 2;
    e[ts_fwd].cap = 0;
    e[ts_fwd ^ 1].cap = 0;
    pair<T, T> res2 = flow(s, t);
    T total_flow = flow_back + res2.first;
    T total_cost = base_cost + res1.second + res2.second;
    return {true, total_flow, total_cost};
  }
};
