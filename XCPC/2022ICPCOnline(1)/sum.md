## C. Delete the Tree

推一下发现答案是叶子的个数。**需要特判 $n = 1$ 的情况**。操他妈的这个就应该写在树论板子的第一行！

```cpp
void Thephix() {
	int n;
	cin >> n;

	if (n == 1) {
		cout << "1\n";
		return;
	}
	
	vector<int> deg(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		deg[u]++, deg[v]++;
	}

	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += deg[i] == 1;
	}
	cout << ans << "\n";
}
```

## D. Find the Number

需要后导零的数量等于 $1$ 的数量。我想的是直接枚举 popcount 然后数位 dp。但是问题是，数位 dp 不擅长处理**找到一个数**的问题（相比于统计贡献和），然后又注意到满足条件的数字不会太多，所以直接预处理出所有满足要求的数字即可。

```cpp
array<vector<int>, 16> ans;

void Thephix() {
	i64 x, y;
	cin >> x >> y;
	
	for (int i = 1; i <= 15; ++i) {
		auto it = lower_bound(ans[i].begin(), ans[i].end(), x);
		if (it != ans[i].end() && *it <= y) {
			cout << *it << "\n";
			return;
		}
	}

	cout << "-1\n";
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	cin >> T;

	constexpr int N = 1E9;
	for (int i = 1; i <= 15; ++i) {
		auto dfs = [&](auto&& dfs, int len, int pc, int now) {
			if (len == -1) {
				if (pc != 0) return;
				i64 val = (now << 1 | 1) << i;
				if (val <= N) {
					ans[i].push_back(val);
				}
				return;
			}
			for (int i = 0; i <= (pc != 0); ++i) {
				dfs(dfs, len - 1, pc - i, now << 1 | i);
			}
		}; dfs(dfs, 30 - (i + 1), i - 1, 0);
	}

	while (T--) {
		Thephix();
	}

	return 0;
}
```

## H. Step Debugging

模拟题，我一开始还想用栈来做，然后 dfs 写起来更简单，队友秒了。

```cpp
void Thephix() {
	constexpr i64 Mod = 20220911;
	
	auto dfs = [&](auto&& dfs) -> i64 {
		i64 ans = 0;
		while (true) {
			string s;
			cin >> s;
			if (s == "library") {
				ans = (ans + 1) % Mod;
			} else if (s == "fin") {
				return ans;
			} else if (s == "for") {
				i64 k;
				cin >> k >> s;
				assert(s == "times");
				return ans * k % Mod;
			} else if (s == "repeat") {
				ans += dfs(dfs);
				ans %= Mod;
			}
		}
	};

	cout << dfs(dfs) << "\n";
}
```

## J. Gachapon

神秘构造题，为了方便我们描述，我们称我们需要构造的数组的大小为 $n$，需要满足的期望为 $m$。我们先定义一个神秘的函数 $f$。$f(x)$ 表示前 $n - x$ 次抽卡全都失败了的情况下，抽出 SSR 的条件期望。然后我们有：

- $f(1) = 1$。因为前 $n - 1$ 次抽卡都失败了，第 $n$ 次抽卡一定成功。
- $f(x) = a_x + (1 - a_x)(1 + f(x - 1)) = 1 + (1 - a_x)f(x - 1)$。这里 $a_x$ 表示为第 $n - x + 1$ 次抽卡成功的概率。

我们的目标是 $f(n) = m$，考虑构造 $a$ 数组。我们直接使用注意力观察到：对于任意一个 $t \in (0, 1), x \in [1, n]$，$f(x) = 1 + (x - 1)\cdot t$ 都是可以做到的。我们使用数学归纳法来证明一下：

对于 $x = 1$，这是平凡的。假设我们已经知道了 $f(x) = 1 + (x - 1)\cdot t$，其中 $x \in [1, n)$，现在我们要让 $f(x + 1) = 1 + (1 - a_{x+1})f(x) = 1 + xt$，解方程可以得到：$1 - a_{x + 1} = \frac{xt}{1 + (x - 1)\cdot t}$。由于 $t \in (0, 1)$，所以 $1 - a_{x + 1} \in (0, 1)$。这样我们就成功地构造了 $a$ 数组。

既然我可以对于任意的 $t \in (0, 1)$ 都可以完成构造，那不妨看下我们需要的 $t$ 是否满足这个条件：$f(n) = 1 + (n - 1)\cdot t = m$ 解得 $t = \frac{m - 1}{n - 1}$。代入 $a$ 中就可以解出所有的 $a_i$，容易发现 $a$ 的分子分母都是小于 $10000$ 的。

别忘了输出 reverse 后的 $a$ 数组。

```cpp
void Thephix() {
	int n, m;
	cin >> n >> m;
	vector<array<i64, 2>> a(n + 1);
	a[1] = { 1, 1 };
	for (int i = 2; i <= n; ++i) {
		i64 x = n - m, y = n - 1 + (i - 2) * (m - 1);
		a[i] = { x / gcd(x, y), y / gcd(x, y) };
	}
	
	reverse(a.begin() + 1, a.end());
	for (int i = 1; i <= n; ++i) {
		auto& [x, y] = a[i];
		cout << x << ' ' << y << "\n";
	}
}
```

## L. LCS-like Problem

需要找到 $s$ 的一个子序列 $s'$ 满足 $s$ 和 $t$ 的最长公共子序列小于等于 $1$。考虑 dp，然后从一个已经确定好的子序列中往后延伸。你会发现，你需要考虑当前字符在 $t$ 中的出现位置一定要比 $s'$ 中其他字符在 $t$ 中的出现次数要早。然后就做完了，直接枚举 $s'$ 的最后一个字符，转移过来即可。

一些细节：

- $s$ 中的一些不在 $t$ 中出现的字符处理起来太麻烦了，直接把它们取出来，反正不影响最长公共子序列的判定。
- 然后从空串转移的时候，是不需要比较出现顺序的。所以需要特判一下从空串转移过来的情况。

```cpp
void Thephix() {
	string s, t;
	cin >> s >> t;

	array<vector<int>, 26> pos {};
	for (int i = 0; i < (int) t.size(); ++i) {
		pos[t[i] - 'a'].push_back(i);
	}

	int ans = 0;
	string p; swap(s, p);
	for (int i = 0; i < (int) p.size(); ++i) {
		if (pos[p[i] - 'a'].empty()) {
			ans++;
		} else s.push_back(p[i]);
	}

	int n = s.size();
	s = ' ' + s;
	vector dp(n + 1, array<int, 26> {});
	for (int i = 1; i <= n; ++i) {
		int ch = s[i] - 'a';
		dp[i] = dp[i - 1];
		dp[i][ch] = max(dp[i][ch], 1);
		for (int j = 0; j < 26; ++j) {
			if (pos[j].empty()) continue;
			if (ch == j) {
				if (pos[ch].size() == 1) {
					dp[i][ch] = max(dp[i][ch], dp[i - 1][j] + 1);
				}
			} else {
				if (pos[ch].back() < pos[j][0]) {
					dp[i][ch] = max(dp[i][ch], dp[i - 1][j] + 1);
				}
			}
		}
	}

	cout << ans + *max_element(dp[n].begin(), dp[n].end()) << "\n";
}
```
