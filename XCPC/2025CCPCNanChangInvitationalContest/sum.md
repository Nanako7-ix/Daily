# NCCPC

> 单挑，菜，[传送门](https://qoj.ac/contest/2521)

## A. 扭蛋

> 二分，贪心

至少需要多少币可以抽完所有扭蛋。显而易见：二分。然后考虑最坏的情况，每次抽都是抽重复的，而且是品质最低的（也就是数量最多）扭蛋。然后考虑把多的扭蛋换新扭蛋，看看是否可行。这样做的时间复杂度是 $O(\log^2 n)$

```cpp
void Thephix() {
	int n, k;
	cin >> n >> k;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	sort(a.begin() + 1, a.end(), greater {});
	for (int i = 1; i <= n; ++i) {
		a[i] += a[i - 1];
	}

	auto check = [&](int x) -> bool {
		int p = lower_bound(a.begin() + 1, a.end(), x) - a.begin();
		int rest = x - p;
		return p + rest / k >= n;
	};

	int l = 1, r = a[n], res = -1;
	while (l <= r) {
		int m = (l + r) >> 1;
		if (check(m)) {
			res = m, r = m - 1;
		} else l = m + 1;
	}
	assert(res != -1);
	cout << res << "\n";
}
```

## B. 精神胜利

如果这是一个 DAG 的话，那么可以 $O(n^2)$ 做，所以我们考虑 SCC 缩点！然后我们打表看一下这写 scc 怎么回事。一看，我草只有一个 $5000$ 的 scc。那么办法了，直接打表观察一下距离数组吧。我草，怎么只有 $1$ 和 $2$（这里指的是边的数量）。$1$ 的情况我们可以 $O(1)$ 判，如果不是 $1$ 就是 $2$ 了。这样在 $n$ 很小的时候，暴力 floyd，否则就用这种玄学方法判断。

那这个为啥能对呢。我们考虑 $u \rightarrow v$ 的长度为 $2$ 的路径不存在的情况。那么就是对于任意一个中转点 $x$，满足 $(u, x)$ 不存在或 $(x, v)$ 不存在。这个事件的概率为 $\frac{3}{4}$。所以长度为 $2$ 的路径不存在的概率为 $(\frac{3}{4})^{n-2}$。在 $n$ 足够大的情况下，这条路径几乎是必然存在的，所以不是 $1$ 就是 $2$。

卡了个最优解！虽然没有赛时出，但是最优解，精神胜利了。

![alt text](/image/XCPC/2025NCCPC.png)

```cpp
void Thephix() {
	int n, q;
	cin >> n >> q;

	vector<string> a(n);
	for (int i = 1; i < n; ++i) {
		cin >> a[i];
	}

	if (n <= 20) {
		vector dp(n + 1, vector<int> (n + 1));
		for (int i = 1; i < n; ++i) {
			for (int j = 0; j < n - i; ++j) {
				dp[i][i + j + 1] = a[i][j] == '1' ? 1 : n;
				dp[i + j + 1][i] = n + 1 - dp[i][i + j + 1];
			}
		}

		for (int k = 1; k <= n; ++k) {
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
				}
			}
		}
		
		while (q--) {
			int u, v;
			cin >> u >> v;
			if (dp[u][v] == n) {
				cout << "-1\n";
			} else {
				cout << dp[u][v] - 1 << "\n";
			}
		}
	} else {
		while (q--) {
			int u, v;
			cin >> u >> v;
			if (u < v) {
				cout << (a[u][v - u - 1] == '1' ? "0\n" : "1\n");
			} else {
				cout << (a[v][u - v - 1] == '1' ? "1\n" : "0\n");
			}
		}
	}
}
```

## C. 虫洞

> 呜呜呜，被透了！有点可惜，赛前听到了解法。

一个看起来很显然，但是仔细一想感觉不太好证，但是认真想还是不难证明的结论是：如果每个点被区间覆盖的次数小于等于 $k$，那么这些区间就是合法的。证明使用数学归纳法，懒得写证明了，应该很简单。

所以我们枚举每一个左端点，计算最大的右端点。这个可以双指针+线段树做。线段树做区间加，然后维护最大值即可。如果想不到双指针，好像不太可做，标记永久化可持久化线段树也不行，反正我不会。不过这个确实很难想不到双指针。

时间复杂度 $O(n\log n)$。

```cpp
struct Tag {
	int add;
	Tag (int x = 0) {
		add = x;
	}
	void apply(const Tag& v) {
		add += v.add;
	}
};

struct Info {
	int Max;
	Info (int x = 0) {
		Max = x;
	}
	void apply(const Tag& v) {
		Max += v.add;
	}
};

Info operator+(const Info& x, const Info& y) {
	return Info { max(x.Max, y.Max) };
}

void Thephix() {
	int n, k;
	cin >> n >> k;
	vector<array<int, 2>> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		auto& [l, r] = a[i];
		cin >> l >> r;
	}

	LazySegmentTree<Info, Tag> seg(n);

	auto check = [&](int p) -> bool {
		auto& [l, r] = a[p];
		seg.modify(l, r, 1);
		int Max = seg.query(1, n).Max;
		seg.modify(l, r, -1);
		return Max <= k;
	};

	auto add = [&](int p) -> void {
		auto& [l, r] = a[p];
		seg.modify(l, r, 1);
	};

	auto del = [&](int p) -> void {
		auto& [l, r] = a[p];
		seg.modify(l, r, -1);
	};

	int ans = 0;
	for (int l = 1, r = 0; l <= n; ++l) {
		while (r + 1 <= n && check(r + 1)) add(++r);
		ans = max(r - l + 1, ans);
		del(l);
	}
	cout << ans << "\n";
}
```

## D. 挑战图同构

> 不认真做牛客多校的伏笔来了。牛客多校8G，为什么建完 MST 之后写树上启发式合并+暴力平衡树乱草。然后也不反思为什么没想到直接顺序枚举边做。

路径权值为最大边权的权值类型的最短路，容易想到 MST。暴力建出两棵 MST，然后想办法判断两棵 MST **等价**。这根本做不了！

考虑从小到大枚举边，那么枚举处理完边权相同的边之后，判断两个图的连通块是否相同即可。因为连这种边权之前前面的连通块相同，连这种边权之后的连通块也相同。说明，合并的连通块之间的所有 $u \in S, v \in T$ 类型的点的距离全部被设置为当前的边权 $w$。因为连接前后连通块就是相同的，所以 $(u, v)$ 对也是相同的。

现在的问题就是如何判断连通块相同。哈希！

对于一个连通块，我们的哈希是这么做的：因为连通块具体怎么连通，我不关心，这就是一个集合。对于这个集合，哈希函数是：

$$
h(S) = \sum_{u \in S} f(u) \bmod P
$$

其中 $f(u)$ 是一个随机的权重，表示 $u$ 这个点。然后 $P$ 是随便一个模数，这里直接使用自然溢出法了。

然后我们需要的是连通块的集合相同，如果我们再次使用加法，那么会发现这个图的哈希值是固定的。那么我们使用异或哈希。然后也可以使用嵌套的哈希，类似于树哈希的那种感觉。反正哈希的方法很多，乱写就行了。这样就做完了。

所以，为什么一定要把 MST 建出来，我是傻逼。

```cpp
auto H = []() {
	constexpr int N = 100000;
	array<u64, N + 1> H {};
	mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
	for (int i = 1; i <= N; ++i) {
		H[i] = rng();
	}
	return H;
} ();

void Thephix() {
	int n, m1, m2;
	cin >> n >> m1 >> m2;

	map<int, array<vector<array<int, 2>>, 2>> E;
	for (int i = 1; i <= m1; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		E[w][0].push_back({ u, v });
	}
	for (int i = 1; i <= m2; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		E[w][1].push_back({ u, v });
	}

	array<u64, 2> Hash {};
	vector<array<u64, 2>> f(n + 1);
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < 2; ++j) {
			f[i][j] = H[i];
			Hash[j] ^= H[i];
		}
	}

	array<DSU, 2> dsu;
	dsu[0].init(n), dsu[1].init(n);

	for (auto& [w, e] : E) {
		for (int i = 0; i < 2; ++i) {
			for (auto [u, v] : e[i]) {
				u = dsu[i].find(u);
				v = dsu[i].find(v);
				if (u == v) continue;
				dsu[i].merge(u, v);
				Hash[i] ^= f[u][i] ^ f[v][i];
				f[u][i] += f[v][i];
				Hash[i] ^= f[u][i];
			}
		}
		
		if (Hash[0] != Hash[1]) {
			cout << "NO\n";
			return;
		}
	}

	cout << "YES\n";
}
```

## E. 魔法阵

> 好像是个很简单的问题（

直接暴力推式子喵。我们需要对于所有的四元组 $(i, j, k, l)$ 满足 $i < j < k < l$ 且 $c_i = c_k，c_j = c_l, c_i \neq c_j$，计算 $a_ia_ja_ka_l$ 求和。也就是这样的式子，下面做一点简单的推导：

$$
\begin{aligned}
&\sum_{i=1}^n\sum_{j=i + 1}^n\sum_{k=j + 1}^n\sum_{l=k + 1}^n a_ia_ja_ka_l[c_i=c_k][c_j=c_l][c_i\neq c_j]\\
=& \sum_{i=1}^n (a_i \sum_{j=1}^{i - 1}\sum_{k=j+1}^{i-1}\sum_{l=k+1}^{i-1} a_ja_ka_l[c_i=c_k][c_j=c_l][c_i\neq c_j])\\
=& \sum_{i=1}^n (a_i \sum_{c=1}^{k} [c \neq c_i] \sum_{j=1}^{i - 1}\sum_{k=j+1}^{i-1}\sum_{l=k+1}^{i-1} a_ja_ka_l[c_j=c][c_k=c_i][c_l=c])
\end{aligned}
$$

令：

$$
f(i, x, y) = \sum_{j=1}^i\sum_{k=j+1}^i\sum_{l=k+1}^i a_ja_ka_l[c_j=x][c_k=y][c_l=x]
$$

那么：

$$
\operatorname{ans} = \sum_{i=1}^n a_i \sum_{c=1}^{k}[c \neq c_i]\cdot f(i-1,c, c_i)
$$

如果我们可以处理出这个 $f(i, x, y)$ 那么我们就可以 $O(nk)$ 计算答案。这个东西我们似乎可以滚动的来处理。假设我们已经计算出了 $f(i - 1, x, y)$，那么：

$$
\begin{aligned}
f(i, x, y) &= \sum_{j=1}^i\sum_{k=j+1}^i\sum_{l=k+1}^i a_ja_ka_l[c_j=x][c_i=y][c_l=x]\\
&= a_i\cdot[c_i=x]\cdot\sum_{j=1}^{i-1}\sum_{k=j+1}^{i-1} a_ja_k[c_j=x][c_i=y] + f(i-1, x, y)
\end{aligned}
$$

更进一步：

$$
f(i, x, y) = f(i - 1, x, y) + 
\begin{cases}
a_i\cdot\sum\limits_{j=1}^{i-1}\sum\limits_{k=j+1}^{i-1} a_ja_k[c_j=x][c_k=y] & x = c_i\\
0 & x \neq c_i
\end{cases}
$$

如果我们可以预处理出：

$$
\sum_{j=1}^{i-1}\sum_{k=j+1}^{i-1} a_ja_k[c_j=x][c_k=y]
$$

那么我们就可以通过枚举 $y$ 来做到 $O(k)$ 地更新 $f(i, x, y)$。注意这里 $x$ 是不需要枚举的，因为只有 $x = c_i$ 的情况下，$f(i, x, y) \neq f(i-1,x,y)$。

令：

$$
g(i, x, y) = \sum_{j=1}^i\sum_{k=j+1}^i a_ja_k[c_j=x][c_k=y]
$$

这个东西是不是挺熟悉的，和 $f$ 长得差不多，那么我们采用相同的处理方式，我们滚动更新这个东西。

$$
g(i, x, y) = a_i\cdot[c_i = y]\cdot\sum_{j=1}^{i-1}a_j[c_j=x] + g(i-1,x,y)
$$

然后：

$$
g(i,x,y) = g(i-1,x,y) + 
\begin{cases}
a_i\cdot\sum\limits_{j=1}^{i-1}a_j[c_j=x] & y = c_i\\
0 & y \neq c_i
\end{cases}
$$

接下来的事就很熟悉了，我们可以通过枚举 $x$ 来 $O(k)$ 更新 $g$，前提是我们需要知道 $\sum\limits_{j=1}^{i-1}a_j[c_j=x]$。令：

$$
h(i, x) = \sum_{j=1}^i a_j[c_j=x]
$$

这个东西终于是可以被预处理的了（当然也能在线）。所以我们预处理这个，然后倒着一步一步更新 $g$ 和 $f$。这样，这个问题就被我们一层一层地解剖开然后逐个击破了。时间复杂度 $O(nk)$。

```cpp
void Thephix() {
	int n, k;
	cin >> n >> k;

	vector<i64> c(n + 1), a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> c[i];
	}
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	Z ans = 0;
	vector f(k + 1, vector<Z> (k + 1));
	vector g(k + 1, vector<Z> (k + 1));
	vector h(k + 1, Z(0));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= k; ++j) {
			if (j == c[i]) continue;
			ans += f[j][c[i]] * a[i];
		}
		for (int y = 1; y <= k; ++y) {
			f[c[i]][y] += g[c[i]][y] * a[i];
		}
		for (int x = 1; x <= k; ++x) {
			g[x][c[i]] += h[x] * a[i];
		}
		h[c[i]] += a[i];
	}
	cout << ans << "\n";
}
```

## G. 玻璃碎晶

> 签到，唐了一发，看错题了，以为是直接除以 $3$ 下取整即可。

总之先三个三个分，然后发现会有剩下的。如果剩下 $0$ 个直接输出答案，如果剩 $2$ 个，直接把这两个塞到任意一个冰晶中间即可。如果剩下 $1$ 个，只能将现有的两个冰晶合并成偶数，然后再用这 $1$ 个来变成奇数。注意不存在，也就是 $0$ 的情况输出 $-1$

```cpp
void Thephix() {
	int n;
	cin >> n;
	int x = n / 3, y = n % 3;
	if (y == 1) x--;
	if (x == 0) x--;
	cout << x << "\n";
}
```

## H. 珍珠链

> 贪心，模拟

首先，我会判断 $-1$。因为最小的情况就是 $1, 2, 3, \cdots$ 这样。所以如果出现 $a_i > i$ 的情况，直接判 $-1$ 即可。剩下的情况一定可以构造出来，因为只需要把 iota 的序列构造出来之后，无脑往上加即可。

首先根据贪心，一定是在能停留的时候停留，这种情况下，后续填的数会大一点，这样减少了操作 $2$ 的次数。什么是能停留呢？首先前面有数字需要加，其次，后面填的数字需要足够大。我们让 $a_i - i$ 表示可以允许停留的次数，这样在 $[1, i]$ 处停留的总次数应该小于等于 $\min\limits_{j = i + 1}^n(a_j - j)$。

```cpp
void Thephix() {
	int n;
	cin >> n;
	vector<i64> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	vector<i64> f(n + 1);
	for (int i = 1; i <= n; ++i) {
		f[i] = a[i] - i;
		if (f[i] < 0) {
			cout << "-1\n";
			return;
		}
	}

	for (int i = n - 1; i >= 1; --i) {
		f[i] = min(f[i + 1], f[i]);
	}
	
	i64 sum = 0, p = 0;
	for (int i = 1; i <= n; ++i) {
		i64 x = min({ sum, f[i] - (p + 1 - i) });
		sum -= x, p += x + 1;
		assert(p <= a[i]);
		sum += a[i] - p;
	}

	cout << p + sum << "\n";
}
```

## I. 二维弹球

> welken 教我的，我是物理飞舞

小球会往两个比较矮的边运动，然后直接分解这两个方向，发现分别是上抛运动。然后就做完了。剩下的就是简单的计算几何问题了。

如果距离 $h$ 或加速度 $a$ 小于 `eps` 的话返回零向量，不然会 wa。我也不懂为什么，唉唉几何是这样的。

```cpp
constexpr double pi = numbers::pi_v<double>;
constexpr double eps = 1e-5;

void Thephix() {
	Point<double> p;
	array<Point<double>, 4> a {};
	cin >> a[0] >> a[1] >> a[2] >> a[3] >> p;
	
	array<Point<double>, 2> L1, L2;
	if (min(a[0].y, a[1].y) < min(a[2].y, a[3].y)) {
		L1 = { a[0], a[1] };
	} else {
		L1 = { a[2], a[3] };
	}

	if (min(a[01].y, a[2].y) < min(a[3].y, a[0].y)) {
		L2 = { a[1], a[2] };
	} else {
		L2 = { a[3], a[0] };
	}

	int n;
	cin >> n;

	auto f = [&](const array<Point<double>, 2>& line) -> Point<double> {
		Point<double> v = (line[1] - line[0]).rotate(pi / 2);
		v /= v.length();

		double a = abs(v.dot(Point<double> (0, -10)));
		double h = abs((line[1] - p).dot(v));

		if (a < eps || h < eps) {
			return Point<double>  { 0, 0 };
		}

		double T = 2 * sqrt(2 * h / a);
		double t = n - floor(n / T) * T;
		t = min(t, T - t);

		return v * (a * t * t / 2);
	};
	
	p += f(L1) + f(L2);
	cout << p.x << ' ' << p.y << "\n";
}
```

## K. 不许偷吃

> 最糖的一集！输出 $-1$ 之后忘记 `return` 了！我草！

注意到只需要考虑 $a_i \bmod 4$ 之后的结果即可。假设我们不需要构造答案，只需要输出是否可以完成。其实两个问题差不多难度。

现在你只需要考虑 $0, 1, 2, 3$ 四种数字出现的次数。你需要做的是构造一个数字使得它在 ${}\bmod 4$ 意义下的前缀和数组不出现 $1$。首先你需要注意的是，$0$ 是没用的。其次：$1$ 和 $3$ 是棘手的，因为可能会带来 $1$。但是 $1$ 和 $3$ 可以相互抵消！这种情况下你可以 $313131$ 地构造数组。这样你就只需要考虑只有 $1$ 或者只有 $3$ 的情况了。然后这个手玩一下就很容易发现是 $332$ 和 $211$ 这样构造数组。于是就做完了。由于和一定是 $0$，所以 $3$ 和数量和 $1$ 的数量一定是同奇偶的，这样剩下的 $1$ 的数量或者 $3$ 的数量一定是偶数。这样构造就很简单，只需要判断 $2$ 是否足够即可。多出来的 $2$ 也是没用的，和 $0$ 一样处理，直接全部塞到数组结尾即可。

```cpp
void Thephix() {
	int n;
	cin >> n;
	array<vector<int>, 4> pos {};
	array<int, 4> cnt {};
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		pos[a[i] % 4].push_back(i);
		cnt[a[i] % 4]++;
	}	
	
	vector<int> ans;

	int x = min(cnt[1], cnt[3]);
	cnt[1] -= x, cnt[3] -= x;
	for (int i = 1; i <= x; ++i)  {
		ans.push_back(pos[3].back()), pos[3].pop_back();
		ans.push_back(pos[1].back()), pos[1].pop_back();
	}

	if (cnt[1] == 0) {
		if (cnt[3] / 2 <= cnt[2] + 1) {
			while (!pos[3].empty()) {
				ans.push_back(pos[3].back()), pos[3].pop_back();
				ans.push_back(pos[3].back()), pos[3].pop_back();
				ans.push_back(pos[2].back()), pos[2].pop_back();
			}
		} else {
			cout << "-1\n";
			return;
		}
	} else if (cnt[3] == 0) {
		if (cnt[1] / 2 <= cnt[2]) {
			while (!pos[1].empty()) {
				ans.push_back(pos[2].back()), pos[2].pop_back();
				ans.push_back(pos[1].back()), pos[1].pop_back();
				ans.push_back(pos[1].back()), pos[1].pop_back();
			}
		} else {
			cout << "-1\n";
			return;
		}
	}

	for (auto x : pos[2]) {
		ans.push_back(x);
	}
	for (auto x : pos[0]) {
		ans.push_back(x);
	}
	for (auto x : ans) {
		cout << x << ' ';
	}
	cout << "\n";
}
```

## L. 羽球比赛

> 原来这个才是签到题

```cpp
void Thephix() {
	int x, y;
	cin >> x >> y;
	if (x >= 30 || (x >= 21 && x - y >= 2)) {
		cout << "Alice\n";
	} else if (y >= 30 || (y >= 21 && y - x >= 2)) {
		cout << "Bob\n";
	} else {
		cout << "Underway\n";
	}
}
```
