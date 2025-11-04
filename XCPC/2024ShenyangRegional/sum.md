# 2024 沈阳

vp 银

## J. Make Them Believe

直接模拟即可。

```cpp
void Thephix() {
	array<pair<string, int>, 8> a;
	for (int i = 0; i < 8; ++i) {
		auto& [name, x] = a[i];
		cin >> name >> x;
	}

	for (int i = 0; i < 8; i += 2) {
		if (a[i].second < a[i + 1].second) {
			swap(a[i], a[i + 1]);
		}
	}

	for (int i = 0; i < 8; i += 4) {
		if (a[i].second < a[i + 2].second) {
			swap(a[i], a[i + 2]);
		}
	}

	for (int i = 0; i < 8; i += 8) {
		if (a[i].second < a[i + 4].second) {
			swap(a[i], a[i + 4]);
		}
	}

	cout << a[0].first << " beats " << a[4].first << '\n';
}
```

## E. Light Up the Grid

好像受到记忆的影响导致想错了。

考虑一张有向图，$16$ 个点，每个点 $9$ 条出边。那么你需要找到一条包含了我所需要的所有点的路径（不含起点）的最小代价。由于点是 $16$ 个，所以包含状态是 $2^16$，所以总共的状态数是 $16\cdot 2^16$。算上转移，每个状态会被转移出去 $9$ 次，大概是 $10^7$ 的复杂度就能 dp 完了。

然后预处理完之后，对于每次查询，找到 $dp(t, *)$ 的最小代价。求超集 max 使用 sosdp 即可。

这题很烦的地方是同一层中的转移我不会处理，所以使用 dijkstra 了。哭哭。

```cpp
constexpr int n = 16;
constexpr int N = 1 << 16;
constexpr i64 inf = 4E18;

array<i64, N> f;

void init() {
	array<int, 4> a;
	cin >> a[0] >> a[1] >> a[2] >> a[3];
	
	vector<vector<array<int, 2>>> adj(n);
	for (int u = 0; u < n; ++u) {
		// 点修改
		adj[u].push_back({ u ^  1, a[0] });
		adj[u].push_back({ u ^  2, a[0] });
		adj[u].push_back({ u ^  4, a[0] });
		adj[u].push_back({ u ^  8, a[0] });
		// 行修改
		adj[u].push_back({ u ^  3, a[1] });
		adj[u].push_back({ u ^ 12, a[1] });
		// 列修改
		adj[u].push_back({ u ^  5, a[2] });
		adj[u].push_back({ u ^ 10, a[2] });
		// 全修改
		adj[u].push_back({ u ^ 15, a[3] });
	}
	
	vector dp(n, vector<i64> (N, inf));
	for (auto [v, w] : adj[0]) {
		dp[v][1 << v] = w;
	}
	for (int s = 0; s < N; ++s) {
		// 很他妈烦，这个地方会遇到 s 相同的转移/松弛，不会处理只能做一遍 dijkstra 了
		vector<int> vis(n + 1);
		priority_queue<array<i64, 2>, vector<array<i64, 2>>, greater<array<i64, 2>>> q;
		for (int u = 0; u < n; ++u) {
			if (dp[u][s] != inf) {
				q.push({ dp[u][s], u });
			}
		}
		while (!q.empty()) {
			auto [_, u] = q.top();
			q.pop();
			if (vis[u]) continue;
			vis[u] = 1;
			for (auto [v, w] : adj[u]) {
				if ((s >> v & 1) == 0) continue;
				if (dp[u][s] + w < dp[v][s]) {
					dp[v][s] = dp[u][s] + w;
					q.push({ dp[v][s], v });
				}
			}
		}

		for (int u = 0; u < n; ++u) {
			if (dp[u][s] >= inf) continue;
			for (auto [v, w] : adj[u]) {
				int t = s | (1 << v);
				dp[v][t] = min(dp[v][t], dp[u][s] + w);
			}
			f[s] = min(f[s], dp[u][s]);
		}
	}

	for (int s = 0; s < N; ++s) {
		f[s] = inf;
		for (int u = 0; u < n; ++u) {
			f[s] = min(f[s], dp[u][s]);
		}
	}

	// sosdp 对 f[s] 求超集 min
	for (int i = 0; i < n; ++i) {
		for (int s = 0; s < N; ++s) {
			if ((s >> i & 1) == 0) {
				f[s] = min(f[s], f[s | (1 << i)]);
			}
		}
	}
}

void Thephix() {
	int n;
	cin >> n;
	
	int s = 0;
	for (int i = 1; i <= n; ++i) {
		int x, y;
		cin >> x >> y;
		int get = 0;
		get |= !(x / 10) << 0;
		get |= !(x % 10) << 1;
		get |= !(y / 10) << 2;
		get |= !(y % 10) << 3;
		s |= 1 << get;
	}

	cout << f[s] << '\n';
}
```

## G. Guess the Polygon

赛时是我开的，但是因为不会处理高精度问题。甚至是根本没注意到需要高精度。

我的询问肯定是不需要高精度的。但是输入答案的时候，需要使用高精度。

考虑我任意一次查询，返回的长度应该是两个 $y$ 相减。$y$ 坐标是用 $y = k(x - x_0) + y_0$ 来计算的，这里的 $(x_0, y_0)$ 是整数，$k$ 的分母应该是一千以内的数，然后再乘上 $x$ 的分母，这里差不多是 $3000$ 的样子。两个坐标相减，考虑他们是互素的，那么分母应该是 $9\cdot 10^6$ 的样子。那么分子差不多也就是 $9\cdot 10^9$，为什么需要高精度的。

哦我草，不一定是两个 $y$ 相减。可能是一堆 $y$ 在加加减减的，所以分母最多可以到达 $\operatorname{lcm}_{k=1}^{1000} k$ 的。这个东西合理怀疑应该是很大的。

确实不会写 python。所以考虑：求面积的两倍对 998244353 取模的结果，注意到面积小于 998244353，所以取模的结果等于原来的结果。记得读入使用高精读入。

还有一种解法是：这题使用 `long double` 精度足够。

```cpp
using Z = ModInt<u32, 998244353>;
constexpr int N = 1000;

void Thephix() {
	int n;
	cin >> n;
	
	int cnt = 0;
	auto query = [&](i64 u, i64 d) -> Z {
		assert(++cnt <= n - 2);
		tie(u, d) = pair(u / gcd(u, d), d / gcd(u, d));
		cout << "? " << u << ' ' << d << endl;
		
		string s, t;
		cin >> s >> t;
		Z U = 0, D = 0;
		for (auto ch : s) U = U * 10 + ch - '0';
		for (auto ch : t) D = D * 10 + ch - '0';
		return U == 0 ? 0 : Z(U) / D;
	};

	vector<int> x(1), y(N + 1);
	for (int i = 1; i <= n; ++i) {
		int _x, _y;
		cin >> _x >> _y;
		x.push_back(_x);
		y[_x]++;
	}
	sort(x.begin() + 1, x.end());
	x.erase(unique(x.begin() + 1, x.end()), x.end());

	int m = x.size() - 1;
	vector<Z> l(m + 1), r(m + 1);
	vector<int> vis_l(m + 1), vis_r(m + 1);

	r[1] = y[x[1]] == 1 ? 0 : query(x[1], 1);
	vis_r[1] = 1;

	l[m] = y[x[m]] == 1 ? 0 : query(x[m], 1);
	vis_l[m] = 1;

	for (int i = 2; i <= m; ++i) {
		// 需要确保 vis_r[i - 1] 和 vis_l[i];
		if (!vis_l[i]) {
			if (y[x[i]] == 1) {
				l[i] = r[i] = query(x[i], 1);
				vis_l[i] = vis_r[i] = 1;
			} else if (vis_r[i - 1]) {
				int len = x[i] - x[i - 1];
				Z mid = query(x[i - 1] * 2 + len, 2);
				l[i] = mid * 2 - r[i - 1];
				vis_l[i] = 1;
			} else {
				int len = x[i] - x[i - 1];
				Z mid1 = query(x[i - 1] * 3 + len, 3);
				Z mid2 = query(x[i - 1] * 3 + len * 2, 3);
				r[i - 1] = 2 * mid1 - mid2;
				l[i] = 2 * mid2 - mid1;
				vis_l[i] = vis_r[i - 1] = 1;
			}
		}

		if (!vis_r[i - 1]) {
			int len = x[i] - x[i - 1];
			Z mid = query(x[i - 1] * 2 + len, 2);
			r[i - 1] = mid * 2 - l[i];
			vis_r[i - 1] = 1;
		}
	}

	Z ans = 0;
	for (int i = 2; i <= m; ++i) {
		ans += (x[i] - x[i - 1]) * (r[i - 1] + l[i]);
	}

	int S = ans.val();
	if (S % 2 == 0) {
		cout << "! " << S / 2 << ' ' << 1 << endl;
	} else {
		cout << "! " << S << ' ' << 2 << endl;
	}
}
```

## D. Dot Product Game

首先注意到，顺序是没有用的，我们只需要考虑他们的匹配关系。不妨在保证匹配关系的前提下，让 $a$ 变成 $[1, 2, 3, \cdots, n]$。这种时候，dot 最小一定是逆序对为 $0$ 的时候，每次操作都会改变逆序对的奇偶性，所以如果当前逆序对有奇数对，那么最后一次操作一定是 alice 做的，否则是 bob 做的。

考虑一次操作，注意到逆序对奇偶性的变化次数为：$(r - l) \cdot d$。就做完了。

```cpp
void Thephix() {
	int n;
	cin >> n;
	vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; ++i) {
		cin >> b[i];
	}

	vector<int> p(n + 1);
	for (int i = 1; i <= n; ++i) {
		p[a[i]] = b[i];
	}

	int ret = n & 1;
	vector<int> vis(n + 1);
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) continue;
		for (int j = i; !vis[j]; j = p[j]) {
			vis[j] = 1;
		}
		ret ^= 1;
	}

	cout << (ret ? 'A' : 'B');
	for (int i = 1; i < n; ++i) {
		char op; i64 l, r, d;
		cin >> op >> l >> r >> d;
		ret ^= (r - l) * d % 2;
		cout << (ret ? 'A' : 'B');
	}
	cout << '\n';
}
```

## B. Magical Palette

神人构造。我也不知道怎么想出来的。读者自证不难（除了 $\gcd(n, m) = 1$ 那个，这个我觉得挺难的（。

```cpp
void Thephix() {
	i64 n, m;
	cin >> n >> m;

	if (n == 1 && m == 1) {
		cout << "Yes\n0\n0\n";
		return;
	}

	if (std::gcd(n, m) != 1) {
		cout << "No\n";
		return;
	}

	cout << "Yes\n";
	for (int i = 0; i < n; ++i) {
		cout << (i * m + 1) % (n * m) << " \n"[i == n - 1];
	}
	for (int i = 0; i < m; ++i) {
		cout << (i * n + 1) % (n * m) << " \n"[i == m - 1];
	}
}
```

## M. Obliviate, Then Reincarnate

图论。我们认为这个酒店一共有 $n$ 层，每层有不同的房间，这些房间是无穷多个的，但是可以确定是在某一列。

例如房间号为 $kn + r$ 的房间，所在的就是第 $r$ 层的第 $k$ 个房间。换房的规则就是，从某一层切换到某一层，然后所在的房间的列数，可能会发生变化。

对于每个查询，我们需要做的就是，能不能变到无穷多的房间。操作是有限的，但是房间是无限的，一个最简单的例子就是：一个操作，让房间所在的列变成下一列。这样房间就能是这一层所有的列了。

我们把操作带来的列的变换考虑为边的权值，所在的层表示为点，那么就可以构造一张有向图。我们需要做的就是 check 从这个点出发，能不能到达一个非零环。

乱搞一下就行了，这类题很多的。考虑返祖边的时候判断是否是非零环。然后 scc 缩点乱搞一下。

```cpp
void Thephix() {
	int n, m, q;
	cin >> n >> m >> q;

	auto get = [&](i64 x) {
		i64 k = x / n;
		i64 r = x % n;
		if (r < 0) r += n, k--;
		return pair(k, r);
	};
	
	vector<vector<array<i64, 2>>> adj(n + 1);
	for (int i = 1; i <= m; ++i) {
		i64 u, v;
		cin >> u >> v;
		auto [k1, r1] = get(u);
		auto [k2, r2] = get(u + v);
		adj[r1 + 1].push_back({ r2 + 1, k2 - k1 });
	}

	int cur = 0, cnt = 0;
	vector<i64> dp(n + 1), ok(n + 1);
	vector<int> dfn(n + 1), low(n + 1), bel(n + 1), stk;

	auto dfs = [&](auto&& dfs, int u) -> void {
		dfn[u] = low[u] = ++cur;
		stk.push_back(u);

		for (auto [v, w] : adj[u]) {
			if (dfn[v] == 0) {
				dp[v] = dp[u] + w;
				dfs(dfs, v);
				low[u] = min(low[u], low[v]);
			} else if (bel[v] == 0) {
				low[u] = min(low[u], dfn[v]);
				ok[u] |= (dp[u] - dp[v] + w) != 0;
			}
		}

		if (dfn[u] == low[u]) {
			int x = cnt++;
			do {
				bel[x = stk.back()] = cnt;
				stk.pop_back();
			} while (x != u);
		}
	};

	for (int i = 1; i <= n; ++i) {
		if (dfn[i] == 0) dfs(dfs, i);
	}

	vector<int> ans(cnt + 1);
	for (int i = 1; i <= n; ++i) {
		ans[bel[i]] |= ok[i];
	}

	vector<int> in(cnt + 1);
	vector<vector<int>> g(cnt + 1);
	for (int u = 1; u <= n; ++u) {
		for (auto [v, w] : adj[u]) {
			if (bel[u] == bel[v]) {
				continue;
			}
			g[bel[v]].push_back(bel[u]);
			in[bel[u]]++;
		}
	}

	queue<int> que;
	for (int i = 1; i <= cnt; ++i) {
		if (in[i] == 0) que.push(i);
	}

	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (auto v : g[u]) {
			ans[v] |= ans[u];
			if (--in[v] == 0) {
				que.push(v);
			}
		}
	}

	for (int i = 1; i <= q; ++i) {
		i64 x;
		cin >> x;
		auto [k, r] = get(x);
		cout << (ans[bel[r + 1]] ? "Yes\n" : "No\n");
	}
}
```
