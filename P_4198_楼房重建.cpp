#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

struct Frac {
	i64 u, d;
	Frac(i64 x = 0, i64 y = 1) {
		u = x, d = y;
	}
	bool operator<(const Frac& o) const {
		return u * o.d < o.u * d;
	}
};

#define ls (u << 1)
#define rs (u << 1 | 1)
template<typename Info>
struct SegmentTree {
	int n;
	std::vector<Info> info;

	SegmentTree() = default;

	SegmentTree(int n) { init(n); }

	template<typename Func>
	SegmentTree(int n, Func&& f) { init(n, f); }

	void init(int n) {
		init(n, [](int p) { return Info {}; });
	}

	template<typename Func>
	void init(int n, Func&& f) {
		this -> n = n;
		info.assign(4 << __lg(n), Info {});
		build(1, 1, n, f);
	}

	int query(int u, int l, int r, Frac Max) {
		if (l == r) return Max < info[u].Max;
		int m = (l + r) >> 1;
		if (Max < info[ls].Max) {
			return query(ls, l, m, Max) + info[u].len - info[ls].len;
		} return query(rs, m + 1, r, Max);
	}

	void pull(int u, int l, int r) {
		if (l == r) return;
		info[u].Max = max(info[ls].Max, info[rs].Max);
		info[u].len = info[ls].len + query(rs, ((l + r) >> 1) + 1, r, info[ls].Max);
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
		pull(u, l, r);
	}

	template<typename Func>
	void modify(int p, Func&& op, int u, int l, int r) {
		if (l == r) {
			op(info[u]);
			return;
		}
		int m = (l + r) >> 1;
		if (p <= m) {
			modify(p, op, ls, l, m);
		} else {
			modify(p, op, rs, m + 1, r);
		}
		pull(u, l, r);
	}

	template<typename Func>
	void modify(int p, Func&& op) {
		modify(p, op, 1, 1, n);
	}
};
#undef ls
#undef rs

struct Info {
	Frac Max;
	int len;
	Info () {
		Max = {0, 1}, len = 0;
	}
};

void Thephix() {
	int n, m;
	cin >> n >> m;

	SegmentTree<Info> seg(n);
	while (m--) {
		int p, x;
		cin >> p >> x;
		seg.modify(p, [&](Info& info) {
			info.Max = Frac(x, p);
			info.len = 1;
		});
		cout << seg.query(1, 1, n, 0) << "\n";
	}
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
