int mygcd(int a,int b) {
  return __gcd(abs(a),abs(b));
}
template<class T>
struct Segt {
  struct node {
    int l,r;
    T w;// gcd
    T sum;
  };
  vector<T> w;
  vector<node> t;
  Segt(){}
  Segt(int n) {init(n);}
  Segt(vector<int> in) {
    int n=in.size()-1;
    w.resize(n+1);
    for (int i=1;i<=n;++i) {
      w[i]=in[i];
    }
    init(in.size()-1);
  }
#define GL k<<1
#define GR k<<1|1
  void init(int n) {
    t.resize(4*n +1);
    auto build=[&](auto self ,int l, int r,int k=1) {
      if (l==r) {
        t[k]={l,r,w[l],w[l]};
        return ;
      }
      t[k]={l,r,0,0};
      int mid=(l+r)/2;
      self(self,l,mid,GL);
      self(self,mid+1,r,GR);
      pushup(k);
    };
    build(build,1,n);
  }
  void pushup(int k) {
    auto pushup=[&](node& p,node& l, node &r) {
      p.w=mygcd(l.w,r.w);
      p.sum=l.sum+r.sum;
    };
    pushup(t[k],t[GL],t[GR]);
  }
  void add(int pos,T val,int k=1) {
    if (t[k].l==t[k].r) {
      t[k].w+=val;
      t[k].sum+=val;
      return ;
    }
    int mid=(t[k].l+t[k].r)/2;
    if (pos<=mid) add(pos,val,GL);
    else add(pos,val,GR);
    pushup(k);
  }
  // 单点赋值, 不用管sum
  void upd(int pos,T val,int k=1) {
    if (t[k].l==t[k].r) {
      t[k].w=val;
      return ;
    }
    int mid=(t[k].l+t[k].r)/2;
    if (pos<=mid) upd(pos,val,GL);
    else upd(pos,val,GR);
    pushup(k);
  }
  T askgcd(int l,int r,int k=1) {
    if (l<=t[k].l and t[k].r<=r) return t[k].w;
    int mid=(t[k].l+t[k].r)/2;
    T ans=0;
    if (l<=mid) ans=mygcd(ans,askgcd(l,r,GL));
    if (mid<r)  ans=mygcd(ans,askgcd(l,r,GR));
    return ans;
  }
  T asksum(int l,int r,int k=1) {
    if (l<=t[k].l and t[k].r<=r) return t[k].sum;
    int mid=(t[k].l+t[k].r)/2;
    T ans=0;
    if (l<=mid) ans+=asksum(l,r,GL);
    if (mid<r)  ans+=asksum(l,r,GR);
    return ans;
  }
};

void solve() {
  int n,m;cin>>n>>m;
  vector<int> a(n+1);
  for (int i=1;i<=n;++i) cin>>a[i];
  for (int i=n;i;--i) a[i]-=a[i-1];
  Segt<int> sgt(a);
  for (int i=1;i<=m;++i) {
    char op;cin>>op;
    if (op=='C') {// 区间修改
      int l,r,d;cin>>l>>r>>d;
      sgt.add(l,d);
      if (r<n) sgt.add(r+1,-d);
    }else {//区间查询
      int l,r;cin>>l>>r;
      cout<<mygcd(sgt.asksum(1,l),sgt.askgcd(l+1,r))<<"\n";
    }
  }
}