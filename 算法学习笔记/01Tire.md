# 01Tire

## 用途

主要用来解决一些异或大小问题。

## 模板

这里给出1类典型的应用的模板。通过维护通过该点的路径条数，得到第k大异或对。（点对区间）

```cpp
struct trie {
  int val, son[2];
} t[N << 5];
int a[N], idx;

void insert(int x) {
  int o = 0;
  for (int i = 30; i >= 0; --i) {
    int y = (x >> i) & 1;
    if (!t[o].son[y]) t[o].son[y] = ++idx;
    o = t[o].son[y];
    t[o].val++;
  }
}
// 最大异或值
int getval(int x) {
  int res = 0, o = 0;
  for (int i = 30; i >= 0; --i) {
    int y = (x >> i) & 1;
    int u = t[o].son[y], v = t[o].son[!y];
    if (v) {
      res |= (1 << i);
      o = v;
    } else {
      o = u;
    }
  }
  return res;
}
// 第k大异或值
int getval(int x, int k) {
  int res = 0, o = 0;
  for (int i = 30; i >= 0; --i) {
    int y = (x >> i) & 1;
    int u = t[o].son[y], v = t[o].son[!y];
    if (u && t[u].val >= k) {
      o = u;
    } else {
      if (u) k -= t[u].val;
      res |= (1 << i);
      o = v;
    }
  }
  return res;
}
```

## 例题

### [P4551 最长异或路径](https://www.luogu.com.cn/problem/P4551)

设置1为根。

考察任意两个点的路径$d(u,v)=d(u,lca(u,v))+d(lca(u,v),v)$

注意到
$$
xor(u,v)=xor(u,lca(u,v))\oplus xor(lca(u,v),v)=xor(1,u)\oplus xor(1,v)
$$


### [E. Beautiful Subarrays](https://codeforces.com/problemset/problem/665/E)

给定一个数组，求$a_i \oplus a_j\le(\ge) Const$ 的对数。

```cpp
struct trie {
  int val, son[2];
} t[N << 5];
int a[N], idx;

void insert(int x) {
  int o = 0;
  for (int i = 30; i >= 0; --i) {
    int y = (x >> i) & 1;
    if (!t[o].son[y]) t[o].son[y] = ++idx;
    o = t[o].son[y];
    t[o].val++;
  }
}
//^x<k
int getval(int x,int k) {
  int res=0,o=0;
  for (int i=30;i>=0;--i) {
    int y=(x>>i)&1,z=(k>>i)&1;
    int s0=t[o].son[y],s1=t[o].son[!y];
    if (z) {
      if (s0) res+=t[s0].val;
      if (!s1) return res;
      o=s1;
    }else {
      if (!s0) return res;
      o=s0;
    }
  }
  return res;
}
```



### [E. Xor Tree](https://codeforces.com/contest/1447/problem/E)

用字典树的二叉树性质dp

