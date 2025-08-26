#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<typename Info>
struct PersistentSegmentTree {
	int n;
	std::vector<Info> info;
	std::vector<int> ls, rs;

	PersistentSegmentTree() = default;

	PersistentSegmentTree(int n, int m) {
		init(n, m);
	}

	void init(int n, int m) {
		this -> n = n;
		info.assign(1, Info {});
		ls.assign(1, 0);
		rs.assign(1, 0);
	}

	void pull(int u) {
		info[u] = info[ls[u]] + info[rs[u]];
	}

	int Node(int u) {
		info.push_back(info[u]);
		ls.push_back(ls[u]);
		rs.push_back(rs[u]);
		return info.size() - 1;
	}

	template<typename Func>
	int build(int l, int r, Func&& f) {
		int u = Node(0);
		if (l == r) {
			info[u] = f(l);
		} else {
			int m = (l + r) >> 1;
			ls[u] = build(l, m, f);
			rs[u] = build(m + 1, r, f);
			pull(u);
		}
		return u;
	}

	template<typename Func>
	int build(Func&& f) {
		return build(1, n, f);
	}

	template<typename Func>
	int modify(int p, Func&& op, int u, int l, int r) {
		u = Node(u);
		if (l == r) {
			op(info[u]);
		} else {
			int m = (l + r) >> 1;
			if (p <= m) {
				ls[u] = modify(p, op, ls[u], l, m);
			} else {
				rs[u] = modify(p, op, rs[u], m + 1, r);
			}
			pull(u);
		}
		return u;
	}

	template<typename Func>
	void modify(int& u, int v, int p, Func&& op) {
		u = modify(p, op, v, 1, n);
	}

	Info query(int L, int R, int u, int l, int r) {
		if (L <= l && r <= R) {
			return info[u];
		}
		int m = (l + r) >> 1;
		if (R <= m) {
			return query(L, R, ls[u], l, m);
		} else if (L > m) {
			return query(L, R, rs[u], m + 1, r);
		} else {
			return query(L, R, ls[u], l, m) + query(L, R, rs[u], m + 1, r);
		}
	}
	
	Info query(int u, int l, int r) {
		assert(l <= r);
		return query(l, r, u, 1, n);
	}

	template<typename Func>
	int findL(int L, int R, Func&& f, int u, int l, int r) {
		if (l > R || r < L || !f(info[u])) {
			return n + 1;
		}
		if (l == r) return l;
		int m = (l + r) >> 1;
		int p = findL(L, R, f, ls[u], l, m);
		if (p > n) {
			p = findL(L, R, f, rs[u], m + 1, r);
		}
		return p;
	}

	template<typename Func>
	int findL(int u, int l, int r, Func&& f) {
		assert(l <= r);
		return findL(l, r, f, u, 1, n);
	}

	template<typename Func>
	int findR(int L, int R, Func&& f, int u, int l, int r) {
		if (l > R || r < L || !f(info[u])) {
			return 0;
		}
		if (l == r) return l;
		int m = (l + r) >> 1;
		int p = findR(L, R, f, rs[u], m + 1, r);
		if (p < 1) {
			p = findR(L, R, f, ls[u], l, m);
		}
		return p;
	}

	template<typename Func>
	auto findR(int u, int l, int r, Func&& f) {
		assert(l <= r);
		return findR(l, r, f, u, 1, n);
	}
};

struct Info {
	int maxl, maxr, sum;
	Info () {
		maxl = maxr = -1E7;
		sum = 0;
	}
	Info (int x) {
		maxl = maxr = sum = x;
	}
};

Info operator+(const Info& x, const Info& y) {
	Info res;
	res.maxl = max(x.maxl, x.sum + y.maxl);
	res.maxr = max(y.maxr, y.sum + x.maxr);
	res.sum = x.sum + y.sum;
	return res;
}

void Thephix() {
	int n;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	vector<int> p(n + 1);
	iota(p.begin(), p.end(), 0);
	sort(p.begin(), p.end(), [&](int i, int j) {
		return a[i] < a[j];
	});

	PersistentSegmentTree<Info> seg(n, n);
	vector<int> ver(n + 1);
	ver[1] = seg.build([](int p) { return 1; });
	for (int i = 1; i < n; ++i) {
		seg.modify(ver[i + 1], ver[i], p[i], [](Info& info) {
			info = -1;
		});
	}

	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		int l = 1, r = n, res = -1;
		while (l <= r) {
			int m = (l + r) >> 1;
			if (seg.query(ver[m], 1, i).maxr + seg.query(ver[m], i, n).maxl - seg.query(ver[m], i, i).sum >= 0) {
				res = m, l = m + 1;
			} else r = m - 1;
		}
		assert(res != -1);
		ans = max(ans, a[p[res]] - a[i]);
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