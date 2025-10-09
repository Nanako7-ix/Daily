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

using Z = ModInt<u32, 1'000'000'007>;

template<std::unsigned_integral T>
constexpr T floor_sqrt (T n) {
	T t = std::sqrt(n);
	while (t * t > n) --t;
	while ((t + 1) * (t + 1) < n) ++t;
	return t;
}

template<typename T>
struct Min_25 {
public:
	Min_25(i64 n) { init(n); }
private:
	i64 n, sq, m;
	vector<T> g1, g2;
	vector<T> pre;

	T& g(i64 k) { return k <= sq ? g1[k] : g2[n / k]; }

	T f(i64 x) { return x; }
	T s(i64 x) { return x * (x + 1) / 2; }
	
	void init(i64 n) {
		this -> n = n;
		this -> sq = [n]() {
			i64 t = std::sqrt(n);
			while (t * t > n) --t;
			while ((t + 1) * (t + 1) < n) ++t;
			return t;
		} ();

		g1.assign(sq + 1, T());
		g2.assign(sq + 1, T());

		sieve(sq);
		m = P.size();
		pre.assign(m + 1, T());
		for (int i = 0; i < m; ++i) {
			pre[i + 1] = pre[i] + f(P[i]);
		}

		vector<i64> x;
		for (i64 k = 1; k <= n; ++k) {
			g(n / k) = s(n / k) - f(1);
			x.push_back(n / k);
			k = n / (n / k);
		}
		
		for (i64 j = 0; j < m; ++j) {
			i64 p = P[j];
			cout << "p = " << p << "\n";
			for (i64 i = 0; i < (int) x.size(); ++i) {
				cout << "g(" << x[i] << ", " << j << ") = " << g(x[i]) << " -> ";
				if (p * p <= x[i]) {
					g(x[i]) -= f(p) * (g(x[i] / p) - pre[max(j - 1, 0LL)]);
					cout << "(" << f(p) << " " << g(x[i] / p) << ' ' << pre[max(j - 1, 0LL)] << ") -> ";
				}
				cout << "g(" << x[i] << ", " << j + 1 << ") = " << g(x[i]) << "\n";
			}
			cout << "\n";
		}

		cout << g(n) << "\n";
	}

	std::vector<i64> minp, P;

	void sieve(i64 n) {
		minp.assign(n + 1, 0);
		P.clear();
		for (i64 i = 2; i <= n; ++i) {
			if (minp[i] == 0) {
				P.push_back(minp[i] = i);
			}
			for (i64& p : P) {
				if(i * p > n) break;
				minp[i * p] = p;
				if(i % p == 0) break;
			}
		}
	}
};

void Thephix() {
	i64 n;
	cin >> n;
	Min_25<i64> min_25(n);
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
