#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

template<u32 Mod> constexpr u32 mulMod(u32 a, u32 b) { return static_cast<u64> (a) * b % Mod; }
template<u64 Mod> constexpr u64 mulMod(u64 a, u64 b) { return static_cast<u128>(a) * b % Mod; }

template<std::integral T>
constexpr T exgcd(T a, T b, T& x, T& y) {
	if(b == 0) { x = 1, y = 0; return a; }
	T d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

template<std::unsigned_integral U, U Mod, typename S = std::make_signed_t<U>>
struct ModInt {
public:
	constexpr ModInt() : x(0) {}
	template<std::unsigned_integral T> constexpr ModInt(T v) : x(v % Mod) {}
	template<std::signed_integral T> constexpr ModInt(T v) { S t = v % S(Mod); x = t < 0 ? t + Mod : t; }
	
	constexpr U val() const { return x; }
	constexpr static int mod() { return Mod; }
	constexpr ModInt operator-() const { return x == 0 ? 0 : Mod - x; }

	constexpr ModInt& operator+=(const ModInt& rhs) & { x += rhs.val(); if(x >= Mod) x -= Mod; return *this; }
	constexpr ModInt& operator-=(const ModInt& rhs) & { x -= rhs.val(); if(x >= Mod) x += Mod; return *this; }
	constexpr ModInt& operator*=(const ModInt& rhs) & { x = mulMod<Mod>(x, rhs.val()); return *this; }
	constexpr ModInt& operator/=(const ModInt& rhs) & { return *this *= rhs.inv(); }

	friend constexpr ModInt operator+(ModInt lhs, const ModInt& rhs) { return lhs += rhs; }
	friend constexpr ModInt operator-(ModInt lhs, const ModInt& rhs) { return lhs -= rhs; }
	friend constexpr ModInt operator*(ModInt lhs, const ModInt& rhs) { return lhs *= rhs; }
	friend constexpr ModInt operator/(ModInt lhs, const ModInt& rhs) { return lhs /= rhs; }

	constexpr ModInt& operator++() { *this += 1; return *this; }
	constexpr ModInt& operator--() { *this -= 1; return *this; }
	constexpr ModInt operator++(int) { auto tmp = *this; *this += 1; return tmp; }
	constexpr ModInt operator--(int) { auto tmp = *this; *this -= 1; return tmp; }

	friend constexpr std::strong_ordering operator<=>(const ModInt &lhs, const ModInt &rhs) = default;
	friend std::istream& operator>>(std::istream& is, ModInt& a) { i64 x; is >> x; a = ModInt(x); return is; }
	friend std::ostream& operator<<(std::ostream& os, const ModInt& a) { os << a.val(); return os; }

	constexpr ModInt pow(i64 b) const { ModInt ret = 1, a = *this; for (; b; b >>= 1, a *= a) if (b & 1) ret *= a; return ret; }
	constexpr ModInt inv() const { return pow(Mod - 2); }
private:
	U x;
};

using Z = ModInt<u32, 998244353>;
constexpr int N = 1000;

void Thephix() {
	int n;
	cin >> n;
	
	int cnt = 0;
	auto query = [&](i64 u, i64 d) -> Z {
		assert(++cnt <= n - 2);
		tie(u, d) = pair(u / gcd(u, d), d / gcd(u, d));
		cout << "? " << u << ' ' << d << endl;
		
		string s, t;
		cin >> s >> t;
		Z U = 0, D = 0;
		for (auto ch : s) U = U * 10 + ch - '0';
		for (auto ch : t) D = D * 10 + ch - '0';
		return U == 0 ? 0 : Z(U) / D;
	};

	vector<int> x(1), y(N + 1);
	for (int i = 1; i <= n; ++i) {
		int _x, _y;
		cin >> _x >> _y;
		x.push_back(_x);
		y[_x]++;
	}
	sort(x.begin() + 1, x.end());
	x.erase(unique(x.begin() + 1, x.end()), x.end());

	int m = x.size() - 1;
	vector<Z> l(m + 1), r(m + 1);
	vector<int> vis_l(m + 1), vis_r(m + 1);

	r[1] = y[x[1]] == 1 ? 0 : query(x[1], 1);
	vis_r[1] = 1;

	l[m] = y[x[m]] == 1 ? 0 : query(x[m], 1);
	vis_l[m] = 1;

	for (int i = 2; i <= m; ++i) {
		// 需要确保 vis_r[i - 1] 和 vis_l[i];
		if (!vis_l[i]) {
			if (y[x[i]] == 1) {
				l[i] = r[i] = query(x[i], 1);
				vis_l[i] = vis_r[i] = 1;
			} else if (vis_r[i - 1]) {
				int len = x[i] - x[i - 1];
				Z mid = query(x[i - 1] * 2 + len, 2);
				l[i] = mid * 2 - r[i - 1];
				vis_l[i] = 1;
			} else {
				int len = x[i] - x[i - 1];
				Z mid1 = query(x[i - 1] * 3 + len, 3);
				Z mid2 = query(x[i - 1] * 3 + len * 2, 3);
				r[i - 1] = 2 * mid1 - mid2;
				l[i] = 2 * mid2 - mid1;
				vis_l[i] = vis_r[i - 1] = 1;
			}
		}

		if (!vis_r[i - 1]) {
			int len = x[i] - x[i - 1];
			Z mid = query(x[i - 1] * 2 + len, 2);
			r[i - 1] = mid * 2 - l[i];
			vis_r[i - 1] = 1;
		}
	}

	Z ans = 0;
	for (int i = 2; i <= m; ++i) {
		ans += (x[i] - x[i - 1]) * (r[i - 1] + l[i]);
	}

	int S = ans.val();
	if (S % 2 == 0) {
		cout << "! " << S / 2 << ' ' << 1 << endl;
	} else {
		cout << "! " << S << ' ' << 2 << endl;
	}
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int T = 1;
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
