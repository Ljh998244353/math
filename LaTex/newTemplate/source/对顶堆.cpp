#include <bits/stdc++.h>
using namespace std;
struct mset {
  const int kInf = 1e9 + 2077;
  multiset<int> less, greater;
  void init() {
    less.clear(), greater.clear();
    less.insert(-kInf), greater.insert(kInf);
  }
  void adjust() {
    while (less.size() > greater.size() + 1) {
      multiset<int>::iterator it = (--less.end());
      greater.insert(*it);
      less.erase(it);
    }
    while (greater.size() > less.size()) {
      multiset<int>::iterator it = greater.begin();
      less.insert(*it);
      greater.erase(it);
    }
  }
  void add(int val_) {
    if (val_ <= *greater.begin())
      less.insert(val_);
    else
      greater.insert(val_);
    adjust();
  }
  void del(int val_) {
    multiset<int>::iterator it = less.lower_bound(val_);
    if (it != less.end()) {
      less.erase(it);
    } else {
      it = greater.lower_bound(val_);
      greater.erase(it);
    }
    adjust();
  }
  int get_middle() { return *less.rbegin(); }
};
