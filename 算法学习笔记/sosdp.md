# 算法学习笔记.SOSDP(子集和dp)--萝莉控都能看懂的sosdp教程。

> 萝莉控都能看懂的sosdp教程。

即是**Sum Over Subsets DP**

## 背景

给定一个集合$U$。定义函数$F,G:\mathcal{P}(U)\rightarrow R $，且
$$
G(K)=\sum_{L\subseteq K }F(L)\qquad (K\subseteq U)
$$
求所有的$G(K)$

考虑容斥，在仅有两个元素时有：
$$
\begin{aligned}
G(\phi)&=F(\phi)\\
G(\{x_1\})&=F(\{x_1\})+F(\phi)\\
G(\{x_2\})&=F(\{x_2\})+F(\phi)\\
G(\{x_1,x_2\})&=F(\{x_1,x_2\})+G(\{x_1\})+G(\{x_2\})-G(\phi)
\end{aligned}
$$
推广到$n$元
$$
G(S)=F(S)+\sum_{K\subset S}(-1)^{|S|-|K|+1}G(K)
$$
时间复杂度为$O(3^n)$

注意到二元形式和二维前缀和很像。如果把一个元素看成一个维度的话，发现其本质就是一个**$n$维前缀和**的问题。

## 高维前缀和

下面介绍高维度前缀和如何求。下面都默认读入了初值。

### 二维前缀和

通常的做法是容斥，但是可以考虑分维度计算。

```cpp
for(int i=1;i<=n;++i){
    for(int j=1;j<=n;++j){
        a[i][j]+=a[i-1][j];
    }
}
for(int i=1;i<=n;++i){
    for(int j=1;j<=n;++j){
        a[i][j]+=a[i][j-1];
    }
}
```

考虑**状态压缩**，以行序为主，将其依次映射到$0 \sim n^2-1$

就有

```cpp
for(int i=0;i<2;++i){
    for(int j=0;j<n*n;++j){
        if(i==0){
            if(j%n!=0) f[j]+=f[j-1];
        }else {
            if((j/n)%n!=0) f[j]+=f[j-n];
        }
    }
}
```

### 高维前缀和

类似地有：

```cpp
int pw[]={1,n,n*n,n*n*n,.....}
for(int i=0;i<d;++i){
    for(int j=0;j<n*n;++j){
        if((j/pw[i])%n!=0) f[j]+=f[j-pw[i]];
    }
}
```

时间复杂度为$O(维数\times 状态数)$

## SOSDP

实际上上述前缀和相当于定义一个偏序关系$(V,\le)$，$V$是$n$维向量的集合，若$a=(a_1,a_2,...,a_n),b=(b_1,b_2,...,b_n)$

$a\le b \iff \forall (1\le i\le n) a_i\le b_i$，那么$F,G:V\rightarrow R$，其中$F(v)=a[v]$ 
$$
G(v)=\sum_{x\le v}F(x)
$$
与我们最初的问题本质是一样的。

---



回归正题。考虑dp

我们定义$f_{i,st}$表示$st$最高可变化位为$i$位的子集和(大于$i$的都固定) 。那么我们有

+ st第$i$位为0，那么$f_{i,st}=f_{i-1,st}$

+ 否则，$f_{i,st}=f_{i-1,st}+f_{i-1,st\oplus 2^i}$

显然可以优化掉第一维。这里就不写了。

---

上面的dp还是太吃操作了，还有更**简单强势**的方法理解。

上面的递推式看上去有点像上面的前缀和。事实上，这就是每一维大小为2的**n维前缀和**。

用二进制压缩集合后，对于集合$A,B$，用向量$a(a_1,a_2,\cdots,a_n),b(b_1,b_2,\cdots,b_n)$表示其二进制，我们说
$$
A\subseteq B \iff a\le b
$$
我们成功将**包含关系**转化成了和**高维前缀和一样的偏序关系**。因此：

**代码模板**

``` cpp
for(int i=0;i<(1ll<<n);++i) f[i]=a[i];
for(int i=0;i<n;++i){
    for(int j=0;j<(1ll<<n);++i){
        if((j>>i)&1) f[j]+=f[j^(1ll<<i)];
    }
}
```

时间复杂度$O(n 2^n)$

> **高维差分**：将循环反向，+变-即可。特别地，sosdp，只用变号
>
> **高维后缀和：** 倒着算即可。sosdp也可以取补集。



## 例题

### [E. Compatible Numbers](https://codeforces.com/problemset/problem/165/E)

将$a_i$看成集合的二进制表达，如果$a_i\&a_j=0$，相当于其中一个要是另外一个集合的补集。

```cpp 
int f[N];
const int U=4194303;
void solve() {
  int n;cin>>n;
  vector<int> a(n+1);
  for (int i=0;i<(1ll<<22);++i) f[i]=-1;
  for (int i=1;i<=n;++i) cin>>a[i],f[U^a[i]]=a[i];
  for (int i=0;i<22;++i) {
    for (int j=0;j<(1ll<<22);++j) {
      if (((j>>i)&1)==0 and f[j^(1ll<<i)]!=-1 and f[j]==-1) {
        f[j]=f[j^(1ll<<i)];
      }
    }
  }
  for (int i=1;i<=n;++i) cout<<f[a[i]]<<" \n"[i==n];
}
```

### [**E - Or Plus Max**](https://atcoder.jp/contests/arc100/tasks/arc100_c?lang=en) 

求$\max_{i|j\le k}a_i+a_j$$i|j\le k$，并不好处理（可以FWT，或FMT）。

于是考虑转化一下，将$i,j$独立出来，发现，如果是等号的话就简单一点，然后对所有k做一个线性的递推即可。

于是我们来考虑$\max_{i|j= k}a_i+a_j$，此时需要满足$i,j\subseteq k$，能否直接找最大值和次大值呢？是可以的，因为这是最大的解，如果$i|j<k$，也不会影响最后的答案。

就变成了对每个k求$\max_{i,j\subseteq k} a_i+a_j$，然后求一个前缀最大值即可。利用sosdp解即可。

````cpp
pair<int,int> MAX(pair<int,int> x,pair<int,int> y) {
  if (x.first<y.first) swap(x.first,y.first);
  x.second=max(x.second,y.first);
  return x;
}

void solve() {
  int n;cin>>n;
  int maxn=1ll<<n;
  vector<pair<int,int>> f(maxn,{-1,-1});
  for (int i=0;i<maxn;++i) cin>>f[i].first;
  for (int i=0;i<n;++i) {
    for (int j=0;j<maxn;++j) {
      if ((j>>i)&1) {
        f[j]=MAX(f[j],f[j^(1ll<<i)]);
      }
    }
  }
  int ans=0;
  for (int i=1;i<maxn;++i) {
    ans=max(ans,f[i].first+f[i].second);
    cout<<ans<<"\n";
  }
}
````



