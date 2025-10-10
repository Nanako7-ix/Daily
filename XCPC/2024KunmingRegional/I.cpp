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

using Z = ModInt<u32, 998244353>;

vector<Z> NTT(vector<Z> a, vector<Z> b) {
	static constexpr Z g = 3;
	static constexpr u64 P = Z::mod();
	static vector<Z> rt { 0, 1 };

	int tot = a.size() + b.size() - 1;
	int k = __lg(tot - 1);
	int n = 1 << (k + 1);

	vector<int> rev(n);
	for (int i = 0; i < n; ++i) {
		rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
	}
	
	if ((int) rt.size() < n) {
		int k = countr_zero(rt.size());
		rt.resize(n);
		for (; (1 << k) < n; ++k) {
			auto e = g.pow((P - 1) >> (k + 1));
			for (int i = 1 << (k - 1); i < (1 << k); ++i) {
				rt[i << 1] = rt[i];
				rt[i << 1 | 1] = rt[i] * e;
			}
		}
	}

	auto dft = [&](vector<Z>& f) {
		for (int i = 0; i < n; ++i) {
			if (i < rev[i]) swap(f[i], f[rev[i]]);
		}
		for (int i = 1; i < n; i <<= 1) {
			for (int j = 0; j < n; j += 2 * i) {
				for (int k = 0; k < i; ++k) {
					Z fx = f[j + k];
					Z fy = f[i + j + k] * rt[i + k];
					f[j + k] = fx + fy;
					f[i + j + k] = fx - fy;
				}
			}
		}
	};

	a.resize(n), b.resize(n);
	dft(a), dft(b);

	for (int i = 0; i < n; ++i) {
		a[i] *= b[i];
	}
	
	reverse(a.begin() + 1, a.end());
	dft(a);
	a.resize(tot);
	Z inv = Z(1 - P) / n;
	for (int i = 0; i < tot; ++i) {
		a[i] *= inv;
	}
	
	return a;
}

void Thephix() {
	i64 n, m;
	cin >> n >> m;
	
	i64 k = m / n;
	m -= k * n;

	vector<Z> a(2 * n + 1);
	for (int i = 1; i <= n; ++i) {
		int x; cin >> x;
		a[x - k + n] = 1;
	}
	
	vector<Z> res(n + 1);
	res[0] = 1;
	for (int b = n; b; b >>= 1) {
		if (b & 1) {
			auto F = NTT(res, a);
			for (int i = 0; i <= n; ++i) {
				res[i] = F[i + n] != 0;
			}
			res.resize(n + 1);
		}
		a = NTT(a, a);
		for (int i = 0; i <= 2 * n; ++i) {
			a[i] = a[i + n] != 0;
		}
		a.resize(2 * n + 1);
	}

	if (res[m] != 0) {
		cout << "Yes\n";
	} else {
		cout << "No\n";
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
