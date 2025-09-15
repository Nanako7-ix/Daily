#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int k = 4;
const string t("ICPC");

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
	int n, q;
	string s;
	cin >> n >> q >> s;

	i64 x, a, b, p;
	cin >> x >> a >> b >> p;
	vector<array<int, 2>> f(q + 1);
	for (int i = 1; i <= q; ++i) {
		x = (a * x + b) % p;
		f[i][0] = x % n + 1;
	}
	for (int i = 1; i <= q; ++i) {
		x = (a * x + b) % p;
		f[i][1] = x % n + 1;
		if (f[i][0] > f[i][1]) {
			swap(f[i][0], f[i][1]);
		}
	}

	vector<vector<Z>> dp(n + 1, vector<Z> (1 << k));
	dp[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		char ch = s[i - 1];
		dp[i] = dp[i - 1];
		for (int s = 1; s < (1 << k); ++s) {
			int p = __lg(s);
			if (ch == t[p]) {
				dp[i][s] += dp[i - 1][s ^ (1 << __lg(s))];
			}
		}
	}

	Z ans = 0;
	for (int i = 1; i <= q; ++i) {
		auto [l, r] = f[i];
		Z   PC = dp[r][12] - dp[l - 1][12] - dp[l - 1][4] * (dp[r][8] - dp[l - 1][8]);
		Z  CPC = dp[r][14] - dp[l - 1][14] - dp[l - 1][2] *  PC - dp[l - 1][6] * (dp[r][8] - dp[l - 1][8]);
		Z ICPC = dp[r][15] - dp[l - 1][15] - dp[l - 1][1] * CPC - dp[l - 1][3] * PC - dp[l - 1][7] * (dp[r][8] - dp[l - 1][8]);
		ans += ICPC;
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
