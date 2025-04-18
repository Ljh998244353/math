## 1.[Insertion Sort](https://codeforces.com/problemset/problem/362/C)(dp,思维)(1800-1900/0)

## 2.[Towers](https://codeforces.com/problemset/problem/229/D)(dp,贪心)(1800-2100/0)

注意到数据范围,可以考虑dp,注意到答案的性质,假设进行到i那么我们只关系最后一个元素的大小,直接放肯定放不下,注意到最后一个元素一定是一段连续的和,可以保存最左边的位置,(或者可以存答案,然后值表示最小的最后一个值),按常规递推的话是$O(n^3)$的,但是我们注意到若更新到一个值,其产生贡献的位置是一段连续的值,且从第二个位置开始,可以从其前一个简单的递推过去,于是可以优化到$O(n^2\log n)$ 足够通过此题.

---

其实注意到单调性,可以用双指针优化到$O(n^2)$

```cpp
for (int i=1;i<=n;++i) {
    int k=i+1;
    for (int j=i;j;--j) {
      f[i][j]=min(f[i][j],f[i-1][j]+1);
      while (pre[k]<2*pre[i]-pre[j-1]) ++k;
      if (k<=n) f[k][i+1]=min(f[k][i+1],f[i][j]+(k-i-1));
    }
  }
```

---

**对于dp问题,可以先不管时间复杂度,找出简单的递推公式,再考虑优化,**于是我们把$O(n^3)$的递推式写出来,
$$
f_{i,j}=\min(f_{j-1,k}+(i-j))=\min(f_{j-1,k})+C
$$
但需要满足
$$
pre_i-pre_{j-1}\ge pre_{j-1}-pre_{k-1}
$$
注意到k越大,$pre_k$越大,$f_{j-1,k}$越小,于是我们可以将最其存下来.

```cpp
g[0]=1,f[0][1]=0;
  for (int i=1;i<=n;++i) {
    for (int j=1;j<=i;++j) {
      if (g[j-1] and pre[g[j-1]-1]>=2ll*pre[j-1]-pre[i]) {
        f[i][j]=min(f[i][j],f[j-1][g[j-1]]+(i-j));
        g[i]=j;
      }
    }
  }
```

注意初值的赋值,建议单独处理,可以优化一维(但没必要)

## 3.[Empty Triangle](https://codeforces.com/contest/2074/problem/E)(概率论)(1600-1700/0)

首先容易想到,每次询问后更新一个点,这样似乎可以解决大部分情况.

---

在三角形内部被分为三个区域,根据抽屉原理,可以确定有一个区域一定会使剩余的点变为1/3,而75次询问,大约会有25次减少,那么显然随机的选取区域极大概率能够成功.

成功概率(>>99.8%)

## 4.[Life is a Game](https://ac.nowcoder.com/acm/problem/231127)(kruskal重构树)(2000-2100/0)

## 5.[Counting Necessary Nodes](https://codeforces.com/contest/2074/problem/F)(思维,几何)(2000-2100/0)

[those found in nodes of segment trees](https://atcoder.jp/contests/abc349/editorial/9879).

按此划分后,容易发现可以单独处理x,y轴,然后划分出的每一个区域是独立的.

## 6.[Game With Triangles: Season 2](https://codeforces.com/contest/2074/problem/G)(区间dp)**(2000-2100/0)**

注意到选择一个三角形后,实际上将问题分成了3个相同的子问题.

容易想到dp,在环上dp比较麻烦.

选择三角形实际上就是选了3个点,然后划分成3个子问题.子问题是在线段上的,可以用`dp[L][R]`计算,但原来的问题并不是`dp[1][n]`,但是我们可以确定一定可用从某个起点开始可以当成线段,否则会相交,那么问题就成了在线段上dp了

容易想到$O(n^5)$的解法

考虑优化,看看有没有重复处理了的东西,假设选择了i,j,k,那么i和j定了的情况,实际上只有区间[i,k]在改变,而只考虑其最大值的话,实际上j的变化是不重要的因此可以优化一维,但要单独处理$i=L,j=R$的情况,得到了$O(n^4)$的解法.

继续优化,先写出$O(n^4)$部分的状态转移方程
$$
f_{L,R}=\max_{i,j}(f_{L,i-1}+f_{i,j}+f_{j+1,R})
$$
i定的情况,和第一项就无关了,此时显然可以合并为$f_{i,R}$,得到$O(n^3)$的算法,
$$
f_{L,R}=\max(\max_{i}(val(L,i,R)+f_{L+1,i-1},+f_{i+1,R-1})+\max_{i}(f_{L,i-1}+f_{i,R}))
$$
用for循环的话,可以枚举区间长度.或者记忆化搜索.注意空集的处理.

注意,**记忆化搜索很慢,可能会被卡.**

## 7. [Chain Queries](https://codeforces.com/contest/1975/problem/E)(图论,思维)(2000-2100/0)

容易想到转化成维护每个点连接的黑点个数,一个问题是是否考虑父亲结点,

维护父亲虽然很好判断,但维护成本很高,肯定不行.

不维护父亲,每次只用更新两个点,不妨设定根后黑色儿子的数量为0,1,2,3+的结点个数.

如何判断呢?

先考虑是否联通,考虑度数和点数的关系,因为没有环,所以有一条链就会使点数比度数大1,

然后判断是否为链,假设加上了父亲,判定条件是c0=0,c1=2(1),c3=0,单个点先不管

c0=0,已经判过,

c1=2,c0<=2,c0>=1

对于c3=0,需要c3=0,若有c2,则c2的父亲需是白色.

容易想到判定c2<=1

上述条件与单个点相容,不同特殊处理了.

c2用set维护即可

时间复杂度$O(n\log n)$

---

注意到最后只剩下一个c2,考虑异或维护,时间复杂度$O(n)$

## 8.[Basic Graph Algorithm](https://qoj.ac/contest/1913/problem/9038)(模拟/1800-1900/0)(24 ICPC上海签到)

注意删除边.

## 9.[Decrease and Swap](https://qoj.ac/contest/1913/problem/9040)(思维/1800-1900/0)(24 ICPC上海铜)

容易想到可能经过一些操作只和后面几个数有关.

考虑倒推(这样只用考虑某一位是否为1),枚举最后两位

1.00,都行

2.01:0000->0100->1010->1101,101,110->01

3.10:0000->0100->1010,1110

4.11:0000->0100->1010->1101->1011,1111

因此只和后5位有关,最好对s实时修改

```cpp
  int cnt=0;
  for (int i=1;i<=n-2;++i) {
    if (s[i]=='1') cnt++;
    else if (cnt) {
      cnt--;
      swap(s[i],s[i-cnt]);
    }
  }
```

## 10.[Geometry Task](https://qoj.ac/contest/1913/problem/9043)(二分/1800-1900/0)(24 ICPC上海银)

容易想到二分答案,贪心地取即可,**注意精度问题.**

对于2e18,可以加个100000..多加几个零.

## 11. [Last Chance: Threads of Despair](https://codeforces.com/gym/105588/problem/L)(贪心/1800-1900/0)(24 ICPC昆明铜)

如何造成最大的伤害?

由于第一次攻击可以任意选择对象,很有操作的空间,可以考虑后面决定,(或者猜测可能需要尽可能减少b最大值).

现在假设只能爆炸,显然可以线性地模拟.当不能继续爆炸再决定具体的安排.

---

我们可以把过程看成:攻击->爆炸->攻击->爆炸.....那么有一种等价形式:攻击->爆炸

## 12.[GCD](https://codeforces.com/gym/105588/problem/G)(数论/2000-2100/0)(24 ICPC昆明铜~银)

看上去很不可做,

容易想到操作次数会很少,不妨试试直接暴力,如果不怕罚时多试几次发现救过了()

可以估计一下设置成25为比较合适.(然后2515ms).

或者,

```cpp
int mx=linf;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int r(int a, int b) {
  return rnd() % (b - a + 1) + a;
}

int work(int x,int y,int dep) {
  if (dep>mx) return iinf;
  if (x==0 or y==0) {
    mx=min(mx,dep);
    return 0;
  }
  int d=__gcd(x,y);
  int rd=r(1,10);
  if (rd&1) return 1+min(work(x-d,y,dep+1),work(x,y-d,dep+1));
  return 1+min(work(x,y-d,dep+1),work(x-d,y,dep+1));
}
```

(62ms)

---

那么为什么操作次数很少呢?给出一种不算最优的算法

如果两个数都是偶数,可以直接除以2,而最多2次操作就能保证至少除2.故最多25次操作.

## 13.[Coin](https://codeforces.com/gym/105588/problem/C)(数学,思维,根号分治?,根号分块)(2000-2100/0)(24 ICPC昆明银)

给的数据范围可以尝试分治.

正难则反.

最后一个人在最后一轮的位置为1,

能否由某一轮的位置推出前一轮的位置?

能否求出轮次?

似乎都可行.

1.求出轮次即求

```cpp
while(n){
    n-=(n+k-1)/k;
}
```

的循环次数,

当$k\le \sqrt{n}$,显然每次至少可以减少$\lceil\sqrt{n}\rceil$,那么对于一个区间$((m-1)^2,m^2]$的数最多操作两次就能离开,那么最多进行$2\lceil\sqrt{n}\rceil$次操作.

否则,注意到减小的值的值域很小,可以分块求解.

时间复杂度为$O(\sqrt{n})$

2.考虑还原,当前索引为x,上一轮为$x+\lceil \frac{x}{k-1}  \rceil$

当$k\le \sqrt{n}$,暴力还原即可.

否则,改变值值域很小,依然可以分块解.

实际上第二类的方法完全可以解决第一类的解法.

## 14[.**Switch Seats**](https://atcoder.jp/contests/abc399/tasks/abc399_d)(思维,细节)(1400-1500/0)

## 15. [Range Power Sum](https://atcoder.jp/contests/abc399/tasks/abc399_f)(数学,dp)(1600-1700/0)

## 16.[**E - Replace**](https://atcoder.jp/contests/abc399/tasks/abc399_e)(图论, 思维)(2000-2100/0)

## 17.[G. Expanding Array](https://codeforces.com/gym/105486)(位运算 , 思维题)(1600-1700/0)

## 18.[I. Good Partitions](https://codeforces.com/gym/105486)(简单数学, 数据结构 , 线段树维护gcd)(1800-1900/0)

## 19.[B. Athlete Welcome Ceremony](https://codeforces.com/gym/105486)(dp , 前缀和)(1800-1900/0)
