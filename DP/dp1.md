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






- [P1654 OSU!](https://www.luogu.com.cn/problem/P1654) 
- [P1772 物流运输](https://www.luogu.com.cn/problem/P1772) 
- [P2890 Cheapest Palindrome G](https://www.luogu.com.cn/problem/P2890)
- [P5839 Moortal Cowmbat G](https://www.luogu.com.cn/problem/P5839)(https://www.luogu.com.cn/record/81318602)
- [P1070 道路游戏](https://www.luogu.com.cn/problem/P1070) 
- [P4158 粉刷匠](https://www.luogu.com.cn/problem/P4158) 
- [P5336 成绩单](https://www.luogu.com.cn/problem/P5336)
- [P3239 亚瑟王](https://www.luogu.com.cn/problem/P3239)
- [P3574 FAR-FarmCraft](https://www.luogu.com.cn/problem/P3574) 
- [P2051 中国象棋](https://www.luogu.com.cn/problem/P2051) (https://www.luogu.com.cn/record/81586130)
- [P2900 Land Acquisition G](https://www.luogu.com.cn/problem/P2900)



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
