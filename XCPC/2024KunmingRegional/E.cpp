#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

template<std::unsigned_integral U>
struct Bitset {
	struct Proxy {
		U& x;
		int p;
		Proxy(U& x, int p) : x(x), p(p) {}
		Proxy& operator=(bool v) {
			x &= ~(U(1) << p);
			if (v) x |= U(1) << p;
			return *this;
		}
		Proxy& operator=(const Proxy& v) {
			return *this = bool(v);
		}
		operator bool() const {
			return x >> p & 1;
		}
		void filp() { x ^= U(1) << p; }
	};

	int n;
	std::vector<U> d;
	static constexpr int B = sizeof(U) * 8;

	Bitset(int n = 0) : n(n) {
		int len = (n + B - 1) / B;
		d.assign(len, 0);
	}

	Bitset(int n, U v) : n(n) {
		int len = (n + B - 1) / B;
		d.assign(len, 0);
		d[0] = v;
	}

	void trim() {
		int r = n % B;
		if (r) d.back() &= (U(1) << r) - 1;
	}

	void resize(int k) {
		int len = (k + B - 1) / B;
		d.resize(len);
		n = k;
		trim();
	}

	void set() {
		int len = d.size();
		for (int i = 0; i < len; ++i) {
			d[i] = U(-1);
		}
		trim();
	}

	void reset() {
		int len = d.size();
		for (int i = 0; i < len; ++i) {
			d[i] = U(0);
		}
	}

	void flip() {
		int len = d.size();
		for (int i = 0; i < len; ++i) {
			d[i] = ~d[i];
		}
		trim();
	}

	Proxy operator[] (int p) {
		assert(0 <= p && p < n);
		return Proxy(d[p / B], p % B);
	}

	const Proxy operator[] (int p) const {
		assert(0 <= p && p < n);
		return Proxy(d[p / B], p % B);
	}

	Bitset operator~() const {
		Bitset res(*this);
		int len = d.size();
		for (int i = 0; i < len; ++i) {
			res.d[i] = ~d[i];
		}
		res.trim();
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
		if (x <= len - 1) d[len - x - 1] = d[len] >> y;
		for (int i = std::max(len - x, 0); i < len; ++i) {
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

	bool any() const { return count() != 0; }
	bool all() const { return count() == n; }
	bool none() const { return count() == 0; }
};

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

	vector<Bitset<u64>> basis(n, Bitset<u64> (n));
	vector<tuple<Bitset<u64>, int, int>> query;

	auto insert = [&](Bitset<u64> x, int u, int v) {
		Bitset<u64> _x(x);
		for (int i = n - 1; i >= 0; --i) {
			if (x[i] == 0) continue;
			if (basis[i].none()) {
				basis[i] = x;
				query.emplace_back(_x, u, v);
				return;
			}
			x ^= basis[i];
		}
	};

	insert(Bitset<u64>(n, 1), 1, 1);
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
			Bitset<u64> x(n);
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

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	// cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
