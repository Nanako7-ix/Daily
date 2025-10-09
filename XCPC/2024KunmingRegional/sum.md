## B. Brackets

> 看了一眼题解之后，会了一点，发现好像只能每个查询单独处理（不会 `l++`）再看一下，发现可以从 $1$ 开始，观察一下可能就会做了

首先题意是：给你 $m$ 个区间，在这 $m$ 个区间内找 $k$ 对区间 $(i, j)$，使得每对区间满足 $S(l_{i}, r_{i})+S(l_{j}, r_{j})$ 为合法括号序列。这 $k$ 对区间不能重复选取。

那么一定是 $S(l_i, r_i)$ 提供左括号，$S(l_j, r_j)$ 提供右括号（可能为空）根据样例 `([)` 不算合法括号序列的提醒，容易想一个 $O(nq)$ 的解法。直接对每个查询计算是否为合法左区间，合法右区间。然后将到时候组合一下。

看了一下题解，有更智慧的解法。首先我们从左到右匹配括号，带上查询的左端点。如果遇到了查询的右端点，那就结算一下这个查询究竟提供了怎样的左括号（哈希值）。如果遇到了没有匹配上的右括号（没有**对应**的左括号）那么说明还没结算的左端点全似了。换句话说，包含了这个位置的所有区间都不是合法的左区间。

如果现在的括号全是正常匹配的，并且正常触发了结算。那么这个字符串不一定是对的，因为少了 $[1, l)$ 这一部分。那怎么判断是不是对的呢。

这里需要一点小小的观察：括号的匹配一定是固定的。那么把所有的括号一视同仁计算，然后直接判断即可。从左到右扫一遍，计算合法左区间，然后从右到左再扫一遍，计算合法右区间。组合一下即可。

需要特殊处理可以互换的情况，即 $S(l_i, r_i)$ 和 $S(l_j, r_j)$ 均为合法括号序列。

```cpp
using Z = ModInt<u32, 998244353>;

mt19937_64 rng((random_device())());
const array<Z, 4> h { rng(), rng(), rng(), rng() };

constexpr array<Z, 2> Base { 131, 13331 };

constexpr int N = 500000;
array<array<Z, 2>, N> f = []() {
	f[0] = { 1, 1 };
	for (int i = 1; i < N; ++i) {
		f[i][0] = f[i - 1][0] * Base[0];
		f[i][1] = f[i - 1][1] * Base[1];
	}
	return f;
} ();

Z Hash(char ch) {
	if (ch == '(' || ch == ')') return h[0];
	if (ch == '[' || ch == ']') return h[1];
	if (ch == '{' || ch == '}') return h[2];
	if (ch == '<' || ch == '>') return h[3];
	__builtin_unreachable();
}

void Thephix() {
	int n, m;
	string s;
	cin >> n >> m >> s;

	vector<array<int, 2>> a(m + 1);
	vector<vector<int>> query(n + 1);
	for (int i = 1; i <= m; ++i) {
		auto& [l, r] = a[i];
		cin >> l >> r;
	}

	auto solve = [&]() -> map<array<i64, 2>, int> {
		map<array<i64, 2>, int> cnt;

		vector<int> pre(n + 1);
		for (int i = 1; i <= n; ++i) {
			if (s[i] == '(' || s[i] == '[' || s[i] == '<' || s[i] == '{') {
				pre[i] = pre[i - 1] + 1;
			} else pre[i] = pre[i - 1] - 1;
		}
		SparseTable Min(pre.begin() + 1, pre.end(), [](int x, int y) {
			return std::min(x, y);
		});
	
		auto check = [&](int l, int r) -> bool {
			assert(l <= r);
			return Min(l, r) >= pre[l - 1];
		};
		
		int err = 0;
		vector<int> stk;
		vector<array<Z, 2>> hash;
		for (int r = 1; r <= n; ++r) {
			char ch = s[r];
			if (ch == '(' || ch == '[' || ch == '{' || ch == '<') {
				stk.push_back(r);
				Z x = 0, y = 0;
				if (!hash.empty()) {
					tie(x, y) = hash.back();
				}
				hash.push_back({
					x * Base[0] + Hash(ch),
					y * Base[1] + Hash(ch)
				});
			} else if (stk.empty() || Hash(ch) != Hash(s[stk.back()])) {
				stk.clear(), hash.clear(), err = r;
			} else {
				stk.pop_back(), hash.pop_back();
			}
	
			int k = stk.size() - 1;
			for (auto l : query[r]) {
				if (l <= err || !check(l, r)) continue;
				auto it = lower_bound(stk.begin(), stk.end(), l);
				if (it != stk.end()) {
					int p = it - stk.begin();
					auto [x, y] = hash.back();
					if (p != 0) {
						x -= hash[p - 1][0] * f[k - p + 1][0];
						y -= hash[p - 1][1] * f[k - p + 1][1];
					}
					cnt[{ x.val(), y.val() }]++;
				} else cnt[{ 0, 0 }]++;
			}
		}
		return cnt;
	};

	s = '$' + s;
	for (int i = 1; i <= m; ++i) {
		auto [l, r] = a[i];
		query[r].push_back(l);
	}
	map<array<i64, 2>, int> cntL = solve();

	for (int i = 1; i <= n; ++i) query[i].clear();
	for (int i = 1; i <= m; ++i) {
		auto [l, r] = a[i];
		query[n - l + 1].push_back(n - r + 1);
	}
	reverse(s.begin() + 1, s.end());
	for (int i = 1; i <= n; ++i) {
		if (s[i] == '(' || s[i] == ')') s[i] ^= '(' ^ ')';
		if (s[i] == '[' || s[i] == ']') s[i] ^= '[' ^ ']';
		if (s[i] == '{' || s[i] == '}') s[i] ^= '{' ^ '}';
		if (s[i] == '<' || s[i] == '>') s[i] ^= '<' ^ '>';
	}
	map<array<i64, 2>, int> cntR = solve();

	int ans = 0;
	for (auto [x, y] : cntL) {
		if (x[0] != 0 || x[1] != 0) {
			ans += min(cntR[x], y);
		}
	}

	cout << ans + cntL[{ 0, 0 }] / 2 << "\n";
}
```

## C. Coin

> 赛时借用了 oeis 之力直接破解了递推（

豪难！！！！这种题完全没有下手点，只会打表了。

假设我们对逐轮模拟，那么显然是 $O(n\log n)$ 的。这是赛时能想到的最好的解法（

不行，$n$ 太大了，有没有更智慧的解法？我们知道这一轮会杀掉 $\lceil\frac{n}{k}\rceil$ 个人，那么杀掉之后是一个 $f(n - \lceil\frac{n}{k}\rceil)$ 的子问题。

假设我们已经知道了这个子问题的答案，能不能快速计算出这是第几个人？可以的，而且还挺简单的。

$$
\begin{aligned}
x' &= k\cdot\lceil\frac{x}{k - 1}\rceil + x \bmod (k - 1)\\
&= k\cdot\lceil\frac{x}{k - 1}\rceil + x - (k-1)\cdot\lceil\frac{x}{k - 1}\rceil\\
&= x + \lceil\frac{x}{k - 1}\rceil
\end{aligned}
$$

这个时候你就会发现和 $n$ 没有关系了，为什么呢。这个你可以画一个图，$f(n)$ 表示点权，然后连边表示本轮淘汰后剩下多少人。于是你发现这棵树非常神奇，它的层次遍历是 $1, 2, 3, 4\cdots$，而每层的点权也就是答案都是一样的。所以我们只需要一直加等于 $\lceil\frac{x}{k - 1}\rceil$ 直到这个数超过 $n$ 即可。

事实上，这个就是 oeis 给出的式子。直接嗯算即可。注意 $\lceil\frac{x}{k - 1}\rceil$ 这个东西在 $k$ 很大的时候，有一段范围内的都是相等的，不要暴力地一次一次加，计算一下需要加多少次然后一口气加上去。

```cpp
void Thephix() {
	i64 n, k;
	cin >> n >> k;

	i64 x = 1;
	while (true) {
		i64 d = (x + k - 2) / (k - 1);
		if (x + d > n) break;
		i64 t = min((n - x) / d, k - 2 - (x - 1) / d);
		if (t == 0) t = 1;
		x += d * t;
	}
	cout << x << "\n";
}
```

## E. Extracting Weights

> 高斯消元 & 线性基

直接枚举 $n^2$ 对点，然后看这 $n^2$ 对点能不能解出这个问题。怎么判断能不能解出来呢？我们把方程组列一下：

$$
\begin{aligned}
a_{11}w_1 \oplus a_{12}w_2 \oplus a_{13}w_3 \oplus \cdots \oplus a_{1n}w_n &= b_1\\
a_{21}w_1 \oplus a_{22}w_2 \oplus a_{23}w_3 \oplus \cdots \oplus a_{2n}w_n &= b_2\\
\cdots\\
a_{m1}w_1 \oplus a_{m2}w_2 \oplus a_{m3}w_3 \oplus \cdots \oplus a_{mn}w_n &= b_m\\
\end{aligned}
$$

这个方程组求解起来就是需要满足系数矩阵的秩为 $n$。用线性基插入方程组，如果线性相关那么就不需要查询这条连边。

一共 $n^2$ 次插入，每次插入时间复杂度为 $O(\frac{n^2}{64})$。

如果满足系数矩阵的秩为 $n$，那么高斯消元。时间复杂度 $O(n^3)$。

```cpp
constexpr int N = 250;

void Thephix() {
	int n, k;
	cin >> n >> k;
	vector<vector<int>> adj(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	array<bitset<N>, N> basis {};
	vector<tuple<bitset<N>, int, int>> query;

	auto insert = [&](bitset<N> x, int u, int v) {
		bitset<N> _x(x);
		for (int i = N; i >= 0; --i) {
			if (x[i] == 0) continue;
			if (basis[i] == 0) {
				basis[i] = x;
				query.emplace_back(_x, u, v);
				return;
			}
			x ^= basis[i];
		}
	};

	insert(bitset<N>(1), 1, 1);
	for (int u = 1; u <= n; ++u) {
		vector<int> dep(n + 1), fa(n + 1);
		
		[&](this auto&& dfs, int u) -> void {
			dep[u] = dep[fa[u]] + 1;
			for (auto& v : adj[u]) {
				if (v == fa[u]) continue;
				fa[v] = u;
				dfs(v);
			}
		} (u);

		for (int v = 1; v <= n; ++v) {
			if (dep[v] != dep[u] + k) {
				continue;
			}
			bitset<N> x;
			for (int w = v; w; w = fa[w]) {
				x[w - 1] = 1;
			}
			insert(x, u, v);
		}
	}

	if ((int) query.size() != n) {
		cout << "NO" << endl;
		return;
	}

	cout << "YES" << endl;
	cout << "? " << n - 1 << " ";
	for (int i = 0; i < n; ++i) {
		auto& [x, u, v] = query[i];
		if (u == v) continue;
		cout << u << ' ' << v << " ";
	}
	cout << endl;

	vector A(n, vector<int> (n + 1));
	for (int i = 0; i < n; ++i) {
		auto& [x, u, v] = query[i];
		for (int j = 0; j < n; ++j) {
			A[i][j] = x[j];
		}
		if (u != v) cin >> A[i][n];
	}

	for (int j = 0; j < n; ++j) {
		for (int i = j; i < n; ++i) {
			if (A[i][j] == 0) continue;
			if (i != j) swap(A[i], A[j]);
			break;
		}
		for (int i = 0; i < n; ++i) {
			if (i == j || A[i][j] == 0) continue;
			for (int k = j; k <= n; ++k) {
				A[i][k] ^= A[j][k];
			}
		}
	}

	cout << "! ";
	for (int i = 1; i < n; ++i) {
		cout << A[i][n] << " ";
	}
	cout << endl;
}
```

### 关于异或的向量空间

定义：

$$
V_k = \{x \in \N^+| x < 2^k \}
$$

$F_2$ 为模 $2$ 域。

定义向量加法：

$$
x, y\in V_k\\
x+y = x \oplus y\\
$$

定义标量乘法：

$$
x \in V_k, k \in F_2\\
k \times x = k\cdot x
$$

则 $V_k$ 为定义在域 $F_2$ 上的向量空间。

proof：

- $\forall u \in V_k,0 \oplus u = u$
- $\forall u \in V_k, u \oplus u = 0$
- $\forall u, v \in V_k, u \oplus v = v \oplus u$
- $\forall u, v, w \in V_k, (u \oplus v) \oplus w = u \oplus (v \oplus w)$
- $\forall u \in V_k, 1\cdot u = u$
- $\forall u,v\in V_k,\forall a\in F_2,a\cdot (u\oplus v)=a\cdot u\oplus a\cdot v$
- $\forall u \in V_k, a,b \in F_2, (a+b)\cdot u=a\cdot u\oplus b\cdot u$
- $\forall u \in V_k, a,b \in F_2, a\cdot (b\cdot u)=(a\times b)\cdot v$

显然不难验证。

这个向量空间非常特殊，特殊就特殊在：$V_k = F_2^k$。

所以这题就是：$AX = b$。在高斯消元的时候，以 $A = F_2^{m\times n}$ 的角度看待系数矩阵，在判断是否线性相关的时候，用 $V_n^m$ 的角度看待系数矩阵。还是有点色情的，我磕 $V_k$ 和 $F_2$ 这对。

## G. GCD

> 直接暴力就过了，太神秘了，赛时也在喷是傻逼题

直接暴力 bfs 做即可。题意是选择 $a$ 或 $b$ 的其中一个正数，然后将这个数减小 $\gcd(a, b)$。这个操作次数是 $\log$ 级别的，理由如下。

如果 $a, b$ 都是偶数，那么他们的 $\gcd$ 也是偶数。于是 $a - \gcd(a, b)$ 和 $b - \gcd(a, b)$ 也都是偶数。以后的任意次操作之后，$a, b$ 都是偶数，所以我们令 $a = \frac{a}{2}$，$b = \frac{b}{2}$，不影响操作次数。

如果 $a, b$ 中有至少一个不是偶数，那么可以 $\gcd(a, b)$ 一定是奇数。我们对奇数减去这个 $\gcd$ 就可以把它变成偶数。所以这个操作次数是非常少的，因此直接暴力搜索是对的。

因为需要最少操作次数，使用 bfs 而不是 dfs。

如果我们不考虑 $a - \gcd(a, b)$ 和 $b - \gcd(a, b)$，而是考虑减去它的一个公因子。这题似乎差的不是很多。当然确实差的挺多，但是依旧是 $\log$ 次的。参考 2025fjcpc 的 J 题构造，可以有所启发。

> 2025 fjcpc J：给你一个数 $x$ 每次选择 $x$ 的一个因子 $d$，然后令 $x$ 加上 $d$，这里 $d$ 不能重复选择。构造一个方案使得 $x$ 变成完全平方数。

构造方案：每次加上这个数的 lowbit 直到成立为止。

证明：lowbit 一定是因子，lowbit 单调递增。

推论：$\min(\operatorname{lowbit}(x), \operatorname{lowbit}(y))$ 是 $x, y$ 的共因子。

本题中，每次操作一定会改变一个数的 lowbit，lowbit 最多改变 log 次（根据单调递增）烧烤一下，有点意思这个思路，不是很会形容这种感觉，可能因为我太菜了根本学不到精髓。

**启发：加减法对于因子来说是很不友好的，因为操作完之后会改变因子，但是我们可以从二进制和 lowbit 的角度考虑。**

```cpp
void Thephix() {
	i64 a, b;
	cin >> a >> b;

	vector<HashMap<i64, bool>> vis(a + 1);
	
	queue<array<i64, 3>> q;
	q.push({ a, b, 0 });
	while (!q.empty()) {
		auto& [x, y, t] = q.front();
		q.pop();

		int d = gcd(x, y);

		if (x == d || y == d) {
			cout << t + 2 << "\n";
			return;
		}

		if (vis[x - d][y] == 0) {
			vis[x - d][y] = 1;
			q.push({ x - d, y, t + 1 });
		}

		if (vis[x][y - d] == 0) {
			vis[x][y - d] = 1;
			q.push({ x, y - d, t + 1 });
		}
	}
}
```

## H. Horizon Scanning

> 极角排序

赛时被判 $0$ 和 $2\pi$ 之类的地方卡了。后面提议直接用 double 存，然后复制一遍数组的时候加上 $2\pi$，这样就可以无脑后面的减前面的了。

这题可能用 eps 也做不到。原本使用的是 $\Delta_{\theta} < 0$ 就判断这是属于绕了一圈的情况，所以需要加上 $2\pi$。但是如果给出来的所有点都是相同极角的，那么就判断不出来什么时候绕了一圈。

总之好像怎么改都不太对的样子。最终还是出现了需要输出 $2\pi$ 但是没有判到的情况。

几何豪难！

```cpp
void Thephix() {
	int n, k;
	cin >> n >> k;
	vector<double> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		int x, y;
		cin >> x >> y;
		a[i] = atan2(y, x);
	}

	sort(a.begin() + 1, a.end());
	for (int i = 1; i <= n; ++i) {
		a.push_back(2 * pi + a[i]);
	}

	double ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans = max(ans, a[i + k] - a[i]);
	}
	cout << ans << "\n";
}
```

## I. Item

> 首先拷打我自己，为什么这么典的问题，没有想到生成函数？为什么没想到，你他妈的是傻逼吗？这不就是他妈的生成函数入门题吗，这是在干什么？怎么能想不到生成函数的？！

你给 $n$ 种物品，问你能不能在其中选择恰好 $n$ 件物品，使得重量恰好为 $m$。这里 $m$ 的范围达到了 $n^2$ 的级别。

## L. Last Chance: Threads of Despair

> 要是正式比赛能有这么好的发挥就好了。

需要一些非常关键的结论。

首先：我们猜测，爆炸的发生一定是越晚越好的，因为这样可以让我们的伤害拉满。

于是我们按照这个思路去考虑应该如何发动攻击。首先不考虑敌方随从的血量，那么一定是血量 $\geq 2$ 的我方随从攻击把伤害全打完，然后再由我方其中生命值为 $1$ 的随从攻击。之后便会发生爆炸。所以我方造成的伤害是固定的。

那万一某一次攻击之后，敌方的随从爆了怎么办呢，我方的伤害不就打不满了？这个问题其实很好解决：

如果敌方存在一个生命值不为 $1$ 的随从，那么这次攻击就打在这名随从身上，不会引发爆炸。否则敌方随从的生命值全为 $1$，那么其实我方的伤害是溢出的，打完这一刀一定全爆了。所以我们不妨假设：这个爆炸先别急着炸，当我打完伤害再炸，反正也不影响战局。

所以现在我们的结论就是：我方可以造成的伤害是固定的，那么接下来就是猜猜爆环节了。要触发连环爆炸，一定要求血量的排列为：

$$
[0, 1, 2, 3, 4, \cdots]
$$

到了这个环节，其实已经没有必要管随从是我方的还是敌方的了，反正都是要爆的。所以我们要做的是：在敌方随从最后一只似掉之前，需要构成以上的序列。那么我们直接排序之后合并两个有序数组。如果存在一只随从的血量，小于等于当前需要的血量，那么就直接把这个随从排在这里。否则就选择敌方生命值最低的随从，把它的生命值砍到这个血量之后排在这个位置。

如果需要攻击的次数大于我方允许攻击的次数，那么就是 No，否则就是 Yes。

```cpp
void Thephix() {
	int n, m;
	cin >> n >> m;
	vector<int> a(n), b(m);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	for (int i = 0; i < m; ++i) {
		cin >> b[i];
	}

	sort(a.begin(), a.end(), greater());
	sort(b.begin(), b.end(), greater());

	int cnt = a.back() == 1;
	for (int i = 0; i < n; ++i) {
		cnt += a[i] > 1;
		a[i]--;
	}

	for (int k = 0; !b.empty(); ++k) {
		if (!a.empty() && a.back() <= k) {
			a.pop_back();
		} else {
			int x = max(b.back() - k, 0);
			b.pop_back();
			if ((cnt -= x) < 0) {
				cout << "NO\n";
				return;
			}
		}
	}

	cout << "YES\n";
}
```

## J. Just another Sorting Problem

> 观察一下就会了

$n = 2$ 的时候，无论如何都是 Alice 获胜。显然的结论。

$n \geq 3$ 的时候，一开始的结论是 Bob 先手必赢，Alice 先手必须一步之内获胜，否则就输了。由于 Alice 可以任意操作，所以只需要判断 $p_i \neq i$ 的个数即可。因为如果 Alice 不能在回合结束的时候复原数组，那么 Bob 出来捣乱就一定赢了。

上面这个结论一定是错的（我都说了是一开始的结论了qwq）那么请你先别急着往下看，烧烤一下，找出 hack。

由于一定不能不操作，所以有没有可能 Bob 先手但是由于被迫操作导致下一步 Alice 直接获胜的例子呢？

$$
[3,1,2]
$$

简单而有效的 hack。所以只需要在 Bob 先手的时候判一下有没有这种情况即可。由于 Bob 只能交换相邻的，直接暴力枚举并 check 即可。

题解的结论好像更完善一点。

```cpp
void Thephix() {
	int n;
	string s;
	cin >> n >> s;

	vector<int> p(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> p[i];
	}

	if (n == 2) {
		cout << "Alice\n";
		return;
	}

	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		cnt += p[i] != i;
	}

	if (s == "Alice") {
		if (cnt > 2) {
			cout << "Bob\n";
		} else {
			cout << "Alice\n";
		}
		return;
	}

	for (int i = 2; i <= n; ++i) {
		cnt -= p[i] != i;
		cnt -= p[i - 1] != i - 1;
		swap(p[i], p[i - 1]);
		cnt += p[i] != i;
		cnt += p[i - 1] != i - 1;
		
		if (cnt > 2) {
			cout << "Bob\n";
			return;
		}
		
		cnt -= p[i] != i;
		cnt -= p[i - 1] != i - 1;
		swap(p[i], p[i - 1]);
		cnt += p[i] != i;
		cnt += p[i - 1] != i - 1;
	}
	cout << "Alice\n";
}
```

## M. Matrix Construction

打表发现，按以下方式构造出来的大概率是对的，直接交直接过

```cpp
void Thephix() {
	cout << "Yes\n";

	int n, m, tot = 0;
	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		vector<int> a(m);
		for (int j = 0; j < m; ++j) {
			a[(i * (m & 1) + j) % m] = ++tot;
		}
		for (int j = 0; j < m; ++j) {
			cout << a[j] << " \n"[j == m - 1];
		}
	}
}
```
