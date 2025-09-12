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

using Z = ModInt<u32, 1'000'000'007>;
Comb<Z> comb;

void Thephix() {
	array<int, 4> c;
	cin >> c[0] >> c[1] >> c[2] >> c[3];

	int n = c[0] + c[1] + c[2] + c[3];
	vector f(n + 1, vector<Z> (c[0] + c[2]));
	for (int i = 1; i <= c[0] + c[2]; ++i) {
		Z x = 0;
		x += comb.C(c[0] - 1, (i + 1) / 2 - 1) * comb.C(c[2] - 1, i / 2 - 1);
		x += comb.C(c[2] - 1, (i + 1) / 2 - 1) * comb.C(c[0] - 1, i / 2 - 1);
		for (int j = 0; j < i; ++j) {
			for (int k = 0; k <= c[0] + c[2] - i; ++k) {
				f[j + k + 1][i - 1 - j] += x * comb.C(i - 1, j) * comb.C(c[0] + c[2] - i, k);
			}
		}
	}			
	
	vector g(n + 1, vector<Z> (c[1] + c[3]));
	for (int i = 1; i <= c[1] + c[3]; ++i) {
		Z x = 0;
		x += comb.C(c[1] - 1, (i + 1) / 2 - 1) * comb.C(c[3] - 1, i / 2 - 1);
		x += comb.C(c[3] - 1, (i + 1) / 2 - 1) * comb.C(c[1] - 1, i / 2 - 1);
		for (int j = 0; j < i; ++j) {
			for (int k = 0; k <= c[1] + c[3] - i; ++k) {
				g[j + k + 1][i - 1 - j] += x * comb.C(i - 1, j) * comb.C(c[1] + c[3] - i, k);
			}
		}
	}

	vector<Z> ans(6 * n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < c[0] + c[2]; ++j) {
			for (int k = 0; k < c[1] + c[3]; ++k) {
				ans[i - 1 + 2 * (j + k)] += f[(i + 1) / 2][j] * g[i / 2][k];
				ans[i - 1 + 2 * (j + k)] += f[i / 2][j] * g[(i + 1) / 2][k];
			}
		}
	}

	for (int i = 0; i <= 2 * n - 2; ++i) {
		cout << ans[i] << " \n"[i == 2 * n - 2];
	}
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
