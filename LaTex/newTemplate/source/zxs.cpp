struct DistinctCountTree {
  static constexpr int N = 2e5 + 10;
  int cntNodes, root[N];
  int last[N];  // 记录每个数字最后出现的位置

  struct node {
    int l, r;
    int sum;  // 区间和
  } tr[4 * N + 17 * N];

  // 单点更新
  void update(int& u, int v, int l, int r, int pos, int val) {
    u = ++cntNodes;
    tr[u] = tr[v];
    tr[u].sum += val;

    if (l == r) return;

    int mid = (l + r) / 2;
    if (pos <= mid)
      update(tr[u].l, tr[v].l, l, mid, pos, val);
    else
      update(tr[u].r, tr[v].r, mid + 1, r, pos, val);
  }

  // 区间求和
  int query(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tr[u].sum;

    int mid = (l + r) / 2, res = 0;
    if (ql <= mid) res += query(tr[u].l, l, mid, ql, qr);
    if (qr > mid) res += query(tr[u].r, mid + 1, r, ql, qr);
    return res;
  }

  // 构建主席树
  void build(int n, int a[]) {
    // 初始化last数组
    for (int i = 0; i <= n; i++) last[i] = 0;

    // 逐个处理每个位置
    for (int i = 1; i <= n; i++) {
      if (last[a[i]] != 0) {
        // 这个数字之前出现过，先清除之前位置的标记
        int temp;
        update(temp, root[i - 1], 1, n, last[a[i]], -1);
        update(root[i], temp, 1, n, i, 1);
      } else {
        // 第一次出现这个数字
        update(root[i], root[i - 1], 1, n, i, 1);
      }
      last[a[i]] = i;  // 更新最后出现位置
    }
  }

  // 查询区间[L,R]中不同数的个数
  int query_distinct(int L, int R) { return query(root[R], 1, n, L, R); }
};