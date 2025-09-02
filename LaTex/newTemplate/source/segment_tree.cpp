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