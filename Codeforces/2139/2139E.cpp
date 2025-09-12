#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<std::unsigned_integral U>
struct Bitset {
	struct Proxy {
		U& x;
		int p;
		Proxy(U& x, int p) : x(x), p(p) {}
		Proxy& operator=(bool v) {
			if (v) x |= U(1) << p;
			else x &= ~(U(1) << p);
			return *this;
		}
		Proxy& operator=(const Proxy& v) {
			return *this = bool(v);
		}
		operator bool() const {
			return x >> p & 1;
		}
	};

	int n;
	std::vector<U> d;
	static constexpr int B = sizeof(U) * 8;

	Bitset(int n = 0) : n(n) {
		int len = (n + B - 1) / B;
		d.assign(len, 0);
	}

	Proxy operator[] (int p) {
		assert(0 <= p && p < n);
		return Proxy(d[p / B], p % B);
	}

	Bitset operator~() const {
		Bitset res(*this);
		int len = d.size();
		for (int i = 0; i < len; ++i) {
			res.d[i] = ~d[i];
		}
		int r = n / B;
		if (r) res.d.back() &= (U(1) << r) - 1;
		return res;
	}

	Bitset& operator&=(const Bitset& o) & {
		assert(n == o.n);
		int len = d.size();
		for (int i = 0; i < len; ++i) {
			d[i] &= o.d[i];
		}
		return *this;
	}

	Bitset& operator|=(const Bitset& o) & {
		assert(n == o.n);
		int len = d.size();
		for (int i = 0; i < len; ++i) {
			d[i] |= o.d[i];
		}
		return *this;
	}

	Bitset& operator^=(const Bitset& o) & {
		assert(n == o.n);
		int len = d.size();
		for (int i = 0; i < len; ++i) {
			d[i] ^= o.d[i];
		}
		return *this;
		bitset<1> x;
		x >>= 1;
	}

	Bitset& operator<<=(const int& k) & {
		int len = d.size(), x = k / B, y = k % B, z = B - y;
		for (int i = d.size() - 1; i > x; --i) {
			d[i] = d[i - x] << y | d[i - x - 1] >> z;
		}
		if (x < len) d[x] = d[0] << y;
		for (int i = 0; i < std::min(x, len); ++i) {
			d[i] = 0;
		}
		return *this;
	}

	Bitset& operator>>=(const int& k) & {
		int len = d.size(), x = k / B, y = k % B, z = B - y;
		for (int i = 0; i < len - x - 1; ++i) {
			d[i] = d[i + x] >> y | d[i + x + 1] << z;
		}
		if (len - x - 1 >= 0) d[len - x - 1] = d[len] >> y;
		for (int i = max(len - x, 0); i < len; ++i) {
			d[i] = 0;
		}
		return *this;
	}

	friend Bitset operator&(Bitset x, const Bitset& y) { x &= y; return x; }
	friend Bitset operator|(Bitset x, const Bitset& y) { x |= y; return x; }
	friend Bitset operator^(Bitset x, const Bitset& y) { x ^= y; return x; }
	friend Bitset operator<<(Bitset x, const int& k) { x <<= k; return x; }
	friend Bitset operator>>(Bitset x, const int& k) { x >>= k; return x; }

	int count() const {
		int ans = 0, len = d.size();
		for (int i = 0; i < len; ++i) {
			ans += std::popcount(d[i]);
		}
		return ans;
	}

	int count(int l, int r) const {
		return (*this >> l).count() - (*this >> (r + 1)).count();
	}

	bool any() const {
		return count() != 0;
	}

	bool all() const {
		return count() == n;
	}
};

void Thephix() {
	int n, k;
	cin >> n >> k;
	vector<vector<int>> adj(n + 1);
	for (int i = 2; i <= n; ++i) {
		int p; cin >> p;
		adj[p].push_back(i);
	}

	int Min = n;
	vector<int> dep(n + 1), cnt(n + 1);

	dep[1] = 1;
	[&](this auto&& dfs, int u) -> void {
		cnt[dep[u]]++;
		if (adj[u].empty()) {
			Min = min(Min, dep[u]);
		}
		for (auto& v : adj[u]) {
			dep[v] = dep[u] + 1;
			dfs(v);
		}
	} (1);
	
	int sum = accumulate(cnt.begin() + 1, cnt.begin() + Min + 1, 0LL);
	int rest = n - sum;
	int ok = 0;

	k = min(k, n - k);
	
	Bitset<u64> dp(k + 1);
	dp[0] = 1;
	for (int i = 1; i <= Min; ++i) {
		dp |= dp << cnt[i];
	}
	for (int i = max(k - rest, 0); i <= k; ++i) {
		ok |= dp[i];
	}
	
	cout << Min + ok - 1 << "\n";
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
