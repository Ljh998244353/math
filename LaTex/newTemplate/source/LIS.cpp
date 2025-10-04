#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n;
  vector<int> a(n + 1);
  vector<int> stk(n + 10);
  int top = 0, ans = 0;
  // 最长不上升子序列
  for (int i = 1; i <= n; ++i) {
    auto pos = lower_bound(stk.begin() + 1, stk.begin() + 1 + top, a[i],
                           [&](int u, int v) { return u >= v; }) -
               stk.begin();
    if (pos > top) top++;
    stk[pos] = a[i];
    ans = max(ans, top);
  }
  cout << ans << "\n";
  top = 0, ans = 0;
  // 最长上升子序列
  for (int i = 1; i <= n; ++i) {
    auto pos =
        lower_bound(stk.begin() + 1, stk.begin() + 1 + top, a[i]) - stk.begin();
    if (pos > top) top++;
    stk[pos] = a[i];
    ans = max(ans, top);
  }
}