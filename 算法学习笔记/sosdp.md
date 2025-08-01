# 萝莉控都能看懂的sosdp

> 萝莉控都能看懂的sosdp。

**Sum Over Subsets DP**

> 前置知识：容斥原理，莫比乌斯反演，状压dp，分治。

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
推广到$n$元，即容斥原理有
$$
F(S)=\sum_{K\subseteq S} (-1)^{|S|-|K|}G(K)
$$
即
$$
G(S)=F(S)+\sum_{K\subset S}(-1)^{|S|-|K|+1}G(K)
$$
通过枚举子集

```cpp
for(int j=st;j;j=(j-1)&st)
```

时间复杂度为$O(3^n)$。

我们对每一个元素是否存在用一个二进制位表示：

先对二维尝试
$$
G_{1,1}=F_{1,1}+G_{1,0}+G_{0,1}-G_{0,0}
$$
不难发现这就是一个二维前缀和。

如果把一个元素看成一个维度的话，发现其本质就是一个**$n$维前缀和**的问题。

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
    for(int j=0;j<pw[d];++j){
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

事实上，这就是每一维大小为2的**n维前缀和**。

用二进制压缩集合后，对于集合$A,B$，用向量$a(a_1,a_2,\cdots,a_n),b(b_1,b_2,\cdots,b_n)$表示其二进制，有
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

**高维差分**

即由$G \to F$。考虑上面的代码，显然我们只需要将循环全部反向，并变成减号就行。

**高维后缀和**

即
$$
G(K)=\sum_{K\subseteq L }F(L)\qquad (K\subseteq U)
$$
全取补集即可变成前缀和。

## 狄利克雷前缀和

$$
G(n)=\sum_{d|n} F(d)
$$

朴素的做法是

```cpp
for(int i = 1; i <= n; ++ i) {
  for(int j = 1; j * i <= n; ++ j) {
    G[i * j] += F[j];
  }
}
```

时间复杂度为$O(n\log n)$

根据算数基本定理，我们可以
$$
n=\prod_{i=1}^{t} p_i^{k_i}
$$

> 因此可以将$d|n$转化为更简单的偏序关系即
> $$
> a|b \iff \vec{k_a} \le \vec{k_b} 
> $$
> 然后就变成了高位前缀和。

有
$$
\begin{aligned}
G(n)&=\sum_{d|n} F(d)\\
&=\sum_{i_1=0}^{k_1}\cdots\sum_{i_t}^{k_t} F\left(\prod_{j=1}^{t}p_j^{i_j} \right)\\
&=\sum_{i_1=0}^{k_1}\cdots\sum_{i_t}^{k_t} F\left(\frac{n}{\prod_{j=1}^{t}p_j^{i_j}} \right)
\end{aligned}
$$
令
$$
H(n,x)=\sum_{i_1=0}^{k_1}\cdots\sum_{i_x}^{k_x} F\left(\frac{n}{\prod_{j=1}^{x}p_j^{i_j}} \right)
$$
若$k_x>0$
$$
\begin{aligned}
H(n,x+1)&=\sum_{i_1=0}^{k_1}\cdots\sum_{i_{x+1}=0}^{k_{x+1}} F\left(\frac{n}{\prod_{j=1}^{x+1}p_j^{i_j}} \right)\\
&=\sum_{i_{x+1}=0}^{k_{x+1}}  \sum_{i_1=0}^{k_1}\cdots F\left(\frac{n}{\prod_{j=1}^{x+1}p_j^{i_j}} \right)\\
&=\sum_{i_{x+1}=0}^{k_{x+1}}  H\left(\frac{n}{p_{x+1}^{i_{x+1}}},x \right)\\
&=H(n,x)+\sum_{i_{x+1}=1}^{k_{x+1}}  H\left(\frac{n}{p_{x+1}^{i_{x+1}}},x \right)\\
&=H(n,x)+\sum_{i_{x+1}=0}^{k_{x+1}-1}  H\left(\frac{\frac{n}{p_{x+1}}}{p_{x+1}^{i_{x+1}}},x \right)\\
&=H(n,x)+H\left(\frac{n}{p_{x+1}},x+1 \right)
\end{aligned}
$$

```cpp
// cnt：素数个数
for(int x = 1; x <= cnt && primes[x] <= n; ++ x) {
  for(int j = 1; j * primes[i] <= n; ++ j) {
    H[j * primes[i]] += H[j];
  }
}
```

只要$x$充分大。显然有
$$
G(n)=H(n)
$$
这个双重循环的总体工作量是：
$$
\sum_{x=1}^{\pi(n)} \Bigl\lfloor \frac{n}{p_x} \Bigr\rfloor
$$
其中 $p_x$ 表示第 $x$ 个素数，$\pi(n)$ 是不超过 $n$ 的素数个数。

- 对于固定的素数 $p$，内层循环执行次数约为 $\lfloor n/p\rfloor$。

- 因此总复杂度
  $$
    T(n)\approx \sum_{p\le n} \frac{n}{p}
    = n\sum_{p\le n}\frac1p.
  $$

- 根据数论中的素数倒数调和级数估计，有
  $$
    \sum_{p\le n}\frac1p = \ln\ln n + O(1).
  $$

于是
$$
T(n) = n\bigl(\ln\ln n + O(1)\bigr) = O\bigl(n\ln\ln n\bigr).
$$
这段代码时间复杂度为$O(n\log \log n)$。

观察这个代码实际上是就是在做**高维前缀和**。

### **狄利克雷后缀和**

$$
G(d)=\sum_{d|n} F(n)
$$

类似地可以推出
$$
H(d,x+1)=H(d,x)+H(dp_{x+1},x+1)
$$

```cpp
for(int i = 1; i <= cnt && primes[i] <= n; ++ i) {
  for(int j = n / primes[i]; j ; -- j) {
    H[j] += H[j * primes[i]];
  }
}
```

### 逆狄利克雷前缀和

就是感觉前缀和的柿子，反解$F$。

这相当于进行高维差分。

```cpp
for(int i = cnt; i ; -- i) {
  for(int j = n / primes[i]; j ; -- j) {
    H[j * primes[i]] -= H[j];
  }
}
```

### 逆狄利克雷后缀和

高维差分

```cpp
for(int i = cnt; i ; -- i) {
  for(int j = 1; j * primes[i] <= n; ++ j) {
    H[j] -= H[j * primes[i]];
  }
}
```

## 快速莫比乌斯变换（FMT，或卷积，与卷积，gcd卷积，和lcm卷积）

> 注意下面如果将集合突然换成了数字，就是用二进制数表示了集合。

FMT 可以处理按位与、按位或等的卷积。

如有集合上的函数$F,G,H$，求出
$$
H(\mathcal{S})=\sum_{\mathcal{I} \bigcup \mathcal{J}=\mathcal{S}} F(\mathcal{I}) G(\mathcal{J})
$$

> 如果我们能找到一种变化，使得
> $$
> FMT(H)_i= FMT(F)_i \times FMT(G)_i
> $$
> 就好了。

~~回忆一下这篇文章的标题~~，我们考虑做高维前缀和。

令
$$
\hat{F}_i=\sum_{k\subseteq i} F_k\quad \
$$
其他函数同理。

有
$$
\begin{aligned}
\hat{H}_i&=\sum_{k\subseteq i} H_k\\
&=\sum_{k\subseteq i} \sum_{x \or y=k}F_x G_y \\
&=\sum_{x\or y \subseteq i} F_xG_y \\
&=\left( \sum_{x\subseteq i}F_x  \right) \left( \sum_{y\subseteq i} F_y\right)   \\
&=\hat{F}_i\times \hat{G}_i 
\end{aligned}
$$
最后对做一次高维差分即可还原。

对称地，容易发现对于与卷积，做**高维后缀和**即可。

对于**gcd卷积做狄利克雷后缀和，lcm卷积做狄利克雷前缀和。**

证明完全类似。

> 实际上，gcd就是整除关系里的与，lcm就是整除关系里的或。

## 快速沃尔什变换（FWT，异或卷积）

> 实际上FWT同样可以做或卷积和与卷积，但比较难写。因此一般只会在FMT不能做的地方写，即异或卷积。
>
> 更多的性质应该会在多项式里写。

~~这里是不是跑题跑得太偏了？~~ 所以关于FWT的更多作用就不在这里写了。

定义
$$
x \circ y=\text{popcount}(x \and y) \mod 2
$$
那么有
$$
(x \circ y)\oplus (x \circ z)=x\circ (y \oplus z)
$$
这相当于

> 简要证明一下,$x \and  y$和$x \and z$同奇偶，那么右式可以在x含有的元素里面考虑，$y \oplus z$元素个数为2（奇/偶）-2（奇/偶），为偶数。



构造
$$
\hat{F}_i=\sum_{i\circ j=0} a_j-\sum_{i\circ j=1} a_j
$$
有
$$
\begin{aligned}
\hat{H}_i&=\sum_{i\circ j=0}H_j-\sum_{i\circ j=1}H_j\\
&=\sum_{i\circ j=0}\sum_{x\oplus y=j}F_x G_y-\sum_{i\circ j=1}\sum_{x\oplus y=j}F_x G_y\\
&=\sum_{i \circ(x\oplus y)=0} F_xG_y-\sum_{i \circ(x\oplus y)=1} F_xG_y\\
&=\sum_{(i \circ x)\oplus(i \circ y)=0} F_xG_y-\sum_{(i \circ x)\oplus(i \circ y)=1} F_xG_y\\
&=\sum_{(i \circ x=0)\and(i \circ y=0)} F_xG_y+\sum_{(i \circ x=1)\and(i \circ y=1)} F_xG_y-\sum_{(i \circ x=0)\and(i \circ y=1)} F_xG_y-\sum_{(i \circ x=1)\and(i \circ y=0)} F_xG_y\\
&=\left(\sum_{(i \circ x=0)}F_x\right) \left( \sum_{(i \circ y=0)} G_y \right)+\left(\sum_{(i \circ x=1)}F_x\right) \left( \sum_{(i \circ y=1)} G_y \right) -\left(\sum_{(i \circ x=0)}F_x\right) \left( \sum_{(i \circ y=1)} G_y \right)-\left(\sum_{(i \circ x=1)}F_x\right) \left( \sum_{(i \circ y=0)} G_y \right)\\
&=\left( \sum_{i\circ{x}=0} F_x-\sum_{i\circ x=1}F_x \right) \times \left( \sum_{i\circ{y}=0} G_y-\sum_{i\circ y=1}G_y \right) \\
&=\hat{F}_i \times \hat{G}_i
\end{aligned}
$$

现在问题就变成了如何快速变换，这里不多说明，应该会在多项式里补。

## FMT and FWT模板代码（含子集卷积）



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



