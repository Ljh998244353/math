> 数学问题

## 102 combinatoria problems from the training of the USA IMO team

### problem3

3.Let ( n ) be an odd integer greater than 1. Prove that the sequence   
$$
\binom{n}{1}, \binom{n}{2}, \ldots, \binom{n}{\frac{n-1}{2}}  
$$
 contains an odd number of odd numbers.

**solution:**
$$
\frac{1}{2}\left(\sum_{i=1}^{n-1}\binom{n}{i} \right)=\frac{1}{2}(2^{n}-2)=2^{n-1}-1
$$
是一个奇数。

### problem4

4.How many positive integers not exceeding 2001 are multiples of 3 or 4 but not 5?

**solution:**

$A_1,A_2,A_3$分别表示是3,4,5的倍数。

所求即
$$
(A_1\cup A_2)\cap(\overline{ A_3})=(A_1\cup A_2)-(A_1\cup A_2)\cap A_3
$$
为801。



### problem6

考虑反证法。

注意到，可以先将女生排好。再将男生插空。且同一个空至少插2个男生。而要保证25个女生之间没有3个相邻的，至少插入13个空。

因为一个女生左右至少得有一个空有男生。而一个空最多满足2个女生。显然与25个男生矛盾。

**std1**

将连续的男生女生看成整体。女生有13个部分，两个部分之间至少两个男生，那么男生至少需要26个。

**std2**

设其按 $a_1,a_2,\cdots,a_{50}$排好。将$a_1,a_3,\cdots,a_{49}$拿出来看。显然其不能连续有两个女生。故最多12个女生。剩下的同理，故女生最多24个。

### problem7

可设#i在决出第i名比赛胜出的事件为A_i 

对于一种可能的结果，一定对应着这4个事件的发生与否。

而对于这四个事件是否发生也对应着一种可能的结果。

故每一种结果和4个独立事件的发生与否构成双射。故有2^4种可能。

### problem11(solution)

### prolblem14(X)

### problem17(X,抽屉，Sidon序列)



**Sidon序列**（又称**B₂序列**）是组合数学中的一个重要概念，定义如下：

一个严格递增的正整数序列 $ S = \{a_1, a_2, \ldots, a_k\} $ 称为 **Sidon序列**，如果它满足： 
**任意两个不同元素的和互不重复**。 
即，对于所有 $ 1 \leq i < j \leq k $ 和 $ 1 \leq m < n \leq k $，若 $ (i,j) \neq (m,n) $，则 $ a_i + a_j \neq a_m + a_n $。

**Sidon序列**（又称**B₂序列**）是组合数学中的一个重要概念，定义如下：

**和唯一性**：Sidon序列的核心特点是所有两两和均唯一。例如，序列 $ \{1, 2, 4, 8\} $ 的和为 $ 3, 5, 6, 9, 10, 12 $，均不重复。

**最大长度**：在范围 $[1, N]$ 内，Sidon序列的最大可能长度约为 $ \sqrt{N} $。例如，当 $ N = 100 $ 时，最大Sidon序列的长度约为10。超过这个长度时，必然存在重复的和（由鸽巢原理保证）。



对于区间 $[1, N]$ 内的Sidon序列，其最大长度的渐近上界为 $\sqrt{N}$，但具体是否严格取决于 $N$ 的取值：



根据 **Erdős–Turán定理**，当 $N$ 充分大时，Sidon序列的最大长度 $k$ 满足：  
$$
k \leq \sqrt{N} + O(N^{1/4}).
$$
这表明 $\sqrt{N}$ 是一个渐近上界，但并非严格确切的数值，因为存在修正项 $O(N^{1/4})$。  

### problem 20(solution)

单独考虑中心的位置，然后分为四个区域，始终保持一个区域有，然后计算。

为
$$
12+\binom{12}{2}+\frac{12+12\times 36}{2}=300
$$

### problem 24 （反证法）



### problem25（进制(ACM)，对应法）

### problem27（图论,guess）



### problem29 

**cur=30** P51



