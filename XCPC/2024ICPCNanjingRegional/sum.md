# 

## E. Left Shifting 3

对于循环位移 $[0, k]$ 次的字符串，计算 `nanjing` 的出现次数。记录出现的位置，那么出现次数就是区间查询。破环成链，然后直接暴力枚举前缀和即可。

```cpp
void Thephix() {
	int n, k;
	cin >> n >> k;

	string s;
	cin >> s;
	s += s;

	if (n < len) {
		cout << "0\n";
		return;
	}

	vector<int> cnt(2 * n + 1);
	for (int i = 0; i <= 2 * n - len; ++i) {
		cnt[i + 1] = cnt[i] + (s.substr(i, len) == p);
	}

	int ans = 0;
	for (int i = 0; i < min(n, k + 1); ++i) {
		ans = max(ans, cnt[i + n - len + 1] - cnt[i]);
	}
	cout << ans << "\n";
}
```

## J. Social Media

有点恶心的模拟题。

分成三种情况：两个点分别在集合内外，两个点都在集合外，两个点都在集合内。

- 对于第三种情况，可以直接贡献答案。
- 然后记录一下对于每个点来说，选择这个点可以提供多少的贡献，也就是第一种情况。
- 然后对于第二种情况也记录一下，因为第二种情况只有 $m$ 个

然后考虑枚举选择哪个点。按贪心来说，选择的两个点，使得这两个点存在连边。然后还有一种情况就是选择两个没有连边的点。这种情况下直接选择贡献最大的两个点即可。

时间复杂度 $O(n + m)$。直接 sort 了懒得写不带 $\log$ 的解法。

```cpp
void Thephix() {
	int k, m, n;
	cin >> k >> m >> n;

	vector<int> a(n + 1);
	for (int i = 1; i <= k; ++i) {
		int x;
		cin >> x;
		a[x] = 1;
	}

	int res = 0;
	vector<int> f(n + 1);
	HashMap<i64, int> cnt;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;

		if (u == v) {
			(a[u] ? res : f[u])++;
			continue;
		}
		
		if (a[u] && a[v]) res++;
		else if (a[u]) f[v]++;
		else if (a[v]) f[u]++;
		else cnt[code(u, v)]++;
	}

	int ans = 0;
	for (auto [x, cnt] : cnt) {
		auto [u, v] = decode(x);
		ans = max(ans, res + f[u] + f[v] + cnt);
	}

	sort(f.begin() + 1, f.end(), greater());
	ans = max(ans, res + f[1] + f[2]);
	cout << ans << "\n";
}
```

## K. Strips

用黑色块来分段，那么你会得到若干个段，对于每个段分别处理即可。

对于一个段，假如不考虑超出边界的问题，那么按照贪心来看，是一个很简单的问题，就是尽量让纸条往右边放。现在考虑不能触碰边界，实际上也就是不能触碰右边界。这个时候只需要从右往左调整即可，如果最右边的纸条不对，那就让它往左调整。这个调整也是贪心的，能不调整就不调整，免得前面的纸条需要继续调整。

妈的，不会贪心。

```cpp
void Thephix() {
	int n, m, k, w;
	cin >> n >> m >> k >> w;

	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	
	vector<int> b(m + 3);
	for (int i = 2; i <= m + 1; ++i) {
		cin >> b[i];
	}
	b[1] = 0, b[m + 2] = w + 1;
	
	sort(a.begin() + 1, a.end());
	sort(b.begin() + 1, b.end());
	
	vector<int> ans;
	auto solve = [&](int l, int r) {
		if (l > r) return true;
		int x = lower_bound(a.begin() + 1, a.end(), l) - a.begin();
		int y = upper_bound(a.begin() + 1, a.end(), r) - a.begin() - 1;
		if (x > y) return true;

		vector<int> res;
		for (int i = x; i <= y; ++i) {
			res.push_back(a[i]);
			while (i + 1 <= y && a[i + 1] <= res.back() + k - 1) ++i;
		}
		
		int len = res.size(), lim = r;
		for (int i = len - 1; i >= 0; --i) {
			if (res[i] + k - 1 > lim) {
				res[i] = lim - k + 1;
				lim = res[i] - 1;
			}
		}
		for (auto x : res) ans.push_back(x);
		return res[0] >= l;
	};
	
	for (int i = 1; i < m + 2; ++i) {
		int l = b[i], r = b[i + 1];
		if (!solve(l + 1, r - 1)) {
			cout << "-1\n";
			return;
		}
	}

	cout << ans.size() << "\n";
	for (int x : ans) cout << x << ' ';
	cout << "\n";
}
```

## G. Binary Tree

二分，贪心，交互题。

看到 $\log$ 次询问就是很明显的是二分吧，怎么二分呢。我一开始想的是利用二叉树来进行二分，也就是走左儿子或者右儿子这样。但是这个很容易被 hack，因为这不是一棵平衡的二叉树，可能左儿子非常地轻，然后这个时候删掉左儿子就似掉了。

那么怎么二分呢？重心！前面的问题就是左儿子太轻了，会似掉，那就让它尽量平衡一点，那么就使用重心来解决。

假如我们找到了重心，那么考虑重心的度数。度数只有可能是 $0, 1, 2, 3$ 这几种情况：

- 如果度数是 $0$，不需要查询，直接得到答案
- 如果度数是 $1$，说明这棵树只有两个点，直接查询这两个点即可得到答案。
- 如果度数是 $2$，这个时候直接查询重心的两个相邻节点。如果答案是距离相等那么可以直接得到答案了，否则一定可以只保留一边。
- 如果度数为 $3$，这个时候查询哪两个节点呢？看看这个删除有什么规律：如果偏向某一边，**保留**这边的子树，否则保留重心及没有被查询的那棵子树。我们要删除的部分大于等于 $\lceil\frac{n}{2}\rceil$，也就是要保留的部分尽可能小。这个时候选择较重的两个儿子即可。

这种操作方式下，一定是保证每次删除的大小大于等于 $\lceil\frac{n}{2}\rceil$。

证明：

这里不讨论度数为 $0$ 或 $1$ 的情况，这种情况显然正确。对于偏向一边的情况，考虑保留偏向的那棵子树的大小。由树的重心性质（ps: 这个性质用深度和最小来证明比较方便），一定满足：

$$
\operatorname{size} < \frac{n}{2}
$$

这样删除的部分大于等于 $\frac{n}{2}$，即 $\lceil\frac{n}{2}\rceil$。对于两边相等的情况，如果度数为 $2$，显然删除的大小为 $n - 1$。对于度数为 $3$ 的情况，由于保留的部分是最小的一棵子树加上重心。最小的那棵子树大小的最大值大概只有 $\frac{n}{3}$ 左右：

考虑三棵子树的大小分别为 $x \leq y \leq z$ 且满足 $x + y + z = n - 1$，那么 $x \leq \lfloor\frac{n-1}{3}\rfloor$，因为一定有一个下取整的，怎么可能三个都上取整呜呜。那么只需证：$n - 1 - \lfloor\frac{n-1}{3}\rfloor \geq \lceil\frac{n}{2}\rceil$ 即可，读者自证不难

所以也是对的。

虽然代码写得很长，但是写的时候来手感了（。所以写的还是很快的。

```cpp
void Thephix() {
	int n;
	cin >> n;
	vector<vector<int>> adj(n + 1);
	for (int u = 1; u <= n; ++u) {
		int ls, rs;
		cin >> ls >> rs;
		if (ls != 0) {
			adj[u].push_back(ls);
			adj[ls].push_back(u);
		}
		if (rs != 0) {
			adj[u].push_back(rs);
			adj[rs].push_back(u);
		}
	}

	int rt = 1;
	vector<int> siz(n + 1);
	while (true) {
		assert(rt != 0);
		[&](this auto&& dfs, int u, int fa) -> void {
			siz[u] = 1;
			for (auto& v : adj[u]) {
				if (v == fa) continue;
				dfs(v, u);
				siz[u] += siz[v];
			}
		} (rt, 0);
		
		int Min = siz[rt], x = 0;
		[&](this auto&& dfs, int u, int fa) -> void {
			int Max = 1;
			for (auto& v : adj[u]) {
				if (v == fa) continue;
				dfs(v, u);
				Max = max(Max, siz[v]);
			}
			Max = max(Max, siz[rt] - siz[u]);
			// 等于的时候也要更新，不然会得到重心为 0 的情况。
			// 或者 Min 的初始值设大一点也行（
			if (Max <= Min) {
				Min = Max;
				x = u;
			}
		} (rt, 0);

		if (adj[x].size() == 0) {
			cout << "! " << x << endl;
			return;
		} else if (adj[x].size() == 1) {
			cout << "? " << x << ' ' << adj[x][0] << endl;
			int t; cin >> t;
			assert(t != 1);
			if (t == 0) cout << "! " << x << endl;
			if (t == 2) cout << "! " << adj[x][0] << endl;
			return;
		} else if (adj[x].size() == 2) {
			int u = adj[x][0], v = adj[x][1];
			cout << "? " << u << ' ' << v << endl;
			int t; cin >> t;
			if (t == 1) {
				cout << "! " << x << endl;
				return;
			}
			if (t == 0) {
				adj[u].erase(find(adj[u].begin(), adj[u].end(), x));
				rt = u;
			}
			if (t == 2) {
				adj[v].erase(find(adj[v].begin(), adj[v].end(), x));
				rt = v;
			}
		} else if (adj[x].size() == 3) {
			[&](this auto&& dfs, int u, int fa) -> void {
				siz[u] = 1;
				for (auto v : adj[u]) {
					if (v == fa) continue;
					dfs(v, u);
					siz[u] += siz[v];
				}
			} (x, 0);

			sort(adj[x].begin(), adj[x].end(), [&](int u, int v) {
				return siz[u] > siz[v];
			});

			int u = adj[x][0], v = adj[x][1];
			cout << "? " << u << ' ' << v << endl;
			int t; cin >> t;
			if (t == 1) {
				adj[x] = { adj[x][2] };
				rt = x;
			}
			if (t == 0) {
				adj[u].erase(find(adj[u].begin(), adj[u].end(), x));
				rt = u;
			}
			if (t == 2) {
				adj[v].erase(find(adj[v].begin(), adj[v].end(), x));
				rt = v;
			}
		} else {
			__builtin_unreachable();
		}
	}
}
```

## B. Birthday Gift

神秘思维题，感觉这辈子都不会做这种。

考虑把奇数位置的 $0$ 和 $1$ 互换，$2$ 保持不变。这样就变成了相邻不同的删除，这种情况下，如果不考虑 $2$ 的存在，一定会剩下一堆相同的字符，也就是 $| cnt(1) - cnt(0) |$。那如果存在 $2$，那就把 $2$ 改成 $0$ 和 $1$ 中较少的那个。因为**最终答案只和 $0, 1$ 出现次数的差值相关**。

我草，这是人类能想到的吗？

```cpp
void Thephix() {
	string s;
	cin >> s;

	for (int i = 0; i < (int) s.size(); ++i) {
		if (s[i] == '2') continue;
		s[i] ^= i & 1;
	}

	array<int, 3> cnt {};
	for (auto& ch : s) {
		cnt[ch - '0']++;
	}

	int ans = abs(cnt[0] - cnt[1]);
	if (cnt[2] > ans) {
		cout << (cnt[2] + ans) % 2 << "\n";
	} else {
		cout << ans - cnt[2] << "\n";
	}
}
```

## I. Bingo

$\min$-$\max$ 容斥。

考虑这样的一个集合 $S$

```cpp
for (int i = 1; i <= n; ++i) {
	Max = -inf;
	for (int j = 1; j <= m; ++j) {
		Max = max(Max, a[i][j]);
	}
	S.insert(Max);
}

for (int j = 1; j <= m; ++j) {
	Max = -inf;
	for (int i = 1; i <= n; ++i) {
		Max = max(Max, a[i][j]);
	}
	S.insert(Max);
}
```

我们需要求的是：对于任意一种排列方式，计算 $\min\limits_{x \in S} x$。对所有的方案求和。

$\min$ 太难求，我们考虑使用 $\min$-$\max$ 容斥来求解。

根据 $\min$-$\max$ 容斥，我们有：

$$
\min_{x \in S} x = \sum_{T \subseteq S \land T \neq \varnothing} (-1)^{|T| - 1} \max_{x \in T} x
$$

我们考虑一下这个 $x$ 的定义，发现 $x$ 表示的是某一行或者某一列的最大值，那么右边的一块 $\max$ 实际上就是选中的行和列中的最大值。

可以直接爆推式子了：

$$
\begin{aligned}
\operatorname{ans} &= \sum_{\operatorname{Arrangement}} \min_{x \in S} x\\
&= \sum_{\operatorname{Arrangement}}\sum_{T\subseteq S \land T \neq \varnothing}(-1)^{|T|-1}\max_{x \in T} x\\
&= \sum_{i=0}^n \sum_{j=0}^m ([i + j \neq 0] (-1)^{i+j-1} \binom{n}{i} \binom{m}{j} (\sum_{k=\operatorname{cnt}} ^ {nm} \operatorname{kth} \cdot \binom{ k-1 }{ \operatorname{cnt}-1 } \operatorname{cnt}! (nm-\operatorname{cnt})!))
\end{aligned}
$$

其中 $\operatorname{cnt} = im + jn - ij$。这条式子表示选择了其中的 $i$ 行，其中的 $j$ 列来构成 $T$ 的情况下的贡献和（不会的多学学拆贡献，拆贡献不过就是考虑改变顺序，也就是求和的次序罢了，基本功喵）

对于：
$$
\sum_{k=\operatorname{cnt}} ^ {nm} \operatorname{kth} \cdot \binom{ k-1 }{ \operatorname{cnt}-1 } \operatorname{cnt}! (nm-\operatorname{cnt})!
$$

这条式子，可以这样子做：

$$
\begin{aligned}
f(\operatorname{cnt}) &= \operatorname{cnt}! (nm-\operatorname{cnt})! \cdot (\sum_{k=\operatorname{cnt}} ^ {nm} \operatorname{kth} \cdot \binom{ k-1 }{ \operatorname{cnt}-1 })\\
&= \operatorname{cnt}! (nm-\operatorname{cnt})! \cdot (\sum_{k=\operatorname{cnt}} ^ {nm} \operatorname{kth} \cdot \frac{(k-1)!}{(\operatorname{cnt}-1)!\cdot(k-\operatorname{cnt})!})\\

g(\operatorname{cnt}) &= \frac{ f(\operatorname{cnt}) }{ \operatorname{cnt} \cdot (nm-\operatorname{cnt})! }\\
&= \sum_{k=\operatorname{cnt}} ^ {nm} \operatorname{kth} \cdot (k-1)! \cdot (k-\operatorname{cnt})!^{-1}
\end{aligned}
$$

那么如果我们可以求出 $g$ 就可以求出 $f$ 了，那么 $g$ 怎么求呢。注意到 $g$ 的贡献方向是：

$$
A(k) \cdot B(k-\operatorname{ cnt }) \rightarrow g(\operatorname{ cnt })
$$

$A$ 和 $B$ 的下标加起来不等于 $\operatorname{ cnt }$，这就很坏了。但是如果我们把 $A$ reverse 一下，$k$ 的符号就是正的了，然后 offset 一下就能求出 $g(x)$ 了。此事在**2025CCPC郑州邀请赛K**中亦有记载。

令：
$$
\begin{aligned}
A(k)&= \operatorname{ kth } \cdot (k-1)!\\
B(nm - k) &= k!^{-1}
\end{aligned}
$$

则：

$$
\begin{aligned}
g(\operatorname{cnt}) &= \sum_{k=\operatorname{cnt}} ^ {nm} ((\operatorname{kth} \cdot (k-1)!) \cdot (\frac{1}{(k-\operatorname{cnt})!})^{-1})\\
&= \sum_{k=\operatorname{cnt}} ^ {nm} A(k) \cdot B(nm - (k - \operatorname{cnt}))\\
&= \sum_{k=\operatorname{cnt}} ^ {nm} A(k) \cdot B(nm - k + \operatorname{cnt})\\
&= [x^{nm+\operatorname{cnt}}](A*B)
\end{aligned}
$$

你可能会有疑惑：这里 $k$ 不是从 $\operatorname{ cnt }$ 开始吗，如果 $k < \operatorname{cnt}$ 怎么办呢？这个简单，注意到 $k < \operatorname{cnt}$ 的时候，$nm-k+\operatorname{cnt} > nm$，给这部分的设为 $0$ 就好了喵~

```cpp
void Thephix() {
	int n, m;
	cin >> n >> m;

	int N = n * m;
	vector<int> kth(N + 1);
	for (int i = 1; i <= N; ++i) {
		cin >> kth[i];
	}
	sort(kth.begin() + 1, kth.end());

	vector<Z> A(N + 1), B(N + 1);
	B[N] = 1;
	for (int k = 1; k <= N; ++k) {
		A[k] = kth[k] * comb.fac(k - 1);
		B[N - k] = comb.invfac(k);
	}

	auto g = NTT(A, B);

	vector<Z> f(N + 1);
	for (int cnt = 1; cnt <= N; ++cnt) {
		f[cnt] = cnt * comb.fac(N - cnt) * g[N + cnt];
	}

	auto cnt = [&](int x, int y) -> int {
		return x * m + y * n - x * y;
	};

	Z ans = 0;
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {
			if (i == 0 && j == 0) continue;
			ans += ((i + j) % 2 == 1 ? 1 : -1) * comb.C(n, i) * comb.C(m, j) * f[cnt(i, j)];
		}
	}
	cout << ans << "\n";
}
```

## M. Ordainer of Inexorable Judgment

给一个凸包，求相交的时间。

显然分成若干个整圈和不足一圈的部分。然后计算的时候直接用极角来做即可。由于这题保证了原点距离凸包至少为 $d$，所以每一圈一定是某个时间区间。而且这个凸包一定是在某个**半平面**内，这样他们极角的差值应该不超过 $\pi$。利用这个修正极角即可。

```cpp

```

## C. Topology

非常变态的计数题。

考虑 $f(u, i)$ 表示：考虑去掉 $u$ 子树内（不包括 $u$ 本身）的节点后所形成的树，对这棵树的满足 $p(i) = u$ 的拓扑序的数量。那么 $\operatorname{ans}(u)$ 是：

$$
\binom{n - u}{\operatorname{siz}(u) - 1}\cdot f(u, u)\cdot g(u)
$$

其中 $g(u)$ 表示的是考虑 $u$ 这棵子树的拓扑序的数量。为什么这么做是对的呢？因为不考虑 $u$ 的子树，得到了一个长度为 $n - (\operatorname{siz}(u) - 1)$ 的拓扑序，并且保证了 $u$ 放在第 $u$ 个位置。然后再把 $u$ 的子树的拓扑序合并进来。合并的时候，把第一个序列的第 $u + 1$ 位开始的后缀跟第二个序列的第 $2$ 位开始的后缀合并，这个的方案数是：

$$
\binom{(n - (\operatorname{siz}(u) - 1) - u) + (\operatorname{siz}(u) - 1)}{\operatorname{siz}(u) - 1} = \binom{n - u}{\operatorname{siz}(u) - 1}
$$

考虑 $g$ 的计算，最简单的解法就是直接通过树上 dp 暴力求解。在这个基础上乱搞一下可以得到这个式子：

$$
g(u) = \frac{\operatorname{siz}(u) !}{\prod\limits_{v \in \operatorname{subtree}(u)} \operatorname{siz}(v)}
$$

接下来再计算 $f(u, i)$。这里是选择从 $fa(u)$ 向 $u$ 转移而不是儿子们向 $u$ 转移。令 $p = fa(u)$，那么转移的时候考虑 $p$ 放在哪个位置。显然只需要考虑 $1 \leq j < i$ 即可。

假设从 $f(p, j)$ 转移到 $f(u, i)$，那么需要做的是：把除了 $u$ 以外的 $p$ 的其他儿子的子树放到拓扑序里面，然后 $u$ 节点直接放到 $i$ 位置。因为 $u$ 一定放在 $i$，所以方案数等价于把其他子树的拓扑序放到原有拓扑序中。

先考虑其他子树的拓扑序。实际上就是考虑去掉 $u$ 子树的 $p$ 子树的拓扑序。用上面的式子求出来应该是：

$$
\frac{(\operatorname{siz}(p) - \operatorname{siz}(u))!\prod\limits_{v \in \operatorname{subtree}(u)} \operatorname{siz}(v)}{\prod\limits_{v \in \operatorname{subtree}(p)} \operatorname{siz}(v)} \cdot \frac{\operatorname{siz}(p)}{\operatorname{siz}(p) - \operatorname{siz}(u)}
$$

合并的方案数是：

$$
\binom{n - \operatorname{siz}(u) - j}{\operatorname{siz}(p) - \operatorname{siz}(u) - 1}
$$

那么：

$$
\begin{aligned}
f(u, i) &= \sum_{j=1}^{i-1} (\binom{n - \operatorname{siz}(u) - j}{\operatorname{siz}(p) - \operatorname{siz}(u) - 1}\cdot \frac{(\operatorname{siz}(p) - \operatorname{siz}(u))!\prod\limits_{v \in \operatorname{subtree}(u)} \operatorname{siz}(v)}{\prod\limits_{v \in \operatorname{subtree}(p)} \operatorname{siz}(v)} \cdot \frac{\operatorname{siz}(p)}{\operatorname{siz}(p) - \operatorname{siz}(u)}  \cdot f(p, j))\\
&= \frac{(\operatorname{siz}(p) - \operatorname{siz}(u))!\prod\limits_{v \in \operatorname{subtree}(u)} \operatorname{siz}(v)}{\prod\limits_{v \in \operatorname{subtree}(p)} \operatorname{siz}(v)} \cdot \frac{\operatorname{siz}(p)}{\operatorname{siz}(p) - \operatorname{siz}(u)} \cdot \sum_{j=1}^{i-1} (\binom{n - \operatorname{siz}(u) - j}{\operatorname{siz}(p) - \operatorname{siz}(u) - 1}\cdot  f(p, j))
\end{aligned}
$$

发现求和这一块东西是一个前缀和的形式。优化一下就可以在 $O(n^2)$ 内求解了。
