#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

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

struct Tag {
	int add;
	Tag (int x = 0) {
		add = x;
	}
	void apply(const Tag& v) {
		add += v.add;
	}
};

struct Info {
	int Max;
	Info (int x = 0) {
		Max = x;
	}
	void apply(const Tag& v) {
		Max += v.add;
	}
};

Info operator+(const Info& x, const Info& y) {
	return Info { max(x.Max, y.Max) };
}

void Thephix() {
	int n, k;
	cin >> n >> k;
	vector<array<int, 2>> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		auto& [l, r] = a[i];
		cin >> l >> r;
	}

	LazySegmentTree<Info, Tag> seg(n);

	auto check = [&](int p) -> bool {
		auto& [l, r] = a[p];
		seg.modify(l, r, 1);
		int Max = seg.query(1, n).Max;
		seg.modify(l, r, -1);
		return Max <= k;
	};

	auto add = [&](int p) -> void {
		auto& [l, r] = a[p];
		seg.modify(l, r, 1);
	};

	auto del = [&](int p) -> void {
		auto& [l, r] = a[p];
		seg.modify(l, r, -1);
	};

	int ans = 0;
	for (int l = 1, r = 0; l <= n; ++l) {
		while (r + 1 <= n && check(r + 1)) add(++r);
		ans = max(r - l + 1, ans);
		del(l);
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
