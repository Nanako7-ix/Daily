# [2024 CCPC 济南站](https://qoj.ac/contest/1843)

> 傻逼场，一堆五题的，没什么区分度。前五题除了构造和暴力可能容易出问题，其他的都是水题啊

## A. The Fool

签到。扫两遍，第一次计算出现次数，第二次找到出现次数为 $1$ 的即可。

```cpp
void Thephix() {
	int n, m, k;
	cin >> n >> m >> k;
	m *= k;

	vector<string> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		a[i] = '$' + a[i];
	}

	map<string, int> cnt;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; j += k) {
			cnt[a[i].substr(j, k)]++;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1, x = 1; j <= m; ++x, j += k) {
			if (cnt[a[i].substr(j, k)] == 1) {
				cout << i << ' ' << x << "\n";
				return;
			}
		}
	}
}
```

## B. The Magician

傻逼暴力。注意到数字是没用的，只需要考虑花色即可。

结论：转移是单向的。也就是某个花色要么被增加，要么被减少。如果同时执行了增加和减少的操作，存在另一种等价操作。

既然这样，操作的顺序是无关紧要的。直接 dfs 即可。

但是直接 dfs 会 TLE（指 qoj 有 hack 数据）我的处理方式是使用上面的结论来进行剪枝（其实也没有剪得很干净，但是够了）还有记忆化可能也是对的。另外一个解法是类似于记忆化搜索的。考虑差值数组，直接使用 dp，状态数是 $6 \times 4^4$。直接处理即可。

```cpp
int rk(char ch) {
	if (ch == 'D') return 0;
	if (ch == 'C') return 1;
	if (ch == 'H') return 2;
	if (ch == 'S') return 3;
	__builtin_unreachable();
}

const array f = {
	vector<array<int, 3>> {
		{ 0, 0, 0 }
	},

	vector<array<int, 3>> {
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
	},

	vector<array<int, 3>> {
		{ 2, 0, 0 },
		{ 0, 2, 0 },
		{ 0, 0, 2 },
		{ 1, 1, 0 },
		{ 1, 0, 1 },
		{ 0, 1, 1 },
	},

	vector<array<int, 3>> {
		{ 3, 0, 0 },
		{ 0, 3, 0 },
		{ 0, 0, 3 },
		{ 2, 1, 0 },
		{ 1, 2, 0 },
		{ 2, 0, 1 },
		{ 1, 0, 2 },
		{ 0, 2, 1 },
		{ 0, 1, 2 },
		{ 1, 1, 1 },
	},
};

void Thephix() {
	int n;
	cin >> n;

	array<int, 4> cnt {};
	for (int i = 1; i <= n; ++i) {
		string s;
		cin >> s;
		cnt[rk(s[1])]++;
	}
	
	array<int, 6> exist {};
	for (int i = 0; i < 6; ++i) {
		cin >> exist[i];
	}	

	int ans = 0;
	array<int, 4> del { 0, 0, 0, 0 };
	[&](this auto&& dfs, int p) -> void {
		if (p == 6) {
			int res = 0;
			for (int i = 0; i < 4; ++i) {
				res += cnt[i] / 5;
			}
			ans = max(ans, res);
			return;
		}

		// 什么都不做
		dfs(p + 1);
		if (exist[p] == 0) return;

		// 做些什么
		if (p < 4) {
			for (int i = del[p] + 1; i <= 3; ++i) {
				for (auto& g : f[i]) {
					int ok = 1;
					for (int j = 0, k = 0; j < 4; ++j) {
						if (j == p) continue;
						if (cnt[j] < g[k]) {
							ok = 0; break;
						}
						k++;
					}
					if (ok == 0) continue;

					for (int j = 0, k = 0; j < 4; ++j) {
						if (j == p) continue;
						del[j] += g[k];
						cnt[j] -= g[k];
						k++;
					}
					cnt[p] += i;

					dfs(p + 1);

					for (int j = 0, k = 0; j < 4; ++j) {
						if (j == p) continue;
						del[j] -= g[k];
						cnt[j] += g[k];
						k++;
					}
					cnt[p] -= i;
				}
			}
		} else {
			for (int i = 0; i < 4; ++i) {
				if (cnt[i] == 0) continue;
				for (int j = 0; j < 4; ++j) {
					if (i == j || del[j]) continue;
					cnt[i]--, cnt[j]++, del[i]++;
					dfs(p + 1);
					cnt[i]++, cnt[j]--, del[i]--;
				}
			}
		}
	} (0);

	cout << ans << "\n";
}
```

## F. The Hermit

先看看什么时候需要删除，应该怎么删除。需要删除的情况就是 $\min = \gcd$ 也就是最小值是集合中所有数的因子。这种情况下，$\min$ 是一定需要被删除的，否则永远 $\gcd = \min$ 恒成立。所以**一定是删除小的数字**，直到这个最小的数字不是最大公因数。

考虑 $f(x)$ 为恰好需要删除 $x$ 个数的集合个数，$g(x)$ 为至少需要删除 $x$ 个数的集合个数。那么 $f(x) = g(x) - g(x + 1)$。

至少需要删的次数为 $k$，也就是前 $k$ 个数一定是类似于套娃的结构，也就是，这样每一个数都是后面的因子。后面的 $n - k$ 个数一定是 $a_k$ 的因子。

$a_{k + 1}, \cdots, a_n$ 的方案数是 $\binom{\lfloor\frac{m}{a_k}\rfloor - 1}{n-k}$。前面的 $k$ 个数的方案数 dp 一下即可。考虑第 $k$ 个数为 $x$，方案数为 $\operatorname{dp}(x, k)$。那么转移方程为：

$$
\operatorname{dp}(x, k) = \sum_{d \mid x} \operatorname{dp}(d, k - 1)
$$

因为需要删除的次数最多为 $\log m$ 次。所以时间复杂度大概是 $O(m\log^2 m)$ 的。题解说是 $O(m\log m\log\log m)$ 的，你看我像是会做的样子吗。而且那个应该是最优复杂度，我写的是傻逼解法，应该是跑满 $O(m \log^2 m)$ 的。

```cpp
using Z = ModInt<u32, 998244353>;
Comb<Z> comb;

void Thephix() {
	int n, m;
	cin >> m >> n;

	const int log = __lg(m - 1) + 2;
	vector dp(log + 1, vector<Z> (m + 1));
	for (int i = 1; i <= m; ++i) {
		dp[1][i] = 1;
	}

	for (int i = 1; i < log; ++i) {
		for (int j = 1; j <= m; ++j) {
			for (int k = 2 * j; k <= m; k += j) {
				dp[i + 1][k] += dp[i][j];
			}
		}
	}
	
	vector<Z> f(log + 1);
	f[0] = comb.C(m, n);
	for (int i = 1; i <= log; ++i) {
		for (int j = 1; j <= m; ++j) {
			f[i] += dp[i][j] * comb.C((m / j - 1), n - i);
		}
	}
	
	Z ans = 0;
	for (int i = 0; i <= log; ++i) {
		if (i < log) f[i] -= f[i + 1];
		ans += f[i] * (n - i);
	}
	cout << ans << "\n";
}
```

## I. The Hanged Man

> yxylx 太强了！

考虑一个菊花图。如果 $(u, v)$ 这条边需要被包含在环上，那么一定是两两配对。如果 $u$ 还有祖先，那么可以剩下一个配对不了，留给祖先来操作。

所以我们有一个最简单的操作方式：

```cpp
void dfs(int u, int fa) {
	vector<int> node;
	for (auto v : adj[u]) {
		if (fa == v) continue;
		node.push_back(dfs(v, u));
	}
	for (int i = 1; i < (int) node.size(); i += 2) {
		link(node[i], node[i - 1]);
	}

	if (node.size() % 2 == 1) {
		return node.back();
	}
	return u;
}
```

但是这个可能会有问题。因为：我的 $u$ 要是没有祖先节点（也就是 $u = 1$）怎么办，那不就似了吗。这个时候注意到，如果我的 $v$ 返回的节点 $w$ 如果不是 $v$ 的话，$w$ 可以直接和 $u$ 连接，从而不需要交给 $u$ 的祖先节点处理。所以我们最好是让 $v$ 返回一个 `node` 中的节点而不是 $v$ 本身。

怎么操作？如果 `node` 本身就不能两两配对，那么按照上面的代码操作即可。如果可以两两配对呢，上面的代码返回的是 $u$，所以我们应该把它拆散，让它不能两两配对。怎么拆散？如果我能找到 `node` 中的一个节点，让它可以直接和 $u$ 连接，这样就可以只剩下奇数个点没有操作了。两两配对后返回那个没有被配对的节点即可。

需要特判根节点，根节点应该尽量返回自己，因为他没有祖先节点，所以返回自己才是有解的。也就是根节点用一开始的解法做，非根节点用拆散的方法做。

最后判断根节点返回的节点是不是 $u$ 的儿子，如果是，那么无解。如果是根节点本身，不需要操作。如果是根节点的一个非儿子的后代，让这个节点和根节点连边即可。

```cpp
void Thephix() {
	int n;
	cin >> n;
	vector<vector<int>> adj(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	vector<array<int, 2>> ans;
	auto dfs = [&](auto&& dfs, int u, int fa) -> int {
		vector<int> x;
		vector<int> y;
		for (auto& v : adj[u]) {
			if (v == fa) continue;
			int w = dfs(dfs, v, u);
			(w == v ? x : y).push_back(w);
		}

		if (u != 1 && (x.size() + y.size()) % 2 == 0) {
			if (!y.empty()) {
				ans.push_back({ y.back(), u });
				y.pop_back();
			}
		}

		vector<int> all;
		for (auto x : x) all.push_back(x);
		for (auto y : y) all.push_back(y);

		int len = all.size();
		for (int i = 1; i < len; i += 2) {
			ans.push_back({ all[i], all[i - 1] });
		}

		if (all.size() % 2 == 1) {
			return all.back();
		}
		return u;
	};
	
	int w = dfs(dfs, 1, 0);
	
	for (auto& v : adj[1]) {
		if (v == w) {
			cout << "-1\n";
			return;
		}
	}

	if (w != 1) {
		ans.push_back({ 1, w });
	}
	
	cout << ans.size() << "\n";
	for (auto& [x, y] : ans) {
		cout << x << ' ' << y << "\n";
	}
}
```

## J. Temperance

这是一个逐步删除的过程。前面已经删除的植物，一定是因为密集度不足才删除的。而我的操作又不能提升密集度，所以前面已经删除的植物一定会被继续删除。所以考虑在需求密集度为 $x$ 的时候需要删除多少植物，做一下前缀和即可。

那么考虑我现在需要密集度为 $k$ 的植物。假设有一行的植物数量恰好为 $k$，那么这里的植物看起来要被全部删掉了。但是这一行中的部分植物，处在一个密集度非常大的列中，所以这个植物暂时删不掉。那我有没有可能继续删导致这个密集度非常大的列，它的密集度下降，从而删掉这个植物呢。显然也是不行的。因为密集度非常大的这一列中的植物，每一个的密集度都是足够大的，所以这一列在此回合中永远不会被删除。

所以这回合中删掉的植物一定是：处在一个植物数量恰好为 $k$ 的行或者列或者那个（不对这怎么还有竖轴的）中，并且没有其他的密集度足够大的 x/y/z 帮它提升密集度，那么这个植物就似掉了。把这句话转化一下，就是这个植物满足：$\max(\operatorname{cnt}_x, \operatorname{cnt}_y, \operatorname{cnt}_z) = k$，那么这个植物在第 $k$ 回合中被删掉。

计算每回合中被删掉的植物的数量，前缀和就行了。

```cpp
void Thephix() {
	int n;
	cin >> n;

	vector<array<int, 3>> a(n + 1);
	array<HashMap<int, int>, 3> cnt;
	for (int i = 1; i <= n; ++i) {
		auto& [x, y, z] = a[i];
		cin >> x >> y >> z;
		cnt[0][x]++;
		cnt[1][y]++;
		cnt[2][z]++;
	}

	vector<int> b(n + 1);
	for (int i = 1; i <= n; ++i) {
		auto& [x, y, z] = a[i];
		b[max({ cnt[0][x], cnt[1][y], cnt[2][z] })]++;
	}

	for (int i = 1; i <= n; ++i) {
		b[i] += b[i - 1];
	}
	for (int i = 0; i < n; ++i) {
		cout << b[i] << " \n"[i == n - 1];
	}
}
```
