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

	mat& operator+=(const mat& o) { return *this = *this + o; }
	mat& operator-=(const mat& o) { return *this = *this - o; }
	mat& operator*=(const mat& o) { return *this = *this * o; }

	pair<T, mat> get() {

	}

	T det() const { return get().first; }
	T inv() const { auto [det, m] = get(); assert(det); return m; }

	mat pow(i64 b) {
		mat a = *this, res = I();
		for (; b; b >>= 1, a *= a) {
			if (b & 1) res *= a;
		}
		return res;
	}

	array<T, n>& operator[](int p) {
		assert(p < n);
		return d[p];
	}

	static mat I() {
		mat I;
		for (int i = 0; i < n; ++i) {
			I[i][i] = 1;
		}
		return I;
	}
};

void Thephix() {
	int n, m;
	cin >> n >> m;
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
