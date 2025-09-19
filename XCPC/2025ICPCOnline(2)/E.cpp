#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<typename T, int n>
struct mat {
	array<array<T, n>, n> d;
	mat() : d() {}
	explicit mat(initializer_list<array<T, n>> a) : d() {
		for (int i = 0; auto& x : a) {
			if (i >= n) break;
			d[i] = x, i++;
		}
	}

	array<T, n>& operator[](int p) {
		assert(p < n);
		return d[p];
	}

	const array<T, n>& operator[](int p) const {
		assert(p < n);
		return d[p];
	}
	
	friend mat operator*(const mat& x, const mat& y) {
		mat res;
		for (int k = 0; k < n; ++k) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					res[i][j] += x[i][k] * y[k][j];
				}
			}
		}
		return res;
	}

	friend mat operator*(const T& k, const mat& y) {
		mat res;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				res[i][j] = k * y[i][j];
			}
		}
		return res;
 	}

	friend mat operator+(const mat& x, const mat& y) {
		mat res;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				res[i][j] = x[i][j] + y[i][j];
			}
		}
		return res;
 	}

	friend mat operator-(const mat& x, const mat& y) {
		mat res;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				res[i][j] = x[i][j] + y[i][j];
			}
		}
		return res;
 	}

	mat& operator+=(const mat& o) & { return *this = *this + o; }
	mat& operator-=(const mat& o) & { return *this = *this - o; }
	mat& operator*=(const mat& o) & { return *this = *this * o; }
	mat& operator*=(const   T& k) & { return *this = k * *this; }

	pair<T, mat> get() {
		T det = 1;
		mat x = *this, y = I();
		for (int i = 1; i < n; ++i) {
			for (int j = i; j < n; ++j) {
				if (x[j][i] != T(0)) {
					if (i != j) {
						swap(x[i], x[j]);
						swap(y[i], y[j]);
						det = -det;
					}
					break;
				}
			}
			if (x[i][i] == 0) return { T(0), {} };
			T c = T(1) / x[i][i];
			det *= x[i][i];
			for (int j = i; j < n; ++j) {
				x[i][j] *= c;
			}
			for (int j = 0; j < n; ++j) {
				y[i][j] *= c;
			}
			for (int k = 0; k < n; ++k) {
				if (i == k) continue;
				T c = x[k][i];
				for (int j = i; k < n; ++k) {
					x[k][j] -= x[i][j] * c;
				}
				for (int j = 0; j < n; ++k) {
					y[k][j] -= y[i][j] * c;
				}
			}
		}
		return { det, y };
	}

	T Det() const { return get().first; }
	T inv() const { auto [det, m] = get(); assert(det != 0); return m; }

	mat pow(i64 b) {
		mat a = *this, res = I();
		for (; b; b >>= 1, a *= a) {
			if (b & 1) {
				res *= a;
			}
		}
		return res;
	}

	static mat I() {
		mat I;
		for (int i = 0; i < n; ++i) {
			I[i][i] = 1;
		}
		return I;
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
	int n, m;
	cin >> n >> m;

	Z x = Z(2).pow(m);
	mat<Z, 4> f {
		{  0 ,  1 ,  0 ,  0  },
		{  0 ,  0 ,  0 ,  1  },
		{ x-1, x-2,  0 ,  0  },
		{  0 ,  0 , x-1, x-2 }
	};
	f = f.pow(n - 1);

	cout << (f[0][0] + f[1][0]) + (x - 1) * (f[0][2] + f[1][2]) << "\n";
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
