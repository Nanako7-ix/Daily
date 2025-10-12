#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<typename T, typename F_Tp, typename sum_Tp>
struct Min_25 {
public:
	vector<i64> minp, P;
	Min_25(i64 n, F_Tp&& F, sum_Tp&& sum) {
		this -> F = F;
		this -> sum = sum;
		init(n);
	}	
	T operator()(i64 n) { return g(n); }
private:
	F_Tp F;
	sum_Tp sum;
	
	i64 n, sq, m;
	vector<T> pre;
	vector<T> g1, g2;
	
	T& g(i64 k) { return k <= sq ? g1[k] : g2[n / k]; }
	
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
			pre[i + 1] = pre[i] + F(P[i]);
		}

		vector<i64> x;
		for (i64 k = 1; k <= n; ++k) {
			g(n / k) = sum(n / k) - F(1);
			x.push_back(n / k);
			k = n / (n / k);
		}
		
		for (i64 j = 0; j < m; ++j) {
			i64 p = P[j];
			for (i64 x : x) {
				if (p * p > x) break;
				g(x) -= F(p) * (g(x / p) - pre[j]);
			}
		}
	}
};

template<typename F_Tp, typename sum_Tp>
Min_25(int, F_Tp, sum_Tp) -> Min_25<std::invoke_result_t<F_Tp, i64>, F_Tp, sum_Tp>;

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

void Thephix() {
	i64 n;
	cin >> n;
	Min_25 f (
		n,
		[](i64 x) { return Z (x); },
		[](i64 x) { return Z (x) * (x + 1) / 2; }
	);

	Min_25 g (
		n,
		[](i64 x) { return Z (x) * x; },
		[](i64 x) { return Z (x) * (x + 1) * (2 * x + 1) / 6; }
	);

	auto& P = f.P;
	int m = P.size();

	vector<Z> pre(m + 1);
	for (int i = 1; i <= m; ++i) {
		pre[i] = pre[i - 1] + P[i - 1] * (P[i - 1] - 1);
	}

	auto dfs = [&](auto&& dfs, i64 n, int x) -> Z {
		Z res = (g(n) - f(n)) - pre[x];
		for (int i = x; i < m && P[i] * P[i] <= n; ++i) {
			i64 j;
			for (j = P[i]; j * P[i] <= n; j *= P[i]) {
				res += (Z(j) * j - j) * ((j != P[i]) + dfs(dfs, n / j, i + 1));
			}
			res += (Z(j) * j - j);
		}
		return res;
	};

	cout << dfs(dfs, n, 0) + 1 << "\n";
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
