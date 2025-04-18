# 组合数学第五版答案-容斥原理及其应用	

> Richard A. Brualdi-Introductory Combinatorics (5th Edition) (2009) 第六章的部分习题答案，直接套公式，书中有详细答案或与书中例题基本一致的题目省略。仅供参考。

因本人水平有限，且没有标答验证，可能有错误，欢迎指正。

## 3

> Find the number of integers between 1 and 10,000 that are neither perfect squares nor perfect cubes.

如何找出既是完全平方数又是完全立方数的数？
注意到$x=a^2=b^3$ 那么$b=a^{\frac{2}{3}}$因此$a^{\frac{1}{3}}$为整数,那么$x=c^6$只需解$c^6\leq10000$即可。

## 19

> Using the evaluation of the derangement numbers as given in Theorem 6.3.1, provide a proof of the relation
>
> $$
> D_n = (n-1)(D_{n-2} + D_{n-1}), \quad (n=3,4,5, ...).
> $$

$$
\begin{aligned}
(n-1)(D_{n-1}+D_{n-2})&=(n-1)\left((n-1)!\sum_{i=0}^{n-1}\frac{(-1)^i}{i!}+(n-2)!\sum_{i=0}^{n-2}\frac{(-1)^i}{i!} \right)\\
&=(n-1)\left((n-1)!+(n-2)!\right)\sum_{i=0}^{n-2}\frac{(-1)^i}{i!}+(n-1)\cdot(-1)^{n-1}\\
&=n!\sum_{i=0}^{n-2}\frac{(-1)^i}{i!}+n!\left(\frac{(-1)^{n-1}(n-1)}{n!} \right)\\
&=n!\sum_{i=0}^{n-2}\frac{(-1)^i}{i!}+n!\left(\frac{(-1)^{n-1}n}{n!}-(-1)^{n-1}\frac{1}{n!} \right)\\
&=D_n
\end{aligned}
$$

## 21

> Prove that $D_n$ is an even number if and only if n is an odd number.

可通过归纳法，或者：

可以根据
$$
D_n=n!\left(1-\frac{1}{1!}+\frac{1}{2!}-\frac{1}{3!}+\cdots+(-1)^n\frac{1}{n!}\right)
$$
单独考虑$D_1$,然后
$$
D_n=(-1)^n \frac{n!}{n!} +(-1)^{n-1} \frac{n!}{(n-1)!}\cdots
$$
当$n>1$时，第三项后面项全是偶数，而第一项为奇数，第二项与n同奇偶，因此$D_n$为偶数，当且仅当$n$为奇数。

或者由于
$$
D_n=nD_{n-1}+(-1)^n
$$
递推一步，可得出：
$$
D_{n+1}\equiv n(n+1)D_{n-1}+n \equiv n\mod{2}
$$

## 27

> A carousel has eight seats, each representing a different animal. Eight girls are seated on the carousel facing forward (each girl ooks at another girl's back). In how many ways can the girls change seats so that each has a different girl in front of her? How does the problem change if all the seats are identical?

记$A_i$表示排列$s_1s_2 \cdots s_8$中$s_i$面向$s_{i+1}$（其中$1 \le i \le 7$），$A_8$表示表示排列$s_1s_2 \cdots s_8$中$s_8$面向$s_1$。

单独考虑$s_8$对$s_1$的情况。

$|A_i|$：$7!+6!=8\times 6!$

$|A_iA_j|$：$6!+2\times 5!=8\times 5!$

$k$个相交为$(8-k)!+k\times(7-k)!=8\times (7-k)!$

答案为13000

当所有座位都相同时，第一个选择的只有1种选法，其余人选法不变，因此排列总数为$\frac{13000}{8} = 1625$。



## 32

>  Let n be a positive integer and let$p_1,p_2,\cdots,p_k$be all the different prime numbers that divide n. Consider the Euler function $\phi$ defined by 
>  $$
>  \phi(n)=|\{k:1 \leq k\leq n,GCD(k,n)=1 \}|
>  $$
>  Use the inclusion-exclusion principle to show that 
>  $$
>  \phi(n)=n\prod_{i=1}^{k} (1-\frac{1}{p_i})
>  $$

设$A_i$为$p_i|\gcd(k,n)$的集合。
$$
\begin{aligned}
\phi(n)&=|\overline{A_1}\cap \overline{A_2}\cap\cdots\cap \overline{A_k}|\\
&=n-\sum_{i}\left(\frac{n}{p_i}\right)+\sum_{i,j}\left(\frac{n}{p_ip_j}\right)-\cdots+(-1)^k(\frac{n}{p_1p_2\cdots p_k})\\
&=n\prod_{i=1}^{k} (1-\frac{1}{p_i})
\end{aligned}
$$

## 33

> ![image-20240824225321055](/images/image-20240824225321055.png)



等价于从围成一圈的$1,2,\cdots,2n$选择不相邻的$m$个数字。我们选出分成$2n-k$和$k$，从$2n-k$中选出$k$个空，每一种选择可进行旋转，有$\frac{2n}{2n-k}$种。所以
$$
a(n,k)=\frac{2n}{2n-k} \binom{2n-k}{k}
$$
或者：

若不考虑$1，2n$，我们可以假设选择$c_1,c_2,\cdots,c_k$，其中小于$c_i$的有$x_i$个，大于$c_k$的有$x_{k+1}$个。那么我们有
$$
x_1+x_2+\cdots +x_{k+1}=2n-k
$$
然后先在两两中间插入一个，转化为
$$
y_1+y_2+\cdots+y_{k+1}=2n-2k+1
$$
其中$0\leq y_i\leq 2n-2k+1$ ，有$\binom{2n-k+1}{k}$

假设选择$2n$，那么 不能选择$1,2n-1$,有$\binom{2n-k-1}{k-1}$

若不选择$2n$，那么有$\binom{2n-k}{k}$

总数为
$$
\binom{2n-k-1}{k-1}+\binom{2n-k}{k}=\frac{k}{2n-k}\binom{2n-k}{k}+\binom{2n-k}{k}=\frac{2n}{2n-k} \binom{2n-k}{k}
$$

> 不知道为什么棋盘和下面的等价，带入k=1，显然是错的，可能是这些位置不是禁止，而是其他位置禁止，那么就显然等价了。
>
> 我们可以进行编号。例如：
>
> ```
> 1200
> 0340
> 0056
> 8007
> ```

## 34

> ![image-20240824225329592](/images/image-20240824225329592.png)

交换求和次序即可。
$$
\begin{aligned}
f*(g*h)(x,y)&=\sum_{x\leq z\leq y}f(x,z)(g*h)(z,y)\\
&=\sum_{x\leq z\leq y}\left( f(x,z)\left(\sum_{z\leq w\leq y}g(z,w)h(w,y) \right)\right)\\
&=\sum_{x\leq z\leq y} \left(\sum_{z\leq w\leq y}f(x,z)g(z,w)h(w,y) \right)\\
&=\sum_{x\leq w\leq y}\left(\sum_{x\leq z\leq w}f(x,z)g(z,w) \right)h(w,y)\\
&=\sum_{x\leq w\leq y}(f*g)(x,w)h(w,y)\\
&=(f*g)*h
\end{aligned}
$$

## 36

>![image-20240824225335976](/images/image-20240824225335976.png)


代码

```cpp
int a[30][30];
void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cin >> a[i][j];
    }
  }
  ll ans = 0;
  for (int i = 0; i < (1ll << n); ++i) {
    vector<int> S;
    // subset S
    for (int j = 0; j < n; ++j) {
      if (i >> j & 1) {
        S.push_back(j + 1);
      }
    }
    ll p = 1;
    for (int k = 1; k <= n; ++k) {
      ll sum = 0;
      for (const auto& x : S) sum += a[k][x];
      p *= sum;
    }
    if ((n - S.size()) & 1) {
      ans -= p;
    } else {
      ans += p;
    }
  }
  cout << ans;
}
```

## 37

> ![image-20240824225341561](/images/image-20240824225341561.png)


赋值法。

设$f*g=\delta$
$$
\delta(A,B)=\sum_{A\subseteq C \subseteq B} f(A,C) g(C,B)
$$

+ 若$A=B$：

  那么
  $$
  f(A,A)g(A,A)=1\Rightarrow g(A,A)=1
  $$
  $g(A,B)=1$

+ 若$|B|-|A|=1$

  那么
  $$
  \begin{aligned}
  0&=f(A,A)g(A,B)+f(A,B)g(B,B)\\
  &=g(A,B)+2
  \end{aligned}
  $$
  $g(A,B)=-2$

+ 若$|B|-|A|=2$

  那么
  $$
  \begin{aligned}
  0&=f(A,A)g(A,B)+f(A,C)g(C,B)+f(A,B)g(B,B) \\
  &=g(A,B)+2g(C,B)+1\\
  &=g(A,B)-4+1
  \end{aligned}
  $$
  $g(A,B)=3$

+ 若$|B|-|A|=3$

  那么
  $$
  \begin{aligned}
  0&=f(A,A)g(A,B)+f(A,C)g(C,B)+f(A,D)g(D,B)+f(A,B)g(B,B) \\
  &=g(A,B)+2g(C,B)+g(D,B)-1 \\
  &=g(A,B)+6-2-1\\
  \end{aligned}
  $$
  $g(A,B)=-3$

综上

若$A\subseteq B$
$$
g(A,B)=\begin{cases}
1&\qquad,A=B\\
-2&\qquad,|B|-|A|=1\\
3&\qquad,|B|-|A|=2\\
-3&\qquad,|B|-|A|=3
\end{cases}
$$

## 38

> ![image-20240824225346059](/images/image-20240824225346059.png)

以$\Pi_3$为例：
$$
\begin{aligned}
\sigma_1&=\{\{ 1,2,3\}\}\\
\sigma_2&=\{\{ 1\},\{ 2,3\}\}\\
\sigma_3&=\{\{ 1,2\},\{ 3\}\}\\
\sigma_4&=\{\{ 1,3\},\{ 2\}\}\\
\sigma_5&=\{\{ 1\},\{ 2\},\{3\}\}\\
\end{aligned}
$$

+ 若$|\sigma|-|\pi|=1$
  $$
  \begin{aligned}
  \mu(\sigma,\pi)=-\left(\mu(\sigma,\sigma )\right)=-1
  \end{aligned}
  $$

+ 若$|\sigma|-|\pi|=2$
  $$
  \mu(\sigma,\pi)=-\left(\mu(\sigma,\sigma )+\mu(\sigma,\sigma_2)+\mu(\sigma,\sigma_3)+\mu(\sigma,\sigma_4) \right)=-(1-3)=2
  $$

## 39

> ![image-20240824225352287](/images/image-20240824225352287.png)

等价于证明$\forall a\in X_n, \mu(1,k)=\mu(a,ka)$对任意正整数成立(满足$ka\leq n$)

考虑使用数学归纳法

+ $k=1$,显然成立

+ 假设对于任意$x\leq t-1$成立。
  $$
  \begin{aligned}
  \mu(1,t)&=-\sum_{x|t,x<t}\mu(1,x)\\
  &=-\sum_{x|t,x<t}\mu(a,xa)\\
  &=\mu(a,ta)
  \end{aligned}
  $$

证毕。

## 40

> ![image-20240824225358425](/images/image-20240824225358425.png)

这里略过证明偏序关系的过程。

这个偏序集是$k$个线性有序集的笛卡尔积。因此可以得到

设$A=p_i\cdot a_i$，$B=q_i\cdot a_i$，$A\leq B$，$m=\max_{1\leq i \leq k}{(q_i-p_i)}$，$c=\sum_{1\leq i\leq k}[q_i-p_i=1]$
$$
\mu(A,B)=\begin{cases}
1&\qquad,m=0\\
(-1)^c&\qquad,m=1\\
0&\qquad,m>1
\end{cases}
$$
