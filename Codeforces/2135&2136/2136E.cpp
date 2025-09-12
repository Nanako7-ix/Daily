#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

struct DSU {
	int n, cnt;
	std::vector<int> f, siz;

	DSU() = default;

	DSU(int n) { init(n); }

	void init(int n) {
		this -> n = n;
		cnt = n;
		f.resize(n + 1);
		siz.assign(n + 1, 1);
		std::iota(f.begin(), f.end(), 0);
	}

	int find(int x) {
		if(f[x] == x) return x;
		return f[x] = find(f[x]);
	}

	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return false;
		siz[f[y] = x] += siz[y], cnt--;
		return true;
	}

	bool same(int x, int y) {
		return find(x) == find(y);
	}

	int size(int x) {
		return siz[find(x)];
	}

	int count() const {
		return cnt;
	}
};

template<u32 Mod> constexpr u32 mulMod(u32 a, u32 b) { return static_cast<u64> (a) * b % Mod; }
template<u64 Mod> constexpr u64 mulMod(u64 a, u64 b) { return static_cast<u128>(a) * b % Mod; }

template<std::unsigned_integral U, U Mod, typename S = std::make_signed_t<U>>
struct ModInt {
public:
		constexpr ModInt() : x(0) {}
		template<std::unsigned_integral T> constexpr ModInt(T v) : x(v % Mod) {}
		template<std::signed_integral T> constexpr ModInt(T v) { S t = v % S(Mod); x = t < 0 ? t + Mod : t; }
		constexpr U val() const { return x; }
		constexpr static int mod() { return Mod; }
		constexpr ModInt operator-() const { return x == 0 ? 0 : Mod - x; }
		constexpr ModInt inv() const { return pow(Mod - 2); }
		constexpr ModInt& operator+=(const ModInt& rhs) & { x += rhs.val(); if(x >= Mod) x -= Mod; return *this; }
		constexpr ModInt& operator-=(const ModInt& rhs) & { x -= rhs.val(); if(x >= Mod) x += Mod; return *this; }
		constexpr ModInt& operator*=(const ModInt& rhs) & { x = mulMod<Mod>(x, rhs.val()); return *this; }
		constexpr ModInt& operator/=(const ModInt& rhs) & { return *this *= rhs.inv(); }
		friend constexpr ModInt operator+(ModInt lhs, const ModInt& rhs) { return lhs += rhs; }
		friend constexpr ModInt operator-(ModInt lhs, const ModInt& rhs) { return lhs -= rhs; }
		friend constexpr ModInt operator*(ModInt lhs, const ModInt& rhs) { return lhs *= rhs; }
		friend constexpr ModInt operator/(ModInt lhs, const ModInt& rhs) { return lhs /= rhs; }
		friend constexpr std::strong_ordering operator<=>(const ModInt &lhs, const ModInt &rhs) = default;
		friend std::istream& operator>>(std::istream& is, ModInt& a) { i64 x; is >> x; a = ModInt(x); return is; }
		friend std::ostream& operator<<(std::ostream& os, const ModInt& a) { os << a.val(); return os; }
		constexpr ModInt pow(i64 b) const { ModInt res = 1, a = *this; for (; b; b >>= 1, a *= a) if (b & 1) res *= a; return res; }
private:
		U x;
};

using Z = ModInt<u32, 998244353>;

void Thephix() {
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> a(n + 1);
	vector<vector<int>> adj(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	DSU dsu(n);
	vector<int> dp(n + 1), fa(n + 1), dep(n + 1);
	[&](this auto&& dfs, int u) -> void {
		dep[u] = dep[fa[u]] + 1;
		for (auto v : adj[u]) {
			if (v == fa[u]) continue;
			if (dep[v] != 0) {
				if (dep[u] < dep[v]) continue;
				for (int x = dsu.find(u); !dsu.same(x, v); x = dsu.find(x)) {
					dp[dsu.find(fa[x])] |= dp[x];
					dsu.merge(fa[x], x);
				}
				if ((dep[u] - dep[v]) % 2 == 0) {
					dp[dsu.find(v)] = 1;
				} else dp[dsu.find(v)] |= dp[dsu.find(u)];
			} else {
				fa[v] = u;
				dfs(v);
			}
		}
	} (1);

	Z ans = 1;
	vector<vector<int>> p(n + 1);
	for (int i = 1; i <= n; ++i) {
		p[dsu.find(i)].push_back(i);
	}
	for (int root = 1; root <= n; ++root) {
		auto& edcc = p[root];
		if (edcc.empty()) continue;
		set<int> S;
		for (auto x : edcc) {
			if (a[x] != -1) {
				S.insert(a[x]);
			}
		}

		if (dp[root] == 1) {
			if (S.empty() || (S.size() == 1 && S.contains(0))) {
				ans *= 1;
			} else {
				ans *= 0;
			}
		} else {
			if (S.size() == 0) {
				ans *= k;
			} else if (S.size() == 1) {
				ans *= 1;
			} else {
				ans *= 0;
			}
		}
	}
	cout << ans << "\n";
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
