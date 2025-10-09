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

template<typename T, typename Func>
struct SparseTable {
	int n;
	Func op;
	std::vector<std::vector<T>> st;

	SparseTable () = default;

	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	SparseTable (const Iter& l, const Iter& r, Func&& f) : n(r - l), op(f) {
		st.assign(std::__lg(n) + 1, std::vector<T> (n + 1));
		for (int i = 1; i <= n; ++i) {
			st[0][i] = l[i - 1];
		}
		for (int i = 1; i <= std::__lg(n); ++i) {
			for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
				st[i][j] = op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
			}
		}
	}

	T operator () (int l, int r) {
		assert(l <= r);
		int k = std::__lg(r - l + 1);
		return op(st[k][l], st[k][r - (1 << k) + 1]);
	}
};

template<typename Iter, typename Func>
SparseTable (const Iter&, const Iter&, Func&&) ->
SparseTable<typename std::iterator_traits<Iter>::value_type, Func>;

using Z = ModInt<u32, 998244353>;

mt19937_64 rng((random_device())());
const array<Z, 4> h { rng(), rng(), rng(), rng() };

constexpr array<Z, 2> Base { 131, 13331 };

constexpr int N = 500000;
array<array<Z, 2>, N> f = []() {
	f[0] = { 1, 1 };
	for (int i = 1; i < N; ++i) {
		f[i][0] = f[i - 1][0] * Base[0];
		f[i][1] = f[i - 1][1] * Base[1];
	}
	return f;
} ();

Z Hash(char ch) {
	if (ch == '(' || ch == ')') return h[0];
	if (ch == '[' || ch == ']') return h[1];
	if (ch == '{' || ch == '}') return h[2];
	if (ch == '<' || ch == '>') return h[3];
	__builtin_unreachable();
}

void Thephix() {
	int n, m;
	string s;
	cin >> n >> m >> s;

	vector<array<int, 2>> a(m + 1);
	vector<vector<int>> query(n + 1);
	for (int i = 1; i <= m; ++i) {
		auto& [l, r] = a[i];
		cin >> l >> r;
	}

	auto solve = [&]() -> map<array<i64, 2>, int> {
		map<array<i64, 2>, int> cnt;

		vector<int> pre(n + 1);
		for (int i = 1; i <= n; ++i) {
			if (s[i] == '(' || s[i] == '[' || s[i] == '<' || s[i] == '{') {
				pre[i] = pre[i - 1] + 1;
			} else pre[i] = pre[i - 1] - 1;
		}
		SparseTable Min(pre.begin() + 1, pre.end(), [](int x, int y) {
			return std::min(x, y);
		});
	
		auto check = [&](int l, int r) -> bool {
			assert(l <= r);
			return Min(l, r) >= pre[l - 1];
		};
		
		int err = 0;
		vector<int> stk;
		vector<array<Z, 2>> hash;
		for (int r = 1; r <= n; ++r) {
			char ch = s[r];
			if (ch == '(' || ch == '[' || ch == '{' || ch == '<') {
				stk.push_back(r);
				Z x = 0, y = 0;
				if (!hash.empty()) {
					tie(x, y) = hash.back();
				}
				hash.push_back({
					x * Base[0] + Hash(ch),
					y * Base[1] + Hash(ch)
				});
			} else if (stk.empty() || Hash(ch) != Hash(s[stk.back()])) {
				stk.clear(), hash.clear(), err = r;
			} else {
				stk.pop_back(), hash.pop_back();
			}
	
			int k = stk.size() - 1;
			for (auto l : query[r]) {
				if (l <= err || !check(l, r)) continue;
				auto it = lower_bound(stk.begin(), stk.end(), l);
				if (it != stk.end()) {
					int p = it - stk.begin();
					auto [x, y] = hash.back();
					if (p != 0) {
						x -= hash[p - 1][0] * f[k - p + 1][0];
						y -= hash[p - 1][1] * f[k - p + 1][1];
					}
					cnt[{ x.val(), y.val() }]++;
				} else cnt[{ 0, 0 }]++;
			}
		}
		return cnt;
	};

	s = '$' + s;
	for (int i = 1; i <= m; ++i) {
		auto [l, r] = a[i];
		query[r].push_back(l);
	}
	map<array<i64, 2>, int> cntL = solve();

	for (int i = 1; i <= n; ++i) query[i].clear();
	for (int i = 1; i <= m; ++i) {
		auto [l, r] = a[i];
		query[n - l + 1].push_back(n - r + 1);
	}
	reverse(s.begin() + 1, s.end());
	for (int i = 1; i <= n; ++i) {
		if (s[i] == '(' || s[i] == ')') s[i] ^= '(' ^ ')';
		if (s[i] == '[' || s[i] == ']') s[i] ^= '[' ^ ']';
		if (s[i] == '{' || s[i] == '}') s[i] ^= '{' ^ '}';
		if (s[i] == '<' || s[i] == '>') s[i] ^= '<' ^ '>';
	}
	map<array<i64, 2>, int> cntR = solve();

	int ans = 0;
	for (auto [x, y] : cntL) {
		if (x[0] != 0 || x[1] != 0) {
			ans += min(cntR[x], y);
		}
	}

	cout << ans + cntL[{ 0, 0 }] / 2 << "\n";
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
