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

using Z = ModInt<u32, 1000003>;

void Thephix() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> x(n + 1, vector<int> (m + 1));
	vector<vector<int>> y(n + 1, vector<int> (m + 1));
	for (int i = 1; i <= n; ++i) {
		string s;
		cin >> s;
		for (int j = 1; j <= m; ++j) {
			if (s[j - 1] == '.') {
				x[i][j] = y[i][j] = -1;
				continue;
			}

			x[i][j] = !(s[j - 1] == '1' || s[j - 1] == '2');
			y[i][j] = !(s[j - 1] == '1' || s[j - 1] == '4');
		}
	}

	Z ans = 1;
	for (int i = 1; i <= n; ++i) {
		array<int, 3> cnt{};
		for (int j = 1; j <= m; ++j) {
			if (x[i][j] != -1) {
				cnt[(j & 1) ^ x[i][j]]++;
			} else cnt[2]++;
		}
		if (cnt[0] && cnt[1]) {
			cout << "0\n";
			return;
		} else if (cnt[2] == m) {
			ans *= 2;
		}
	}

	for (int j = 1; j <= m; ++j) {
		array<int, 3> cnt{};
		for (int i = 1; i <= n; ++i) {
			if (y[i][j] != -1) {
				cnt[(i & 1) ^ y[i][j]]++;
			} else cnt[2]++;
		}
		if (cnt[0] && cnt[1]) {
			cout << "0\n";
			return;
		} else if (cnt[2] == n) {
			ans *= 2;
		}
	}

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
