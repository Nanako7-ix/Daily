#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

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

template<typename Z>
vector<Z> f = []() {
	constexpr int N = 100000;
	vector<Z> f(N + 1);
	f[0] = 1;
	for (int i = 1; i <= N; ++i) {
		f[i] = f[i - 1] * i;
	}
	return f;
} ();

template<typename Z>
vector<Z> g = []() {
	constexpr int N = 100000;
	vector<Z> g(N + 1);
	g[N] = f<Z>[N].inv();
	for (int i = N; i >= 1; --i) { // 这里不要复制，别写成正序遍历了
		g[i - 1] = g[i] * i;
	}
	return g;
} ();

template<typename T>
T lagrangeIota(T x, const vector<T>& y) {
	int n = y.size();
	if (x < n) return y[x.val()];

	vector<T> lp(n + 1), rp(n + 1);
	lp[0] = rp[n] = 1;
	for (int i = 0; i < n; ++i) {
		lp[i + 1] = lp[i] * (x - i);
	}
	for (int i = n - 1; i >= 0; --i) {
		rp[i] = rp[i + 1] * (x - i);
	}

	T ans = 0;
	for (int i = 0; i < n; ++i) {
		if ((n - 1 - i) & 1) {
			ans -= y[i] * lp[i] * rp[i + 1] * g<T>[i] * g<T>[n - 1 - i];
		} else {
			ans += y[i] * lp[i] * rp[i + 1] * g<T>[i] * g<T>[n - 1 - i];
		}
	}
	return ans;
}

template<typename T>
T lagrangeAny(T x, const vector<pair<T, T>>& f) {
	T ans = 0; int n = f.size();
	for (int i = 0; i < n; ++i) {
		Z u = 1, d = 1;
		auto& [xi, yi] = f[i];
		for (int j = 0; j < n; ++j) {
			if (i == j) continue;
			auto& [xj, yj] = f[j];
			if (x == xj) return yj;
			u *=  x - xj;
			d *= xi - xj;
		}
		ans += yi * u / d;
	}
	return ans;
}

void Thephix() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
	}

	vector<pair<Z, Z>> f(n);
	f[0] = { 0, n == 1 };
	for (int i = 1; i < n; ++i) {
		cout << "? 1 " << n << ' ' << i << endl;
		auto& [x, y] = f[i];
		x = i, cin >> y;
	}

	cout << "!" << endl;
	int x; cin >> x;
	cout << lagrangeAny<Z>(x, f) << endl;
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
