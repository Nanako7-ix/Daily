# 训练记录

すべてはここから

> 这个Repository其实是用来放平时训练的代码的
> 因为写起来舒服所以就直接用README来写训练记录了

## 2025年3月

### 牛客周赛 87

#### [小苯的V图](https://ac.nowcoder.com/acm/contest/105623/A)

水题，[Code](./nowcoder/牛客周赛-Round-87/A.cpp)

#### [小苯的数字切割](https://ac.nowcoder.com/acm/contest/105623/B)

水题，[Code](./nowcoder/牛客周赛-Round-87/B.cpp)

#### [小苯的Z串匹配](https://ac.nowcoder.com/acm/contest/105623/C)

水题，[Code](./nowcoder/牛客周赛-Round-87/C.cpp)

#### [小苯的最大和](https://ac.nowcoder.com/acm/contest/105623/D)

Tag: 线性DP

很典的线性DP，没有归成水题是因为我是 DP 苦手，[Code](./nowcoder/牛客周赛-Round-87/D.cpp)

#### [小苯的数组构造](https://ac.nowcoder.com/acm/contest/105623/E)

Tag: 贪心，构造

比较恶心的点就是需要满足 $a_i > 0$ 吧，贪心一下尽可能多覆盖一下就好了。挺水的。[Code](./nowcoder/牛客周赛-Round-87/E.cpp)

#### [小苯的ovo2.0](https://ac.nowcoder.com/acm/contest/105623/F)

Tag: Guess，贪心

注意到如果整个字符串都是任意选择的，那么一定是中间的某一段选择 'v'，然后两边选择 'o'。这是一个简单的贪心结论。

然后直接猜测对于只能选择部分字符的情况也满足这种情况。直接 $O(n^2)$ 枚举区间然后 $O(n)$ check就过了。

[Code](./nowcoder/牛客周赛-Round-87/F.cpp)

### 3月31日

#### [Yet Another Real Number Problem](https://codeforces.com/contest/2035/problem/D)

Tag: 单调栈

CF Rating: 1800

显然一个数字 $a_i$ 可以被拆成 $x\cdot 2^{t}$，那么这题的操作就是重新分配 $2^t$，且只能向后传
递。

考虑已经计算完了 $f(i - 1)$，那么只需要考虑插入一个数字 $a_i$，应该如何分配 $2^t$。显然只可能出现前面的数字传递给 $a_i$ 的情况，因为前面的安排已经是最好的了。前面的安排一定是全部的 $2^t$ 集中在若干个数字上，那么我们需要考虑的是：将哪些数字上的 $2$ 传递给当前数字。

容易想到，越是靠后的这些数字，越是和 $2$ 不适配，否则前面的 $2$ 就会直接给到后面来了，也就是具有一个单调性。那么我们每次只需要判断最后面的数字是否需要向当前数字提供 $2$ 即可。判断方式需要计算是否提供 $2$ 这两种情况下的贡献，两个作比较可以得到一条不等式。

[Code](./Codeforces/2035/2035D.cpp)

## 2025年4月

### 4.1

#### [Monster](https://codeforces.com/contest/2035/problem/E)

Tag: 整除分块

CF Rating: 2300

简单的贪心结论：一定是先升级若干次（中间可能强行发动攻击若干次）后，只发动攻击不升级，直到怪物死亡。

考虑没有限制升级 $k$ 次后强行发动攻击的限制，那么显然有：如果你攻击次数相同，那么升级没有用。攻击次数的计算公式是：$\lceil \frac{n}{d} \rceil$，所以可以想到整除分块，因为对于 $\lceil \frac{n}{d} \rceil$ 相等的 $d$，代价都是一样的。

这是一个上取整的整除分块，和下取整的有所不同。因为上取整的公式为 $\lceil \frac{n}{d} \rceil = \lfloor\frac{n + d - 1}{d}\rfloor$。所以 $\lceil \frac{n}{x} \rceil = \lceil \frac{n}{y} \rceil$ 等价于 $\lfloor \frac{n - 1}{x} \rfloor = \lfloor \frac{n - 1}{y} \rfloor$。这就变成了一个下取整的整除分块问题了。需要注意的是当 $x \geq n$ 的时候，右端点为 $\inf$，不能直接计算，会出现除零错误。其实这个问题在下取整的时候也是存在的，只是似乎见的比较少所以都没注意而已。

```cpp
for (int x = 1; x <= n; ++x) {
    i64 l = x;
    i64 r = min(n, x >= m ? INF : (m - 1) / ((m - 1) / x));
    f((m + x - 1) / x);
    x = r;
}
```

考虑按照被迫使用攻击操作的次数进行分类。那么就有自带等级，并且怪物血量被提前削减，这都是容易解决的。只要你升级次数在 $k$ 以内就不会出现被迫发动攻击的情况。这个时候就可以使用上面提到的解法解决了。

[Code](./Codeforces/2035/2035E.cpp)

### 4.3

#### [红魔塔](https://ac.nowcoder.com/acm/contest/106509/A)

水题, [Code](./nowcoder/牛客练习赛136/A.cpp)

#### [冰冻青蛙](https://ac.nowcoder.com/acm/contest/106509/B)

水题, [Code](./nowcoder/牛客练习赛136/B.cpp)

#### [灵梦的字符串问题](https://ac.nowcoder.com/acm/contest/106509/C)

Tag: 模拟, 贪心

注意到如果当前字符比后面第一个和当前字符不相等的字符大，那么一定是有操作后的字典序小于不操作的。考虑到有代价限制，所以是优先选择靠前的位置操作。但是这样有一个问题，如果是相同的一段字符，那么选择哪个字符都是一样的，所以在这种情况下是优先选择代价小的。

那么一个比较优雅的写法就是将成块的字符对代价数组 $a$ 排序，这样就能统一成：靠前的操作点优先选择。

[Code](./nowcoder/牛客练习赛136/C.cpp)

#### [幽幽子的魔法宴会](https://ac.nowcoder.com/acm/contest/106509/D)

Tag: 贪心，思维

注意到如果我 $x$ 的最高位固定，那么进行操作的 $a_i$ 也是确定的。所以考虑枚举 $x$ 的最高位，然后先尝试拉满贡献，然后再考虑降低代价。

枚举 $x$ 的最高位：如果 $a_i$ 在该位为 $1$，那么这个数不进行操作，否则这个数一定进行操作。

拉满贡献：因为哪些数进行操作是已知的，这样对于每一个位，可以通过投票的方式少数服从多数来决定这位是否为 $1$。

拉满贡献之后如果是满足要求的，那么考虑降低代价。从高位到低位考虑每个 $1$ 的位置，如果可以删除就删除，也是经典贪心了。

坑点：特判 $x = 0$，因为枚举最高位的时候没有考虑不存在最高位。没判这个调红温了。

[Code](./nowcoder/牛客练习赛136/D.cpp)
