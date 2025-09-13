# dp1

## [P1131 [ZJOI2007] 时态同步](https://www.luogu.com.cn/problem/P1131)（树形dp）

dp[x]为将x的子树的叶子节点全部变成最长距离的最小花费。

$dp[x]=\sum dp[y]+mxdep[x]-mxdep[y]$

## [P1800 software](https://www.luogu.com.cn/problem/P1800)(二分,dp)

未知的东西太多不好直接搞。

注意到单调性，可以二分答案，减少一个未知数。

将其中一个放到dp的一维。

显然可以这样设计$f_{i,j}$到i，弄好j个1，最多弄多少个2。
$$
f_{i,j}=\max f_{i-1,k}+\frac{x-(j-k)*b_1}{b_2}
$$
时间复杂度
$$
O(n^3 \log {n^2})
$$

## P1880 [[NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)(四边形不等式优化dp)

$$
n^3 \to n^2
$$

对于区间dp
$$
dp[l][r]=\min_{l< k< r} dp[l][k]+dp[k][r] +w(l,r)
$$
设$l\le l'\le r'\le r$若：

+ $w(l',r')\le w(l,r)$

+ $w(l,r')+w(l',r) \le w(l,r)+w(l',r')$**（四边形不等式）**

**那么有**

+ 若$w(l,r)$满足上述两个个条件，那么$dp[l][r]$**满足四边形不等式**
+ 如果$dp[l][r]$满足**四边形不等式**，假设$m[l][r]$为$dp[l][r]$的最优决策点，那么$m[l][r-1]\le m[l][r]\le m[l+1][r]$

我们把$dp[l][r]=\min_{l< k< r} dp[l][k]+dp[k][r] +w(l,r)$取到最小的$k$叫做最优决策点。

结论2相当于在说，最优决策点的矩阵**每一行、每一列**都是**单调不减**的。（这非常重要，实际上这才是这个优化的核心。你甚至选择不去证明四边形不等式，**而是通过打表猜出这个结论**）。

```cpp
for (int i = 1; i <= n; ++i)
    m[i][i] = i; // 初始化边界决策点
for (int d = 2; d <= n; ++d)
    for (int l = 1, r = d; r <= n; ++l，++ r)
    {
        dp[l][r] = INF;
        for (int k = m[l][r - 1]; k <= m[l + 1][r]; ++k) // 利用结论，缩小了枚举范围
            if (dp[l][k] + dp[k + 1][r] + w(l, r) < dp[l][r])
            {
                dp[l][r] = dp[l][k] + dp[k + 1][r] + w(l, r); // 更新dp数组
                m[l][r] = k; // 更新决策点
            }
    }
```

如果 $f(l,r)$ 和$ g(l,r)$ 符合四边形不等式/区间包含单调性，则对于任意 $A,B≥0$ ，$ Af(l,r)+Bg(l,r)$ 也符合四边形不等式/区间包含单调性。

如果存在$f(x) $和$ g(x) $使$ w(l,r)=f(r)−g(l) $，则$ w(l,r) $符合**四边形恒等式**（即等号总是成立的四边形不等式）。如果$ f ， g $单增，则 $w $还符合区间包含单调性。

若 $h(x$) 单增且下凸， $w(l,r)$ 符合四边形不等式和区间包含单调性，则$ h(w(l,r)) $也符合四边形不等式和区间包含单调性。

若$ h(x) $下凸，$w(l,r)$ 符合四边形**恒**等式和区间包含单调性，则 $h(w(l,r))$ 也符合四边形不等式。



对于
$$
dp[i][j]=\min_{1 \le k \le j} dp[i-1][k]+w(k,j)
$$
若$w(i,k)$满足四边形不等式和区间包含单调性。则$dp[i][j]$符合四边形不等式，且它的最优决策点满足$m[i-1][j]\le m[i][j] \le m[i][j+1]$

虽然这个结论的不等式看起来和上面有点不一样，但本质是相同的，都是m矩阵每一行、每一列单调不减。只是因为DP顺序不同，采取了不同的写法。这次的DP顺序不再是按对角线DP，而是按行DP。需要注意，如果要用四边形不等式优化DP，第二层循环需要逆序进行。



## [P4310 绝世好题](https://www.luogu.com.cn/problem/P4310)

因为含同一位的数只用转移离他最近的一个。。。

或者设计dp[i]为最后一项第i位为1的最长子串。

## [P5322 [BJOI2019] 排兵布阵](https://www.luogu.com.cn/problem/P5322)

转移完整！！！

## [P1004 [NOIP 2000 提高组] 方格取数](https://www.luogu.com.cn/problem/P1004)(多维dp)

考虑把两条路径同时进行,由于移动的限制，到达同一个点必然同时。`dp[i][j][k][l]`

表示第一条路到$(i,j)$第二条路到$(k,l)$，



## [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)

注意dp顺序!!!.

## [P2014 [CTSC1997] 选课](https://www.luogu.com.cn/problem/P2014)

对一个子树，只需保证一定选根节点就可以正常dp了

```cpp
  function<void(int)> dfs=[&](int x) {
    sz[x]=1;
    f[x][0]=a[x];
    for (auto y:ver[x]) {
      dfs(y);
      sz[x]+=sz[y];
    }
    for (auto y:ver[x]) {
      for (int i=sz[x]-1;i;--i) {
        for (int j=min(sz[y]-1,i-1);j>=0;--j) {
          f[x][i]=max(f[x][i],f[x][i-j-1]+f[y][j]);
        }
      }
    }
  };
```

## [UVA1437 String painter](https://www.luogu.com.cn/problem/UVA1437)(区间dp+思维)

```cpp
f[0]=0;
    for (int i=1;i<=n;++i) {
      f[i]=dp[1][i];
      if (a[i]==b[i]) f[i]=min(f[i],f[i-1]);
      for (int k=0;k<i;++k)f[i]=min(f[i],f[k]+dp[k+1][i]);
    }
```

## [P3080 [USACO13MAR] The Cow Run G/S](https://www.luogu.com.cn/problem/P3080)(区间dp+贪心)

可以证明最优的情况最后一定会位于两端点.设计$dp[l][r][0/1]$

只修改初始位置的值即可.

## [P1896 [SCOI2005] 互不侵犯](https://www.luogu.com.cn/problem/P1896)(状压dp)

直接存显然存不下,但发现只用考虑前10个位置,就可以状压 .

## [P2622 关灯问题 II](https://www.luogu.com.cn/problem/P2622)(状压dp+最短路)

## [CF685B Kay and Snowflake](https://codeforces.com/problemset/problem/685/B)(树的重心)

由儿子的重心更新父亲的重心.

## [C. Game on Tree](https://codeforces.com/problemset/problem/280/C)(期望)

对于这类每次随机选择还剩下的一些东西，然后删除和这些有关系的一些东西，问期望什么时候删完。

我们可以染色，初始为白色，选到白色，就先把和他有关系的那些染黑，然后继续，问期望删除多少个白色的对象。

就可以设随机变量，利用期望的线性性解决。在本题就是深度的倒数之和。

## [A. Chain Reaction](https://codeforces.com/contest/607/problem/A)(二分)

或者直接

```cpp
void solve() {
  int n;cin>>n;
  vector<int> b(N);
  for (int i=1;i<=n;++i) {
    int x;cin>>x>>b[x+1];
  }
  vector<int> f(N);
  int mx=0;
  for (int i=1;i-1<=1e6;++i) f[i]=f[max<int>(0,i-b[i]-1)]+(b[i]!=0),mx=max(mx,f[i]);
  cout<<n-mx<<"\n";
}
```



## [P2467 地精部落](https://www.luogu.com.cn/problem/P2467)（数学）

注意到如果两个	数$i$和$i+1$不相邻，可以直接交换。

将$A_i$替换成$N+1-A_i$，依旧合法，但交换山峰山谷。

定义$DP[i][j]$表示用$[1,i]$，第一个数用j且为山峰的数量。

有
$$
DP[i][j]=DP[i][j-1]+DP[i-1][i-j+1]
$$
由于只和相对大小有关，我们可以直接设计$DP[i][0/1]$表示长度为$i$，首位为山峰或者山谷的数量。

考虑更新，不妨枚举最大元素的位置，先不考虑山峰或者山谷。有
$$
DP[i]=\sum_{k=1}^{i} \binom{i-1}{k-1} DP[k-1]DP[i-k]
$$
可以根据最大元素位置奇偶性，加上第二维来DP。



## [P4269 [USACO18FEB] Snow Boots G](https://www.luogu.com.cn/problem/P4269)(并查集维护)

## [P4302 字符串折叠](https://www.luogu.com.cn/problem/P4302)(区间dp)

```cpp
  for (int b=2;b<=n;++b) {
     for (int l=1,r=b;r<=n;++l,++r) {
       for (int k=l;k<r;++k) {
         f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]);
       }
       for (int k=l;k<r;++k) {
         int len=k-l+1;
         if (b%len) continue;
         if (check(l,r,len)) f[l][r]=min(f[l][r],f[l][k]+3+((b/len)>=10)+((b/len)>=100));
       }
     }
   }
```



## [P1613 跑路（倍增dp，Floyd）](https://www.luogu.com.cn/problem/P1613)

直接做太复杂，但是我们只用考虑两点之间是否有一条长$2^k$的路径，然后重新建图跑最短路即可。

注意dp顺序。

`f[k][i][j][t]`表示用$\{1,2,\cdots,k\}$，$i$到$j$是否存在一条长度为$2^t$的路。

有
$$
f_{k,i,j,t}|=f_{k-1,i,k,t-1} \and f_{k-1,k,j,t-1}
$$

```cpp
for (int t=1;t<=60;++t) for (int k=1;k<=n;++k) for (int i=1;i<=n;++i) for (int j=1;j<=n;++j) f[i][j][t]|=f[i][k][t-1]&f[k][j][t-1];
```

## [P4124 手机号码](https://www.luogu.com.cn/problem/P4124) (数位dp,记忆化)

维数太多,注意找好方便的递推,比如减少各维的相互影响.

`dp[i][j][k][a][b][c][d]`表示当前要定第i位(这样可以让这一位与其他位毫无关系，最方便)，第i+2位为j, i+1位为k,前面是否已经有3个相邻相等的,前面是否严格小于给定的数,前面是否出现4,前面是否出现8.

我们可以确定第i位选择的上界`lim`

那么
$$
f_{i,j,k,a,b,c,d}=\sum_{t=0}^{lim} f_{i-1,k,t,a\or(t==a \and t==b),b\or(t<lim) ,c \or (t==4),d\or (t==4) }
$$
对于边界情况, i==0,说明已经填完,检查题目的三个条件即可.

```cpp
i64 F(int p,int x,int y,bool tri,bool less,bool ff,bool fe) {
  if (ff and fe) return 0;
  if (p==0) return tri;
  if (vis[p][x][y][tri][less][ff][fe]) return val[p][x][y][tri][less][ff][fe];
  vis[p][x][y][tri][less][ff][fe]=1;
  int lim=9;
  if (less==0) lim=num[p];
  i64 sum=0;
  for (int i=0;i<=lim;++i) sum+=F(p-1,y,i,tri or (i==x and i==y),less or (i<lim),ff or i==4,fe or i==8);
  return val[p][x][y][tri][less][ff][fe]=sum;
}
```

## [P1654 OSU!](https://www.luogu.com.cn/problem/P1654) （期望dp+数学）

维护每一次操作后权值期望的变化量。根据期望的线性性直接加起来就是答案。这样我们只用维护从最近一次失败后的成功地那一段。

设次数为一的期望为$a_i$，二为$b_i$。有
$$
E(x)=a_i=p_i(a_{i-1}+1)
$$

$$
E(x^2)=b_i=p_i(b_{i-1}+2a_{i-1}+1)
$$

设答案为$f_i$，那么有
$$
f_{i}=f_{i-1}+p_{i}(3b_{i-1}+3a_{i-1}+1)
$$




## [P1772 物流运输](https://www.luogu.com.cn/problem/P1772) （图论+dp）

假设不能换路径，求最短路，只要把所有点封锁起来即可。注意到路径是一段一段的，相同的一段不能换路径，考虑枚举换路的位置，可以dp。设$dp_i$为前$i$的答案，预处理$cost[i][j]$表示$i$到$j$天不换路的最短路。有
$$
dp_i=\min_{j=0}^{i-1} (dp_{j}+cost_{j+1,i}*(i-j)+k)
$$

## [P2890 Cheapest Palindrome G](https://www.luogu.com.cn/problem/P2890)(区间dp)

比较容易忽视的一点是$s[l]=s[r]$的情况，可以直接转移。



## [P5839 [USACO19DEC] Moortal Cowmbat G](https://www.luogu.com.cn/problem/P5839)(前缀和优化)

首先很容易算出$a[i][j]$表示从$i\to j$，利用前缀和可以快速算出$cost[i][j][t]$表示把$[i,j]$全部变成字符t。这样可以很容易得到一个$N^2$的做法。考虑优化，注意到$K$小的时候 ，我们向前枚举分段位置，一段不会超过$2K$。

$K$比较大的时候，段数会很少。（似乎不能根号分治，寄）

我们考虑将$cost[i][j][t]$用前缀和表示。
$$
dp[i]=\min_{j=0}^{i-k} (dp[j]+pre[t][i]-pre[t][j])
$$
对每一种颜色存下$dp[j]-pre[t][j]$的最小值，就只用枚举颜色了。

## [P1070 道路游戏](https://www.luogu.com.cn/problem/P1070)（对角线前缀和，单调队列优化dp）

首先$O(N^3)$的做法显然。设$f_i$为前$i$时间的最大价值。有递推式
$$
f_i=\max_{k=1}^{n} \max_{j=1}^{\min(i,p)} (f_{i-j}+cost(k,j,i))
$$
这里$cost(k,j,i)$表示走$j$步，终点为$k$，到终点时间为$i$的价值。$pfx[i][j]$为对角线前缀和（由多条对角线合并）。$a[i][j]$表示到$(i,j)$的边权。
$$
cost(k,j,i)=pfx[k][i]-pfx[k-j][i-j]-c[k-j]
$$
考虑优化掉$j$循环。
$$
\max_{j=1}^{\min(i,p)} (f_{i-j}-pfx[k-j][i-j]-c[k-j])
$$
去掉$j$，令
$$
g_{i,k}=f_{i}-pfx[k][i]-c[k]
$$
有
$$
f_{i,k}=pfx[k][i]+ \max_{j=1}^{\min(i,p)} g_{i-j,k-j}
$$
可用$n$个单调队列优化。每一个单调队列由若干条对角线构成。

关键点在于$g$函数的初始化，即需要算出$g_{0,x}$的值。
$$
g_{0,x}=-c[x]
$$
坑点：前缀和计算

```cpp
for (int i=1;i<=n;++i) for (int j=1;j<=m;++j) {
        int now=(i+j-1)%n;
        if (now==0) now=n;
        int lst=now-1;
        if (lst==0) lst=n;
        pfx[now][j]+=pfx[lst][j-1];
    }
```

或者我们固定机器人，旋转图。那么第$i$个工厂$j$时刻的代价是`c[(i+j-2)%n+1]`，$j$时刻$i$点右侧的金币数是`a[(i+j-2)%n+1][j]`。那么问题转化为

**每次花一定的代价在一个地方放机器人，最多维持p单位时间，每单位时间机器人都会捡起自己右边道路上的金币，机器人不动**

有
$$
f_i=\max_{j=1}^{n} \max_{k=\max(0,i-p)}^{i-1} (f_k+pfx[j][i]-pfx[j][k]-cost[j][k+1])
$$

$$
g[j][k]=f_k-pfx[j][k]-cost[j][k+1]
$$

通过单调队列计算即可。



## [P4158 粉刷匠](https://www.luogu.com.cn/problem/P4158) （分组背包）

先计算一块板子，用$f_{i,j,(0/1)}$表示前$i$个，染色$j$次，第$i$个染$0/1$最多能正确粉刷数。
$$
f_{i,j,0}=\max(f_{i-1,j-1,1},f_{i-1,j,0})+(s[i]=0)\\
f_{i,j,1}=\max(f_{i-1,j-1,0},f_{i-1,j,1})+(s[i]=1)
$$
$f_{0,0,0/1}=0$

然后就可以得到第$i$块板子染色$j$次最多的正确粉刷数，设其为$w_{i,j}$，显然这就是一个分组背包。

## [P5336 成绩单](https://www.luogu.com.cn/problem/P5336)(神秘区间dp)

一组数划分为$k$组，最小化
$$
ak+b\sum_{i=1}^{k}(\max i-\min i)^2
$$
抽取连续的一段，可能由多个连续段拼接起来。考虑区间dp。即$dp[i][j]$表示把区间$[i,j]$内所有数消除的最小代价，很难dp，考虑消除一次操作，就可以存下更多信息。实际上代价麻烦的地方在于最值，考虑将其存下来。

$f_{i,j,l,r}$，表示区间$[i,j]$，进行一些操作后剩下的最小值为$l$，最大值为$r$的最小代价。
$$
dp_{i,j}=\min _{l,r} f_{i,j,l,r} +a+b(r-l)^2
$$
下面就只需考虑$f_{i,j,l,r}$如何转移。考虑区分右边界是否剩下：

若剩下
$$
f_{i,j,\min(l,a[j]),\max(r,a[j])}=f_{i,j-1,l,r}
$$
若已经被消除
$$
f_{i,j,l,r}=f_{i,k,l,r}+\min_{x,y} f_{k+1,r,x,y}+a+b(y-x)^2=f_{i,k,l,r}+dp_{k+1,r}
$$
分数需要离散化。

## [P3239 亚瑟王](https://www.luogu.com.cn/problem/P3239)(期望dp)

**利用期望线性性**，计算每张卡牌被使用的概率。第一张牌的概率很好算，但是后面的牌会被前面影响。于是进行dp。容易想到一种复杂度很高的dp，所以我们考虑间接计算。

假设一张卡牌考虑了$r$次，其成功使用的概率为。
$$
1-(1-p_i)^{r}
$$
后面麻烦的地方在于不知道具体考虑了多少次，于是我们考虑$f_{i,j}$表示前$i$个有$j$个使用了的概率，$r$轮中。
$$
P_i= \sum_{j=0}^{i-1} f_{i-1,j} (1-(1-p_i)^{r-j})
$$
下面转移$f_{i,j}$

这里很容易错写成
$$
f_{i,j}=f_{i-1,j}(1-P_i)+f_{i-1,j-1}P_i
$$
但是注意这里$j$被固定了。
$$
f_{i,j}=f_{i-1,j}(1-p_i)^{r-j}+f_{i-1,j-1}(1-(1-p_i)^{r-j+1})
$$


时间复杂度$O(TNR)=O(NTR)$。

难点在于发现每个位置被成功使用的概率仅仅和前面成功使用次数有关，这样就很方便计算。

## [P3574 FAR-FarmCraft](https://www.luogu.com.cn/problem/P3574) （树上dp）

首先一定是第一次经过时配送（除了节点1）。我们必须解决这个问题才能dp。

**他的汽油恰好够走每条路两遍。**事实上每条边至少得走2遍。于是我们知道节点1的时间为$2n-1+c[1]>c[1]$。可以dp。

$f[i]$表示以$i$为根的子树的答案。相当于有$k$对数，$(x,y)$，以一定的顺序遍历最小化
$$
\max \sum_{u前遍历的节点} x+y_{now}
$$
假设现在随机排列，最大值的位置为$v$，其前一个为$u$，若$u,v$交换更优的话有$x_u-y_u>x_v-y_v$，于是我们按$x-y$升序排序遍历即可。

$x=2sz[i]$，$y=1+f[i]$

## [P2051 中国象棋](https://www.luogu.com.cn/problem/P2051)(计数dp)

实际上就是每行每列最多2个棋子。不太好容斥。考虑dp。首先肯定要利用没行列最多2个棋子这一限制。考虑$f_{i,a,b,c}$为遍历到$i$行，有$0$个棋子的列数量为$a$，1-b，2-c。
$$
f_{i,a,b,c}=f_{i-1,a,b,c}+\binom{a+1}{1}f_{i-1,a+1,b-1,c}+\binom{b+1}{1}f_{i-1,a,b+1,c-1}+\binom{a+2}{2}f_{i-1,a+2,b-2,c}+\binom{b+2}{2}f_{i-1,a,b+2,c-2}+\binom{a+1}{1}\binom{b}{1}f_{i-1,a+1,b,c-1}
$$
$f_{0,m,0,0=1}$

## [P2900 Land Acquisition G](https://www.luogu.com.cn/problem/P2900)（斜率优化dp）

直接做很困难，但我们发现若一个矩形长宽都小于等于另外一个，那么我们就可以直接删除。进一步，我们以长度为第一关键字，宽度为第二关键字排序。这时我们发现合并的矩形一定是**一段连续的区间**。跟具体地，若我们先删除上面情况的矩形，那么合并一段连续的区间只需要知道最左边的矩形的长度，最右边矩形的宽度即可。这时有一个$O(N^2)$的dp，设$f_i$为购买到$i$，的最小花费。
$$
f_i=\min_j(f_{j-1}+a_jb_i)
$$
$a$ 为长度，$b$为宽度。考虑优化。$j$是独立的，将$a_jb_i +f_{j-1}$看成一条直线，$a_j$递减。注意到随着$b_i$的递增，我们的转移点（决策点）是递增的。（上凸包）。

或者将看成一个点$(-a_j,f_{j-1})$，最小化$z=-xb_i+y$，$y=b_i x+z$，相当于定斜率平移直线，找截距最小的点。容易连接任意两个点，当$b_i$大于这条直线斜率时，截距更小的是后面那个点，反之是前面的点。考察那些点可能成为被选中，由于$x,y$均递增，若相邻两条直线斜率满足$k_1<k_2$，都可能被选中，但是$k_1\ge k_2$，中间的点一定不会被选中，因此发现斜率应该是递增的，即是一个凸包，那么随着$b_i$的增大，一直向后选就行。



## [P2513 [HAOI2009] 逆序对数列](https://www.luogu.com.cn/problem/P2513)(数位dp，前缀和优化)

具体的数字并不重要。考虑dp$f_{i,j}$表示长度为$i$的全排列中，逆序对为$j$的数量。
$$
f_{i,j}=\sum_ {k=0}^{k=\min(j,i-1)} f_{i-1,j-k}
$$
前缀和优化一下即可。

## [D. Min-Max Tree](https://qoj.ac/contest/2513/problem/14304)(树形dp,维护链,算贡献)

若处理最大最小的关系，就变得非常复杂。注意到题目等价于连通块内任选两个点作差的最大值，因此，我们可以认为，其实就是将树划分为若干连通块，并在每个连通块取两个数作差，最大化它们的和。并且发现答案是若干条链。（相当于给点附上权（0，1，-1））

考虑一棵子树如何平衡，因为他最多向上合并一条链。因此考虑dp$f_{i,j}$，$j=0,1,2$表示以$i$为根的子树，已经平衡，或者经过根的那条连只选了一个负数，或者只选了一个正数的最大值。



## [P2511 [HAOI2008] 木棍分割](https://www.luogu.com.cn/problem/P2511)（前缀和优化，暴力？滚动数组）

先二分可以找到最小值。然后dp计算数量。$f_{i,j}$为前$i$个分$j$段的方案书。
$$
f_{i,j}=\sum_{k=0}^{i-1} f_{k,j-1}[sum(k+1,i)\le x]
$$
用前缀和优化即可。

滚动数组一定要注意初始化问题



## [P1776 宝物筛选](https://www.luogu.com.cn/problem/P1776)(多重背包，单调队列优化）

朴素的dp是
$$
dp_{i,j}=\max_{k=0}^{c} (dp_{i-1,j-kw}+kv)
$$
注意到$j$每次变化的步长是固定的。考虑取模分组，就变成了求一滑动的区间的最值，利用单调队列优化即可。









































































- [CF1107E](https://www.luogu.com.cn/problem/CF1107E)
- [P2886 Cow Relays G](https://www.luogu.com.cn/problem/P2886)(https://www.luogu.com.cn/record/74852082)
- [P2151 HH去散步](https://www.luogu.com.cn/problem/P2151) 
- [P2279 消防局的设立](https://www.luogu.com.cn/problem/P2279) 
- [P4441 Retro](https://www.luogu.com.cn/problem/P4441) 
- [P5785 任务安排（批量计划）](https://www.luogu.com.cn/problem/P5785) (https://www.luogu.com.cn/record/76455128)
- [P3188 梦幻岛宝珠](https://www.luogu.com.cn/problem/P3188) (https://www.luogu.com.cn/record/82011233)
- [P2943 Cleaning Up G](https://www.luogu.com.cn/problem/P2943) 
- [P2519 problem a](https://www.luogu.com.cn/problem/P2519) 
- [P8476 惊蛰](https://www.luogu.com.cn/problem/P8476) 
- [P4284 概率充电器](https://www.luogu.com.cn/problem/P4284)
- [P4155 国旗计划](https://www.luogu.com.cn/problem/P4155) 

