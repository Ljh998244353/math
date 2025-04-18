## 1.ABC 364 [F - Range Connect MST](https://atcoder.jp/contests/abc364/tasks/abc364_f)(思维/并查集/线段树)(1700-1800/0)

### Problem Statement

There is a graph with $N + Q$ vertices, numbered $1, 2, \ldots, N + Q$. Initially, the graph has no edges.

For this graph, perform the following operation for $i = 1, 2, \ldots, Q$ in order:

-   For each integer $j$ satisfying $L_i \leq j \leq R_i$, add an undirected edge with cost $C_i$ between vertices $N + i$ and $j$.

Determine if the graph is connected after all operations are completed. If it is connected, find the cost of a minimum spanning tree of the graph.

A minimum spanning tree is a spanning tree with the smallest possible cost, and the cost of a spanning tree is the sum of the costs of the edges used in the spanning tree.

### Constraints

-   $1 \leq N, Q \leq 2 \times 10^5$
-   $1 \leq L_i \leq R_i \leq N$
-   $1 \leq C_i \leq 10^9$
-   All input values are integers.

### 思路

首先容易想到按边权排序。我们默认每一次操作至少添加一次，那么我们可以将$N+1\sim N+Q$看成已经联通，我们可以初始状态看成$N+1$个连通块，目标是使最后只剩下一个联通块。而对于具体的一次操作我们显然需要连接范围内所有联通块。

#### 利用set

注意到每一个连通块连接的点是连续的。我们用set储存每个连通块最小的点的编号，每次操作可以二分快速找到连通块数量。具体细节看代码。

```cpp
struct node {
  int l, r, c;
  bool operator<(const node& u) const { return c < u.c; }
} a[N];
void solve() {
  int n, q;
  cin >> n >> q;
  set<int> st;
  for (int i = 1; i <= n; ++i) st.insert(i);
  for (int i = 1; i <= q; ++i) cin >> a[i].l >> a[i].r >> a[i].c;
  sort(a + 1, a + 1 + q);
  ll ans = 0;
  for (int i = 1; i <= q; ++i) {
    auto s = st.upper_bound(a[i].l), e = st.upper_bound(a[i].r);
    s--, e--;
    ll cnt = 1;
    if (s != e) {
      s++;
      while (s != e) {
        auto it = ++s;
        s--;
        st.erase(s);
        s = it;
        cnt++;
      }
      cnt++;
      st.erase(e);
    }
    ans += cnt * a[i].c;
  }
  if (st.size() > 1) ans = -1;
  cout << ans;
}
```

#### 利用并查集

原理和用set类似。

代码

```cpp
struct node {
  int l, r, c;
  bool operator<(const node& u) const { return c < u.c; }
} a[N];
int pre[N];
inline int root(int x) { return pre[x] = (pre[x] == x ? x : root(pre[x])); }
void solve() {
  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) pre[i] = i;
  for (int i = 1; i <= q; ++i) cin >> a[i].l >> a[i].r >> a[i].c;
  sort(a + 1, a + 1 + q);
  ll ans = 0;
  for (int i = 1; i <= q; ++i) {
    auto [l, r, c] = a[i];
    ans += c;
    while (root(l) != root(r)) ans += c, pre[root(r)] = root(r) - 1;
  }
  if (root(1) != root(n)) ans = -1;
  cout << ans;
}

```

#### 利用线段树

我们维护一个数组$t$，若$i$与$i+1$联通，则为0否则为1。那么，$[l,r]$的联通块数量为$[l,r)$的和加1。证明很容易，不多赘述。

```cpp
struct node {
  int l, r, c;
  bool operator<(const node& u) const { return c < u.c; }
} a[N];
#define ls p << 1
#define rs p << 1 | 1
struct tree {
  ll l, r, s, lz, mlz;
} t[N << 2];

inline ll mo(ll x) { return (x + mod) % mod; }

inline void push_up(ll p) { t[p].s = mo(t[ls].s + t[rs].s); }

void update(ll p, ll k, ll x) {
  t[p].s = mo(mo(t[p].s * k) + mo(x * (t[p].r - t[p].l + 1)));
  t[p].mlz = mo(t[p].mlz * k);
  t[p].lz = mo(mo(t[p].lz * k) + x);
}

void push_down(ll p) {
  if (t[p].lz == 0 && t[p].mlz == 1) return;
  update(ls, t[p].mlz, t[p].lz);
  update(rs, t[p].mlz, t[p].lz);
  t[p].lz = 0, t[p].mlz = 1;
}
void build(ll p, ll l, ll r) {
  t[p] = {l, r, 0, 0, 1};
  if (l == r) {
    t[p].s = 1;
    return;
  }
  ll mid = l + r >> 1;
  build(ls, l, mid);
  build(rs, mid + 1, r);
  push_up(p);
}

void modify(ll p, ll l, ll r, ll k, ll x) {
  if (l > r) return;
  if (l <= t[p].l and r >= t[p].r) {
    update(p, k, x);
    return;
  }
  push_down(p);
  if (l <= t[ls].r) modify(ls, l, r, k, x);
  if (r >= t[rs].l) modify(rs, l, r, k, x);
  push_up(p);
}
ll query(ll p, ll l, ll r) {
  if (l > r) return 0;
  if (l <= t[p].l and r >= t[p].r) return t[p].s;

  push_down(p);
  ll res = 0;
  if (l <= t[ls].r) res = mo(res + query(ls, l, r));
  if (r >= t[rs].l) res = mo(res + query(rs, l, r));
  return res;
}

void solve() {
  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= q; ++i) cin >> a[i].l >> a[i].r >> a[i].c;
  sort(a + 1, a + 1 + q);
  build(1, 1, n - 1);
  ll ans = 0;
  for (int i = 1; i <= q; ++i) {
    auto [l, r, c] = a[i];
    ans += c * (1 + query(1, l, r - 1));
    modify(1, l, r - 1, 0, 0);
  }
  if (query(1, 1, n - 1)) ans = -1;
  cout << ans;
}
```

## 2.ABC 361 [F - x = a^b](https://atcoder.jp/contests/abc361/tasks/abc361_f)(容斥原理/细节/dp)(1600-1700/0)

### Problem Statement

How many integers $x$ between $1$ and $N$, inclusive, can be expressed as $x = a^b$ using some positive integer $a$ and a positive integer $b$ **not less than $2$**?

### Constraints

-   All input values are integers.
-   $1 \le N \le 10^{18}$

### 方法一

答案为
$$
\sum_{i=1}^{n} [i可以被表示为a^b]
$$


注意到，一个数如果可以表示为$a^{kb}$那么它一定也可以被表示为$a^b$，那么我们可以先只考虑$b$为质数。我们先排除1，注意到$2^{60}>10^{18}$，那么我们可以只考虑$60$以内的质数，只有17个。设其为$p_i$，我们令$A_i$表示可以表示为$a^{p_i}$的个数。那么答案显然为
$$
|A_1\cup A_2\cup \cdots\cup A_n|
$$
利用容斥原理显然可以解决。

但是由于精度问题，我们不能直接`pow(n,1.0/x)`解$\sqrt[x]{n}$，或者解出来后在向左右分别枚举一下，python是可以解决的。但是c++不行。

但是因为这几个质数乘积要小于$60$。实际需要解的数量是很少的，且$x>2$从1枚举也只需要$1e6$，因此可以直接枚举。而$x=2$时，也不能用`sqrt()`,得用`sqrtl()`。

```cpp
int pri[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};

int nr(ll n, ll r) {
  if (r == 2) return sqrtl(n);
  for (int i = 2;; ++i) {
    if (pow(i, r) > n) {
      return i - 1;
    }
  }
}
void solve() {
  ll n;
  cin >> n;
  int up = 0;
  for (; up < 17; ++up) {
    if (1ll << pri[up] > n) break;
  }
  ll ans = 0;
  for (int i = 1; i < (1ll << up); ++i) {
    int cnt = 0, r = 1;
    for (int j = 0; j < 17; ++j) {
      if (i >> j & 1) cnt++, r *= pri[j];
      if (r >= 60) break;
    }
    if (r < 60) {
      ans += (cnt % 2 == 0 ? -1 : 1) * (nr(n, r) - 1);
    }
  }
  cout << ans + 1;
}
```

### 方法二

不妨设$f(x)$为$2\sim n$仅可表示为$a^x$的个数，$g(x)$为可以表示为$a^x$的个数。

那么显然有
$$
f(x)=g(x)-f(2x)-f(3x)\cdots
$$
从后向前递推即可。

到这里发现，前面的代码能过是**运气好**。因为`pow`还是会错。参考答案可以自己写个`pow`函数。

```cpp
ll safe_pow(ll a, ll b) {
  ll res = 1;
  for (ll i = 0; i < b; i++) {
    double dres = res;
    dres *= a;
    if (dres > 2e18) {
      return 2e18;
    }
    res *= a;
  }
  return res;
}

int nr(ll n, ll r) {
  if (r == 2) return sqrtl(n);
  for (int i = 2;; ++i) {
    if (safe_pow(i, r) > n) {
      return i - 1;
    }
  }
}
int f[100], g[100];
void solve() {
  ll n;
  cin >> n;
  ll ans = 1;
  for (int i = 2; i <= 60; ++i) g[i] = nr(n, i) - 1;
  for (int x = 60; x >= 2; --x) {
    f[x] = g[x];
    for (int k = 2; k * x <= 60; ++k) f[x] -= f[k * x];
    ans += f[x];
  }
  cout << ans;
}

```

我们也可以用二分来替换开根运算，保证精度。~~但是懒得写~~

## 3.ABC362 [F - Perfect Matching on a Tree](https://atcoder.jp/contests/abc362/tasks/abc362_f)(树的重心/思维)(1900-2000/0)

### Problem Statement

You are given a tree $T$ with $N$ vertices. The vertices are numbered $1$ to $N$, and the $i$\-th edge $(1 \leq i \leq N-1)$ connects vertices $u_i$ and $v_i$ bidirectionally.

Using $T$, define a complete graph $G$ with $N$ vertices as follows:

-   The weight $w(x,y)$ of the edge between vertices $x$ and $y$ in $G$ is the shortest distance between vertices $x$ and $y$ in $T$.

Find one **maximum weight maximum matching** in $G$. That is, find a set of $\lfloor N/2 \rfloor$ pairs of vertices $M=\{(x_1,y_1),(x_2,y_2),\dots,(x_{\lfloor N/2 \rfloor},y_{\lfloor N/2 \rfloor})\}$ such that each vertex $1,2,\dots, N$ appears in $M$ at most once, and $\displaystyle \sum_{i=1}^{\lfloor N/2 \rfloor} w(x_i,y_i)$ is maximized.

### Constraints

-   $2 \leq N \leq 2 \times 10^5$
-   $1 \leq u_i  < v_i \leq N$
-   The input graph is a tree.
-   All input values are integers.

### 思路

考虑计算一条边可能被计算的次数。易证，边$(x,y)$最多被计算$\min(size_x,size_y)$次。考虑每一条边都能达到上界。

下面构造一种方案能够达到上界。

引入树的重心的概念：

树的重心是以其为根节点时的**最大子树大小**最小。下面给出一些性质。

1. 等价于最大子树大小不超过$\frac{n}{2}$。
2. 树最多2个重心，且此时树有偶数个节点，且重心两两相邻。
3. 树中所有点到某个点的**距离和**中，到重心的距离和是最小的；如果有两个重心，那么到它们的距离和一样。反过来，距离和最小的点一定是重心。
4. 往树上增加或减少一个**叶子**，如果原节点数是奇数，那么重心可能**增加**一个，原重心**仍是重心**；如果原节点数是偶数，重心可能**减少**一个，另一个重心**仍是重心**。
5. 两棵树通过连一条边组合成新树，则新树重心在原来两棵树的重心的连线上。

我们以树的重心为根，其有若干子树。且我们每条路径的两个点分别在两个子树上。

那么假设边$(x,y)$且$y$是$x$的父亲。则有$x$的子树所有节点所匹配的点形成的路径一定会经过$(x,y)$。

下面考虑如何构造这样的方案。

首先，若节点数为偶数，那么最后会子树会剩下一个节点，容易发现将其与根节点匹配即可。然后我们考虑如何找到不同子树的点。注意到每个子树大小小于等于$\frac{n}{2}$ ，且每颗子树的dfs序连续，那么我们可以找dfs序为$(i,i+\frac{n}{2})$的两个点。

#### 代码

```cpp
vector<int> g[N];
int si[N], cen, n;
void dfs(int x, int pre) {
  si[x] = 1;
  int mx = 0;
  for (const auto& y : g[x]) {
    if (y == pre) continue;
    dfs(y, x);
    si[x] += si[y];
    mx = max(mx, si[y]);
  }
  mx = max(mx, n - si[x]);
  if (mx <= n / 2) cen = x;
}

int dfn[N], idx, hs[N];
void dfs1(int x, int pre) {
  dfn[x] = ++idx;
  hs[idx] = x;
  for (const auto& y : g[x]) {
    if (y == pre) continue;
    dfs1(y, x);
  }
}

void solve() {
  int x, y;
  cin >> n;
  for (int i = 1; i < n; ++i) {
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  dfs(1, 1);
  dfs1(cen, cen);
  if (n & 1) {
    for (int i = 2; i <= n / 2 + 1; ++i) cout << hs[i] << " " << hs[i + n / 2] << "\n";
  } else {
    for (int i = 1; i <= n / 2; ++i) cout << hs[i] << " " << hs[i + n / 2] << "\n";
  }
}
```



## [2024 SHCPC](https://codeforces.com/gym/105229/attachments) 

### 4. A.无线网络整点栅格统计(枚举,(1600-1700/0))

已知正方形两点坐标$(x_1,y_1),(x_2,y_2)$

令`dx=x2-x1,dy=y2-y1`，可以得到`x3=x1+dy,y3=y1-dx,x4=x3+dx,y4=y3+dy`

### 5. M.不共戴天(思维,构造(1700-1800/0)

注意到可以将其列成表格，

| 1    | 2    | 3    |
| ---- | ---- | ---- |
| 4    | 5    | 6    |
| 7    | 8    | 9    |
| 10   | 11   | 12   |

那么所有横着连的不可能和竖着连的相同.且无法多连.枚举一排个数即可.

## 6. [**D. 1-2-K Game**](https://codeforces.com/contest/1194/problem/D)(博弈论)(1600-1700/0)

我们可以列出每个位置的胜负情况.可发现会产生一个$T=k+1$的循环.证明略.

## 7.  [**F - Teleporting Takahashi 2**](https://atcoder.jp/contests/abc372/tasks/abc372_f) (DP)(1800-1900/0)

如果么没有多余的边,那么每次转移固定.且编号是可计算的.那么每次只需要,计算最多50次即可.

### code

```cpp
void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 1; i <= m; ++i) {
    int x, y;
    cin >> x >> y;
    g.push_back({x, y});
  }
  auto id = [&](int i, int x) { return ((i - x) % n + n) % n == 0 ? n : ((i - x) % n + n) % n; };
  f[1] = 1, ff[1] = 1;
  for (int i = 1; i <= k; ++i) {
    vector<int> v;
    for (const auto& [x, y] : g) {
      int p = id(y - 1 == 0 ? n : y - 1, i - 1);
      f[p] += ff[id(x, i - 1)];
      f[p] %= mod;
      v.push_back(p);
    }
    for (const auto x : v) ff[x] = f[x];
  }
  ll ans = 0;
  for (int i = 1; i <= n; ++i) ans = (ans + f[i]) % mod;
  cout << ans << "\n";
}
```

## 8.[**G - Add and Multiply Queries**](https://atcoder.jp/contests/abc368/tasks/abc368_g)(树状数组)(1800-1900/0)	

注意到其不超过1e18，那么乘法最多不超过60次，因此大量$b$数组是1，所以我们可以用`set`记录b数组非1的位置，并用树状数组维护区间和。

```cpp
void solve() {
  cin >> n;
  vector<int> a(n + 1), b(n + 1);
  for (int i = 1; i <= n; ++i) cin >> a[i], add(i, a[i]);
  set<int> st;
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
    if (b[i] > 1) st.insert(i);
  }
  st.insert(n + 1);
  int q;
  cin >> q;
  while (q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int i, x;
      cin >> i >> x;
      add(i, x - a[i]);
      a[i] = x;
    } else if (op == 2) {
      int i, x;
      cin >> i >> x;
      if (x == 1) {
        if (st.count(i)) st.erase(i);
        b[i] = 1;
      } else {
        b[i] = x;
        st.insert(i);
      }
    } else {
      int l, r;
      cin >> l >> r;
      ll ans = a[l++];
      // cout << ans << endl;
      for (int i = l; i <= r;) {
        int up = min(r, *st.lower_bound(i));
        //  cout << up << endl;
        ans += prefix(up - 1) - prefix(i - 1);
        ans = max(ans + a[up], ans * b[up]);
        // cout << "ans: " << ans << "\n";
        i = up + 1;
      }
      cout << ans << "\n";
    }
  }
}
```

## 9.**[C - Row and Column Order](https://atcoder.jp/contests/arc181/tasks/arc181_c)**(构造)(1600-1700/0)

### 法一

一种简单的做法是，将$S_j:=S_i$ 然后在加一个1。这样就能保证满足行，对于列，若我们按Q从后往前加，就能保证，前面的包含在后面的，且后面的1更多，因此也满足。

```cpp
void solve() {
  int n;
  cin >> n;
  vector<int> p(n + 1), q(n + 1);
  for (int i = 1; i <= n; ++i) cin >> p[i];
  for (int i = 1; i <= n; ++i) cin >> q[i];
  vector<vector<int>> ans(n + 1, vector<int>(n + 1));
  for (int i = 1, j = n; i <= n; ++i, --j) {
    ans[p[i]] = ans[p[i - 1]];
    ans[p[i]][q[j]] = 1;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cout << ans[i][j];
    }
    cout << '\n';
  }
}
```

### 法二

我们递归的做，先将$P_1$全填0，$Q_n$全填1，然后删除这一行和列。

这样做，对于行，后填的填的1更多，且前面的含于后面。

对于列，同理。

```cpp
void solve() {
  int n;
  cin >> n;
  vector<int> p(n + 1), q(n + 1);
  for (int i = 1; i <= n; ++i) cin >> p[i];
  for (int i = 1; i <= n; ++i) cin >> q[i];
  vector<vector<int>> ans(n + 1, vector<int>(n + 1));
  vector<bool> c(n + 1);
  auto dfs = [&](auto& self, int x) -> void {
    if (x > n) return;
    c[p[x]] = 1;
    for (int i = 1; i <= n; ++i) {
      if (c[i]) continue;
      ans[i][q[n + 1 - x]] = 1;
    }
    self(self, x + 1);
  };
  dfs(dfs, 1);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cout << ans[i][j];
    }
    cout << "\n";
  }
}
```

## 10.[D. Connect the Dots](https://codeforces.com/contest/2020/problem/D)(并查集+dp)(1600-1700/0)

并查集+dp

注意到d很小，因此可以枚举d，考虑将d当做一个常数。

对于固定的d，如果我们知道每一个点所能连接的最远的点。就可以轻松解决。

我们设`f[i][j]`为$d=j$时，i的最远点。有状态转移方程
$$
f_{i,j}=\max(f_{i,j},(f_{i,j}\geq i+j)f_{i+1,j})
$$

$$
f_{i+j,j}=\max(f_{i+j,j},f_{i,j})
$$

```CPP
void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) pre[i] = i;
  for (int i = 1; i <= 10; ++i) {
    for (int j = 1; j <= n; ++j) {
      f[j][i] = j;
    }
  }
  for (int i = 1; i <= m; ++i) {
    int a, d, k;
    cin >> a >> d >> k;
    f[a][d] = max(f[a][d], a + k * d);
  }
  //  d: 1~10
  for (int i = 1; i <= 10; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      if (f[j - i][i] >= j) {
        f[j - i][i] = max(f[j - i][i], f[j][i]);
        f[j][i] = f[j - i][i];
      }
    }
  }
  for (int i = 1; i <= 10; ++i) {
    for (int j = n; j >= 1; --j) {
      merge(j, f[j][i]);
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (root(i) == i) ans++;
  }
  cout << ans << "\n";
}

```

## 11.[**B - Improve Inversions**](https://atcoder.jp/contests/arc180/tasks/arc180_b)(贪心)(1800-1900/0)

对于$i$来说，我们在后面找比他小的然后从大到小交换是最好的。

那么我们从小到大枚举$i$，然后从大到小交换，因为前面交换的都比$i$小，那么不会影响$i$的交换次数。

因此可以达到
$$
\sum_{i=1}^{n}\sum_{j=i+k}^{n}[a_j<a_i]
$$
并且可以证明这是最大的。因为假设我们交换一次，$x,y(x<y)$ ，那么，对于$l\leq x-k$和$l>y-k$不会有影响。但对于$x-k<l\leq y-k$若$l=x$，则一定减少一次，否则，至少可以保证不会变多。

因此这就是最大值。

## 12.**F - Tree Degree Optimization**(贪心 prufer 序列)(1800-1900/0)

https://oi-wiki.org/graph/prufer/

## 13.[**G - AtCoder Tour**](https://atcoder.jp/contests/abc358/tasks/abc358_g)(DP/最短路)(1600-1700/0)

容易想到它一定会走到一个终点并一直停在那里。

### 法一

可以枚举终点`(i,j)`。只连接权值小于终点的点。定义权值为`a[i][j]-a[x][y]`。

```cpp
ll a[100][100];
ll n, m, k, d[3000];
vector<pll> g[3000];

int to_i(int x, int y) { return (x - 1) * m + y; }

bool check(int x, int y) { return x > 0 && x <= n && y > 0 && y <= m; }

bitset<3000> vis;

void dij(int x) {
  vis = 0;
  for (int i = 1; i <= 2500; ++i) d[i] = linf;
  d[x] = 0;
  priority_queue<pll, vector<pll>, greater<pll>> q;
  q.push({0, x});
  while (q.size()) {
    auto [_, id] = q.top();
    q.pop();
    if (vis[id]) continue;
    vis[id] = 1;
    for (const auto& [y, z] : g[id]) {
      if (d[y] > d[id] + z) {
        d[y] = d[id] + z;
        q.push({d[y], y});
      }
    }
  }
}

void solve() {
  cin >> n >> m >> k;
  int si, sj;
  cin >> si >> sj;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> a[i][j];
    }
  }
  ll ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (a[i][j] < a[si][sj]) continue;
      for (int ii = 1; ii <= n; ++ii) {
        for (int jj = 1; jj <= m; ++jj) {
          g[to_i(ii, jj)].clear();
        }
      }
      for (int ii = 1; ii <= n; ++ii) {
        for (int jj = 1; jj <= m; ++jj) {
          if (check(ii + 1, jj)) {
            if (a[ii + 1][jj] <= a[i][j]) g[to_i(ii, jj)].push_back({to_i(ii + 1, jj), a[i][j] - a[ii + 1][jj]});
            if (a[ii][jj] <= a[i][j]) g[to_i(ii + 1, jj)].push_back({to_i(ii, jj), a[i][j] - a[ii][jj]});
          }
          if (check(ii, jj + 1)) {
            if (a[ii][jj + 1] <= a[i][j]) g[to_i(ii, jj)].push_back({to_i(ii, jj + 1), a[i][j] - a[ii][jj + 1]});
            if (a[ii][jj] <= a[i][j]) g[to_i(ii, jj + 1)].push_back({to_i(ii, jj), a[i][j] - a[ii][jj]});
          }
        }
      }
      dij(to_i(si, sj));
      // cout << "end:" << i << " " << j << endl;
      // cout << "dis:" << d[to_i(i, j)] << endl;
      ans = max(ans, k * a[i][j] - d[to_i(i, j)]);
    }
  }
  cout << ans;
}
```

### 法二

枚举走到终点的步数。利用dp找到指定步数下最大权值。可利用滚动数组优化。

```cpp
void solve() {
  cin >> n >> m >> k;
  int si, sj;
  cin >> si >> sj;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      f[0][i][j] = f[1][i][j] = -linf;
    }
  }
  f[0][si][sj] = 0;
  ll ans = k * a[si][sj];
  for (int x = 1; x <= min(k, 1ll * n * m); ++x) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        for (int t = 0; t < 4; ++t) {
          int cx = i + dx[t], cy = j + dy[t];
          if (check(cx, cy)) f[x & 1][i][j] = max(f[(x - 1) & 1][cx][cy] + a[i][j], f[x & 1][i][j]);
        }
      }
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        ans = max(ans, f[x & 1][i][j] + (k - x) * a[i][j]);
      }
    }
  }
  cout << ans;
}
```

## 14.[Help is needed for Dexter](https://www.luogu.com.cn/problem/UVA11384)（数学）(1400-1500/0)

显然重复的元素越多越好。

注意到一种较优的做法是
$$
f_n=f_{\left\lfloor\frac{n}{2} \right\rfloor}+1
$$
先在来证明这是最优的。显然有$f_n$是不减少的。

有$f_n=\left\lfloor\log_2{n}\right\rfloor+1$

若这不是最优的，则存在最小的$m$使得
$$
f_m\leq \left\lfloor\log_2{m}\right\rfloor
$$
 那么
$$
f_{m-1}=\left\lfloor\log_2{(m-1)}\right\rfloor+1
$$
而$f_m\geq f_{m-1}$，故
$$
m=2^k
$$
因此我们可以进行$k$次操作让，$2^k$个元素变成0，不妨设第$i$次操作减去$a_i$。

设$S$为$\{1,2,\cdots,k\}$的非空子集。那么就有对于$1\leq x \leq 2^k$ 存在一个$S$ 使得$\sum_{i\in S} a_i=x$，但是只有$2^k-1$个非空子集。不可能形成$2^k$个元素。

故上式就是最优解。

## 15[.Colored Cubes](https://www.luogu.com.cn/problem/UVA1352)（枚举/代码）

数据很小，考虑直接枚举。难点在于写代码。

可以先打表出一个正方体的所有情况，枚举每一个正方体的情况，第一个可以按照默认位置。然后记录每一面的各个颜色出现次数，保留最多的即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define REP(i, n) for (int i = 1; i <= (n); ++i)
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int mod = 998244353;
// using i128=__int128_t;
const int N = 1e6 + 9;
const int iinf = 1e9;
const ll linf = 1e18;

int pose[25][7] = {
    {0, 0, 0, 0, 0, 0, 0}, {0, 3, 2, 6, 1, 5, 4}, {0, 3, 1, 2, 5, 6, 4}, {0, 3, 5, 1, 6, 2, 4}, {0, 3, 6, 5, 2, 1, 4}, {0, 5, 3, 6, 1, 4, 2}, {0, 6, 3, 2, 5, 4, 1},
    {0, 2, 3, 1, 6, 4, 5}, {0, 1, 3, 5, 2, 4, 6}, {0, 1, 2, 3, 4, 5, 6}, {0, 5, 1, 3, 4, 6, 2}, {0, 6, 5, 3, 4, 2, 1}, {0, 2, 6, 3, 4, 1, 5}, {0, 6, 2, 4, 3, 5, 1},
    {0, 2, 1, 4, 3, 6, 5}, {0, 1, 5, 4, 3, 2, 6}, {0, 5, 6, 4, 3, 1, 2}, {0, 2, 4, 6, 1, 3, 5}, {0, 1, 4, 2, 5, 3, 6}, {0, 5, 4, 1, 6, 3, 2}, {0, 6, 4, 5, 2, 3, 1},
    {0, 4, 5, 6, 1, 2, 3}, {0, 4, 6, 2, 5, 1, 3}, {0, 4, 2, 1, 6, 5, 3}, {0, 4, 1, 5, 2, 6, 3},
};

void solve() {
  int n;
  while (cin >> n && n) {
    vector<array<string, 10>> col(n + 1);
    REP(i, n) REP(j, 6) cin >> col[i][j];
    int ans = iinf;
    int p[n + 1];
    auto count = [&]() -> int {
      map<string, int> cnt[7];
      REP(i, 6) cnt[i][col[1][i]]++;
      for (int i = 2; i <= n; ++i) {
        REP(j, 6) cnt[j][col[i][pose[p[i]][j]]]++;
      }
      int res = 0;
      REP(i, 6) {
        int mx = 0;
        for (auto it = cnt[i].begin(); it != cnt[i].end(); ++it) mx = max(mx, it->second);
        res += n - mx;
      }
      return res;
    };
    function<void(int)> dfs = [&](int id) -> void {
      if (id > n) return ans = min(ans, count()), void();
      REP(i, 24) {
        p[id] = i;
        dfs(id + 1);
      }
    };
    dfs(2);
    cout << ans << "\n";
  }
}

inline void STDIO() {
  ios::sync_with_stdio(false), cout.tie(0), cin.tie(0);
  return;
}
int main() {
  STDIO();
  int _ = 1;
  // cin>>_;
  while (_--) solve();
  return 0;
}
```

## 16.[Even Parity](https://www.luogu.com.cn/problem/UVA11464)（枚举/代码）



第一行一旦确定，所有的都确定了。枚举第一行的所有情形。检查是否满足条件即可。

难点还是写代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define REP(i, n) for (int i = 1; i <= (n); ++i)
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int mod = 998244353;
// using i128=__int128_t;
const int N = 1e6 + 9;
const int iinf = 1e9;
const ll linf = 1e18;
int dx[] = {0, 0, -1};
int dy[] = {1, -1, 0};

void solve() {
  int n;
  cin >> n;
  auto check = [&](int x, int y) { return x > 0 && x <= n && y > 0 && y <= n; };
  vector<vector<int>> a(n + 1, vector<int>(n + 1));
  vector<vector<int>> c(n + 1, vector<int>(n + 1));
  REP(i, n) REP(j, n) cin >> a[i][j];
  int ans = -1, mi = iinf;
  for (int i = 0; i < 1ll << n; ++i) {
    if (i == 2) {
      int x = 1;
    }
    vector<int> b(n + 1);
    for (int j = 0; j < n; ++j) b[j + 1] = i >> j & 1;
    bool ok = true;
    int cnt = 0;
    for (int j = 1; j <= n && ok; ++j) {
      for (int k = 1; k <= n && ok; ++k) {
        if (b[k] == 0 && a[j][k] == 1) ok = false;
        if (b[k] == 1 && a[j][k] == 0) cnt++, c[j][k] = b[k];
      }
      for (int k = 1; k <= n; ++k) {
        int C = 0;
        for (int l = 0; l < 3; ++l) {
          int cx = j + dx[l], cy = k + dy[l];
          if (check(cx, cy) && c[cx][cy]) C++;
        }
        if (C & 1) {
          b[k] = 1;
        } else {
          b[k] = 0;
        }
      }
    }
    if (ok) mi = min(mi, cnt);
    c = a;
  }
  if (mi < iinf) ans = mi;
  cout << ans << "\n";
}

inline void STDIO() {
  ios::sync_with_stdio(false), cout.tie(0), cin.tie(0);
  return;
}
int main() {
  STDIO();
  int _ = 1;
  cin >> _;
  REP(i, _) cout << "Case " << i << ": ", solve();
  return 0;
}
```

## 17.Image Is Everything(枚举/代码)

https://www.luogu.com.cn/problem/UVA1030

我们将一定没有的位置标记出来，即可算出答案。有以下两种情况。

1. 视图有`.`。
2. 几个视图相互矛盾。

难点依旧是写代码。具体实现看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define REP(i, n) for (int i = 1; i <= (n); ++i)
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int mod = 998244353;
// using i128=__int128_t;
const int N = 1e6 + 9;
const int iinf = 1e9;
const ll linf = 1e18;

char s[10][15][15], h[15][15][15];

int n;
void T(int i, int j, int k, int l, int& x, int& y, int& z) {
  if (i == 1) return x = l, y = k, z = j, void();
  if (i == 2) return x = n + 1 - k, y = l, z = j, void();
  if (i == 3) return x = n + 1 - l, y = n + 1 - k, z = j, void();
  if (i == 4) return x = k, y = n + 1 - l, z = j, void();
  if (i == 5) return x = n + 1 - j, y = k, z = l, void();
  if (i == 6) return x = j, y = k, z = n + 1 - l, void();
}

void solve() {
  while (cin >> n && n) {
    REP(i, n) REP(j, 6) REP(k, n) cin >> s[j][i][k];
    REP(i, n) REP(j, n) REP(k, n) h[i][j][k] = '?';
    REP(i, 6) REP(j, n) REP(k, n) if (s[i][j][k] == '.') {
      REP(l, n) {
        int x, y, z;
        T(i, j, k, l, x, y, z);
        h[x][y][z] = '.';
      }
    }
    while (true) {
      bool ok = true;
      REP(i, 6) REP(j, n) REP(k, n) if (s[i][j][k] != '.') {
        REP(l, n) {
          int x, y, z;
          T(i, j, k, l, x, y, z);
          if (h[x][y][z] == '.') continue;
          if (h[x][y][z] == '?') {
            h[x][y][z] = s[i][j][k];
            break;
          }
          if (h[x][y][z] == s[i][j][k]) break;
          h[x][y][z] = '.';
          ok = false;
        }
      }
      if (ok) break;
    }
    int ans = 0;
    REP(i, n) REP(j, n) REP(k, n) ans += (h[i][j][k] != '.');
    cout << "Maximum weight: " << ans << " gram(s)\n";
  }
}
inline void STDIO() {
  ios::sync_with_stdio(false), cout.tie(0), cin.tie(0);
  return;
}
int main() {
  STDIO();
  int _ = 1;
  // cin>>_;
  while (_--) solve();
  return 0;
}
```

## 18.[A Different Task](https://www.luogu.com.cn/problem/UVA10795)(数学)(1800-1900/0)

我们从大到小移动是最优的。下面给出证明。

我们考虑移动$x$的前一步，若需要移动，那么我们需要将$1,2,\cdots,x-1$全部移动到另外一个柱子上。不管是否先移动小的，此时完全一致。故从大到小移动一定不劣。

考虑最大的，如果在正确的柱子上，就不需要移动，并且可以直接删除。

另外注意到操作完全可逆。假设我们需要将$k$，从1移动到2，那么我们先将$1,2,\cdots,k-1$移动到3。将初始到这个状态需要的操作数，和最终状态到这个状态的操作数分别计算出来。相加即是答案。

具体地。我们有函数`f(st,k,g)`，为从状态$st$，将$1,2,\cdots,k$移动到$g$需要的最少操作数。

那么答案为`f(s,k-1,6-s[k]-e[k])+f(e,k-1,6-s[k]-e[k])+1`。

下面考虑计算f

若$k$就在$g$，那么`f(st,k,g)=f(st,k-1,g)`，注意处理$k=0$。

否则`f(st,k,g)=f(st,k-1,6-g-st[k])+2^{k-1}`

代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define REP(i, n) for (int i = 1; i <= (n); ++i)
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int mod = 998244353;
// using i128=__int128_t;
const int N = 1e6 + 9;
const int iinf = 1e9;
const ll linf = 1e18;

ll f(vector<int>& st, int k, int g) {
  if (k == 0) return 0;
  if (st[k] == g) return f(st, k - 1, g);
  return f(st, k - 1, 6 - g - st[k]) + (1ll << k - 1);
}

void solve() {
  int n, _ = 0;
  while (cin >> n && n) {
    cout << "Case " << (++_) << ": ";
    vector<int> s(n + 1), e(n + 1);
    for (int i = 1; i <= n; ++i) cin >> s[i];
    for (int i = 1; i <= n; ++i) cin >> e[i];
    ll ans = 0;
    for (int i = n; i >= 1; --i) {
      if (s[i] != e[i]) {
        ans = f(s, i - 1, 6 - s[i] - e[i]) + f(e, i - 1, 6 - s[i] - e[i]) + 1;
        break;
      }
    }
    cout << ans << '\n';
  }
}

inline void STDIO() {
  ios::sync_with_stdio(false), cout.tie(0), cin.tie(0);
  return;
}
int main() {
  STDIO();
  int _ = 1;
  // cin>>_;
  while (_--) solve();
  return 0;
```

## 19.[Network](https://www.luogu.com.cn/problem/UVA315)(DFS,贪心)

以s为根。

有贪心策略，从最深节点开始遍历。走$k$个父亲，然后从他开始dfs，标记离他小于k的。下面说明其正确性。

首先$k$子树下全部标记了。同时，更靠近上面的节点。故一定不会更差。

代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define REP(i, n) for (int i = 1; i <= (n); ++i)
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int mod = 998244353;
// using i128=__int128_t;
const int N = 1010;
const int iinf = 1e9;
const ll linf = 1e18;
vector<int> d[N], g[N];
bitset<N> vis;
int fa[N], n, s, k;
void dfs(int x, int pre, int dep) {
  fa[x] = pre;
  for (const auto y : g[x]) {
    if (y == pre) continue;
    dfs(y, x, dep + 1);
  }
  if (x != pre && g[x].size() == 1) d[dep].push_back(x);
}

void dfs2(int x, int pre, int dep) {
  if (dep > k) return;
  vis[x] = 1;
  for (const auto y : g[x]) {
    if (y == pre) continue;
    dfs2(y, x, dep + 1);
  }
}

void solve() {
  cin >> n >> s >> k;
  vis = 0;
  for (int i = 1; i <= n; ++i) g[i].clear();
  for (int i = 1; i <= n; ++i) d[i].clear();
  for (int i = 1; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  dfs(s, s, 0);
  int ans = 0;
  for (int i = n; i > k; --i) {
    for (const auto x : d[i]) {
      if (vis[x]) continue;
      int y = x;
      ans++;
      for (int i = 1; i <= k; ++i) y = fa[y];
      dfs2(y, y, 0);
    }
  }
  cout << ans << '\n';
}

inline void STDIO() {
  ios::sync_with_stdio(false), cout.tie(0), cin.tie(0);
  return;
}
int main() {
  STDIO();
  int _ = 1;
  cin >> _;
  while (_--) solve();
  return 0;
}
```



## 20.[Pie](https://www.luogu.com.cn/problem/UVA12097)(实数二分)

可用`const double Pi = acos(-1.0);`得到$\pi$的值。

代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define REP(i, n) for (int i = 1; i <= (n); ++i)
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int mod = 998244353;
// using i128=__int128_t;
const int N = 1e6 + 9;
const int iinf = 1e9;
const ll linf = 1e18;
const double Pi = acos(-1.0);

void solve() {
  int n, f;
  cin >> n >> f;
  f++;
  vector<int> r(n + 1);
  REP(i, n) cin >> r[i];
  auto check = [&](double x) {
    ll cnt = 0;
    REP(i, n) {
      double S = Pi * r[i] * r[i];
      cnt += (ll)(S / x);
      if (cnt >= f) return true;
    }
    return false;
  };
  double L = 0, R = 1e17;
  while (R - L > 1e-6) {
    double mid = (R + L) / 2.0;
    if (check(mid)) {
      L = mid;
    } else {
      R = mid;
    }
  }
  cout << fixed << setprecision(6) << L << "\n";
}

inline void STDIO() {
  ios::sync_with_stdio(false), cout.tie(0), cin.tie(0);
  return;
}
int main() {
  STDIO();
  int _ = 1;
  cin >> _;
  while (_--) solve();
  return 0;
}
```

## 21.[Beijing Guards](https://www.luogu.com.cn/problem/UVA1335)(贪心+二分/数学)(2000-2100/0)

### 法一

假设有$x$个礼物，如何才能避免相邻重复呢。一种策略是一个从前往后拿，一个从后往前拿。

当偶数个人时，显然奇数从前往后，偶数从后往前拿即可。

我们假设第一个人从前往后拿。那么第二个人应该尽量从后往前拿。所以我从第二个人开始从前往后拿，交替进行。

偶数正确性显然。

奇数时有，最后一个应尽可能从后往前拿，即少拿前面的，那么这要求前一个尽量拿前面的，这样递推下去，即证。

注意特判`n==0`

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define REP(i, n) for (int i = 1; i <= (n); ++i)
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int mod = 998244353;
// using i128=__int128_t;
const int N = 1e6 + 9;
const int iinf = 1e9;
const ll linf = 1e18;

void solve() {
  int n;
  while (cin >> n && n) {
    // d->[1,r1]
    vector<int> r(n + 1), u(n + 1), d(n + 1);
    for (int i = 1; i <= n; ++i) cin >> r[i];
    d[1] = r[1];
    auto check = [&](int x) {
      if (x < r[1]) return false;
      int a = r[1], b = x - r[1];
      for (int i = 2; i <= n; ++i) u[i] = d[i] = 0;
      for (int i = 2; i <= n; ++i) {
        if (i & 1) {
          u[i] = min(b - u[i - 1], r[i]);
          d[i] = min(r[i] - u[i], a - d[i - 1]);
          if (u[i] + d[i] < r[i]) return false;
        } else {
          d[i] = min(r[i], a - d[i - 1]);
          u[i] = min(b - u[i - 1], r[i] - d[i]);
          if (u[i] + d[i] < r[i]) return false;
        }
      }
      return d[n] == 0;
    };
    if (n % 2 == 0) {
      int ans = r[1] + r[n];
      for (int i = 1; i < n; ++i) ans = max(ans, r[i] + r[i + 1]);
      cout << ans << "\n";
      continue;
    }
    if (n == 1) {
      cout << r[1] << "\n";
      continue;
    }
    int L = 0, R = 1e9;
    while (L + 1 != R) {
      int mid = L + R >> 1;
      if (check(mid)) {
        R = mid;
      } else {
        L = mid;
      }
    }
    cout << R << "\n";
  }
}

inline void STDIO() {
  ios::sync_with_stdio(false), cout.tie(0), cin.tie(0);
  return;
}
int main() {
  STDIO();
  int _ = 1;
  // cin >> _;
  while (_--) solve();
  return 0;
}
```

### 法二

基于第一种方法的策略。如果你注意力再强一点。可以注意到：

答案为
$$
A=\max\left(\max_{i=1}^{n-1}(r_i+r_{i+1}),r_1+r_n, \left\lceil \frac{\sum r_i }{\lfloor \frac{n}{2} \rfloor} \right \rceil \right )
$$
重点是
$$
A\ge\left\lceil \frac{\sum r_i }{\lfloor \frac{n}{2} \rfloor} \right \rceil\quad\quad\quad (*)
$$
假设已经满足前面的式子。

> 偶数显然，仅考虑奇数情形。

我们证明满足要求的充要条件是（*）式。

**必要性**：设有$x$种，每一种最多被$\lfloor \frac{n}{2} \rfloor$个人 共有，于是
$$
x\left\lfloor \frac{n}{2} \right \rfloor\ge \sum r_i
$$
**充分性** ：由于对称性，我们可以**假设$r_1$最大**。设$f_i$为第$i$个人的礼物与$r_1$的交集。有递推关系：

$f_1=r_1,f_2=0$
$$
f_{2k}=\min(r_{2k},r_1-f_{2k-1})
$$

$$
f_{2k+1}=\max(0,r_{2k}+r_{2k+1}+r_1-A-f_{2k})
$$

若$r_{2k}\le r_1-f_{2k-1}$：

那么有$f_{2k}=r_{2k}$，将$f_{2k+1}$带入$f_{2k+2}$有：
$$
\begin{aligned}
f_{2k+2}&=\min(r_{2k+2},\min(r_{1},A+f_{2k}-r_{2k}-r_{2k+1}))\\
&=\min(r_{2k+2},A-r_{2k+1})\\
&=r_{2k+2}
\end{aligned}
$$

> 这说明，若$f_{2k+2}\neq r_{2k+2}$，那么$f_{2k}\neq r_{2k}$。

否则：$f_{2k}=r_1-f_{2k-1}$，带入有
$$
\begin{aligned}
f_{2k+1}&=\max(0,r_{2k}+r_{2k+1}+f_{2k-1}-A)\\
&=\max(0,r_{2k+1}+r_{2k}+\max(0,r_{2k-1}+r_{2k-2}+f_{2k-3}-A) -A)\\
&=\max(0,r_{2k+1}+r_{2k}-A,r_{2k+1}+r_{2k}+r_{2k-1}+r_{2k-2}+f_{2k-3}-2A)\\
&=\max(0,r_{2k+1}+r_{2k}+r_{2k-1}+r_{2k-2}+f_{2k-3}-2A)
\end{aligned}
$$
一直递推下去，显然有
$$
f_{2k+1}=\max(0,\sum_{i=2}^{2k+1}+r_1-kA)
$$
不妨设$n=2t+1$，

若$f_{2t}=r_{2t}$，显然成立。

否则
$$
f_n=\max(0,\sum_{i=1}^{n}r_i-\left\lfloor \frac{n}{2} \right \rfloor A )=0
$$
证毕。

### 法三

如果你没有那么强的注意力，并且没想到贪心策略。

我们可以设$mx_i$$mi_i$分别为第$i$个人礼物与第一个的最大，最小交集。显然有递推公式
$$
mx_i=\min(r_i,r_{1}-mi_{i-1})
$$

$$
mi_i=\max(0,r_1+r_i+r_{i-1}-mx_{i-1}-A)
$$

我们需要$mi_n=0$，注意到满足单调性，二分即可。

**代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define REP(i, n) for (int i = 1; i <= (n); ++i)
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int mod = 998244353;
// using i128=__int128_t;
const int N = 1e6 + 9;
const int iinf = 1e9;
const ll linf = 1e18;

void solve() {
  int n;
  while (cin >> n && n) {
    int L = 0, R = 1e9;
    vector<int> r(n + 1), mi(n + 1), mx(n + 1);
    REP(i, n) cin >> r[i];
    mi[1] = mx[1] = r[1];
    if (n == 1) {
      cout << r[1] << "\n";
      continue;
    }
    REP(i, n) L = max(L, r[i] + r[i % n + 1]);
    auto check = [&](int x) {
      for (int i = 2; i <= n; ++i) {
        mx[i] = min(r[i], r[1] - mi[i - 1]);
        mi[i] = max(0, r[1] + r[i] + r[i - 1] - mx[i - 1] - x);
      }
      return mi[n] == 0;
    };
    while (L + 1 != R) {
      int mid = L + R >> 1;
      if (check(mid)) {
        R = mid;
      } else {
        L = mid;
      }
    }
    if (check(L)) R = L;
    cout << R << "\n";
  }
}

inline void STDIO() {
  ios::sync_with_stdio(false), cout.tie(0), cin.tie(0);
  return;
}
int main() {
  STDIO();
  int _ = 1;
  // cin >> _;
  while (_--) solve();
  return 0;
}
```

## 22 .[Calculator Conundrum](https://www.luogu.com.cn/problem/UVA11549)(floyd 判圈)

用`set`，直接暴力显然可做。但空间复杂度过高。

事实上，我们知道一定会循环，于是利用Floyd判圈法即可。

```cpp
void solve() {
  int n, k;
  cin >> n >> k;
  auto nex = [&](int x) -> int {
    ll res = 1ll * x * x;
    int b[20], h = 0, p;
    while (res) b[++h] = res % 10, res /= 10;
    p = min(h, n);
    for (int i = 1; i <= p; ++i) res = res * 10 + b[h--];
    return res;
  };
  int p1 = k, p2 = k, ans = k;
  do {
    p1 = nex(p1);
    p2 = nex(p2), ans = max(ans, p2);
    p2 = nex(p2), ans = max(ans, p2);
  } while (p1 != p2);
  cout << ans << "\n";
}
```

## 23.[Meteor](https://www.luogu.com.cn/problem/UVA1398)(扫描线)

计算每个点在框里的时间。然后就比较典了。可以直接离散化线段树做。

但用扫描线更简单。下面是扫描线代码。

```cpp
struct node {
  double x;
  int ty;
  bool operator<(const node u) const { return x == u.x ? ty < u.ty : x < u.x; }
};

void solve() {
  int h, w, n;
  cin >> w >> h >> n;
  auto cal = [&](int x, int v, int e, double& L, double& R) {
    if (v == 0) {
      if (x <= 0 || x >= e) R = L - 1;
    } else if (v > 0) {
      L = max(L, -(double)(x) / v);
      R = min(R, (double)(e - x) / v);
    } else {
      L = max(L, (double)(e - x) / v);
      R = min(R, -(double)(x) / v);
    }
  };
  vector<node> e;
  for (int i = 1; i <= n; ++i) {
    int x, y, a, b;
    cin >> x >> y >> a >> b;
    double L = 0, R = 1e9;
    cal(x, a, w, L, R);
    cal(y, b, h, L, R);
    if (L < R) {
      e.push_back({L, 1});
      e.push_back({R, -1});
    }
  }
  sort(e.begin(), e.end());
  int ans = 0, cur = 0;
  for (const auto& [x, y] : e) {
    // cout << x << " " << y << "\n";
    cur += y;
    ans = max(cur, ans);
  }
  cout << ans << "\n";
}
```

## 24.[City Game](https://ac.nowcoder.com/acm/problem/51000)（扫描线 dP）

我们将连续的空格看成一条线，维护三个信息，$(i,j)$向上的最大高度，以及这个 长度最多向左，右移动的位置。可以证明答案一定在这之中。

```cpp
int a[N][N], le[N][N], L[N][N], R[N][N];
void solve() {
  int n, m;
  cin >> n >> m;
  REP(i, n) REP(j, m) {
    char x;
    cin >> x;
    a[i][j] = (x == 'F');
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    int p = 0;
    for (int j = 1; j <= m; ++j) {
      if (a[i][j]) {
        le[i][j] = le[i - 1][j] + 1;
        L[i][j] = max(p + 1, L[i - 1][j]);
      } else {
        p = j;
      }
    }
    p = m + 1;
    for (int j = m; j >= 1; --j) {
      if (a[i][j]) {
        R[i][j] = min(p - 1, R[i - 1][j] == 0 ? m + 1 : R[i - 1][j]);
        ans = max(ans, le[i][j] * (R[i][j] - L[i][j] + 1));
      } else {
        p = j;
      }
    }
  }
  cout << ans * 3;
}
```

## 25.[C2. Adjust The Presentation (Hard Version)](https://codeforces.com/contest/2021/problem/C2)(DS,思维)(1800-1900/0)

维护每个数在b首次出现的位置，需要满足第一个为1，且递增排序。我们改变一个值，只会形象左右两边的数。用map存一下即可。

```cpp
void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  vector<int> a(n + 10), b(m + 10), pos(n + 10);
  for (int i = 1; i <= n; ++i) cin >> a[i], pos[a[i]] = i;
  for (int i = 1; i <= m; ++i) cin >> b[i];
  int cnt = 0;
  vector<set<int>> st(n + 1);
  map<int, int> f;
  for (int i = 1; i <= m; ++i) st[b[i]].insert(i);
  auto insert = [&](int i) {
    auto [it, y] = f.emplace(i, b[i]);
    if (!y) return;
    auto r = next(it);
    if (r != f.end()) cnt += (pos[b[i]] + 1 != pos[r->second]);
    if (it != f.begin()) {
      auto l = prev(it);
      cnt += (pos[b[i]] - 1 != pos[l->second]);
      if (r != f.end()) {
        cnt -= (pos[l->second] + 1 != pos[r->second]);
      }
    }
  };
  auto erase = [&](int i) {
    auto it = f.find(i);
    if (it == f.end()) return;
    auto r = next(it);
    if (r != f.end()) cnt -= (pos[b[i]] + 1 != pos[r->second]);
    if (it != f.begin()) {
      auto l = prev(it);
      cnt -= (pos[b[i]] - 1 != pos[l->second]);
      if (r != f.end()) {
        cnt += (pos[l->second] + 1 != pos[r->second]);
      }
    }
    f.erase(it);
  };
  for (int i = 1; i <= n; ++i) {
    if (st[i].size()) insert(*st[i].begin());
  }
  if (cnt || f.begin()->second != a[1]) {
    cout << "TIDAK\n";
  } else {
    cout << "YA\n";
  }
  for (int i = 1; i <= q; ++i) {
    int x, t;
    cin >> x >> t;
    if (b[x] != t) {
      st[b[x]].erase(x);
      erase(x);
      if (st[b[x]].size()) insert(*st[b[x]].begin());
      if (st[t].size()) erase(*st[t].begin());
      b[x] = t;
      st[t].insert(x);
      insert(*st[t].begin());
    }
    if (cnt || f.begin()->second != a[1]) {
      cout << "TIDAK\n";
    } else {
      cout << "YA\n";
    }
  }
}
```

## 26.[**3 Team Division**](https://atcoder.jp/contests/abc375/tasks/abc375_e)(DP)(1400-1500/0)

```cpp
int f[110][510][510];
void solve() {
  int n, ex = 0;
  cin >> n;
  vector<pii> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i].first >> a[i].second;
    ex += a[i].second;
  }
  if (ex % 3) {
    cout << "-1";
    return;
  }
  ex /= 3;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= ex; ++j) {
      for (int k = 0; k <= ex; ++k) {
        f[i][j][k] = iinf;
      }
    }
  }
  // f[i][j][k], 到i，1有j，2有k，的最小次数。
  f[0][0][0] = 0;
  int sum = 0;
  for (int i = 1; i <= n; ++i) {
    sum += a[i].second;
    for (int x = 0; x <= ex; ++x) {
      for (int y = 0; y <= ex; ++y) {
        int z = sum - x - y;
        if (z > ex || z < 0) continue;
        if (y >= a[i].second) f[i][x][y] = min(f[i][x][y], f[i - 1][x][y - a[i].second] + (a[i].first != 2));
        if (x >= a[i].second) f[i][x][y] = min(f[i][x][y], f[i - 1][x - a[i].second][y] + (a[i].first != 1));
        if (z >= a[i].second) f[i][x][y] = min(f[i][x][y], f[i - 1][x][y] + (a[i].first != 3));
      }
    }
  }
  cout << (f[n][ex][ex] > n ? -1 : f[n][ex][ex]);
}
```

## 27.[C. Alya and Permutation](https://codeforces.com/contest/2035/problem/C)(贪心/构造)(1200-1300/0)

```cpp
int lb(int n) { return n & (-n); }

void solve() {
  int n;
  cin >> n;
  if (n & 1) {
    //.....1&3|n-1&n
    cout << n << "\n";
    for (int i = 1; i <= n; ++i) {
      if (i == 1 || i == 3 || i == n - 1 || i == n) continue;
      cout << i << " ";
    }
    cout << 1 << " " << 3 << " " << n - 1 << " " << n << "\n";
  } else {
    int h = n, cnt = 1;
    while (h > 1) {
      h >>= 1;
      cnt <<= 1;
    }
    h *= cnt;
    cout << 2 * h - 1 << '\n';
    if (n == h) {
      // 3&1|n-2&n-1|n
      for (int i = 1; i <= n; ++i) {
        if (i == 1 || i == 3 || i == n - 2 || i == n - 1 || i == n) continue;
        cout << i << " ";
      }
      cout << 1 << " " << 3 << " " << n - 2 << " " << n - 1 << " " << n << "\n";
    } else {
      // 6
      // |n-1&1|h-2&h-1|h
      for (int i = 1; i <= n; ++i) {
        if (i == n - 1 || i == 1 || i == h - 2 || i == h - 1 || i == h) continue;
        cout << i << " ";
      }
      cout << n - 1 << " " << 1 << " " << h - 2 << " " << h - 1 << " " << h << "\n";
    }
  }
}

```



## 28.[D. Yet Another Real Number Problem](https://codeforces.com/contest/2035/problem/D)(单调栈，贪心)(1600-1700/0)



```cpp
void solve() {
  int n;
  cin >> n;
  vector<pll> stk;
  ll sum = 0, a, r;
  for (int i = 1; i <= n; ++i) {
    ll cnt = 0;
    cin >> a;
    while (a % 2 == 0) {
      a >>= 1;
      cnt++;
    }
    while (stk.size() && (cnt >= 30 || stk.back().first <= (a << cnt))) {
      sum += stk.back().first;
      cnt += stk.back().second;
      stk.pop_back();
    }
    if (cnt) {
      stk.push_back({a, cnt});
    } else {
      sum += a;
    }
    ll ans = sum % mod;
    for (const auto& [x, y] : stk) ans = (ans + qpow(2, y, mod) * x % mod) % mod;
    cout << ans << " ";
  }
  cout << "\n";
}
```



## 29.**[E - Sensor Optimization Dilemma 2](https://atcoder.jp/contests/abc374/tasks/abc374_e)**(数学/二分)(1400-1500/0)



```cpp
void solve() {
  ll n, m;
  cin >> n >> m;
  vector<ll> a(n + 1), b(n + 1), p(n + 1), q(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i] >> p[i] >> b[i] >> q[i];
    if (b[i] * p[i] > a[i] * q[i]) {
      swap(a[i], b[i]), swap(p[i], q[i]);
    }
  }
  auto check = [&](ll x) {
    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
      // ll t = a[i] * b[i];
      // ll k = x / t, r = x % t;
      // sum += k * b[i] * p[i];
      ll cnt = 4e18;
      for (int j = 0; j <= b[i]; ++j) cnt = min(cnt, j * 1ll * p[i] + ((max(0ll, x - j * a[i]) + b[i] - 1) / b[i]) * q[i]);
      for (int j = 0; j <= a[i]; ++j) cnt = min(cnt, j * 1ll * q[i] + ((max(0ll, x - j * b[i]) + a[i] - 1) / a[i]) * p[i]);
      sum += cnt;
      if (sum > m) return false;
    }
    return sum <= m;
  };
  ll L = 0, R = 1e9 + 1;
  while (L + 1 != R) {
    ll mid = L + R >> 1;
    if (check(mid)) {
      L = mid;
    } else {
      R = mid;
    }
  }
  cout << L << "\n";
}
```

## 30.[D. Penchick and Desert Rabbit](https://codeforces.com/contest/2031/problem/D)(DP)(1600-1700/0)

## 31.[D. Cool Graph](https://codeforces.com/problemset/problem/2029/D)(构造)(1800-1900/0)

肯定是变成一颗树简单一点。注意到如果每一个连通块只有1个或2个点，就很简单了。

对一个点度数大于1进行操作。将其度数减小到1或0。



## 32.[E. Coloring Game](https://codeforces.com/problemset/problem/1991/E)（二分图，构造）(1800-1900/0)

```cpp
vector<int> g[N];
int col[N];
// 二分图判定
bool dfs(int x) {
  for (const auto& y : g[x]) {
    if (col[y] == col[x]) return false;
    if (col[y] != -1) continue;
    col[y] = col[x] ^ 1;
    if (!dfs(y)) return false;
  }
  return true;
}
void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) g[i].clear();
  for (int i = 1; i <= m; ++i) {
    int x, y;
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  for (int i = 1; i <= n; ++i) col[i] = -1;
  col[1] = 0;
  if (!dfs(1)) {
    cout << "Alice" << endl;
    for (int i = 1; i <= n; ++i) {
      cout << "1 2" << endl;
      int x, y;
      cin >> x >> y;
    }
    return;
  }
  vector<int> col1, col2;
  for (int i = 1; i <= n; ++i) {
    if (col[i]) {
      col2.push_back(i);
    } else {
      col1.push_back(i);
    }
  }
  cout << "Bob" << endl;
  while (col1.size() || col2.size()) {
    int x, y;
    cin >> x >> y;
    if (x > y) swap(x, y);
    if (col1.size() && x == 1) {
      cout << col1.back() << " " << 1 << endl;
      col1.pop_back();
    } else if (col2.size() && (x == 2 || y == 2)) {
      cout << col2.back() << " " << 2 << endl;
      col2.pop_back();
    } else {
      if (col1.size()) {
        cout << col1.back() << " " << 3 << endl;
        col1.pop_back();
      } else {
        cout << col2.back() << " " << 3 << endl;
        col2.pop_back();
      }
    }
  }
}
```

## 33.[P1453 城市环路](https://www.luogu.com.cn/problem/P1453)（基环树，DP）(2000-2100/0)

## 34. [Shohag Loves XOR (Hard Version)](https://codeforces.com/contest/2039/problem/C2)(数论/二分)(1800-1900/0)

和上面类似地，

$y+x\ge x \oplus y=ky$ 那么如果y大于x，无解。先处理是y的倍数情况。

如果$x\oplus y=kx\quad (k>1)$  ，如果这个柿子具有单调性就很简单了。 但是并没有。

不过我们发现$y=x\oplus kx$ 
$$
x\oplus kx \le x+kx \le (k+2)x-x\le x\oplus (k+2)x
$$
注意$x=y$ 。

于是我们进行2次二分即可。

```CPP
void solve() {
  ll x, m;
  cin >> x >> m;
  ll ans = 0;
  ll mm = min(m, x);
  for (int y = 1; y <= mm; ++y) {
    if (x == y) continue;
    int t = x ^ y;
    if (t % y == 0 && t % x != 0) ans++;
  }
  if (m >= x) ans++;
  ull L = 0, R = (m + x) / x / 2 + 10;
  while (L + 1 != R) {
    ull mid = L + R >> 1;
    ull t = (1ull * x) ^ (mid * 2) * x;
    if (t <= m) {
      L = mid;
    } else {
      R = mid;
    }
  }
  ans += L;
  L = 0, R = (m + x) / x / 2 + 10;
  while (L + 1 != R) {
    ull mid = L + R >> 1;
    ull t = (1ull * x) ^ (mid * 2 + 1) * x;
    if (t <= m) {
      L = mid;
    } else {
      R = mid;
    }
  }
  ans += L;
  cout << ans << '\n';
}
```

**std：**

对于是x的倍数时。

设$p=x\oplus y$，注意到大部分$p\le m$ 都可以成立。在$x|p$的前提下，要成立只需要$p\oplus x\le m$即可。

即$p\le m-x$，而$p\le m+x$ ,因此可以枚举$(m-x,m+x]$中的2个p即可。

同时，可以在枚举y的倍数时排除x。但是实际上，不会有重复。（除了0）

因为
$$
x\oplus y< 2\max(x,y) \le lcm(x,y)
$$

```cpp
void solve() {
  ll x, m;
  cin >> x >> m;
  ll ans = 0;
  ll mm = min(m, x);
  for (int y = 1; y <= mm; ++y) {
    int t = x ^ y;
    if (t % y == 0) ans++;
  };
  if (m >= x) {
    ll p = (m - x) - (m - x) % x;
    ans += p / x + (p < 1);
    p += x;

    if ((p ^ x) >= 1 && (p ^ x) <= m) ans++;
    p += x;
    if ((p ^ x) >= 1 && (p ^ x) <= m) ans++;
    ans--;
  }
  cout << ans << "\n";
}
```



## 35. [Shohag Loves GCD](https://codeforces.com/contest/2039/problem/D)(数论)(1600-1700/0)

容易想到一种方案，从1开始从大的选，每一个选完后标记不能和自己一样的位置。

但肯定不能暴力。

注意到算数基本定理，我们可以考虑每一个下标质因数分解。

然后注意到对于
$$
j=\prod_{i=1}^{n} p_i^{k_i}
$$
选第
$$
d_j=\left(\sum_{i=1}^{n} k_i\right)+1
$$
大的即可。

可以证明按照这个方案构造的答案就是答案，构造不出来就无解。

设第$i$大对应的值为$-i$，即$a_j=b_{dj}$，b降序排列

又
$$
d_{\gcd(i,j)}<d_i \quad  j<i
$$


对于任意$i$和$j<i$。
$$
a_{\gcd(i,j)}=b_{d_{\gcd(i,j)}}> b_{d_i}=a_i\ge \gcd(a_i,a_j)
$$

下面证明这是最大的。考虑归纳证明，对于每一个不能替换成更大的。

第一个显然。

若前$k$个不能替换，对第$k+1$个

假设
$$
d_{k+1}=x
$$
$c_1,c_2,\cdots,c_{x-1}$ 是减少$i$个因子后的索引。

那么有
$$
a_{\gcd(k+1,c_i)}=b_{\gcd(k+1,c_i)}=b_{c_i}=a_{c_i}
$$
故其也不能替换成更大的。证毕。

那么如果无法这样构造答案，当且仅当最大的$d_i$比可选择的元素多。由上述证明显然无解。

可以用筛法求d

```cpp
int d[1000009];
void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> s(m + 1), ans(n + 1);
  for (int i = m; i >= 1; --i) cin >> s[i];
  int mx = 0;
  for (int i = 1; i <= n; ++i) mx = max(mx, d[i]);
  if (mx >= m) {
    cout << "-1\n";
    return;
  }
  for (int i = 1; i <= n; ++i) {
    cout << s[d[i] + 1] << " \n"[i == n];
  }
}

inline void STDIO() {
  ios::sync_with_stdio(false), cout.tie(0), cin.tie(0);
  return;
}
int main() {
  STDIO();
  for (int i = 2; i <= (int)1e6; ++i) {
    if (d[i]) continue;
    for (int j = i; j <= (int)1e6; j += i) {
      int x = j;
      while (x % i == 0) x /= i, d[j]++;
    }
  }
  int _ = 1;
  cin >> _;
  while (_--) solve();
  return 0;
}
```

**std**

考虑证明$i<j,i|j$有
$$
a_{\gcd(a_i,a_j)}\neq \gcd(a_i,a_j)
$$
是满足条件的充分条件。即
$$
若\forall (i<j,i|j) 有 a_{\gcd(a_i,a_j)}\neq \gcd(a_i,a_j) 则 不存在 i<j,a_{\gcd(a_i,a_j)}= \gcd(a_i,a_j)
$$
考虑证明其逆否命题
$$
若\exist i<j ,a_{\gcd(a_i,a_j)}= \gcd(a_i,a_j),则\exist (i<j,i|j)有 a_{\gcd(a_i,a_j)}= \gcd(a_i,a_j)
$$
设$g=\gcd(i,j)$。
$$
a_{\gcd(g,j)}=a_g=\gcd(a_g,a_j)
$$
$g<j,g|j$

考虑一个整除链$i_1|i_2...$，递减赋值即可。可以得出我的方法的结论。

给出另外一种构造方法。

用set维护，每一个索引被禁止的值。但是要证明时间复杂度就必须完成上述证明，~~就没必要这样做了~~

## [36. Equation](https://codeforces.com/gym/104825/problem/L)(数论/扩展欧几里得)(2000-2100/0)

```cpp
ll exgcd(ll a, ll b, ll& x, ll& y) {
  if (b == 0) return x = 1, y = 0, a;
  int d = exgcd(b, a % b, y, x);
  return y -= a / b * x, d;
}
 
void solve() {
  ll m, x;
  cin >> m;
  x = m;
  vector<int> p;
  for (ll i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      ll res = 1;
      while (x % i == 0) x /= i, res *= i;
      p.push_back(res);
    }
  }
  if (x > 1) p.push_back(x);
  set<int> st;
  for (int i = 0; i < (1ll << p.size()); ++i) {
    ll a = 1, b = 1;
    for (int j = 0; j < p.size(); ++j) {
      if (i >> j & 1) {
        a *= p[j];
      } else {
        b *= p[j];
      }
    }
    // cout << a << " " << b << "\n";
    ll x, y;
    exgcd(a, b, x, y);
    // cout << a * x << " ";
    // cout << ((a * x) % m + m) % m << "\n";
    st.insert((a * x % m + m) % m);
  }
  cout << st.size() << "\n";
  for (auto it = st.begin(); it != st.end(); ++it) cout << (*it) << " ";
  cout << "\n";
}
```

## [37C. 小L的旅行](https://codeforces.com/gym/104825/problem/C)（最短路，01BFS,数学）(1800-1900/0)

注意到不可能全部连

01BFS

主要用途：用来解决边权只有 00 或 11 的最短路问题。或者能够转化为这种边权值的最短路问题。

主要方法：用一个双端队列 `deque`，被边权为 00 的边更新的点放到队首，被边权为 11 的边更新的点放到队尾。

时间复杂度 O(n+m)O(n+m)。避免使用其他最短路算法造成的时间浪费。

正确性：因为只有 0,10,1，这样入队在队列中的点 vv 仍然具有单调性（是指 disvdisv 的单调性）。

## 38. LCA [Determinant](https://codeforces.com/gym/104825/problem/H)（数学/线代)(1800-1900/0)

注意到行列式求值可以同时进行行变换和列变换。利用代数余子式递推的求出值。

## 39.[小L的数学题](https://codeforces.com/gym/104825/problem/D)(数论)(2400-2500/0)

注意卡常

容易想到时间复杂度应该会带根号.那么可以考虑转化为枚举什么平方之类的.

直接算显然不行,考虑构造双射转化成计算另外一种东西.

暴力的过程,是枚举每个数的因数判断,是否具有什么性质呢?

若$(d,\frac{n}{d})=x>1$,说明了什么,说明$x^2|n$,可以打表找一下规律,猜想一对$(d,\frac{n}{d})$都一一对应了一个含完全平方数的因子.

因为设$d=ax,(d,\frac{n}{d})=x$,与之对应了唯一一个因子$ax^2$,同理对于一个因子$ax^2$,$(ax,\frac{n}{ax})=x$也对应了唯一个$ax$.

因此可以转化为求$1\sim n$不含平方因子的因子数.

然后就有容斥

##  40.D. [Speedbreaker](https://codeforces.com/contest/2019/problem/D)（思维）(1800-1900/0)



## 41[太阳系DISCO](https://ac.nowcoder.com/acm/contest/97439/D)(数论(exgcd)/图论(bfs))(1600-1700/0)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
using ll = long long;
using ull = unsigned long long;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int mod = 998244353;
const int N = 1e6 + 9;
const int iinf = 1e9;
const ll linf = 1e18;

ll exgcd(ll a, ll b, ll& x, ll& y) {
  if (b == 0) return x = 1, y = 0, a;
  int d = exgcd(b, a % b, y, x);
  return y -= a / b * x, d;
}


void solve() {
  int n,k,a,b,x,y;
  cin>>n>>k>>a>>b>>x>>y;
  y=n-y;
  int ans=linf,mix;
  for (int i=1;i<=n;++i) {
    if (i*x%n==0) {
      mix=i;
      break;
    }
  }
  // cout<<mix<<"\n";
  for (int i=0;i<=n;++i) {
    for (int j=0;j<=min(1ll,k);++j) {
      int cur=(a+i*y+j*(n/2))%n;
      int t=((b-cur)%n+n)%n;
      //rx-sn=t
      int d=__gcd(x,n);
      if (t%d) continue;
      int r,s;
      exgcd(x,n,r,s);
      r*=(t/d);
      r=(r%mix+mix)%mix;
      // cout<<r<<" "<<x<<" "<<s<<" "<<n<<"\n";
      // cout<<i<<" "<<j<<" "<<r<<'\n';
      // cout<<t<<" "<<s<<"\n";
      ans=min(ans,i+j+r);
    }
  }

  // vector<int> ra(n+1,-1),rb(n+1,-1);
  // ra[0]=rb[0]=0;
  // for (int i=1;i<n;++i) {
  //   int r=(i*x)%n;
  //   if (ra[r]==-1)  ra[r]=i;
  // }
  // for (int i=1;i<n;++i) {
  //   int r=(i*y)%n;
  //   if (rb[r]==-1)  rb[r]=i;
  // }
  // for (int i=0;i<n;++i) {
  //   if (ra[i]==-1) continue;
  //   for (int j=0;j<=min(1ll,k);++j) {
  //     int cur=(a+i+j*(n/2))%n;
  //     int t=((b-cur)%n+n)%n;
  //     if (rb[t]!=-1) {
  //       ans=min(ans,ra[i]+j+rb[t]);
  //     }
  //   }
  // }
  if (ans>10*n) {
    cout<<"-1\n";
  }else {
    cout<<ans<<'\n';
  }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int Case = 1;
  //cin >> Case;
  while (Case--) solve();
  return 0;
}

// 8 1 1 7 3 3
```

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
using ll = long long;
using ull = unsigned long long;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int mod = 998244353;
const int N = 1e6 + 9;
const int iinf = 1e9;
const ll linf = 1e18;
bitset<N> vis;
void solve() {
  int n,k,a,b,x,y;
  cin>>n>>k>>a>>b>>x>>y;
  y=n-y;
  //0 -> x,1 -> y
  auto go=[&](int cur,bool ty,int c=0)->int {
    int nex=cur+(ty==0?x:y);
    if (c) nex=cur+c;
    return nex>n?nex-n:nex;
  };
  vector<int> d(n+1);
  for (int i=1;i<=n;++i) d[i]=iinf;
  queue<int> q;
  q.push(a);
  d[a]=0;
  vis[a]=1;
  while (q.size()) {
    auto cur=q.front();
    q.pop();
    int nex=go(cur,0);
    if (!vis[nex]) {
      d[nex]=d[cur]+1;
      vis[nex]=1;
      q.push(nex);
    }
    nex=go(cur,1);
    if (!vis[nex]) {
      d[nex]=d[cur]+1;
      vis[nex]=1;
      q.push(nex);
    }
  }
  int ans=d[b];
  if (k) ans=min( ans,d[go(b,0,n/2)]+1) ;
  if (ans>n) {
    cout<<"-1\n";
  }else {
    cout<<ans<<"\n";
  }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int Case = 1;
 // cin >> Case;
  while (Case--) solve();
  return 0;
}

```

## 42.[普通DISCO-1](https://ac.nowcoder.com/acm/contest/97439/E)(图论)(1800-1900/0)

## 43.[**E - Sum of Max Matching**](https://atcoder.jp/contests/abc383/tasks/abc383_e)(贪心，并查集)(1600-1900/0)

## 44.[ 普通DISCO-2](https://ac.nowcoder.com/acm/contest/97439/F)（stO(1)求LCA）(2000-2100/0)

```cpp
#include <bits/stdc++.h>
using namespace std;
// #define int long long
using ll = long long;
using ull = unsigned long long;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int mod = 998244353;
const int N = 5e5 + 9;
const int iinf = 1e9;
const ll linf = 1e18;
vector<int> g[N];
int len[N], dep[N], mxs[N],eord[N<<1],fp[N],idx,fa[N];
void dfs(int x, int pre) {
  fa[x]=pre;
  dep[x]=dep[pre]+1;
  mxs[x]=1;
  eord[++idx]=x;
  if (fp[x]==0) fp[x]=idx;
  for (auto& y : g[x]) {
    if (y==pre) continue;
    dfs(y,x);
    eord[++idx]=x;
    mxs[x]=max(mxs[x],mxs[y]+1);
  }
}
int f[N<<1][35];
void init() {
  for (int i=1;i<=idx;++i) f[i][0]=eord[i];
  for (int len=1;len<30;++len) {
    for (int l=1;l<=idx;++l) {
      int r=l+(1ll<<len)-1;
      if (r>idx) break;
      f[l][len]=min(f[l][len-1],f[l+(1ll<<len-1)][len-1],[&](const int& x,const int& y){return dep[x]<dep[y];});
    }
  }
}
int lca(int x,int y) {
  int L=fp[x],R=fp[y];
  if (L>R) swap(L,R);
  int len=__lg(R-L+1);
  // cout<<L<<" "<<R<<"\n" ;
  return min(f[L][len], f[R - (1 << len) + 1][len],[&](const int& x,const int& y){return dep[x]<dep[y]; });
}


void solve() {
  int n;
  cin >> n;
  for (int i = 1; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  dfs(1,1);
  init();
  // for (int i=1;i<=idx;++i) cout<<eord[i]<<" \n"[i==idx];
  // for (int len=0;len<=3;++len) {
  //   for (int l=1;l<=idx;++l) {
  //     int r=l+(1ll<<len)-1;
  //     if (r>idx) break;
  //     cout<<f[l][len]<<"\n";
  //   }
  // }
  function<bool(int)> check=[&](int x)->bool {
    int rt=0;
    for (int i=1;i<=n;++i) {
      if (dep[i]>x) {
        if (rt==0) rt=fa[i];
        else rt=lca(rt,fa[i]);
      }
    }

    if (rt==0) return true;
    if (rt==1) return false;
    for (int i=2;i<=n;++i) {
      int t=lca(i,rt);
      if (t==i|| t== rt) continue;
      if (dep[fa[i]]+mxs[rt]<=x && dep[fa[rt]]+mxs[i]<=x ) return true;
    }
    return false;
  };
  int L=0,R=iinf;
  while (L+1!=R) {
    int mid=L+R>>1;
    if (check(mid)) {
      R=mid;
    }else {
      L=mid;
    }
  }
  cout<<R;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int Case = 1;
  // cin >> Case;
  while (Case--) solve();
  return 0;
}

```



## 45.[**F - Dangerous Sugoroku**](https://atcoder.jp/contests/abc388/tasks/abc388_f)(数论(二元一次不定方程的正整数解),dp,矩阵快速幂)(2200-2300/0)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
using ll = long long;
using ull = unsigned long long;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int mod = 998244353;
const int N = 1e6 + 9;
const int iinf = 1e9;
const ll linf = 1e18;
//342
//365
bool f[370];
void solve() {
  int n,m,A,B;cin>>n>>m>>A>>B;
  vector<int> L(m+1),R(m+1);
  for (int i=1;i<=m;++i) cin>>L[i]>>R[i];
  for (int i=1;i<=m;++i) {
    if (R[i]-L[i]+1>=B) {
      cout<<"No\n";
      return;
    }
  }
  if (A==B) {
    if ((n-1)%B) {
      cout<<"No\n";
      return ;
    }
    for (int i=1;i<=m;++i) {
      for (int j=L[i];j<=R[i];++j) {
        if ((j-1)%B==0) {
          cout<<"No\n";
          return ;
        }
      }
    }
    cout<<"Yes\n";
    return ;
  }
  f[0]=1;
  for (int i=1;i<370;++i) {
    for (int j=i-B;j<=i-A;++j) if (j>=0 and f[j]) f[i]=1;
  }
  vector<int> LL,RR;
  for (int i=1;i<=m;++i) {
    if (L[i]-1>=R[i-1]+1) LL.push_back(R[i-1]+1),RR.push_back(L[i]-1);
  }
  LL.push_back(R[m]+1),RR.push_back(n);
  map<int,int> ok;
  ok[1]=1;
  for (int k=0;k<LL.size();++k) {
    for (int pos=LL[k];pos<=min(LL[k]+B-1,RR[k]);++pos) {
      for (int i=A;i<=B;++i) {
        if (ok[pos-i]) {
          ok[pos]=1;
          break;
        }
      }
      if (ok[pos]) {
        for (int j=max(LL[k],RR[k]-B+1);j<=RR[k];++j) {
          if (f[min(j-pos,365ll)]) ok[j]=1;
        }
      }
    }
  }
  if (ok[n]) cout<<"Yes\n";
  else cout<<"No\n";
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int Case = 1;
  // cin >> Case;
  while (Case--) solve();
  return 0;
}
//
// 8 3 3 4
// 2 2
// 3 3
// 4 4

//Yes
```

**矩乘**

## 46.  [D - 9 ](https://atcoder.jp/contests/arc052/tasks/arc052_d/editorial)(根号分治+数位dp)(2000-2100/0)



```
#include <bits/stdc++.h>
using namespace std;
#define int long long
using ll = long long;
using ull = unsigned long long;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int mod = 998244353;
const int N = 1e6 + 9;
const int iinf = 1e9;
const ll linf = 1e18;
const int B = 1e4;
ll f[12][B][91][2];
void solve() {
  ll M, K;
  cin >> K >> M;
  if (K >= B) {
    ll ans = 0;
    for (int i = 0; i <= 90; ++i) {
      for (int t = 0; t * K + i <= M; ++t) {
        int res = 0,x=t*K+i;
        while (x) {
          res += x % 10;
          x /= 10;
        }
        ans +=res==i;
      }
    }
    cout << ans-1;
  } else {
    vector<int> d(12, 0);
    int n = 0;
    while (M) {
      d[++n] = M % 10;
      M /= 10;
    }
    reverse(d.begin()+1,d.begin()+1+n);
    for (int i = 0; i <= d[1]; ++i) f[1][i % K][i][d[1] == i] = 1;
    for (int i = 1; i <n; ++i) {
      for (int j = 0; j < K; ++j) {
        for (int k = 0; k <= 90; ++k) {
          for (int x = 0; x <= 9; ++x) {
            if (k+x>90) continue;
            f[i + 1][(j * 10ll + x) % K][k + x][0] += f[i][j][k][0];
            if (x == d[i+1])
              f[i + 1][(j * 10ll + x) % K][k + x][1] += f[i][j][k][1];
            if (x < d[i+1])
              f[i + 1][(j * 10ll + x) % K][k + x][0] += f[i][j][k][1];
          }
        }
      }
    }
    ll ans = 0;
    for (int i=0;i<=90;++i) ans+=(f[n][i%K][i][0]+f[n][i%K][i][1]);
    cout<<ans-1;
  }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int Case = 1;
  // cin >> Case;
  while (Case--) solve();
  return 0;
}
```

## 47.[**F - Rated Range**](https://atcoder.jp/contests/abc389/tasks/abc389_f) (线段树二分)(1800-1900/0)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
using i64 = long long;
using i128 = __int128;
using u64 = unsigned long long;
const int mod = 998244353;
const int N = 5e5 + 9;
const int iinf = 1e9;
const i64 linf = 1e18;
/*
线段树（LazySegmentTree）
左闭右开
*/
template <class Info, class Tag>
struct LazySegmentTree {
  int n;  // n+1
  vector<Info> info;
  vector<Tag> tag;
  // init begin
  LazySegmentTree() : n(0) {}
  LazySegmentTree(int n_, Info v_ = Info()) {
    init(n_ + 1, v_);  // 下标从1开始
  }
  template <class T>
  LazySegmentTree(vector<T> init_) {
    init(init_);
  }
  void init(int n_, Info v_ = Info()) { init(vector(n_, v_)); }
  template <class T>
  void init(vector<T> init_) {
    n = init_.size();
    info.assign(4 << __lg(n), Info());
    tag.assign(4 << __lg(n), Tag());
    std::function<void(int, int, int)> build = [&](int p, int l, int r) {
      if (r - l == 1) {
        info[p] = init_[l];
        return;
      }
      int m = (l + r) / 2;
      build(2 * p, l, m);
      build(2 * p + 1, m, r);
      pull(p);
    };
    build(1, 1, n);
  }
  // init end
  //  up
  void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
  // 修改
  void apply(int p, const Tag &v, int len) {
    info[p].apply(v, len);
    tag[p].apply(v);
  }
  // down
  void push(int p, int len) {
    apply(2 * p, tag[p], len / 2);
    apply(2 * p + 1, tag[p], len - len / 2);
    tag[p] = Tag();
  }
  // 单点修改
  void modify(int p, int l, int r, int x, const Info &v) {
    if (r - l == 1) {
      info[p] = v;
      return;
    }
    int m = (l + r) / 2;
    push(p, r - l);
    if (x < m) {
      modify(2 * p, l, m, x, v);
    } else {
      modify(2 * p + 1, m, r, x, v);
    }
    pull(p);
  }
  void modify(int p, const Info &v) { modify(1, 1, n, p, v); }
  // 区间查询
  Info rangeQuery(int p, int l, int r, int x, int y) {
    if (l >= y || r <= x) {
      return Info();
    }
    if (l >= x && r <= y) {
      return info[p];
    }
    int m = (l + r) / 2;
    push(p, r - l);
    return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
  }
  Info rangeQuery(int l, int r) { return rangeQuery(1, 1, n, l, r); }

  // 区间修改
  void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
    if (l >= y || r <= x) {
      return;
    }
    if (l >= x && r <= y) {
      apply(p, v, r - l);
      return;
    }
    int m = (l + r) / 2;
    push(p, r - l);
    rangeApply(2 * p, l, m, x, y, v);
    rangeApply(2 * p + 1, m, r, x, y, v);
    pull(p);
  }
  void rangeApply(int l, int r, const Tag &v) {
    return rangeApply(1, 1, n, l, r, v);
  }
  //线段树二分
  template <class F>
  int findFirst(int p, int l, int r, int x, int y, F &&pred) {
    if (l >= y || r <= x) {
      return -1;
    }
    if (l >= x && r <= y && !pred(info[p])) {
      return -1;
    }
    if (r - l == 1) {
      return l;
    }
    int m = (l + r) / 2;
    push(p,r-l);
    int res = findFirst(2 * p, l, m, x, y, pred);
    if (res == -1) {
      res = findFirst(2 * p + 1, m, r, x, y, pred);
    }
    return res;
  }
  //第一个满足条件F的位置
  template <class F>
  int findFirst(int l, int r, F &&pred) {
    return findFirst(1, 1, n, l, r, pred);
  }
  template <class F>
  int findLast(int p, int l, int r, int x, int y, F &&pred) {
    if (l >= y || r <= x) {
      return -1;
    }
    if (l >= x && r <= y && !pred(info[p])) {
      return -1;
    }
    if (r - l == 1) {
      return l;
    }
    int m = (l + r) / 2;
    push(p,r-l);
    int res = findLast(2 * p + 1, m, r, x, y, pred);
    if (res == -1) {
      res = findLast(2 * p, l, m, x, y, pred);
    }
    return res;
  }
  //最后一个满足条件F的位置
  template <class F>
  int findLast(int l, int r, F &&pred) {
    return findLast(1, 1, n, l, r, pred);
  }
};

struct Tag {
  int x = 0;
  void apply(const Tag &t) & { x += t.x; }
};

struct Info {
  int sum = 0,mx=-iinf,mi=iinf;
  void apply(const Tag &t, int len) & {
    sum += t.x * len;
    mx +=t.x;
    mi +=t.x;
  }
};
// merge
Info operator+(const Info &a, const Info &b) {
  Info res={};
  res.sum=a.sum+b.sum;
  res.mx=max(a.mx,b.mx);
  res.mi=min(a.mi,b.mi);
  return res;
}

void solve() {
  int n, q;
  cin >> n;
  vector<Info> f(5e5 + 1);
  for (int i = 1; i <= 5e5; ++i) f[i].sum =f[i].mx=f[i].mi= i;
  LazySegmentTree<Info, Tag> seg(f);
  for (int i = 1; i <= n; ++i) {
    int L, R;cin >> L >> R;
    int l=seg.findFirst(1,5e5+1,[&](const Info& info){return info.mx>=L;});
    int r=seg.findLast(1,5e5+1,[&](const Info& info){return info.mi<=R;});
    seg.rangeApply(l, r + 1, {1});
  }
  cin >> q;
  for (int i = 1; i <= q; ++i) {
    int x;
    cin >> x;
    cout << seg.rangeQuery(x, x + 1).sum << "\n";
  }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int Case = 1;
  // cin >> Case;
  while (Case--) solve();
  return 0;
}
```

## 48.[**E - Square Price**](https://atcoder.jp/contests/abc389/tasks/abc389_e)(数学/二分)(1800-1900/0)

形如
$$
\begin{aligned}
&\sum_{i=1}^{n}k_i^2P_i\le M\\
&max \qquad \sum_{i=1}^n k_i
\end{aligned}
$$
有
$$
\begin{aligned}
&\sum_{i=1}^{n}k_i^2P_i=\sum_{i=1}^{n}\sum_{j=1}^{k_i}(2j-1) P_i \le M \\
&max \qquad \sum_{i=1}^{n}\sum_{j=1}^{k_i}1
\end{aligned}
$$
将
$$
(2j-1)P_i
$$
看成整体并排序,求最大的小于M的前缀和.

易知道,存在最大的x能加完所有小于等于x的数,并尽可能加完x+1.二分即可.

## 49.[D. Unique Median](https://codeforces.com/contest/2056/problem/D)(计数)(2200-2300/0)

## 50.[E. Nested Segments](https://codeforces.com/contest/2056/problem/E)(计数/Catlan)(2400-2500/0)

