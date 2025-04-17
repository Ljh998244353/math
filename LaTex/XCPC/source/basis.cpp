/*异或线性基
 *求数集子集异或和第k小(k从0开始计数)
 */
struct Basis {
    vector<u64> B;
    int cntz=0;//0的个数
    bool ok=false;
    void insert(u64 x) {
      for (auto b:B) x=min(x,x^b);
      for (auto& b: B) b=min(b,b^x);
      if (x) B.push_back(x);
      else cntz++;
    }
    void _min() {
      sort(B.begin(),B.end());
      for (int i=1;i<B.size();++i) {
        for (int j=i-1;j>=0;--j) {
          B[i]=min(B[i],B[i]^B[j]);
        }
      }
    }
    //第k小的异或和
    u64 query(int k,bool overphi) {//第k小,包含空集?(k从0开始数)
      if (!ok)_min(),ok=true;
      if (!overphi and !cntz) k++;
      if (k>=(1ll<<(B.size()))) return -1;
      int res=0;
      for (int i=0;i<B.size();++i) {
        if ((k>>i)&1) res^=B[i];
      }
      return res;
    }
  
    u64 querymx() {
      return query((1ll<<B.size())-1,1);
    }
  
    void print() {
      for (int i=0;i<B.size();++i) cout<<B[i]<<" ";
      cout<<"\n";
    }
  
    //线性基的合并(双log)
    void operator+=(Basis& _B) {
      for (auto &b:_B.B) this->insert(b);
    }
    friend Basis operator+(Basis& b1,Basis& b2) {
      Basis res=b1;
      for (auto& b:b2.B)res.insert(b);
      return res;
    }
};