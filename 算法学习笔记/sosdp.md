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

特别地，sosdp直接变号即可。

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

## 快速莫比乌斯变换（FMT，或卷积，与卷积，gcd卷积，lcm卷积，子集卷积）

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

### 子集卷积

$$
H_i=\sum_{j \or k=i ,j\and k=0} F_j G_k
$$

注意到$j \and k= 0 \iff |j|+|k|=|j\or k|$

如果我们将$F_{j}$根据 $|j|$分开，即这3个函数，每个划分为$n$个函数。从而有
$$
H_z=\sum_{x+y=z}F_x or G_{y}
$$
将每一个 $H_z$求出来即可。

## 快速沃尔什变换（FWT，异或卷积）

> 实际上FWT同样可以做或卷积和与卷积，但比较难写。因此一般只会在FMT不能做的地方写，即异或卷积。
>

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

现在问题就变成了如何快速变换。

分治构造。
$$
FWT(A)=merge(FWT[A_0]+FWT[A_1],FWT[A_0]-FWT[A_1])
$$
$A_0,A_1$会去掉当前位。

若当前位为0，则根本不影响答案。

若为1，对后半部分操作时，去掉这一位应该取个负号。

## FMT and FWT模板代码

```cpp
template<class T>
struct Convo {
  // 快速幂
  long long qpow(long long a, long long b) const {
    long long res = 1;
    while (b) {
      if (b & 1) res = res * a % mod;
      a = a * a % mod;
      b >>= 1;
    }
    return res;
  }

  // SOS 前缀和
  void sos_prefix(vector<T>& f, int nx) {
    int N = 1 << n;
    for (int i = 0; i < n; ++i) {
      for (int mask = 0; mask < N; ++mask) {
        if (mask & (1 << i)) {
          f[mask] = (f[mask] + f[mask ^ (1 << i)]) % mod;
        }
      }
    }
  }
  // SOS 逆
  void sos_inverse(vector<T>& f, int n) {
    int N = 1 << n;
    for (int i = 0; i < n; ++i) {
      for (int mask = 0; mask < N; ++mask) {
        if (mask & (1 << i)) {
          f[mask] = (f[mask] - f[mask ^ (1 << i)] + mod) % mod;
        }
      }
    }
  }
  // SOS 后缀和
  void sos_suffix(vector<T>& f, int n) {
    int N = 1 << n;
    for (int i = 0; i < n; ++i) {
      for (int mask = 0; mask < N; ++mask) {
        if (!(mask & (1 << i))) {
          f[mask] = (f[mask] + f[mask | (1 << i)]) % mod;
        }
      }
    }
  }
  // SOS 后缀逆
  void sos_suffix_inverse(vector<T>& f, int n) {
    int N = 1 << n;
    for (int i = 0; i < n; ++i) {
      for (int mask = 0; mask < N; ++mask) {
        if (!(mask & (1 << i))) {
          f[mask] = (f[mask] - f[mask | (1 << i)] + mod) % mod;
        }
      }
    }
  }

  // 线性筛及 Möbius
  vector<int> primes, mu;
  vector<bool> is_comp;
  void init_sieve(int N) {
    mu.assign(N + 1, 1);
    is_comp.assign(N + 1, false);
    for (int i = 2; i <= N; ++i) {
      if (!is_comp[i]) {
        primes.push_back(i);
        mu[i] = -1;
      }
      for (int p : primes) {
        if ((long long)i * p > N) break;
        is_comp[i * p] = true;
        mu[i * p] = (i % p == 0 ? 0 : -mu[i]);
        if (i % p == 0) break;
      }
    }
  }
  // Dirichlet 前缀和
  void dirichlet_prefix(vector<T>& F, int n) {
    for (int p : primes) {
      if (p > n) break;
      for (int i = 1; i * p <= n; ++i) {
        F[i * p] = (F[i * p] + F[i]) % mod;
      }
    }
  }
  // Dirichlet 前缀逆
  void dirichlet_prefix_inverse(vector<T>& G, int n) {
    for (int i = (int)primes.size() - 1; i >= 0; --i) {
      int p = primes[i];
      if (p > n) continue;
      for (int j = 1; j * p <= n; ++j) {
        G[j * p] = (G[j * p] - G[j] + mod) % mod;
      }
    }
  }
  // Dirichlet 后缀和
  void dirichlet_suffix(vector<T>& F, int n) {
    for (int p : primes) {
      if (p > n) break;
      for (int i = n / p; i >= 1; --i) {
        F[i] = (F[i] + F[i * p]) % mod;
      }
    }
  }
  // Dirichlet 后缀逆
  void dirichlet_suffix_inverse(vector<T>& H, int n) {
    for (int i = (int)primes.size() - 1; i >= 0; --i) {
      int p = primes[i];
      if (p > n) continue;
      for (int j = n / p; j >= 1; --j) {
        H[j] = (H[j] - H[j * p] + mod) % mod;
      }
    }
  }

  // OR 卷积
  void OR(vector<T>& F, vector<T>& G, int n) {
    sos_prefix(F, n);
    sos_prefix(G, n);
    int N = 1 << n;
    for (int i = 0; i < N; ++i) F[i] = (long long)F[i] * G[i] % mod;
    sos_inverse(F, n);
  }
  // AND 卷积
  void AND(vector<T>& F, vector<T>& G, int n) {
    sos_suffix(F, n);
    sos_suffix(G, n);
    int N = 1 << n;
    for (int i = 0; i < N; ++i) F[i] = (long long)F[i] * G[i] % mod;
    sos_suffix_inverse(F, n);
  }
  // GCD 卷积
  void GCD(vector<T>& F, vector<T>& G, int n) {
    dirichlet_suffix(F, n);
    dirichlet_suffix(G, n);
    for (int i = 1; i <= n; ++i) F[i] = (long long)F[i] * G[i] % mod;
    dirichlet_suffix_inverse(F, n);
  }
  // LCM 卷积
  void LCM(vector<T>& F, vector<T>& G, int n) {
    dirichlet_prefix(F, n);
    dirichlet_prefix(G, n);
    for (int i = 1; i <= n; ++i) F[i] = (long long)F[i] * G[i] % mod;
    dirichlet_prefix_inverse(F, n);
  }
  // 子集卷积
  void SUBSET(vector<T>& A, vector<T>& B, int n) {
    int N = 1 << n;
    vector<vector<T>> f(n + 1, vector<T>(N)), g(n + 1, vector<T>(N));
    for (int mask = 0; mask < N; ++mask) {
      int pc = __builtin_popcount(mask);
      f[pc][mask] = A[mask];
      g[pc][mask] = B[mask];
    }
    for (int i = 0; i <= n; ++i) {
      sos_prefix(f[i], n);
      sos_prefix(g[i], n);
    }
    vector<vector<T>> h(n + 1, vector<T>(N));
    for (int mask = 0; mask < N; ++mask) {
      for (int i = 0; i <= n; ++i) {
        long long sum = 0;
        for (int j = 0; j <= i; ++j) {
          sum += (long long)f[j][mask] * g[i - j][mask] % mod;
        }
        h[i][mask] = sum % mod;
      }
    }
    for (int i = 0; i <= n; ++i) sos_inverse(h[i], n);
    for (int mask = 0; mask < N; ++mask) A[mask] = h[__builtin_popcount(mask)][mask];
  }

  // FWT 异或卷积
  void FWT(vector<T>& F, int n, bool inverse = false) {
    int N = 1 << n;
    for (int len = 1; len < N; len <<= 1) {
      for (int i = 0; i < N; i += len << 1) {
        for (int j = 0; j < len; ++j) {
          T u = F[i + j], v = F[i + j + len];
          F[i + j] = (u + v) % mod;
          F[i + j + len] = (u - v + mod) % mod;
        }
      }
    }
    if (inverse) {
      long long inv = qpow(N, mod - 2);
      for (int i = 0; i < N; ++i) F[i] = (long long)F[i] * inv % mod;
    }
  }
  // 异或卷积接口
  void XOR(vector<T>& F, vector<T>& G, int n) {
    FWT(F, n, false);
    FWT(G, n, false);
    int N = 1 << n;
    for (int i = 0; i < N; ++i) F[i] = (long long)F[i] * G[i] % mod;
    FWT(F, n, true);
  }
};
```



## 例题

### [E. Compatible Numbers](https://codeforces.com/problemset/problem/165/E)

将$a_i$看成集合的二进制表达，如果$a_i\&a_j=0$ 。如果我们对$a_i$异或全集，那么满足条件的就会是其子集。希望合并其所有子集的信息，可以利用SOSDP的思想。

```cpp
int f[4200000];
const int U=4194303;
void solve() {
  int n;cin>>n;
  vector<int> a(n+1);
  for (int i=0;i<(1ll<<22);++i) f[i]=-1;
  for (int i=1;i<=n;++i) cin>>a[i],f[a[i]]=a[i];
  for (int i=0;i<22;++i) {
    for (int j=0;j<(1ll<<22);++j) {
      if ((j>>i)&1 and f[j^(1ll<<i)]!=-1 and f[j]==-1) {
        f[j]=f[j^(1ll<<i)];
      }
    }
  }
  for (int i=1;i<=n;++i) cout<<f[U^a[i]]<<" \n"[i==n];
}
```



### [**E - Or Plus Max**](https://atcoder.jp/contests/arc100/tasks/arc100_c?lang=en) 

我们只需要考虑等于$K$的情况，而$i,j$为其子集。那么显然用sosdp维护其最大值，次大值即可。

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

### [E. Vowels](https://codeforces.com/problemset/problem/383/E)

用二进制表示。合法单词当且仅当&不为0。不太好算，但可以直接计算不合法的单纯，就和第一题一样了。

### [D. Jzzhu and Numbers](https://codeforces.com/problemset/problem/449/D)

计算and起来等于某个数比较困难，考虑计算其后缀和，即and起来的数是x的超集，然后再差分即可。而这个东西可以通过计算包含x的元素个数简单的计算。

```cpp
const int U=1048575;
void solve() {
  int n;cin>>n;
  vector<i64> f(1100000,0),p(n+1,0);
  p[0]=1;
  for (int i=1;i<=n;++i) p[i]=2ll*p[i-1]%mod;
  for (int i=1;i<=n;++i) {
    int x;cin>>x;
    f[x]++;
  }
  Convo<i64> conv;
  conv.sos_suffix(f,20);
  for (int i=0;i<(1ll<<20);++i) f[i]=(1ll*p[f[i]]-1ll+mod)%mod;
  conv.sos_suffix_inverse(f,20);
  cout<<f[0]<<"\n";
}
```

### [E. Boolean Function](https://codeforces.com/problemset/problem/582/E)

对于这种未确定的表达式计数问题，我们一般可以建立表达式树。然后在树上dp。

定义$dp[i][j]$为当前第$i$个节点，n个答案为j的方案数。有
$$
dp[i][j]=\sum_{x \odot y=j} dp[a][x]\cdot dp[b][y]
$$
再利用FMT计算即可。

```cpp
const int T=16;
vector<int> g[300];
int fa[300];
char ch[400];
i64 f[400][1ll<<T];

void solve() {
  string s;cin>>s;
  int now=1,tot=1;
  for (auto c:s) {
    if (c=='(') {
      g[now].push_back(++tot),fa[tot]=now,now=tot;
    }else if (c==')') {
      now=fa[now];
    }else {
      ch[now]=c;
    }
  }
  int n;cin>>n;
  vector<array<bool,5>> Info(n);
  int res=0;
  for (int i=0;i<n;++i) {
    auto &[a,b,c,d,r]=Info[i];
    cin >> a >> b >> c >> d >> r;
    if (r) res|=(1ll<<i);
  }
  int maxn=1ll<<n;
  Convo<i64> conv;
  function<void(int)> dfs=[&](int x){
    if (g[x].empty()) {
      if (ch[x]=='?') {
        for (int i=0;i<4;++i) {
          int S=0;
          for (int j=0;j<n;++j) if (Info[j][i]) S|=(1ll<<j);
          f[x][S]++,f[x][((1ll<<n)-1)^S]++;
        }
      }else {
        int opt=0,t=ch[x]-'A';
        if (islower(ch[x])) opt=1,t=ch[x]-'a';
        int S=0;
        for (int i=0;i<n;++i) if (Info[i][t]^opt) S|=(1ll<<i);
        f[x][S]=1;
      }
      return ;
    }
    int a=g[x][0],b=g[x][1];
    dfs(a),dfs(b);
    if (ch[x]=='&' or ch[x]=='?') {
      vector<i64> F(maxn),G(maxn);
      for (int i=0;i<maxn;++i) F[i]=f[a][i],G[i]=f[b][i];
      conv.AND(F,G,n);
      for (int i=0;i<maxn;++i) f[x][i]=(f[x][i]+F[i])%mod;
    }
    if (ch[x]=='|' or ch[x]=='?') {
      vector<i64> F(maxn),G(maxn);
      for (int i=0;i<maxn;++i) F[i]=f[a][i],G[i]=f[b][i];
      conv.OR(F,G,n);
      for (int i=0;i<maxn;++i) f[x][i]=(f[x][i]+F[i])%mod;
    }
  };
  dfs(1);
  cout<<f[1][res]<<"\n";
}
```

### [P4717 【模板】快速莫比乌斯/沃尔什变换 (FMT/FWT)](https://www.luogu.com.cn/problem/P4717)

直接套板子。

### [P6097 【模板】子集卷积](https://www.luogu.com.cn/problem/P6097)





# 参考文献

[Troverld的博客](https://www.cnblogs.com/Troverld/p/14601821.html)

[OIwiki](https://oi.wiki/math/poly/fwt/#%E5%90%8C%E6%88%96%E8%BF%90%E7%AE%97)
