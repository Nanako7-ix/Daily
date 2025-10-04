# The 2022 ICPC Asia Nanjing Regional Contest

> 可能打的有点不像人类

## A. Stop, Yesterday Please No More

> 好像挺简单的，为什么一开始在想二维数点（虽然二维数点是对的，但是在想树套树就是我的不对了）明明可以一步到位的，懒得想细节，细节想不过来，只能先用最傻逼的方法写然后慢慢加优化。我什么时候才能聪明一点可以直接想到正解呢

假设没有坑，直接处理最终会有哪些袋鼠会留下来，显然这是一个矩形 $[x_L, y_L]\times [x_R, y_R]$。

然后枚举坑的初始位置，显然坑对应的是一条路径。然后你需要查询在不同的起始位置下，这条路径和最终留下的袋鼠有一个交集，这个交集就是额外似掉的袋鼠。计算一下总共还没似的袋鼠的数量是否等于 $k$。

由于坑的初始位置有限，所以也只需要处理 $2n \cdot 2m$ 范围内的路径即可。这个范围很小，直接二维前缀和。

```cpp
void Thephix() {
	int n, m, k;
	string s;
	cin >> n >> m >> k >> s;

	int N = 2 * n, M = 2 * m;
	vector<vector<int>> pre(N + 1, vector<int> (M + 1));
	pre[1 + n][1 + m] = 1;
	
	int len = s.size();
	int xL = 1, yL = 1, xR = n, yR = m;
	for (int i = 0, x = 1, y = 1; i < len; ++i) {
		if (s[i] == 'U') x++;
		if (s[i] == 'D') x--;
		if (s[i] == 'L') y++;
		if (s[i] == 'R') y--;
		if (x + n >= 1 && x + n <= N && y + m >= 1 && y + m <= M) {
			pre[x + n][y + m] = 1;
		}
		xL = max(xL, x), xR = min(xR, x + n - 1);
		yL = max(yL, y), yR = min(yR, y + m - 1);
	}

	if (xL > xR || yL > yR) {
		if (k == 0) {
			cout << n * m << '\n';
		} else cout << "0\n";
		return;
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			pre[i][j] += pre[i - 1][j];
			pre[i][j] += pre[i][j - 1];
			pre[i][j] -= pre[i - 1][j - 1];
		}
	}

	auto query = [&](int xl, int yl, int xr, int yr) -> int {
		xl += n, yl += m, xr += n, yr += m;
		return pre[xr][yr] - pre[xl - 1][yr] - pre[xr][yl - 1] + pre[xl - 1][yl - 1];
	};

	int ans = 0;
	int need = (xR - xL + 1) * (yR - yL + 1) - k;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (query(xL - i + 1, yL - j + 1, xR - i + 1, yR - j + 1) == need) {
				ans++;
			}
		}
	}
	cout << ans << "\n";
}
```

## B. Ropeway

> 好像很简单，但是写得很唐。

把 $a$ 设为 $[0, a, 0]$ 的形式，$s$ 设为 $1+s+1$ 形式，这样更方便我们后续的处理。

假如没有修改：容易想到 dp，$\operatorname{dp}(i)$ 表示考虑数组 $[a_1, a_2, \cdots, a_i]$，并选择 $i$ 的情况下的最小代价。

如果没有强制选择，那么可以做一个 $O(nk)$ 的无脑 dp，枚举上一个选择的位置进行转移：

$$
\operatorname{dp}(i) = a(i) + \min_{j=i-k}^{i-1} \operatorname{dp}(j)
$$

但是现在有强制选择。假设 $[i - k, i - 1]$ 范围内有强制选择的位置 $p$，那么 $[i - k, p)$ 是不可取的。这样修改一下转移方程就好了。

vp 时的解法是，按照 $1$ 来分段，这样每一段单独计算，dp 转移方程就不需要修改了。但是分段计算比较繁琐，这里按照上面的方式来做。

考虑优化 dp，注意到这是一个在前一段找 min 的操作，我队友直接单调队列优化 dp 秒了。

如何实现**截断**功能，只需要在遇到 $1$ 的时候把队列清空即可（太智慧了）

下面考虑单点修改。注意到修改后，$\operatorname{dp}(1)$ 到 $\operatorname{dp}(p - 1)$ 都是没有发生变化的。那不妨处理前后缀来做。

$\operatorname{pre}(i)$ 表示的是上文的 dp，$\operatorname{suf}(i)$ 表示的是考虑 $[i, n]$ 这个后缀并且一定选取 $i$ 的时候的最小代价。这样就可以计算答案了。

因为新的方案要么包含 $a_p'$ 要么不包含。两种情况各算一遍取最小即可。

对于包含的情况：

$$
\operatorname{ans} = \min_{i=p-k}^{p-1} \operatorname{pre}(i) + a_p' + \min_{i=p+1}^{p-k} \operatorname{suf}(i)
$$

对于不包含的情况，也可以类似计算，使用双指针即可。

时间复杂度 $O(\sum_t(n + kq))$

```cpp
void Thephix() {
	int n, k;
	cin >> n >> k;
	n += 2;

	vector<int> a(n + 1);
	for (int i = 2; i < n; ++i) {
		cin >> a[i];
	}

	string s;
	cin >> s;
	s = "$1" + s + "1";

	vector<int> pos;
	for (int i = 1; i <= n; ++i) {
		if (s[i] == '1') pos.push_back(i);
	}

	vector<i64> pre = [&]() -> vector<i64> {
		vector<i64> dp(n + 1);
		deque<int> que;
		dp[1] = a[1];
		que.push_back(1);
		for (int i = 2; i <= n; ++i) {
			if (i - que.front() > k) que.pop_front();
			dp[i] = dp[que.front()] + a[i];
			if (s[i] == '1') que.clear();
			else while (!que.empty() && dp[i] <= dp[que.back()]) {
				que.pop_back();
			}
			que.push_back(i);
		}
		return dp;
	} ();

	vector<i64> suf = [&]() -> vector<i64> {
		vector<i64> dp(n + 1);
		deque<int> que;
		dp[n] = a[n];
		que.push_back(n);
		for (int i = n - 1; i >= 1; --i) {
			if (que.front() - i > k) que.pop_front();
			dp[i] = dp[que.front()] + a[i];
			if (s[i] == '1') que.clear();
			else while (!que.empty() && dp[i] <= dp[que.back()]) {
				que.pop_back();
			}
			que.push_back(i);
		}
		return dp;
	} ();

	i64 ans = pre[n];
	
	int q; cin >> q;
	while (q--) {
		int p, v;
		cin >> p >> v;
		p++;
		if (s[p] == '1') {
			cout << ans + v - a[p] << "\n";
			continue;
		}

		auto it = lower_bound(pos.begin(), pos.end(), p);
		int l = *prev(it), r = *it;

		i64 ans = inf;

		// 考虑新的选择中，带有 a[p]
		i64 min_pre = inf, min_suf = inf;
		for (int i = max(l, p - k); i < p; ++i) {
			min_pre = min(min_pre, pre[i]);
		}
		for (int i = min(r, p + k); i > p; --i) {
			min_suf = min(min_suf, suf[i]);
		}
		ans = min(ans, min_pre + v + min_suf);

		// 考虑新的选择中，不带有 a[p]
		i64 Min = inf;
		for (int i = max(l, p + 1 - k), j = p; i < p; ++i) {
			while (j + 1 <= r && j - i < k) {
				Min = min(Min, suf[++j]);
			}
			ans = min(ans, pre[i] + Min);
		}

		cout << ans << "\n";
	}
}
```

## D. Chat Program

> 容易想到二分+pbds，这个做法是比较极限的

直接二分答案。对于每个值 $x$，需要判断大于 $x$ 的数量是否小于 $k$。我们枚举区间，然后分别计算区间内的和区间外的数。对于区间外的数，pbds 很容易处理。对于区间内的数，我们构造：

$$
f(i) = a(i) + c + id
$$

当区间为 $[l, r]$ 的时候，有 $a'(i) = a(i) + c + (i - l)\cdot d = f(i) - ld$，所以 $a'(i) < x \Rightarrow f(i) < x + ld$，这个也可以用 pbds 做。

然后如果在全局进行二分，然后每次 check 扫一遍整个数组，vp 的时候是 t 了的。但是注意到：我们可以直接扫一遍整个数组，然后查询：如果我对这个区间操作，可以得到的答案是多少。然后对于所有的区间取 $\max$，这样就可以过了，因为不需要扫 $\log$ 次。

时间复杂度 $O(n\log A\log n)$

```cpp
using namespace __gnu_pbds;

template<typename T,
template<typename Node_CItr, typename Node_Itr, typename Cmp_Fn_, typename _Alloc_>
typename update = tree_order_statistics_node_update>
struct Tree : tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, update> {
using super = tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, update>;
	int tot = 0;
	void insert(const T& v) { super::insert({v, ++tot}); }
	void erase(const T& v) { super::erase(super::lower_bound({v, 0})); }
	T find_by_order(int k) { return super::find_by_order(k - 1) -> first; }
	int order_of_key(const T& v) { return super::order_of_key({v, 0}) + 1; }
	T prev(const T& v) { return find_by_order(order_of_key(v) - 1); }
	const T next(const T& v) { return find_by_order(order_of_key(v + 1)); }
};

constexpr i64 inf = 1E15;

void Thephix() {
	int n, k, m;
	i64 a1, d;
	cin >> n >> k >> m >> a1 >> d;

	vector<i64> a(n + 1), f(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		f[i] = a[i] + a1 + i * d;
	}

	Tree<i64> in, out;
	for (int i = 1; i < m; ++i) {
		in.insert(f[i]);
	}
	for (int i = m; i <= n; ++i) {
		out.insert(a[i]);
	}
	
	i64 ans = 0;
	for (int l = 1, r = m; r <= n; ++l, ++r) {
		out.erase(a[r]);
		in.insert(f[r]);
		
		auto check = [&](i64 x) -> bool {
			int cnt = 0;
			cnt += out.size() - (out.order_of_key(x + 1) - 1);
			cnt += in.size() - (in.order_of_key(x + l * d + 1) - 1);
			return cnt < k;
		};
		
		i64 x = 0, y = inf, res = -1;
		while (x <= y) {
			i64 mid = (x + y) >> 1;
			if (check(mid)) {
				res = mid, y = mid - 1;
			} else x = mid + 1;
		}

		assert(res != -1);
		ans = max(ans, res);
		
		out.insert(a[l]);
		in.erase(f[l]);
	}

	cout << ans << "\n";
}
```

题解给出了一个更优秀的 check 方式。依旧考虑对全局二分，然后考虑 check $x$ 是否可以作为答案。我们让 $x$ 的数记作 $1$ 小于等于的数记作 $0$，那么需要的是，是否存在一个区间使得 $1$ 的数量小于 $k$。

考虑一个数的变化情况。当操作区间从左到右移动的时候，一个数先变成最大值，然后再慢慢减小。所以如果一个数大于 $x$，那么任意的左端点都会提供一次贡献，如果一个数的最大可能小于等于 $x$，那么这个数不会提供任何贡献。否则一定是对某些操作提供一点贡献，容易发现这些操作构成一个区间。那么我们对于每一个数，做一次区间加，然后 check 一下是否存在一个操作满足条件即可。区间加使用差分。

```cpp
void Thephix() {
	int n, k, m;
	i64 a1, d;
	cin >> n >> k >> m >> a1 >> d;

	vector<i64> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	auto check = [&](i64 x) -> bool {
		vector<int> f(n + 2);

		for (int i = 1; i <= n; ++i) {
			if (a[i] >= x) {
				f[1]++;
			} else if (a[i] + a1 + (min(m, i) - 1) * d >= x) {
				f[max(1, i - m + 1)]++; // 他妈的这个范围调死我了
				f[clamp<i64>(
					i - (d == 0 ? 0 : (x - a[i] - a1 + d - 1) / d),
					max(1, i - m + 1),
					i
				) + 1]--;
			}
		}
		
		for (int i = 1; i <= n - m + 1; ++i) {
			f[i] += f[i - 1];
			if (f[i] >= k) return true;
		}
		return false;
	};

	i64 l = 0, r = inf, ans = -1;
	while (l <= r) {
		i64 m = (l + r) >> 1;
		if (check(m)) {
			ans = m, l = m + 1;
		} else r = m - 1;
	}

	assert(ans != -1);
	cout << ans << "\n";
}
```

## I. Perfect Palindrome

> 签到

至少需要多少次使得字符串 $s$ 的任意循环同构都是回文串。显然对于任意两个下标，都可以找到一种方式使得他们在字符串中是对称的位置。所以任意两个字符都需要相同。所以至少需要长度减众数次操作。

对于任意两个相邻的字符，我们让它们分布在一头一尾，就可以让他们两个相等。如此一来，任意两个相邻的字符都相等，所以整个字符串都应该相等。

```cpp
void Thephix() {
	string s;
	cin >> s;

	array<int, 26> cnt {};
	for (auto& ch : s) {
		cnt[ch - 'a']++;
	}

	cout << s.size() - *max_element(cnt.begin(), cnt.end()) << "\n";
}
```

## G. Inscryption

> 反悔贪心。

考虑平均能力值的计算公式：

$$
\frac{\operatorname{sum}}{\operatorname{cnt}}
$$

其中 $\operatorname{sum}$ 指的是曾经获得过的野兽的个数，$\operatorname{cnt}$ 指的是当前的野兽个数。显然 $\operatorname{sum} \geq \operatorname{cnt}$。对于一次操作，要么选择获得一只野兽，即 $\operatorname{sum}$ 增加 $1$。要么选择合并两只野兽，即 $\operatorname{cnt}$ 减小 $1$。

我们看看这两个操作应该如何选择。执行完操作 $1$ 和操作 $2$ 后，当前的价值分别为 $\frac{\operatorname{sum} + 1}{\operatorname{cnt} + 1}$ 和 $\frac{\operatorname{sum}}{\operatorname{cnt} - 1}$。显然有操作 $2$ 优于操作 $1$。

也就是尽量选择操作 $2$。但是操作 $2$ 在 $\operatorname{cnt} = 1$ 的时候无法执行，怎么办呢。直接反悔即可。记录下一共有多少次反悔机会，然后在无法操作的时候反悔即可。

```cpp
void Thephix() {
	int n;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	i64 sum = 1, cnt = 1, f = 0;
	for (int i = 1; i <= n; ++i) {
		int x = a[i];
		if (x == 1) {
			sum++, cnt++;
		} else if (x == -1) {
			if (cnt >= 2) {
				cnt--;
			} else if (f > 0) {
				sum++, cnt++, f--;
			} else {
				cout << "-1\n";
				return;
			}
		} else {
			if (cnt >= 2) {
				cnt--, f++;
			} else cnt++, sum++;
		}
	}

	int g = gcd(sum, cnt);
	cout << sum / g << ' ' << cnt / g << "\n";
}
```

## M. Drain the Water Tank

> 我是几何飞舞啊！我好像每道几何题都要写至少一个小时，哪怕是极角排序板子题也要写一小时。感觉几何有点克制我了。

vp 的时候队友关键结论：把水平的部分缩点一下即可。这样就基本做完了。需要注意的是，这可能是一个凹包，所以需要判下凹点是否真的是需要的点，直接用叉积判断即可。样例给了这种情况，也是相当好了。

```cpp
void Thephix() {
	int n;
	cin >> n;
	vector<Point<i64>> a(n + 1);
	vector<int> p;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		if (!p.empty() && a[p.back()].y == a[i].y) {
			p.pop_back();
		}
		p.push_back(i);
	}


	if (a[p.back()].y == a[p.front()].y) {
		p.pop_back();
	}

	auto check = [&](int j) {
		int i = j - 1; if (i < 1) i = n;
		int k = j + 1; if (k > n) k = 1;
		return (a[j] - a[i]).cross(a[k] - a[j]) > 0;
	};

	int ans = 0;
	int m = p.size();
	for (int i = 0; i < m; ++i) {
		int x = p[(i - 1 + m) % m];
		int y = p[i];
		int z = p[(i + 1) % m];
		if (a[x].y > a[y].y && a[z].y > a[y].y) {
			ans += check(y);
		}
	}
	cout << ans << "\n";
}
```

这题的细节：

1. 叉积的计算需要用原多边形来做，因为缩点后的多边形可能不是简单多边形。
2. 缩点的时候，最好保留线段的端点，否则用原多边形的点计算可能会得到叉积为 $0$ 的结果。如果判合法用的是 $\geq 0$ 还好，要是用 $> 0$ 就要红温半天了。至于如何保留端点，可以看看我上面的实现。

## E. Color the Tree

> 虚树。当时想到了最朴素的 $O(n^2)$ dp，但是发现没办法优化，所以没和队友说。虚树的解法就是基于这个 $O(n^2)$ 的 dp 优化的。

首先我们定义这样的 dp 数组：

$$
\operatorname{dp}(u, k) 
$$

表示考虑 $u$ 为根的子树，把深度为 $k$ 的点全部染色所需要的最小代价。

显然可以有这样的转移方程：

$$
\operatorname{dp}(u, k) = \min(a_{k - \operatorname{dep}(u)}, \sum_{v} \operatorname{dp}(v, k))
$$

这样的 dp，状态转移是 $O(n^2)$ 的。以上是我赛时的写法，感觉没什么可以优化的。

注意到，对于每个 $k$ 是独立的！换句话说，对于 $k_1$ 和 $k_2$ 来求答案，两个的解法是完全没有相交的。

所以我们可以 for 所有的 $k$ 来完成这题。对于每个 $k$，考虑我们需要将 $\operatorname{dep} = k$ 的所有点染色。我们对这些点构建虚树，在虚树上完成树形 dp。

这个时候就不是用 $a_{k - \operatorname{dep}(u)}$ 来转移了，因为不能只考虑一个点，而是需要考虑 $[u, fa(u))$ 这条路径上的点，所以应该是：

$$
\min_{i = k - \operatorname{dep}(u)}^{k - \operatorname{dep}(fa(u))-1}(a_i)
$$

区间最小值使用 ST 表实现，时间复杂度 $O(n\log n)$。

```cpp
void Thephix() {
	int n;
	cin >> n;
	vector<i64> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	SparseTable Min(a.begin() + 1, a.end(), [](i64 i, i64 j) {
		return min(i, j);
	});

	VirtualTree tr(n);
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		tr.add(u, v);
	}
	tr.work(1);

	auto& dep = tr.dep;
	int Max = *max_element(dep.begin(), dep.end());
	vector<vector<int>> p(Max + 1);
	for (int i = 1; i <= n; ++i) {
		p[dep[i]].push_back(i);
	}

	i64 ans = 0;
	vector<i64> dp(n + 1);
	vector<vector<int>> adj(n + 1);

	for (int i = 1; i <= Max; ++i) {
		vector<array<int, 2>> E;
		int rt = tr.build(p[i].begin(), p[i].end(), [&](int u, int v) {
			E.push_back({ u, v });
		});
		for (auto& [u, v] : E) {
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		

		auto dfs = [&](auto&& dfs, int u, int fa) {
			if (dep[u] == i) {
				dp[u] = Min(i - dep[u] + 1, i - dep[fa]);
				return;
			}
			dp[u] = 0;
			for (auto& v : adj[u]) {
				if (v == fa) continue;
				dfs(dfs, v, u);
				dp[u] += dp[v];
			}
			dp[u] = min(dp[u], Min(i - dep[u] + 1, i - dep[fa]));
		}; dfs(dfs, rt, 0);

		ans += dp[rt];

		for (auto& [u, v] : E) {
			adj[u].pop_back();
			adj[v].pop_back();
		}
	}

	cout << ans << "\n";
}
```
