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

	void pull(int u) {
		info[u] = info[ls] + info[rs];
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

	Info query(int L, int R, int u, int l, int r) {
		if (L <= l && r <= R) {
			return info[u];
		}
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
		if (l > R || r < L || !f(info[u])) {
			return n + 1;
		}
		if (l == r) return l;
		int m = (l + r) >> 1;
		int p = findL(L, R, f, ls, l, m);
		if (p > n) {
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
		if (l > R || r < L || !f(info[u])) {
			return 0;
		}
		if (l == r) return l;
		int m = (l + r) >> 1;
		int p = findR(L, R, f, rs, m + 1, r);
		if (p < 1) {
			p = findR(L, R, f, ls, l, m);
		}
		return p;
	}

	template<typename Func>
	auto findR(int l, int r, Func&& f) {
		assert(l <= r);
		return findR(l, r, f, 1, 1, n);
	}
};
#undef ls
#undef rs

#define v first
#define c second
template<typename T, int _N>
struct MooreVote {
	using Vote = pair<T, i64>;
	constexpr static int N = _N - 1;
	
	array<Vote, N> d;
	
	MooreVote () {
		d.fill(Vote { T(), 0 });
	}
	
	MooreVote (const T& e, i64 cnt = 1) {
		d.fill(Vote { T(), 0 });
		d[0] = Vote { e, cnt };
	}
	
	void merge(const Vote& vote) {
		for (auto& [v, c] : d) {
			if (v == vote.v) {
				c += vote.c;
				return;
			}
		}

		auto p = min_element(d.begin(), d.end(), [](const Vote& x, const Vote& y) {
			return x.c < y.c;
		}) - d.begin();

		int del = min(d[p].c, vote.c);
		if (d[p].c < vote.c) {
			d[p] = vote;
		}
		for(auto& [v, c] : d) {
			if (c > 0) c -= del;
		}
	}
	
	friend MooreVote operator+(MooreVote x, MooreVote y) {
		for (Vote& vote : y.d) x.merge(vote);
		return x;
	}
};
#undef v
#undef c

void Thephix() {
	int n, q;
	cin >> n >> q;
	vector<int> a(n + 1), x;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		x.push_back(a[i]);
	}

	sort(x.begin(), x.end());
	x.erase(unique(x.begin(), x.end()), x.end());

	int m = x.size();
	vector<vector<int>> p(m + 1);
	for (int i = 1; i <= n; ++i) {
		a[i] = lower_bound(x.begin(), x.end(), a[i]) - x.begin() + 1;
		p[a[i]].push_back(i);
	}

	SegmentTree<MooreVote<int, 3>> seg(n, [&](int i) { return a[i]; });
	for (int i = 1; i <= q; ++i) {
		int l, r;
		cin >> l >> r;
		auto d = seg.query(l, r).d;

		auto count = [&](int x) {
			return upper_bound(p[x].begin(), p[x].end(), r) - lower_bound(p[x].begin(), p[x].end(), l);
		};

		set<int> ans;
		for (auto& [v, c] : d) {
			if (count(v) > (r - l + 1) / 3) {
				ans.insert(v);
			}
		}
		
		if (ans.empty()) {
			cout << -1 << "\n";
		} else {
			for (auto i : ans) {
				cout << x[i - 1] << ' ';
			}
			cout << "\n";
		}
	}
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
