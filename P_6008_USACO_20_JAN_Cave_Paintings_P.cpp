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

using Z = ModInt<u32, 1'000'000'007>;

void Thephix() {
	int n, m;
	cin >> n >> m;
	vector<string> a(n + 1);
	for (int i = n; i >= 1; --i) {
		cin >> a[i];
		a[i] = '$' + a[i];
	}

	auto encode = [&](int x, int y) { return (x - 1) * m + y; };

	DSU dsu(n * m);

	vector<Z> dp(n * m + 1);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			dp[encode(i, j)] = a[i][j] == '.';
		}
	}

	for (int i = 1, cnt = 0; i <= n; ++i) {
		cnt += m;
		for (int j = 1; j <= m; ++j) {
			if (a[i][j] == '#') continue;
			if (i >= 2 && a[i - 1][j] == '.'){
				int x = dsu.find(encode(i, j));
				int y = dsu.find(encode(i - 1, j));
				dsu.merge(x, y), dp[x] *= dp[y];
			}
			if (j >= 2 && a[i][j - 1] == '.'){
				int x = dsu.find(encode(i, j));
				int y = dsu.find(encode(i, j - 1));
				dsu.merge(x, y), dp[x] *= dp[y];
			}
		}
		for (int j = 1; j <= m; ++j) {
			if (dsu.find(encode(i, j)) == encode(i, j)) {
				dp[encode(i, j)] += 1;
			}
		}
	}

	Z ans = 1;
	for (int i = 1; i <= n * m; ++i) {
		if (dsu.find(i) == i) {
			int x = i / m + 1, y = i % m;
			if (y == 0) x--, y = m;
			if (a[x][y] == '#') {
				assert(dp[i] == 1);
				continue;
			}
			ans *= dp[i];
			cout << i / m + 1 << ' ' << i % m << ' ' << dp[i] << "\n";
		}
	}
	cout << endl;
	cout << ans << "\n";
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
