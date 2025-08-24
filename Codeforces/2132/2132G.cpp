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

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

constexpr int N = 2000000;
array<array<Z, 2>, N + 1> R;
array<array<Z, 2>, N + 1> C;

void Thephix() {
	int n, m;
	cin >> n >> m;
	int N = n << 1 | 1, M = m << 1 | 1;
	
	vector a(N + 1, vector<char> (M + 1, '$'));
	for (int i = 1; i <= n; ++i) {
		string s; cin >> s;
		for (int j = 1; j <= m; ++j) {
			a[2 * i][2 * j] = s[j - 1];
		}
	}

	vector Hash(N + 1, vector<array<Z, 2>> (M + 1));
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			Hash[i][j][0] = Hash[i - 1][j][0] * R[1][0] + Hash[i][j - 1][0] * C[1][0] - Hash[i - 1][j - 1][0] * R[1][0] * C[1][0] + a[i][j];
			Hash[i][j][1] = Hash[i - 1][j][1] * R[1][1] + Hash[i][j - 1][1] * C[1][1] - Hash[i - 1][j - 1][1] * R[1][1] * C[1][1] + a[i][j];
		}
	}

	i64 ans = N * M;
	for (int i = 2; i < N; ++i) {
		for (int j = 2; j < M; ++j) {
			i64 H = min<i64>(i, N - i + 1);
			i64 W = min<i64>(j, M - j + 1);
			Z x = Hash[i][j + W - 1][0]
					- Hash[i - H][j + W - 1][0] * R[H][0]
					- Hash[i][j - W][0] * C[2 * W - 1][0]
					+ Hash[i - H][j - W][0] * C[2 * W - 1][0] * R[H][0];
			Z y = Hash[i + H - 1][j + W - 1][1]
					- Hash[i - 1][j + W - 1][1] * R[H][1]
					- Hash[i + H - 1][j - W][1] * C[2 * W - 1][1]
					+ Hash[i - 1][j - W][1] * C[2 * W - 1][1] * R[H][1];
			if (x == y * R[H - 1][0] * C[2 * W - 2][0]) {
				H = max(i, N - i + 1) / 2 * 2;
				W = max(j, M - j + 1) / 2 * 2;
				if (i % 2 == 0) H--;
				if (j % 2 == 0) W--;
				ans = min(ans, H * W);
			}
		}
	}
	cout << ans - n * m << "\n";
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	cin >> T;

	R[0] = C[0] = {1, 1};
	R[1][0] = rng(), R[1][1] = R[1][0].inv();
	C[1][0] = rng(), C[1][1] = C[1][0].inv();
	for (int i = 1; i < N; ++i) {
		R[i + 1][0] = R[i][0] * R[1][0];
		R[i + 1][1] = R[i][1] * R[1][1];
		C[i + 1][0] = C[i][0] * C[1][0];
		C[i + 1][1] = C[i][1] * C[1][1];
	}

	while (T--) {
		Thephix();
	}

	return 0;
}