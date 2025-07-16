struct Heap {
  int k;
  int sum = 0;
  multiset<i64> mxq, miq;
  map<int, int> mxc, mic;
  void init(vector<int> _init) {
    sort(_init.begin() + 1, _init.end(), greater<int>());
    for (int i = 1; i <= k; ++i) miq.insert(_init[i]), mic[_init[i]]++;
    for (int i = k + 1; i < _init.size(); ++i)
      mxq.insert(-_init[i]), mxc[-_init[i]]++;
  }
  void adj() {
    while (miq.size() < k) {
      miq.insert(-*mxq.begin()), mic[-*mxq.begin()]++;
      mxc[*mxq.begin()]--;
      mxq.erase(mxq.begin());
    }
    while (miq.size() > k) {
      mxq.insert(-*miq.begin());
      mxc[-*miq.begin()]++;
      mic[*miq.begin()]--;
      miq.erase(miq.begin());
    }
  }
  void insert(i64 x) {
    if (x >= *miq.begin())
      miq.insert(x), mic[x]++;
    else
      mxq.insert(-x), mxc[-x]++;
    adj();
  }
  void erase(i64 x) {
    if (x >= *miq.begin())
      miq.erase(miq.find(x)), mic[x]--;
    else
      mxq.erase(mxq.find(-x)), mxc[-x]--;
  }
  i64 queryk() { return *miq.begin(); }
};