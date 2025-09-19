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

#define ls (u << 1)
#define rs (u << 1 | 1)
template<typename Info, typename Tag>
struct LazySegmentTree {
	int n;
	std::vector<Info> info;
	std::vector<Tag>  tag;

	LazySegmentTree() = default;

	LazySegmentTree(int n) { init(n); }

	template<typename Func>
	LazySegmentTree(int n, Func&& f) { init(n, f); }

	void init(int n) {
		init(n, [](int p) { return Info {}; });
	}

	template<typename Func>
	void init(int n, Func&& f) {
		this -> n = n;
		info.assign(4 << __lg(n), Info {});
		tag.assign(4 << __lg(n), Tag {});
		build(1, 1, n, f);
	}

	void pull(int u) {
		info[u] = info[ls] + info[rs];
	}

	void apply(int u, const Tag& v) {
		info[u].apply(v);
		tag[u].apply(v);
	}

	void push(int u) {
		apply(ls, tag[u]);
		apply(rs, tag[u]);
		tag[u] = Tag {};
	}

	template<typename Func>
	void build(int u, int l, int r, Func&& f) {
		if (l == r) {
			info[u] = f(l);
			return;
		}
		int m = (l + r) >> 1;
		build(ls, l, m, f);
		build(rs, m + 1, r, f);
		pull(u);
	}

	template<typename Func>
	void modify(int p, Func&& op, int u, int l, int r) {
		if (l == r) {
			op(info[u]);
			return;
		}
		push(u);
		int m = (l + r) >> 1;
		if (p <= m) {
			modify(p, op, ls, l, m);
		} else {
			modify(p, op, rs, m + 1, r);
		}
		pull(u);
	}

	template<typename Func>
	void modify(int p, Func&& op) {
		modify(p, op, 1, 1, n);
	}

	void modify(int L, int R, const Tag& v, int u, int l, int r) {
		if (L <= l && r <= R) {
			apply(u, v);
			return;
		}
		push(u);
		int m = (l + r) >> 1;
		if (L <= m) modify(L, R, v, ls, l, m);
		if (R > m)  modify(L, R, v, rs, m + 1, r);
		pull(u);
	}

	void modify(int l, int r, const Tag& v) {
		assert(l <= r);
		modify(l, r, v, 1, 1, n);
	}

	Info query(int L, int R, int u, int l, int r) {
		if (L <= l && r <= R) {
			return info[u];
		}
		push(u);
		int m = (l + r) >> 1;
		if (R <= m) {
			return query(L, R, ls, l, m);
		} else if (L > m) {
			return query(L, R, rs, m + 1, r);
		} else {
			return query(L, R, ls, l, m) + query(L, R, rs, m + 1, r);
		}
	}

	Info query(int l, int r) {
		assert(l <= r);
		return query(l, r, 1, 1, n);
	}

	template<typename Func>
	int findL(int L, int R, Func&& f, int u, int l, int r) {
		if(l > R || r < L || !f(info[u])) {
			return n + 1;
		}
		if(l == r) return l;
		push(u);
		int m = (l + r) >> 1;
		int p = findL(L, R, f, ls, l, m);
		if(p > n) {
			p = findL(L, R, f, rs, m + 1, r);
		}
		return p;
	}

	template<typename Func>
	int findL(int l, int r, Func&& f) {
		assert(l <= r);
		return findL(l, r, f, 1, 1, n);
	}

	template<typename Func>
	int findR(int L, int R, Func&& f, int u, int l, int r) {
		if(l > R || r < L || !f(info[u])) {
			return -0;
		}
		if(l == r) return l;
		push(u);
		int m = (l + r) >> 1;
		int p = findR(L, R, f, rs, m + 1, r);
		if(p < 1) {
			p = findR(L, R, f, ls, l, m);
		}
		return p;
	}

	template<typename Func>
	int findR(int l, int r, Func&& f) {
		assert(l <= r);
		return findR(l, r, f, 1, 1, n);
	}
};
#undef ls
#undef rs

using Z = ModInt<u32, 998244353>;

struct Tag {
	Z mul;
	Tag (Z x = 1) : mul(x) {}
	void apply(const Tag& v) {
		mul *= v.mul;
	}
};

struct Info {
	Z sum;
	Info (Z x = 0) : sum(x) {}
	void apply(const Tag& v) {
		sum *= v.mul;
	}
};

Info operator+(const Info& x, const Info& y) {
	return Info { x.sum + y.sum };
}

void Thephix() {
	int n;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	vector<int> L { 0 }, R { 0 };
	for (int i = 1; i <= n; ++i) {
		if (a[i] > L.back()) {
			L.push_back(a[i]);
		}
	}
	for (int i = n; i >= 1; --i) {
		if (a[i] > R.back()) {
			R.push_back(a[i]);
		}
	}

	vector<Z> dpL = [&]() -> vector<Z> {
		int len = L.size() - 1;
		vector<Z> dp(n + 1);
		LazySegmentTree<Info, Tag> seg(len);
		for (int i = 1; i <= n; ++i) {
			int p = lower_bound(L.begin(), L.end(), a[i]) - L.begin();
			assert(p <= len);
			if (p < len) seg.modify(p, len - 1, Z(2));
			if (L[p] == a[i]) {
				Z cnt = p == 1 ? 1 : seg.query(p - 1, p - 1).sum;
				seg.modify(p, [&](Info& info) { info.sum += cnt; });
			}
			dp[i] = seg.query(len, len).sum;
		}
		for (int i = n; i > 1; --i) {
			dp[i] -= dp[i - 1];
		}
		return dp;
	} ();

	vector<Z> dpR = [&]() -> vector<Z> {
		int len = R.size() - 1;
		vector<Z> dp(n + 1);
		LazySegmentTree<Info, Tag> seg(len);
		for (int i = n; i >= 1; --i) {
			int p = lower_bound(R.begin(), R.end(), a[i]) - R.begin();
			assert(p <= len);
			if (p < len) seg.modify(p, len - 1, Z(2));
			if (R[p] == a[i]) {
				Z cnt = p == 1 ? 1 : seg.query(p - 1, p - 1).sum;
				seg.modify(p, [&](Info& info) { info.sum += cnt; });
			}
			dp[i] = seg.query(len, len).sum;
		}
		for (int i = 1; i < n; ++i) {
			dp[i] -= dp[i + 1];
		}
		return dp;
	} ();

	Z ans = 0, sum = 0;
	for (int i = 1; i <= n; ++i) {
		ans += (dpL[i] + sum) * dpR[i];
		sum *= 2, sum += dpL[i];
	}
	cout << ans << "\n";
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
