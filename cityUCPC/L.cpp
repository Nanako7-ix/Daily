#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<typename Fn>
struct ChthollyTree {
	struct Node {
		i64 l, r;
		mutable Fn v;
		Node (i64 l, i64 r, Fn v) {
			this -> l = l;
			this -> r = r;
			this -> v = v;
		}
		bool operator< (const Node& o) const {
			return l < o.l;
		}
	};
	
	i64 n;
	std::set<Node> odt;
	Fn op;
	
	ChthollyTree (i64 n) { init(n); }

	void init (i64 n) {
		this -> n = n;
		odt.clear();
		odt.emplace(1, n, Fn());
	}

	std::set<Node>::iterator split(i64 p) {
		if (p == n + 1) return odt.end();
		auto it = odt.lower_bound(Node {p, 0, 0});
		if (it != odt.end() && it -> l == p) return it;
		--it;
		auto [l, r, v] = *it;
		odt.erase(it);

		odt.emplace(l, p - 1, v);
		v.offset(r - l + 1);
		return odt.emplace(p, r, v).first;
	}

	void flat(int l, int r) {
		assert(1 <= l && l <= r && r <= n);
		auto y = split(r + 1);
		auto x = split(l);
		odt.erase(x, y);
		odt.emplace(l, r, Fn());
	}

	template<typename F>
	void apply(int l, int r, F&& f) {
		assert(1 <= l && l <= r && r <= n);
		auto y = split(r + 1);
		auto x = split(l);
		for (auto it = x; it != y; ++it) {
			auto& [l, r, v] = *it;
			f(l, r, v);
		}
	}
};

struct Func {
	i64 x;
	Func (i64 x = 0) : x(x) {}
	void offset(i64) { }
	operator i64& () { return x; }
};

void Thephix() {
	int n, q;
	cin >> n >> q;
	vector<i64> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	ChthollyTree<Func> odt(n);
	vector<i64> d(n + 1);
	for (int i = 1; i <= n; ++i) {
		d[i] = a[i] - a[i - 1];
		odt.apply(i, i, [&](int, int, i64& v) { v = d[i]; });
	}

	auto add = [&](int l, int r, i64 v) -> void {
		odt.apply(l, r, [&](int, int, i64& x) { x += v; });
		if (r < n) {
			odt.apply(r + 1, r + 1, [&](int, int, i64& x) {
				x -= (r - l + 1) * v;
			});
		}
	};

	auto set = [&](int l, int r, i64 v) -> void {
		i64 x = 0, y = 0;
		if (l > 1) {
			odt.apply(1, l - 1, [&](int L, int R, i64 val) {
				x += (R - L + 1) * val;
				y += (R - L + 1) * val;
			});
		}
		odt.apply(l, min(r + 1, n), [&](int L, int R, i64 val) {
			y += (R - L + 1) * val;
		});
		odt.apply(l, l, [&](int, int, i64& val) {
			val = v - x;
		});
		
		if (r < n) {
			odt.apply(r + 1, r + 1, [&](int, int, i64& val) {
				val = y - (r - l + 1) * v;
			});
		}

		if (l != r) {
			odt.flat(l + 1, r);
			odt.apply(l + 1, r, [&](int, int, i64& x) { x = v; });
		}
	};

	auto query = [&](int l, int r) -> int {
		int ans = 0, ok = 0;
		i64 last;
		odt.apply(max(l, 2), min(r + 1, n), [&](int, int, i64 val) {
			if (ok == 0) {
				ok = 1;
			} else {
				ans += (last < 0 && val > 0) || (last > 0 && val < 0);
			}
			last = val;
		});
		return ans;
	};

	while (q--) {
		int op, l, r;
		cin >> op >> l >> r;
		if (op == 1) {
			i64 v;
			cin >> v;
			add(l, r, v);
		} else if (op == 2) {
			i64 v;
			cin >> v;
			set(l, r, v);
		} else {
			cout << query(l, r) << "\n";
		}
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
