#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

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

template<typename Z>
struct Comb {
	int n;
	std::vector<Z> f, g;
	Comb() : n(0), f{1}, g{1} {}
	void init(int m) {
		if (m <= n) return;
		f.resize(m + 1);
		g.resize(m + 1);
		for (int i = n + 1; i <= m; ++i) {
			f[i] = f[i - 1] * i;
		}
		g[m] = f[m].inv();
		for (int i = m; i >= n + 1; --i) {
			g[i - 1] = g[i] * i;
		}
		n = m;
	}
	Z fac(int m) {
		if (n < m) init(2 * m);
		return f[m];
	}
	Z invfac(int m) {
		if (n < m) init(2 * m);
		return g[m];
	}
	Z inv(int m) {
		return invfac(m) * fac(m - 1);
	}
	Z C(int n, int m) {
		if (n < m || m < 0) return 0;
		return fac(n) * invfac(m) * invfac(n - m);
	}
	Z A(int n, int m) {
		if (n < m || m < 0) return 0;
		return fac(n) * invfac(n - m);
	}
};

using Z = ModInt<u32, 998244353>;
Comb<Z> comb;

void Thephix() {
	int n;
	cin >> n;
	vector<vector<int>> adj(n + 1);
	for (int u = 2; u <= n; ++u) {
		int p; cin >> p;
		adj[p].push_back(u);
	}

	vector<int> siz(n + 1);
	vector<Z> g(n + 1);
	auto jxt = [&](auto&& jxt, int u, int p) -> void {
		siz[u] = 1;
		g[u] = 1;
		for (auto& v : adj[u]) {
			if (v == p) continue;
			jxt(jxt, v, u);
			siz[u] += siz[v];
			g[u] *= g[v];
		}
		g[u] *= siz[u];
	}; jxt(jxt, 1, 0);
	
	vector<vector<Z>> f(n + 1, vector<Z> (n + 1));
	f[1][1] = 1;

	auto dfs = [&](auto&& dfs, int u, int p) -> void {
		if (p != 0) {
			Z x = comb.fac(siz[p] - siz[u]) * g[u] / g[p] * siz[p] / (siz[p] - siz[u]);
			Z y = 0;
			for (int i = 1; i <= n; ++i) {
				f[u][i] = x * y;
				y += comb.C(n - siz[u] - i, siz[p] - siz[u] - 1) * f[p][i];
			}
		}
		for (auto& v : adj[u]) {
			if (v == p) continue;
			dfs(dfs, v, u);
		}
	}; dfs(dfs, 1, 0);

	for (int u = 1; u <= n; ++u) {
		Z ans = comb.C(n - u, siz[u] - 1) * f[u][u] * (comb.fac(siz[u]) / g[u]);
		cout << ans << " \n"[u == n];
	}
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
