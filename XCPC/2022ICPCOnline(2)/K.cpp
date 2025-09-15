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

constexpr int N = 201;
constexpr int g[16] = {
	0, 4, 3, 8, 2, 7, 9, 9, 1, 9, 5, 9, 6, 9, 9, 9
};

void Thephix() {
	int n;
	cin >> n;
	vector<vector<int>> f(N + 1, vector<int> (N + 1));
	for (int i = 1; i <= n; ++i) {
		int op, x, y;
		cin >> op >> x >> y;
		x += 100, y += 100;
		if (op == 1) {
			f[x][y] = f[x][y + 1] = f[x + 1][y] = f[x + 1][y + 1] = 15;
		} else {
			f[x][y] |= 1 << 0;
			f[x + 1][y] |= 1 << 1;
			f[x][y + 1] |= 1 << 2;
			f[x + 1][y + 1] |= 1 << 3;
		}
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			f[i][j] = g[f[i][j]];
		}
	}

	Z a = 0, b = 0;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (f[i][j] == 0) continue;
			if (f[i][j] <= 4) {
				b += Z(2).inv();
			} else if (f[i][j] <= 8) {
				b += Z(3).inv();
			} else {
				assert(f[i][j] == 9);
				int x, y;

				x = i - 1, y = j;
				a += x < 1 || x > N || y < 1 || y > N || f[x][y] == 1 || f[x][y] == 3 || f[x][y] == 5 || f[x][y] == 0;
				
				x = i, y = j - 1;
				a += x < 1 || x > N || y < 1 || y > N || f[x][y] == 1 || f[x][y] == 2 || f[x][y] == 6 || f[x][y] == 0;
				
				x = i + 1, y = j;
				a += x < 1 || x > N || y < 1 || y > N || f[x][y] == 2 || f[x][y] == 4 || f[x][y] == 7 || f[x][y] == 0;
				
				x = i, y = j + 1;
				a += x < 1 || x > N || y < 1 || y > N || f[x][y] == 3 || f[x][y] == 4 || f[x][y] == 8 || f[x][y] == 0;
			}
		}
	}
	cout << a << ' ' << b << '\n';
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
