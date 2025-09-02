using namespace std;
struct Maxheap {
  int n;
  vector<int> w;
  Maxheap(auto &_init):w(_init) {
    n=static_cast<int>(_init.size())-1;
    w.resize(n+1);
    for (int i=1;i<=n;++i) up(i);
  }
  void up(int x) {
    while (x>1 and w[x]>w[x/2]) swap(w[x],w[x/2]),x/=2;
  }
  void down(int x) {
    while (x*2<=n) {
      int t=x*2;
      if (t+1<=n and w[t+1]>w[t]) t++;
      if (w[x]>=w[t]) return ;
      swap(w[x],w[t]);
      x=t;
    }
  }
};