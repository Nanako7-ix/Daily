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

	void assign(int l, int r, const Fn& val) {
		assert(1 <= l && l <= r && r <= n);
		auto y = split(r + 1);
		auto x = split(l);
		odt.erase(x, y);
		odt.emplace(l, r, val);
	}

	template<typename F>
	void perform(int l, int r, F&& f) {
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

constexpr i64 Mod = 1'000'000'007;

i64 power(i64 a, i64 b, i64 P) {
	i64 res = 1;
	for (a %= P; b; a = a * a % P, b >>= 1) {
		if (b & 1) res = res * a % P;
	}
	return res;
}

void Thephix() {
	int n, m;
	i64 seed, V;
	cin >> n >> m >> seed >> V;

	auto rng = [&]() -> int {
		int ret = seed;
		seed = (seed * 7 + 13) % Mod;
		return ret;
	};

	vector<i64> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		a[i] = rng() % V + 1;
	}

	ChthollyTree<Func> odt(n);
	for (int i = 1; i <= n; ++i) {
		odt.assign(i, i, a[i]);
	}

	auto add = [&](int l, int r, int v) {
		odt.perform(l, r, [&](int, int, i64& x) { x += v; });
	};

	auto assign = [&](int l, int r, int x) {
		odt.assign(l, r, x);
	};

	auto kth = [&](int l, int r, int k) -> i64 {
		vector<array<i64, 2>> val;
		odt.perform(l, r, [&](int L, int R, i64 x) {
			val.push_back({ x, R - L + 1 });
		});
		sort(val.begin(), val.end());
		for (int i = 0; i < (int) val.size(); ++i) {
			auto& [x, cnt] = val[i];
			if (cnt >= k) return x;
			k -= cnt;
		}
		assert(0);
		return 114514;
	};

	auto query = [&](int l, int r, int x, int y) {
		i64 sum = 0;
		odt.perform(l, r, [&](int L, int R, i64 v) {
			sum += (R - L + 1) * power(v, x, y) % y;
			sum %= y;
		});
		return sum;
	};

	for (int i = 1; i <= m; ++i) {
		int op, l, r;
		op = rng() % 4 + 1;
		l  = rng() % n + 1;
		r  = rng() % n + 1;
		if (l > r) swap(l, r);

		if (op == 1) {
			int x = rng() % V + 1;
			add(l, r, x);
		} else if (op == 2) {
			int x = rng() % V + 1;
			assign(l, r, x);
		} else if (op == 3) {
			int x = rng() % (r - l + 1) + 1;
			cout << kth(l, r, x) << "\n";
		} else {
			int x = rng() % V + 1;
			int y = rng() % V + 1;
			cout << query(l, r, x, y) << "\n";
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
