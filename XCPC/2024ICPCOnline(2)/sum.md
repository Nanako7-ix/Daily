# [The 2024 ICPC Asia EC Regionals Online Contest (II)](https://qoj.ac/contest/1799)

## [A. Gambling on Choosing Regionals](https://qoj.ac/contest/1799/problem/9370)

每个队伍考虑最坏的情况。既然是最坏的情况，那一定是你去哪，强队就会过来狙击你，所以选择一个少人的赛站是正确的。那么只需要考虑 $c_i$ 最小的赛站即可，然后你的排名就等于：满足 $c_i$ 要求的情况下，比你强的队伍的个数 + 1。注意到弱队的参加情况对你来说是没用的，所以直接倒序枚举就做完了。

```cpp
void Thephix() {
	int n, m;
	cin >> n >> m;
	vector<int> c(m + 1);
	for (int i = 1; i <= m; ++i) {
		cin >> c[i];
	}
	int Min = *min_element(c.begin() + 1, c.end());

	vector<tuple<int, string, int>> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		auto& [w, s, id] = a[i];
		cin >> w >> s;
		id = i;
	}
	sort(a.begin() + 1, a.end(), greater {});

	int now = 0;
	map<string, int> cnt;
	vector<int> ans(n + 1);
	for (int i = 1; i <= n; ++i) {
		auto& [w, s, id] = a[i];
		if (cnt[s] < Min) {
			now++, cnt[s]++;
		}
		ans[id] = now;
	}
	for (int i = 1; i <= n; ++i) {
		cout << ans[i] << "\n";
	}
}
```

## [C. Prefix of Suffixes](https://qoj.ac/contest/1799/problem/9372)

需要在线求出 Z 函数。说明 `zFunction` 的板子没用了，考虑 lcp 还能怎么做。lcp 和 前缀函数是很类似的，我们可以考虑使用 kmp 来求解。考虑一个字符串在 extend 的时候，Z 函数的变化情况：显然有一部分位置的 Z 函数值是不变的，而另一部分的 Z 函数值是会 +1 的，我们考虑什么时候它会 +1。如果一个后缀，在 extend 之后，仍然是 s 的 border，那么它会 +1，否则它的 Z 函数从此以后不会再发生变化。那么也就是说，我只要对于所有的后缀，求出它第一次不再是 border 的时间点，就能确定它的 Z 函数值。显然这个 Z 函数值最多被确定 $n$ 次，我们要做的就是快速找到那些：原来是 border，但 extend 之后不再是 border 的后缀。

所有你有了一个暴力跳 border 的方法：找到原来的所有的 border，其中有一部分的 border，extend 后不再是 border，这个时候把它的 Z 函数值确定下来。这样做一看就很不对吧，会 T，所以你考虑怎么快速地找到我想要的 border。

观察一下我想要的 border 是什么。假设我们现在 append 的字符是 ch，那么一个长度为 $t$ 的 border 在 extend 之后仍然是 border，当且仅当 $\text{s}_{t + 1} \neq \text{ch}$。我们记 border tree 上每个节点的 next 表示该前缀的下一个字符。那么我们需要找的就是原来的 border 链上，所有 $\text{next} \neq \text{ch}$ 的节点。我们灵光一闪，对于每个节点，维护往上跳 border 中第一个 next 与当前节点的 next 不同的节点，我们称为 up。

up 首先是好维护的，如果父节点与当前节点的 next 不同，显然 up 就是父节点。否则和父节点的 up 值相同。其次，up 值是好利用的。我们暴力跳 border 的过程中，如果遇到了我们不想要的节点（$\text{next} = \text{ch}$），我们就跳 up 而不是跳 fail。因为我需要找的是与 $\text{ch}$ 不同，也就是与 $\text{next}(u)$ 不同的节点，这个时候刚好满足 up 的定义，所以是跳 up 会更好（因为可以略过一部分的 $\text{next} = \text{ch}$ 的节点）。于是你就发现：我草怎么过了

事实上你会发现：虽然我正常跳 fail 会跳到不需要的节点，但是当我跳 up 之后的下一个节点一定是需要的节点，这也就是说，我在最坏的情况下，访问到的需要的节点和不需要的节点数量是 $1:1$ 的，而我们需要的节点的总数量是 $O(n)$ 的，所以我们访问到的不需要的节点数也不会超过 $O(n)$。这样我们只访问了 $O(n)$ 个节点就完成了 `zFunction` 的确定。

妈的写 0base 还是太折磨了！

```cpp
void Thephix() {
	int n;
	cin >> n;
	vector<int> a(n), k(n);
	vector<int> fail(n), up(n + 1);
	i64 ans = 0, tot = 0;
	for (int i = 0, j = 0; i < n; ++i) {
		int ch, x;
		cin >> ch >> x >> k[i];
		a[i] = ch = (ch + ans) % n;
		if (i == 0 || ch == a[0]) {
			tot += k[i];
		}
		if (i != 0) {
			up[i] = a[i] == a[j] ? up[j] : j;
			for (int u = up[i]; u; u = a[u] == ch ? up[u] : fail[u - 1]) {
				if (a[u] == ch) continue;
				tot -= k[i - u];
			}
			while (j && a[i] != a[j]) j = fail[j - 1];
			fail[i] = j += (a[i] == a[j]);
		}
		ans += tot * x;
		cout << ans << "\n";
	}
}
```

## [E. Escape](https://qoj.ac/contest/1799/problem/9374)

我们可以发现，机器人可以选择反复横跳来延长自己的生命，这个行为我们可以认为是

## [F. Tourist](https://qoj.ac/contest/1799/problem/9375)

签到题，经典环节：meikailonglong

```cpp
void Thephix() {
	int n;
	cin >> n;
	vector<i64> a(n + 1);
	i64 now = 1500;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		now += a[i];
		if (now >= 4000) {
			cout << i << "\n";
			return;
		}
	}
	cout << "-1\n";
}
```

## [G. Game](https://qoj.ac/contest/1799/problem/9376)

我们考虑直接爆搜！记当前 Alice 的 chip 的数量为 $x$，Bob 的 chip 的数量为 $y$，我们发现，如果 $x = y$，那么一局定胜负，如果 $x > y$ 那么你输一把我就直接赢了，如果 $x < y$，那么首先我下一把只能赢。于是你可以光速构思出这样的代码：

```cpp
function f(x, y) -> ModInt<998244353> {
	if x == y: return win
	if x < y : return win * f(x, y - x)
	if x > y : return win + fail * f(x - y, x)
}
```

然后你就会发现，我出一个 $x = 10^9$，$y = 1$ 的，你不炸了吗。这个时候你会发现，诶？如果 y 赢了，那么还是没什么用啊，下一把局势还是这样，y 只能继续赢，直到连赢 $10^9$ 把。那我们能不能这样，直接计算出我需要连赢的局数？于是你把上面的代码改了一下：

```cpp
function f(x, y) -> ModInt<998244353> {
	if x == y: return win
	if x < y : return win.pow(k) * f(x, y - kx)
	if x > y : return ?
}
```

坏了，第三个怎么改。这个时候你会发现，你现在需要做的是返回赢的概率。而最终的游戏不存在平局，那么不就是返回 1 - 对方赢的概率吗？那我只直接反过来求对方获胜的概率，然后再用 $1$ 减掉这个概率，不就算完了吗？对吗？不对，win 和 fail 是什么，我获胜的概率，那平局呢？

这个时候就有数学大神可以做到带着平局的可能性一起计算了，但是我是飞舞，我不会。那么我们考虑一件事：我平局不会影响当前的局势，那么我可以考虑一下，我第一次遇到非平局的情况时，我获胜的概率是多大？于是：

$$
\begin{aligned}
\text{win} &= \sum_{i=0}^\infty \text{win} \cdot \text{draw}^i\\
&= \text{win} \sum_{i=0}^\infty \text{draw}^i\\
&= \text{win} \cdot \frac{1}{1 - \text{draw}}\\
&= \frac{\text{win}}{1 - (1 - \text{win} - \text{fail})}\\
&= \frac{\text{win}}{\text{win} + \text{fail}}
\end{aligned}
$$

```cpp
void Thephix() {
	i64 x, y, a1, a2, b;
	cin >> x >> y >> a1 >> a2 >> b;

	cout << [&](this auto&& f, i64 x, i64 y, Z p) -> Z {
		if (x == y) return p;
		if (x > y) return 1 - f(y, x, 1 - p);
		i64 k = (y - 1) / x;
		return p.pow(k) * f(x, y - k * x, p);
	} (x, y, Z(a1) / (a1 + a2)) << "\n";
}
```

## [I. Strange Binary](https://qoj.ac/contest/1799/problem/9378)

简单的签到，构造一个只包含 $-1, 0, 1$ 的数组使得 

$$
n = \sum_{i=0}^{31} a_i2^i
$$

于是你很快写完了一个二进制数。发现他还有另一个条件：不能有相邻两个位置同时为 $0$。所以你想把 $0$ 消掉，这个时候你发现：

$$
2^x - 2^{x-1} - 2^{x-2} - \cdots- 2^y = 2^y
$$

所以我从高位往低位照，遇到 $0$ 的时候，找到下一个不为 $0$ 的数字（这个数字一定是 $1$），然后通过上面的公式把 $0$ 全部消掉。这个时候你就会发现一些问题：如果不存在下一个不为 $0$ 的数字怎么办。那就消不了了，所以你只能祈祷 $0$ 的数量不超过 $1$。

所以你只需要判断结尾两个数字是否同时为 $0$，如果是，那么输出 NO，否则输出构造方案。

```cpp
void Thephix() {
	int n;
	cin >> n;
	array<int, 32> a {};
	for (int i = 0; i < 32; ++i) {
		a[i] = n >> i & 1;
	}
	
	if (a[0] == 0 && a[1] == 0) {
		cout << "NO\n";
		return;
	}

	cout << "YES\n";
	for (int i = 31; i >= 0; --i) {
		if (a[i] != 0) continue;
		int next = -1;
		for (int j = i; j >= 0; --j) {
			if (a[j] == 1) {
				next = j;
				break;
			}
		}
		if (next == -1) {
			assert(i == 0);
		} else {
			a[i] = 1;
			for (int j = i - 1; j >= next; --j) {
				a[j] = -1;
			}
		}
	}

	for (int i = 0; i < 32; i += 8) {
		for (int j = 0; j < 8; ++j) {
			cout << a[i + j] << " \n"[j == 7];
		}
	}
}
```

## [J. Stacking of Goods](https://qoj.ac/contest/1799/problem/9378)

直接排序做就好了，为什么排序我也不知道。但是看了题解我觉得很对，交换两个位置，计算交换前后的差，然后用这个来排序。确实想不到，这有什么办法，玉玉了。

```cpp
void Thephix() {
	int n;
	cin >> n;
	i64 ans = 0;
	vector<array<i64, 2>> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		i64 w, v, c;
		cin >> w >> v >> c;
		ans += v;
		a[i] = { w, c };
	}
	sort(a.begin() + 1, a.end(), [](array<i64, 2> x, array<i64, 2> y) {
		return x[0] * y[1] > y[0] * x[1];
	});
	
	vector<i64> suf(n + 2);
	for (int i = n; i >= 1; --i) {
		suf[i] = suf[i + 1] + a[i][1];
	}
	for (int i = 1; i <= n; ++i) {
		ans -= a[i][0] * suf[i + 1];
	}
	cout << ans << "\n";
}
```

## [L. Bad Gateway](https://qoj.ac/contest/1799/problem/9381)

直观的感受就是：时间如果太短了，那么就直接不需要刷新，等他结束就行了，否则我们就刷新界面。所以假设我们的剩余时间为 $[1, k]$ 的时候直接等待结束，在 $(k, T]$ 的时候选择刷新。

我们设 $f(x)$ 为从 $x$ 开始，时间走到 $0$ 的期望步数，那么 $x \leq k$ 时，$f(x) = x$。当 $x > k$ 时，我们考虑枚举重投的次数 $n$，则：

$$
\begin{aligned}
f(x) &= \sum_{n=1}^\infty (\frac{k}{T}\cdot(\frac{T-k}{T})^{n-1}\cdot(n+\frac{\sum_{i=1}^k f(i)}{k}))\\
&= \frac{k}{T}(\sum_{n=1}^\infty n\cdot(\frac{T-k}{T})^{n-1} + \sum_{n=1}^\infty(\frac{T-k}{T})^{n-1}\frac{\sum_{i=1}^k f(i)}{k})\\
&= \frac{k}{T}(\sum_{n=1}^\infty -T((\frac{T-k}{T})^n)' + \frac{\sum_{i=1}^k f(i)}{k}\sum_{n=1}^\infty(\frac{T-k}{T})^{n-1})\\
&= \frac{k}{T}(-T(\sum_{n=1}^\infty (\frac{T-k}{T})^n)' + \frac{\frac{(1+k)k}{2}}{k}\sum_{n=1}^\infty(\frac{T-k}{T})^{n-1})\\
&= \frac{k}{T}(-T(\frac{\frac{T-k}{T}}{1-\frac{T-k}{T}})' + \frac{1+k}{2}\cdot\frac{1}{1-\frac{T-k}{T}})\\
&= \frac{k}{T}(-T(\frac{T-k}{k})' + \frac{1+k}{2}\cdot \frac{T}{k})\\
&= -k\cdot(\frac{T}{k}-1)' + \frac{1+k}{2}\\
&= k\cdot \frac{T}{k^2} + \frac{1+k}{2}\\
&= \frac{T}{k} + \frac{1+k}{2}
\end{aligned}
$$

我们最后需要的答案是：

$$
\begin{aligned}
&\frac{\sum_{x=1}^T f(x)}{T}\\
=&\frac{1}{T}(\sum_{x=1}^k f(x) + \sum_{x = k + 1}^T f(x))\\
=&\frac{1}{T}(\frac{(1+k)k}{2} + (T-k)(\frac{T}{k} + \frac{1+k}{2}))\\
=&\frac{1}{T}(\frac{(1+k)k}{2} + \frac{T^2}{k} - T^2 + \frac{T+Tk}{2}-\frac{(1+k)k}{2})\\
=&\frac{T}{k}+\frac{1+k}{2}-T
\end{aligned}
$$

当 $k=\sqrt{2T}$ 的时候，上式取得最值。为了方便计算，把上式化成：

$$
\frac{T + k + k^2 - 2kT}{2k}
$$

然后就可以直接计算这个比较 $k = \lfloor\sqrt{2T}\rfloor$ 和 $k = \lceil\sqrt{2T}\rceil$ 的时候的大小，取 Min 就是答案。

我草！这么难！

```cpp

```

如果没有直观的感觉怎么办，那么没救了。这个东西可以证明的，但是证明的前提也是要先想到，想不到是真寄了（没错就是我）。
