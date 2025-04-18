# 递推关系和生成函数

## 1

>![image-20240909140350501](/images/image-20240909140350501.png)

### d

$$
\begin{aligned}
\sum_{i=0}^{n} f_i^2&=f_0^2+\sum_{i=1}^{n}f_i^2\\
&=f_0f_1+\left(f_1(f_2-f_0)+f_2(f_3-f_1)+\cdots+f_n(f_{n+1}-f_{n-1}) \right)\\
&=f_nf_{n+1}
\end{aligned}
$$

## 2

>![image-20240909140828646](/images/image-20240909140828646.png)

容易想到证明$f_n$与上式差值绝对值小于$\frac{1}{2}$
$$
\begin{aligned}
\left |f_n-\frac{1}{\sqrt{5}} {\left( \frac{1+\sqrt{5}}{2} \right)^n} \right|&=\left|\frac{1}{\sqrt{5}} {\left( \frac{1-\sqrt{5}}{2} \right)}^n \right| \\
&=\frac{1}{\sqrt{5}}\left(\frac{2}{\left(1+\sqrt{5} \right)} \right)^n\\
&<\frac{1}{\sqrt{5}}\\
&<\frac{1}{2}
\end{aligned}
$$

## 3

> ![image-20240909141704032](/images/image-20240909141704032.png)

### b

$$
f_n=3f_{n-3}+2f_{n-4}\equiv 2f_{n-4} \mod{3}
$$

因此
$$
3|f_n\iff 3|f_{n-4}
$$

### c

我们对斐波拉契数列 取模有
$$
0,1,1,2,3,1,0,1,\cdots
$$
发现其以$6$为周期循环。

## 6

>![image-20240910155854537](/images/image-20240910155854537.png)

我们令
$$
f_n=a_xf_{n-x}+b_xf_{n-x-1}
$$
显然有
$$
b_n=a_{n-1}
$$
且
$$
a_n=a_{n-1}+b_{n-1}=a_{n-1}+a_{n-2}\Rightarrow b_n=b_{n-1}+b_{n-2}
$$


又$b_0=0,b_1=1$故$b$是斐波拉契数列。

那么有
$$
f_n=f_{x+1}f_{n-x}+f_xf_{n-x-1}
$$
设$n=km$，用数学归纳法即可。

## 7

>![image-20240910160533931](/images/image-20240910160533931.png)

设$n=km+r$ ，

那么有
$$
f_n=f_{r+1}f_{km}+f_rf_{km-1}
$$
注意到
$$
\gcd(f_n,f_{n+1}) =1
$$
我们有
$$
f_{km-1}=f_mf_{(k-1)m}+f_{m-1}f_{(k-1)m-1}
$$


从而有
$$
\gcd(f_{km-1},f_m)=\gcd(f_m,f_{m-1})=1
$$
故
$$
\gcd(f_n,f_m)=\gcd(f_m,f_r)
$$
然后令n=m，m=r。类比欧几里得算法。可得
$$
\gcd(f_n,f_m)=f_{\gcd(n,m)}
$$

## 9

> ![image-20240910165450019](/images/image-20240910165450019.png)

有
$$
h_n=2(h_{n-1}+h_{n-2})
$$
特征方程$x^2-2x-2=0$的根为
$$
x=1\pm\sqrt{3}
$$
初值为$h_0=1,h_1=3$

带入得
$$
\begin{cases}
c_1+c_2=1\\
c_1(1+\sqrt{3})+c_2(1-\sqrt{3})=3
\end{cases}
$$
解得
$$
c_1=\frac{3+2\sqrt{3}}{6}(1+\sqrt{3})^n+\frac{3-2\sqrt{3}}{6}(1-\sqrt{3})^n
$$


## 15

> ![image-20240910170155353](/images/image-20240910170155353.png)

有
$$
\frac{1}{1-x}=\sum_{n=0}^{\infty}x^n
$$
同时微分并乘$x$
$$
\frac{x}{(1-x)^2}=\sum_{n=0}^{\infty}nx^n
$$
同时微分并乘$x$
$$
\frac{x-x^3}{(1-x)^4}=\sum_{n=0}^{\infty}n^2x^n
$$
同时微分并乘$x$
$$
\frac{x^3+4x^2+x}{(1-x)^4}=\sum_{n=0}^{\infty}n^3x^n
$$
或者由
$$
n^3 = 6 \binom{n}{3} + 6 \binom{n}{2} + \binom{n}{1}
$$
得
$$
\begin{aligned}
g(x)&=\sum_{n=0}^{\infty}6\binom{n}{3}x^n+\sum_{n=0}^{\infty}6\binom{n}{2} x^n+\sum_{n=0}^{\infty} \binom{n}{1}x^n\\
&=6x^3\sum_{n=0}^{\infty} \binom{n+3}{n}x^n+6x^2\sum_{n=0}^{\infty}\binom{n+2}{n}x^n+x\sum_{n=0}^{\infty}\binom{n+1}{n}x^n\\
&=\frac{6x^3}{(1-x)^4}+\frac{6x^2}{(1-x)^3}+\frac{x}{(1-x)^2}\\
&=\frac{x^3+4x^2+x}{(1-x)^4}
\end{aligned}
$$

## 21

>![image-20240911135029474](/images/image-20240911135029474.png)

设该$n+2$边形其中一个顶点为$v$，我们连接其左右两个顶点后形成一个$n+1$边形。然后设其连出去的$n-1$条对角线分别产生$k_i$个交点。那么将新产生$k_i+1$个区域。因此答案为
$$
h_n=h_{n-1}+1+\sum_{i=1}^{n-1}(k_i+1)=h_{n-1}+n+\sum_{i=1}^{n-1}k_i
$$
而事实上$k_i$的和就是$n+2$边形的对角线产生的非顶点的交点数与$n+1$边形的差。

**引理**：而对于一个$n$边形不考虑共点和顶点的情况下，将产生$\binom{n}{4}$的交点。

**证明：**对于四个顶点，我们连完对角线将产生一个交点，而任意一个交点，将对应四个顶点。因此交点数和从$n$个顶点选出4个点是一一对应的。证毕。

故上式等于
$$
\begin{aligned}
h_n&=h_{n-1}+n+\sum_{i=1}^{n-1}k_i\\
&=h_{n-1}+\binom{n+2}{4}-\binom{n+1}{4}+n\\
&=h_{n-1}+\binom{n+1}{3}+n
\end{aligned}
$$
有
$$
\begin{aligned}
(1-x)g(x)&=h_0+\sum_{n=1}^{\infty}\left(\binom{n+1}{3}+n \right)x^{n}\\
&=\sum_{n=1}^{\infty}\binom{n+1}{3}x^n+\sum_{n=1}^{\infty}nx^n\\
&=x^2\sum_{n=0}^{\infty}\binom{n+3}{3}x^n+\sum_{n=0}^{\infty} nx^n\\
&=\frac{x^2}{(1-x)^4}+\frac{x}{(1-x)^2}\\
\end{aligned}
$$
从而
$$
\begin{aligned}
g(x)&=\frac{x^2}{(1-x)^5}+\frac{x}{(1-x)^3}\\
&=x^2\sum_{n=0}^{\infty}\binom{n+4}{n}x^n+x\sum_{n=0}^{\infty}\binom{n+2}{n}x^n\\
&=\sum_{n=0}^{\infty}\binom{n+2}{4}x^n+\sum_{n=0}^{\infty}\binom{n+1}{2}x^n\\
&=\sum_{n=0}^{\infty}\left(\binom{n+2}{4}+\binom{n+1}{2} \right)x^n
\end{aligned}
$$
综上
$$
h_n=\binom{n+2}{4}+\binom{n+1}{2}
$$
或者考虑迭代法

## 25

> ![image-20240914213455922](/images/image-20240914213455922.png)

使用生成函数：
$$
\begin{aligned}
g(x)&=\left(\sum_{n=0}^{\infty}\frac{x^n}{n!} \right)^2\left(1+\frac{x^2}{2!}+\cdots \right)\left(x+\frac{x^3}{3!}+\cdots \right)\\
&=e^{2x}\left(\frac{e^x+e^{-x}}{2} \right) \left( \frac{e^x-e^{-x}}{2} \right)\\
&=\frac{e^{4x}-1}{4}\\
&=\frac{1}{4}\sum_{n=0}^{\infty} 4^{n} \frac{x^n}{n!}-\frac{1}{4}\\
&=\sum_{n=1}^{\infty} 4^{n-1} \frac{x^n}{n!}
\end{aligned}
$$
故
$$
h_n=4^{n-1}(n\geq 1)
$$
特别地：$h_0=1$

## 29

> ![image-20240920143718421](/images/image-20240920143718421.png)

设$a_n$为$1,3$均出现奇数次时的数，且$b_n$为一奇一偶。

那么有
$$
\begin{cases}
a_n=3a_{n-1}+2b_{n-1}\\
b_n=3b_{n-1}+a_{n-1}+h_{n-1}\\
h_n=3h_{n-1}+2b_{n-1}\\
a_n+2b_n+h_n=5^n
\end{cases}
$$
消元可得到$h_n$的递推式
$$
h_n-4h_{n-1}+3h_{n-2}=2\cdot5^{n-2}
$$
其齐次递推式的特征方程为
$$
x^2-4x+3=0
$$
从而求出解
$$
H_n=c_13^n+c_2
$$
下面求一个特解，设$h_n=p5^n$，解得$p=\frac{1}{4}$。

那么
$$
h_n=c_13^n+c_2+\frac{5^n}{4}
$$
带入$h_0,h_1$得
$$
h_n=\frac{2\cdot 3^n+1+5^n}{4}
$$
或者根据递推式，利用生成函数：
$$
\begin{aligned}
(1-4x+3x^2)g(x)&=1-x+\sum_{n=2}^{\infty}2\cdot5^{n-2}x^n\\
&=1-x+2x^2\sum_{n=0}^{\infty}(5x)^n\\
&=1-x+\frac{2x^2}{1-5x}
\end{aligned}
$$
那么
$$
\begin{aligned}
g(x)&=\frac{1-x}{1-4x+3x^2}+\frac{2x^2}{(1-5x)(1-4x+3x^2)}\\
&=\frac{1}{1-3x}+\frac{\frac{1}{4}}{1-5x}-\frac{\frac{1}{2}}{1-3x}+\frac{\frac{1}{4}}{1-x}\\
&=\frac{1}{2}\sum_{n=0}^{\infty}3^nx^n+\frac{1}{4}\sum_{n=0}^{\infty}5^nx^n+\frac{1}{4}\sum_{n=0}^{\infty}x^n\\
&=\sum_{n=0}^{\infty}\left(\frac{5^n+2\cdot3^n+1}{4} \right)x^n
\end{aligned}
$$
故
$$
h_n=\frac{5^n+2\cdot3^n+1}{4} 
$$



## 37

> ![image-20240924154940086](/images/image-20240924154940086.png)

为了计算$a_n$我们不妨将其分成以$22$开头的和其他，若以$22$开头显然有$a_{n-2}$ 种，否则我们再将$a_{n-1}$分成三类，开头为$0,1,2$

设其分别有$x,y,z$种。

那么有
$$
a_n=(y+z)+(x+z)+(x+y)+a_{n-2}=2a_{n-1}+a_{n-2}
$$


## 41

> ![image-20240924154950797](/images/image-20240924154950797.png)

我们不妨对这$2n$个点编号，若我们先连接$1,x$，显然$2|x$，且满足递推式
$$
h_n=\sum_{k=1}^{n}h_{k-1}h_{n-k}
$$
为卡特兰序列。

故
$$
h_n=\frac{1}{n+1} \binom{2n}{n}
$$

## 49

> ![image-20240929111735871](/images/image-20240929111735871.png)

**公式似乎有错**，应该是
$$
(x+y)(x+qy)\cdots(x+q^{m-1}y)=\sum_{k=0}^{n}q^{\binom{k}{2}}\binom{n}{k}_q x^{n-k}y^k
$$


注意到：
$$
\binom{n}{k}_q=\prod_{i=1}^{k}\frac{1-q^{n-k+i}}{1-q^i}
$$
因此：
$$
\binom{n}{k}_q=\frac{1-q^n}{1-q^{n-k}}\binom{n-1}{k}_q\\
\binom{n}{k}_q=\frac{1-q^n}{1-q^k}\binom{n-1}{k-1}_q
$$
故
$$
\begin{aligned}
q^k\binom{n}{k}_q+\binom{n}{k-1}_q&=q^k\frac{1-q^{n+1-k}}{1-q^{n+1}}\binom{n+1}{k}+\frac{1-q^k}{1-q^{n+1}}\binom{n+1}{k}\\
&=\left(\frac{q^k-q^{n+1}+1-q^{k}}{1-q^{n+1}} \right)\binom{n+1}{k}\\
&=\binom{n+1}{k}
\end{aligned}
$$

同理可得
$$
\binom{n}{k}+q^{n+1-k}\binom{n}{k-1}=\binom{n+1}{k}
$$


显然可以用数学归纳法证明：

$n=1$显然。

设$n=m$成立，那么当$n=m+1$时，有：
$$
\begin{aligned}
&(x+y)(x+qy)\cdots(x+q^{m-1}y)(x+q^my)\\
&=(x+q^my)\sum_{k=0}^{m}q^{\binom{k}{2}} \binom{m}{k}_qx^{m-k}y^k\\
&=\sum_{k=0}^{m}q^{\binom{k}{2}} \binom{m}{k}_qx^{m+1-k}y^k+\sum_{k=1}^{m+1}q^{\binom{k-1}{2}}q^m\binom{m}{k-1}_qx^{m+1-k}y^k\\
&=\binom{m}{0}_qx^{m+1} +\sum_{k=1}^{m}\left(\left(q^{\binom{k}{2}} \binom{m}{k}_q+q^{\binom{k-1}{2}+m} \binom{m}{k-1}_q\right)x^{m+1-k}y^k \right)+q^{\binom{m}{2}+\binom{m}{1}} \binom{m}{m}_qy^{m+1}\\
&=\binom{m+1}{0}_q x^{m+1}+\sum_{k=1}^{m}\left(q^{\binom{k}{2}}\left( \binom{m}{k}_q+q^{m+1-k}\binom{m}{k-1}_q \right)x^{m+1-k}y^k \right)+q^{\binom{m+1}{2}}y^{m+1}\\
&=\sum_{k=0}^{m+1}q^{\binom{k}{2}}\binom{m+1}{k}_qx^{m+1-k}y^k
\end{aligned}
$$
证毕。



## 50

> ![image-20240929131531914](/images/image-20240929131531914.png)
> ![image-20240929131603989](/images/image-20240929131603989.png)

有
$$
\begin{aligned}
g_n&=\sum_{k=1}^{n} \binom{n-k}{k-1}\\
&=\sum_{k=1}^{n} \binom{n-k-1}{k-1}+\sum_{k=1}^{n}\binom{n-k-1}{k-2}\\
&=\sum_{k=1}^{n-1}\binom{n-1-k}{k-1}+\sum_{k=1}^{n}\binom{n-2-(k-1)}{k-1-1}\\
&=g_{n-1}+\sum_{k=0}^{n-1}\binom{n-2-k}{k-1}\\
&=g_{n-1}+\sum_{k=1}^{n-2}\binom{n-2-k}{k-1}\\
&=g_{n-1}+g_{n-2}
\end{aligned}
$$

## 51

> ![image-20240929134343436](/images/image-20240929134343436.png)

有
$$
(1-3x)g(x)=2-4\sum_{n=1}^{\infty}nx^n
$$
故
$$
\begin{aligned}
g(x)&=\frac{2}{1-3x}-\frac{4}{1-3x} \sum_{n=1}^{\infty}nx^n\\
&=\frac{2}{1-3x}-\frac{4x}{1-3x}\sum_{n=0}^{\infty}\binom{n+1}{n}x^n\\
&=\frac{2}{1-3x}-\frac{4x}{1-3x}\frac{1}{(1-x)^2}\\
&=\frac{-1}{1-3x} + \frac{3-x}{(1-x)^2} \\
&=\sum_{n=0}^{\infty} (2n+3-3^n)x^n
\end{aligned}
$$
