## F. The Hermit

先看看什么时候需要删除，应该怎么删除。需要删除的情况就是 $\min = \gcd$ 也就是最小值是集合中所有数的因子。这种情况下，$\min$ 是一定需要被删除的，否则永远 $\gcd = \min$ 恒成立。所以**一定是删除小的数字**，直到这个最小的数字不是最大公因数。

考虑 $f(x)$ 为恰好需要删除 $x$ 个数的集合个数，$g(x)$ 为至少需要删除 $x$ 个数的集合个数。那么 $f(x) = g(x) - g(x + 1)$。

至少需要删的次数为 $k$，也就是前 $k$ 个数一定是类似于套娃的结构，也就是，这样每一个数都是后面的因子。后面的 $n - k$ 个数一定是 $a_k$ 的因子。

$a_{k + 1}, \cdots, a_n$ 的方案数是 $\binom{\lfloor\frac{m}{a_k}\rfloor - 1}{n-k}$。前面的 $k$ 个数的方案数 dp 一下即可。考虑第 $k$ 个数为 $x$，方案数为 $\operatorname{dp}(x, k)$。那么转移方程为：

$$
\operatorname{dp}(x, k) = \sum_{d \mid x} \operatorname{dp}(d, k - 1)
$$

因为需要删除的次数最多为 $\log m$ 次。所以时间复杂度大概是 $O(m\log^2 m)$ 的。

```cpp
void Thephix() {
	int n, m;
	std::cin >> m >> n;

	vector<array<i64, Log + 1>> dp(m + 1);
	for (int i = 1; i <= m; ++i) {
		dp[i][1] = 1;
	}
	for (int j = 1; j < 20; ++j) {
		for (int i = 1; i <= m; ++i) {
			for (int k = 2 * i; k <= m; k += i) {
				(dp[k][j + 1] += dp[i][j]) %= Mod;
			}
		}
	}
	
	vector<i64> f(Log + 2);
	f[0] = Comb::C(m, n);
	for (int i = 1; i <= Log; ++i) {
		for (int j = 1; j <= m; ++j) {
			f[i] += dp[j][i] * Comb::C((m / j - 1), n - i) % Mod;
			f[i] %= Mod;
		}
	}


	i64 ans = 0;
	for (int i = 0; i <= Log; ++i) {
		ans += (f[i] - f[i + 1] + Mod) * (n - i) % Mod;
		ans %= Mod;
	}
	cout << ans << "\n";
}
```