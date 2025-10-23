#include <bits/stdc++.h>
using namespace std;

struct BIT {
  int n;
  vector<int> t;
  void init(int _n) {
    n = _n;
    t.assign(n + 1, 0);
  }
  void add(int i, int v) {
    for (; i <= n; i += i & -i) t[i] += v;
  }
  int sum(int i) {
    int s = 0;
    for (; i > 0; i -= i & -i) s += t[i];
    return s;
  }
  int sum(int l, int r) { return sum(r) - sum(l - 1); }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, mx = 1;
  cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i], mx = max(mx, a[i]);
  int q;
  cin >> q;
  struct Query {
    int L, R, idx;
  };
  vector<Query> qs(q);
  for (int i = 0; i < q; i++) {
    cin >> qs[i].L >> qs[i].R;
    qs[i].idx = i;
  }
  sort(qs.begin(), qs.end(),
       [](const Query& A, const Query& B) { return A.R < B.R; });

  BIT bit;
  bit.init(n);
  vector<int> last(mx + 1, 0);
  vector<int> ans(q);
  int curQ = 0;
  for (int i = 1; i <= n; i++) {
    if (last[a[i]] != 0) bit.add(last[a[i]], -1);
    bit.add(i, 1);
    last[a[i]] = i;
    while (curQ < q && qs[curQ].R == i) {
      ans[qs[curQ].idx] = bit.sum(qs[curQ].L, qs[curQ].R);
      curQ++;
    }
  }
  for (int i = 0; i < q; i++) cout << ans[i] << "\n";
  return 0;
}
