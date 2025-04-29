## [1.](https://ac.nowcoder.com/acm/contest/95323/H)（板/优先队列）

## 2.[**C - LCM of GCDs**](https://atcoder.jp/contests/arc124/tasks/arc124_c?lang=en)(数论、暴力)

需要知道，所有公因数是最大公因数的因数。

且[a,b]<=[ta,b]

## 3.[D. Game With Triangles](https://codeforces.com/contest/2063/problem/D)（线性规划+三分）(2000-2100/0)

## 4.[B. Cost of the Array](https://codeforces.com/contest/2059/problem/B)(思维)(1200-1300/0)

## 5.[C. Customer Service](https://codeforces.com/contest/2059/problem/C)(思维)(1600-1700/0)



## 6.[E. Beautiful Subarrays](https://codeforces.com/problemset/problem/665/E)(01Tire)

$$
a \oplus b \le (\ge) k
$$

可以考虑01Tire

给定数组A

求a[j]与a[i]$1\le i \le j-1$中大于k的个数,考虑01Tire

或者按位,注意用`__gnu_pbds::gp_hash_table`

```cpp
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> //关联容器，必加
#include <ext/pb_ds/hash_policy.hpp>     //哈希表
#include <ext/pb_ds/tree_policy.hpp>     //平衡树
#include <ext/pb_ds/trie_policy.hpp>     //字典树
#include <ext/pb_ds/priority_queue.hpp>  //优先队列
using namespace  std;
#define int long long
const int N=1e6+9;


void solve() {
  int n,k;cin>>n>>k;
  vector<int> a(n+1),b(n+1);
  for (int i=1;i<=n;++i) cin>>a[i],b[i]=a[i]^b[i-1];
  int ans=0;
  for (int i=30;i>=0;--i) {
    if (k>>i&1)continue;
    __gnu_pbds::gp_hash_table<int,int> cnt1,cnt0;
    cnt0[0]++;
    int ck=(k>>(i+1));
    for (int j=1;j<=n;++j) {
      int t=(b[j]>>(i+1))^ck;
      if (b[j]>>i&1) {
        if (cnt0[t]) ans+=cnt0[t];
        cnt1[(b[j]>>(i+1))]++;
      }else {
        if (cnt1[t])ans+=cnt1[t];
        cnt0[(b[j]>>(i+1))]++;
      }
    }
    // cout<<i<<"\n";
    // cout<<ans<<"\n";
  }
  __gnu_pbds::gp_hash_table<int,int> cnt;
  cnt[0]++;
  for (int i=1;i<=n;++i) {
    ans+=cnt[b[i]^k];
    cnt[b[i]]++;
  }
  cout<<ans<<'\n';
}
```



## 7.[**E - Maximize XOR**](https://atcoder.jp/contests/abc386/tasks/abc386_e?lang=en)(组合)

考虑给出
$$
\binom{n}{k}\le T
$$
估计k的大小,k取小的一侧

有$n\ge 2k$
$$
T\ge \frac{n}{k}\frac{n-1}{k-1}\cdots\ge2^k
$$
故
$$
k\le \log_2{T}
$$

## 8.[Tokitsukaze and Absolute Expectation](https://ac.nowcoder.com/acm/contest/95336/A)(期望,求和)

对于离散随机变量$X\in [a,b),Y \in[c,d)$

求
$$
E(|Y-X|)
$$
主要需要两类计算, 

+ 无交集的情况，
  $$
  E(Y)-E(X)
  $$

+ 完全重叠的情况，需要求和，（$c=b-a$）
  $$
  \begin{aligned}
  \sum_{a \le i< b}\sum_{a \le j < b} |j-i|&=\sum_{0 \le i< b-a}\sum_{0 \le j < b-a} |j-i|\\
  &=2\sum_{0\le i <c}\sum_{i\le j<c} (j-i)\\
  &=2\left(\sum_{0\le i< c}\sum_{i\le j<c} j^{\underline{1}} -\sum_{0\le i< c}\sum_{i\le j<c}i  \right)\\
  &=2\left(\sum_{0\le i< c}\left. \frac{j^{\underline{2}}}{2}\right|_i^c -\sum_{0\le i< c}(ci-i^2) \right)\\
  &=2\left( c\frac{c^{\underline{2}}}{2}-\frac{1}{2} \sum_{0\le i< c}i^{\underline{2}} -c\sum_{0\le i< c}i^{\underline{1}} +\sum_{0\le i <c} (i^{\underline{2}}+i^{\underline{1}}) \right)\\
  &=2\left( c\frac{c^{\underline{2}}}{2}-\frac{1}{6} c^{\underline{3}} -c\frac{1}{2} c^{\underline{2}} +\frac{1}{3}c^{\underline{3}}+ \frac{1}{2}c^{\underline{2}} \right)\\
  &=\frac{1}{3}\left( 3cc^{\underline{2}}- c^{\underline{3}} -3cc^{\underline{2}} +2c^{\underline{3}}+ 3c^{\underline{2}} \right)\\
  &=\frac{1}{3}\left(c^{\underline{3}}+ 3c^{\underline{2}} \right)\\
  &=\frac{c(c-1)(c+1)}{3}\\
  &=\frac{(b-a-1)(b-a)(b-c+1)}{3}
  \end{aligned}
  $$

## 9.[Tokitsukaze and XOR-Triangle](https://ac.nowcoder.com/acm/contest/95336/L)(异或，典)

$$
\sum_{l \le i \le r} \sum_{i \le j\le r} a_i \oplus b_j
$$

可以直接用按位看用前缀和化简推柿子做，或者

首先
$$
\sum_{l \le i \le r} \sum_{l' \le j\le r'} a_i \oplus b_j
$$
是好做的，然后
$$
[l\le i\le j\le r]=[l\le i \le r][i\le j\le n]-[l\le i\le r][r+1\le j\le n]
$$
后一半好算，前一半由于n固定了，可以预处理，再前缀和。

## 10.[E. Restorer Distance](https://codeforces.com/problemset/problem/1355/E)(三分)(2000-2100/0)

写差分函数分析。

## 11.[小L的位运算](https://ac.nowcoder.com/acm/contest/95337/C)（典）

对于n个非负数，每次选两个非0数减一最多多少次操作。
$$
\min\left(\frac{sum}{2},sum-mx \right)
$$
若mx>sum-mx，有2mx>sum，答案为sum-mx

否则可以维持mx-mi<=1，从而答案为sum/2

## 12.[**F - Damage over Time**](https://atcoder.jp/contests/abc303/tasks/abc303_f)(思维，数学)(2200-2300)

预处理攻击时间t，最大的伤害。

按$d\cdot t$排序，将时间划分为$[0,t_1),\cdots,[t_n,\infty)$，用map存，map[t]=k，表示大于t用技能k

```cpp
struct node {
  int t,d;
  bool operator<(const node& u) const {
    return t*d==u.t*u.d?d<u.d:t*d<u.t*u.d;
  }
}a[N];

void solve() {
  int n,h;cin>>n>>h;
  for (int i=1;i<=n;++i) cin>>a[i].t>>a[i].d;
  sort(a+1,a+1+n);
  map<int,int> f;
  int cur=n,p=n;
  for (;cur>=1;) {
    while (p>=1 and a[p].d<=a[cur].d) p--;
    if (p==0) {
      f[1]=cur;
    }else {
      f[(a[p].d*a[p].t+a[cur].d-1)/a[cur].d]=cur;
    }
    cur=p;
  }
  // for (const auto& [x,y]:f) {
  //   cout<<x<<" "<<y<<"\n";
  // }
  f.insert({1e18,-1});
  auto check=[&](int x) {
    auto it=f.begin();
    i128 sum=0;
    while (next(it)!=f.end() and it->first<=x) {
      int l=it->first,r=min(x,next(it)->first-1);
      i128 d=a[it->second].d;
      int t=a[it->second].t;
      i128 res=(d*l+d*min(t,r))*(min(t,r)-l+1)/2;
      if (r>t) res+=(r-t)*d*t;
      sum+=res;
      if (sum>=h) return true;
      it=next(it);
    }
    return sum>=h;
  };
  int L=0,R=1e18;
  while (L+1!=R) {
    int mid=L+R>>1;
    if (check(mid)) {
      R=mid;
    }else {
      L=mid;
    }
  }
  cout<<R<<"\n";
}
```

## 13[A. Ban or Pick, What's the Trick](https://codeforces.com/gym/104065/problem/A)（博弈论，dp）

找不到特别优秀的性质，能否直接枚举？

有多少状态？

性质有

+ 每次一定选最大的（自己或别人）；

+ 这样选完k个不再pick；

这样的话，如果知道第几轮，以及各自选的英雄数，就能确定一个局面。状态有$nk^2$种，直接记忆化搜索即可。

定义f（rond,apick,bpick）,为当前的答案，具有后效性，但无前效性，（博弈论的dp大多如此）。一般采用记忆化搜索逆推。

动态规划使用条件：

最优子结构：指问题的最优解包含其子问题的最优解，使用动态规划的基本条件；
子问题重叠：每次计算的时候需要重复用到之前的求解过程
单向有效性：指整个问题中的求解过程都只有一个方向相关，

+ 无后效性：每个阶段的求解都与之后的求解没有关系“无后效性”。
+ 无前效性：如果只存在后效行，无前效性质，则可以通过逆序的动态规划进行

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
using i64 = long long;
using i128 = __int128;
using u64 = unsigned long long;
const int mod = 998244353;
const int N = 1e5 + 9;
const int iinf = 1e9;
const i64 linf = 1e18;
int f[N<<1][15][15];
bool vis[N<<1][15][15];

void solve() {
  int n,k;cin>>n>>k;
  vector<int> a(n+1),b(n+1);
  for (int i=1;i<=n;++i) cin>>a[i];
  for (int i=1;i<=n;++i) cin>>b[i];
  sort(a.begin()+1,a.end(),greater<int>());
  sort(b.begin()+1,b.end(),greater<int>());
  //已经进行了r轮，a pick x, b pick y 后面的答案。
  function<int(int,int,int)> work=[&] (int r,int x,int y)->int {
    if (r==2*n) return 0ll;
    if (vis[r][x][y]) return f[r][x][y];
    vis[r][x][y]=1;
    int na=r/2-y+x+1,nb=(r+1)/2-x+y+1;
    if (r%2==0) {
      // max
      // pick
      int res=-linf;
      if (na>=1 and na<=n and x<k)  res=max(res,a[na]+work(r+1,x+1,y));
      // ban
      if (nb>=1 and nb<=n) res=max(res,work(r+1,x,y));
      f[r][x][y]=res;
      return res;
    }else {
      // min
      // pick
      int res=linf;
      if (nb>=1 and nb<=n and y<k) res=min(res,work(r+1,x,y+1)-b[nb]);
      //ban
      if (na>=1 and na<=n) res=min(res,work(r+1,x,y));
      f[r][x][y]=res;
      return res;
    }
  };
  cout<<work(0,0,0);
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int Case = 1;
  // cin >> Case;
  while (Case--) solve();
  return 0;
}
```

## 14.[小L的字符串翻转](https://ac.nowcoder.com/acm/contest/95337/D)（数学，思维）

**统计一个01串，各个长度子串的同“色 ”块数**

用调和级数优化，可以简单的到O(nlogn)

否则考虑逆向计算。

对于一段相同的串，对长度k会减少多少呢?

单独考虑最后一段。

每一段开头有S%k=0，设其为$s_1,s_2,\cdots$ ，区间为$[s_1,s_2)...$

对于串$[l,r]$，答案为$(r+1)/k-(l+k-1)/k$

即$r/k-(l+k-1)/k+(r+1 \mod k=0)$

代码

```cpp
  vector<int> ans(n+1);
  for (int i=0;i<n;) {
    int l=i,r;
    while (i+1<n and  s[i+1]==s[i]) ++i;
    r=i;
    if (r+1==n) for (int k=2;k<=n;++k) ans[k]-=(r/k-(l+k-1)/k+1);
    else for (int k=2;k<=r-l+1;++k) ans[k]-=((r+1)/k-(l+k-1)/k);
    i=r+1;
  }
```

时间复杂度分析
$$
O\left(\sum_{k=1}^{x} sz-1\right)=O(n)
$$

## 15.[小L的构造](https://ac.nowcoder.com/acm/contest/95337/L)(数论，构造)

**缩小范围进行匹配**

如果要把差距很大的两个数字放在一起很难找。

**考虑能否对相近的一些数字配对。**

**6具有两个不同的素因数**

相邻3个，显然不行，考虑6个，能否实现。

相邻一定互质，相邻奇数一定互质（x+2-x=2），对模6的情况讨论有

$2,3|6n$，$2|2(3n+1)$ ，$3|3(2n+1)$,$2|2(3n+2)$ ，

考虑将$2,4$放一起，$3,6$放一起，

而$6n+4-6n-1=3$ 故$\gcd(6n+4,6n+1)\le 3$显然不会是2，3，故互质。

同理$6n+5-6n-3=2$显然互质，因此。

每6个一组可以将$1,2,4$，$3,5,6$放一起。

那么若最后剩余3,4,5个怎么处理。此时显然只需要匹配一个即可。

3**无解**，

4，5 （1，2，4）即可。

在n=6k+3，需要另外分析。

先拿9个出去配对。（1，2，4） （3，7，9） （5，6，8）

这里与9配对显然不够好，12，没意义，15...都没6的性质好。

## 16[H. 小鸡的排列构造](https://ac.nowcoder.com/acm/contest/95338/H)(构造,排列)

容易猜到一定有解。样例没有不可能的，而且似乎限制并不特别多。

题目说了同奇偶，可能两类构造方法不同。

全是偶数，直接反着排列即可。（告诉我们似乎限制比较松）。

奇数时，考虑限制最多的时候的情况。

最小的区间是3，而3只要是错排列即可。（2，3，1）（3，1，2）

是否可拓展呢。

容易拼凑出来（2，3，1）+（3，1，2）+（2，3，1）=（4，5，2，3，1）->（1，2，3，4，5）似乎可行。

构造方案是从（2，3，1）向前依次填数。

（2，3，1）前加数时+2个，为（5，2，3，1），

（3，1，2）前加数时（4，5，2，3，1）；

因此为（n-1，n，n-3，n-2，……）

考虑证明这样交错拼接一定满足条件，

一个拼起来显然成立，

若小于等于k个拼起来都成立，

若拼完长度是偶数，显然成立。

若是奇数，只需证明整体成立，分析奇偶即可。

## 17.[E. Level Up](https://codeforces.com/problemset/problem/1997/E)(根号分治/树状数组)

对于k较小时,可以暴力预处理,k大的时候等级最高比较小可以枚举每一等级的区间,二分求解.

---

直接处理不太可能,往往需要预处理一些东西,来简化.

考虑对固定$i$或$k$,有无比较好的性质.

如固定k,那么对于每一个i,若逃跑需要判断前面是否有至少kai个被攻击,以目前的信息,并不好判断,这里希望能有一个前面的位置关于k的一个被攻击的性质。

那么固定i,判断需要依赖k.并不好处理.再考虑有没有其他性质呢.实际上答案只有2个,是否存在一个分界点呢.

我们发现,k减小会导致到达i的等级变大(或相等),而且对于i,到达该位置的等级大于$a_i$时逃跑.具有单调性.k越小,越容易跑

考虑求出每一个位置被攻击的最小k.这一信息可以在给定k的情况下判断后面的位置是否被攻击。考虑二分然后用树状数组维护即可.时间复杂度$O(n\log n \log{\max{a}})$ a的大小是2e5,满足.

## 18.[L. A Game On Tree](https://codeforces.com/gym/105459/problem/L)（概率dp）

**常规套路算贡献**。总的选择数知道，计算所有可能的公共路径的平方和即可。

即求
$$
\sum_{e_i是公共路径的边}(|e_1|+|e_2|+...)^{2}= \sum|e_i|^2+\sum_{i,j}|e_i||e_j|
$$


这里权值是1，那么分别求两部分即可，第一部分，即使求$e_i$作为公共路径的种类从它的两个端点向外各选择2个点即可。

第二种情况比较难选，直接枚举两条边太慢。考虑**转化成枚举一个点，**，可以**枚举其LCA**，

定1为根

对于一个点，有多少种方法选出两条边，且这两条边端点的LCA是它。设为u

若在同一子树，那么一条已经固定，只需在这子树选另外一条边。然后选点，选边可以等价为选一个点，然后再在其子树选2个点。注意不要选重复，同时需要乘2。因为无序

否则不同子树。每个两个子树内各选两个点即可。

化简一下就可以了。再看需要什么东西dfs处理即可。

或者考虑求
$$
\sum_{p_1}\sum_{p_2}\left( \sum_{e}[e\in p_1][e\in p_2] \right)^{2}
$$
转化为求
$$
\begin{aligned}
&\sum_{p_1}\sum_{p_2} \sum_{e,f}[e\in p_1,p_2][f\in p_1,p_2]\\
&=\sum_{e,f}\sum_{p_1}[e\in p_1][f\in p_1] \sum_{p_2} [e\in p_2] [f\in p_2]\\
&=\sum_{e,f}\left(\sum_{p}[e,f\in p] \right)^2
\end{aligned}
$$
设
$$
A_{e,f}=\sum_{p}[e,f\in p]
$$
即包含$e,f$的路径数。

然后分$e=f$，$e\neq f$ 和上面一样了。



## 19.[E. Omkar and Forest](https://mirror.codeforces.com/contest/1536/problem/E)(计数,思维)

注意0是特殊的。考虑单独算0。那么假设有一些位置为0后，其余不为0有多少种方案呢。

首先距离0为1的地方填1，那么距离0为2的位置填的数应该大于1小于等于2，故位2，（均为最小距离）利用归纳法容易证明填的数只能是最小距离。

若前k个成立，则d=k+1时，一定与一个d=k相邻，故其只能填k,k+1,k-1,若填k，则其相邻的位置必有k-1，由于其距离已经填k-1的位置的距离一定大于等于2，故这个k-1一定是未填部分填的，那么就一定得新填0.k-1类似，故只能填k+1.证毕。

因此只有一种方案。设有k个#，答案为$2^k$，如果没有0要减去1(空集)。 

## 20.[**B - Hamiltonish Path**](https://atcoder.jp/contests/agc013/tasks/agc013_b?lang=en) （构造，图论）

注意题目It can be proved that such a path always exists. 而不是给你一定存在的数据。说明这个性质比较容易满足

---



找不到什么好的性质，能够直接找到。考虑**逐步调整。**

若其中一个端点不满足，考虑任选一个点接在后面，此时点不会重复，最多进行n-1次。每条边询问一次。

可用双端队列维护。

## 21.[E - Sorted and Sorted](https://atcoder.jp/contests/arc097/tasks/arc097_c?lang=en)(DP，逆序对)

题意

两组数混合在一起，交换相邻位置，使其各自有序

---

如果没用分类就是求逆序数，因为初末状态一定。因此如果我们知道末态就是求逆序对数（这里指球的位置关系）。

而对逆序数计数，可以从左到右枚举，对于放第i个时，计算前面的放好的一开始在它右边的个数。

设$f_{i,j}$为放置前i个白球，j个黑球的最小代价，$costw_{i,j}$为放置前i个白球，j个黑球后放入第i+1个白球产生的逆序数。
$$
f_{i,j}=\min(f_{i-1,j}+costw_{i-1,j},f_{i,j-1}+costb_{i,j-1})
$$
如何计算costw，$costw_{i,j}$为前i个白球和j个黑球，在第${i+1}$个白球右边的数。

有
$$
costw_{i,j}=costw_{i,j-1}+posb_{j}>posw_{i+1}
$$
而$costw_{i,0}$再单独算即可。

 

## 22.[E. Natasha, Sasha and the Prefix Sums](https://codeforces.com/problemset/problem/1204/E)(折线图，组合数学，计数)

由+1，-1组成的前缀和，容易想到**折线图**（卡特兰序列）。

对于**特定的最大前缀和**不好控制，考虑求**最大大于等于k**的折线。

其一定会与等于k这条线有交点，把他对称一下就是求$(0,2k)$到$(n+m,n-m)$的路径数。

有
$$
\binom{n+m}{\frac{n+m+(n-m)-2k}{2}}=\binom{n+m}{n-k}
$$
差分一下即可。

## 23.[G. Bicycles](https://codeforces.com/problemset/problem/1915/G)(分层图最短路)

## 24[.J. Middle Race](https://codeforces.com/gym/104065/problem/J)(交互,博弈,二分)

先考虑一定有解。guess结论

容易想到去比逼近$\frac{sum}{3}$。为什么一定有解，若$X$是最其线性组合接近$\frac{sum}{3}$的整数，

那么设其为$\frac{sum}{3}-d$,若是中值，不妨设$d>0$，若$Y,Z>X$，那么有$X+Y+Z\ge sum+d$

因此如何求得$(a,b,c)$最接近某个数的线性组合呢。知道其最和一定，相当于只有两个参数，枚举一个，二分一个即可。

## 25.[D. Eating](https://codeforces.com/contest/2064/problem/D)（异或， 01Tire，思维）(1800-1900/0)

**解法一:**

设$suf[t]$为其后缀异或和。

题目等价于求最大的$t$ $suf[t] \oplus x<w[t-1]$,对于$a \oplus x<$c，可以考虑用**01Tire**。

a是存在字典树里，c是定值的话很容易求。但此时显然不满足，因为c是变化的。考虑转化一下。

发现我们可以离线处理询问，将x存在字典树上，然后对每一个$t$，处理一下，打上标记。最后查询即可。

**解法二:**

注意到如果前面的数最高位小于当前的数字，就可以吃，并且最高位不变。并且最高位大于该数字直接结束，否则最高位减小，故时间复杂度合理。 那么按位考虑即可。

## 26.[D. Happy New Year](https://codeforces.com/problemset/problem/1313/D)（状压dp/扫描线）(2400-2500/0)

$k\le 8$ 应该很关键。想到可能是为了使用$dp$，但想不到状态转移方程。

---

因为$k$过于小，想到状压dp。转移方程就能写了。前面的左端点暴力维护即可。类似扫描线的写法。

当前为左端点，记录了前面左端点为cnt个后，枚举状态更新。若为右端点，看是否在前面出现然后讨论即可。代码细节较多，注意数组大小。

## 27.[B. Present](https://codeforces.com/problemset/problem/1322/B)(双指针，异或)(2000-2100/0)

求
$$
\oplus_{1 \le i \le n} \oplus_{i+1 \le j \le n} (a_i+a_j)
$$
拆分成两个无关的区间似乎没什么用。

---

考虑按位计算，固定i，只与前i-1个数有关，并且算第j位，只与前j位有关。并且可以求出2个范围，使得这一位为1。排序后双指针即可。**练习双指针**



## 28.[C. Instant Noodles](https://codeforces.com/problemset/problem/1322/C)(数论，思维，图论？)(2200-2300/0)

容易想到看成映射，故就是一个数论问题。若$f: L\rightarrow R$ 维护了点的信息不好处理集合关系。

---

但如果考虑点集。就比较好合并，因此考虑左侧一个点集对应的右侧的权值。那么答案就将是合并后的右侧权值的组合的最大公因数。容易猜想其就是单个值的最大公因数。(因为不能保证能选出每一个单个的，所以证明不太容易，答案证明如下)

设所有权值除以单个值的gcd，后答案将变为1。若不然。存在k>1，整除所有f(S)，首先所有权值和一定能取到。故只用考虑k|sum的情况。注意到一定有 单个值不能整除k（gcd=1），我们选择对应点集最小的一个（度最小），然后不选这个点集的所有点，构成的值一定 k一定不整除它。代码好写。

应set维护点集，map维护这个映射即可。注意排除空集。

## 29.[D. Ehab the Xorcist](https://codeforces.com/problemset/problem/1325/D)(异或,数学)(1700-1800/0)

猜想长度小于等于3,利用$a+b=a\oplus b+a\& b$ 

## 30.[B. Edge Weight Assignment](https://codeforces.com/problemset/problem/1338/B)(图论,结论(guess),dp?)(1800-1900/0)

## (X)31.[E. Mycraft Sand Sort](https://codeforces.com/contest/2064/problem/E)(思维，计数,线段树二分?,并查集+链表)

注意到c=c',可以交换相同颜色(因为可以从终局倒退没做颜色的值(仅仅只是排序)).对于颜色相同的值，能交换除非中间的值都小于较小者。

那么隔离出来每一种颜色，每一个元素都有一个范围可以选择。这样的题一般**先考虑限制最紧的情况**。范围可以使用线段树维护。但比较麻烦。

我们从小到大枚举，**计算贡献**，考虑到大的值会可能包含小的值，即如$a<b<c$ ，知道a能和b，c换，那么b也能和c换。考虑使用并查集维护。 首先相邻同色的可以交换。将其合并。初始设定边界为$(i-1,i+1)$，先不管是否同色，如何保证边界的大小呢。

## 32.[C. Perfect Triples](https://codeforces.com/problemset/problem/1338/C)(异或,构造,思维,打表找规律)(2200-2300)

最小的元素的规律容易发现,第二小(为偶数位)的打出2进制观察规律即可.

---

b的范围已知,实际上要求出其排列.字典序尽量小,即是求出**一个字典序最小的排列异或其序号得到另一个排列**.优先考虑字典序.一种想法是分块,缩小范围.观察到0,1,2,3,可以用0,2,3,1,考虑继续看2位.那么4为的情况,有16个数,而前两位最多4个数,故第2个两位也必须有4种数,并且为了字典序小,必须连续.因此依旧填0,2,3,1,具体可用数学归纳法证明.	

## 33.[B. Orac and Medians](https://codeforces.com/problemset/problem/1349/B)(guees,思维)(2000-2100/0)

## 34.[C. Choosing flowers](https://codeforces.com/problemset/problem/1379/C)(二分,贪心,思维)(2000-2100/0)

注意到选b的只可能有一个,那么枚举哪一个选b然后前缀和二分,替换即可.

## 35.[D. Problem about GCD](https://codeforces.com/contest/2043/problem/D)(guess,数论,结论)(1800-1900/0)

给定一个区间求其距离差距最大的一对互质的数.

---

考虑转变思路,求给定一个数,与他互质的数之前的距离多大.设连续x个都与其不互质,我们只考虑质因数,知道最坏的情况可能有

2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47质因数,其中不互质的数的个数为
$$
x*(1-\frac{1}{2})......
$$
可以计算出x小于等于7.因此得出结论,

**在[1e18]的范围下,一个数最多与连续7个数不互质**

## 36.[E. Matrix Transformation](https://codeforces.com/contest/2043/problem/E)(图论,思维,3色dfs判环)

按位看,转化为01矩阵.问题在于难点在于行列都有的情况,如何选择.

---

考虑**化简操作**,你只可以把一行转化成0或一列转化成1.然后发现这显然和操作的顺序有关,不行当且仅当操作形成一个循环.(注意是按位才有必须进行操作的说法,而按位的正确性显然)

考虑建图,然后判环.只判必要进行操作的环.

注意我们只需要考虑改变了的.所以应该一位一位建图.因为可能形成的环中有一位不必要进行.

---



考虑逆序操作，我们每次可以将目标矩阵的全 0 行或全 1 列换成任何数，判断能否得到当前矩阵。

我们每次将目标矩阵的一个全 0 行或全 1 列删去，同时删去当前矩阵的对应行/对应列，不断进行此操作，若最后两个矩阵相同则可以完成目标，否则不可以。正确性不难证明。

## 37.[M. Matrix Construction](https://codeforces.com/gym/105588/problem/M)(构造,签到)(1600-1700/0)

矩阵,考虑行,列,对角线.

## 38.[H. Horizon Scanning](https://codeforces.com/gym/105588/problem/H)(game)(1600-1700/0)

## 39.[C. Trapmigiano Reggiano](https://codeforces.com/contest/2071/problem/C)(构造)(1600-1700/0)

按深度考虑可以保证dep大于当前操作的深度,

或逆dfs序

## 40.[D2. Infinite Sequence (Hard Version)](https://codeforces.com/contest/2071/problem/D2)(数学)(2200-2300/0)

先考虑能否直接计算,似乎很困难.而数据的范围也比较大.

---

考虑类似继续一个点,能否进行**递归计算**前缀和.我们希望从求单个点的函数找出性质.令p为前n个异或和.

观察
$$
\begin{aligned}
&a_{2n}=a_{2n+1}=p\\
&a_{2n+2}=a_{2n+3}=p\oplus a_{n+1}\\
&\vdots\\
&a_{2n+6}=a_{2n+7}=p\oplus a_{n+3}
\end{aligned}
$$
容易想到可以计算$4k+1$的前缀和,

预处理$[1,2n)$的值,然后计算[2n,4k+1]的值第二部分奇偶部分和相同.以偶数部分为例子
$$
evensum=p+p\oplus a_{n+1}+\cdots +p+p\oplus a_{2k}
$$
令
$$
e=\sum \limits _{n+1 \le i \le 2k,i\text{是偶数}} a_i
$$


即
$$
sum=\begin{cases}
e  ,&p=0\\
(4k-2n)-e ,&p=1
\end{cases}
$$
于是我们分开处理奇数和偶数

有
$$
epre_m=sum+epre_{2n-1}\\
opre_m=sum+opre_{2n-1}
$$
对sum进行一些变化,然后递归处理.

## 41.[**F - Smooth Occlusion**](https://atcoder.jp/contests/abc395/tasks/abc395_f) (二分/贪心)(1600-1700/0)

假设第二个条件已经满足,那么怎么才能代价最小

假设H已经确定,可以直接计算.(不需要再考虑第二个条件).

故H取最大即可.然后计算满足第二个条件的最小操作次数,即是

**对于一个数组,操作最小次数(每次选一个减少1),让他们相邻的差距全都小于k**

贪心思路:由于最小值不会改变,那么我们每次选最小值,并更新其相邻位置的答案,那么我们可以确定当前最小值已经和这个数组没有关系了,重复操作直到全部确定,用set维护即可.

---

注意到,若将高度设为H可以满足条件,那么将H减小也可以满足条件,那么考虑二分找到最大的H.

对于给定的h,可以给上牙确定一个范围,然后i的范围对i+1有影响,.....

---

## 42.[Removing Leaves](https://codeforces.com/problemset/problem/1385/F)(代码/换根dp)(2200-2300/0)

**用set要将二维偏序关系定义完整,** **dp要注意什么时候才能变成叶子**

## 43. [Stoned Game](https://codeforces.com/problemset/problem/1396/B)(game/贪心)(1800-1900/0)

事实上并不算博弈论,不需要考虑策略,每次取两个,能操作的次数是固定的,贪心计算,最后有无剩余即可.

## 44. [Monster Invaders](https://codeforces.com/contest/1396/problem/C)(dp)(2200-2300/0)

代码细节较多.最后一步用暴力转移比较好.



## 45.[Divide Square](https://codeforces.com/contest/1401/problem/E)(数组数组/划分区域)(2400-2500/0)

划分区域,考虑找交点个数.g

## 46. [Reverse and Swap](https://codeforces.com/contest/1401/problem/F)(线段树/思维)(2400-2500/0)

**数组越界**

## 47.[Fixed Point Removal](https://codeforces.com/problemset/problem/1404/C)(线段树二分/二维数点,离线处理区间问题)(2200-2300/0)

已知每次询问的O(n)做法,区间问题可以尝试离散处理.

**找到一个端点固定后可以比较快速计算一个区间的答案,并且这个端点可以向某一个方向更新.**

---

二维偏序关系考虑**二维数点**,如果不满足差分的性质,可以维护每个左端点开始的值,并用当前的值更新.

注意树状数组可以找前缀和第k大.

## 48.[最快相同](https://ac.nowcoder.com/acm/contest/102742/F)(数论/exgcd)(2200-2300/0)

由于可以任意选择,假设减去的总量为kx,那么只要一个数没被减去超过x次就一定可以实现.

换句话说,题目就等价于找最大的最终的数x.

**注意精度问题.**

## 49.[New Roads](https://codeforces.com/contest/746/problem/G)(构造/图论)(2000-2100/0)

可以先让叶子最多,然后构造.最少不好做(甚至不好确定什么时候最小)

---

## 50.[Shortest Path](https://codeforces.com/problemset/problem/59/E)(最短路/dp)(2000-2100/0)

注意n很小,而禁止的与边有关,于是可以计算保存最后一条边的最短路.
