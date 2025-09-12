#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<typename T>
struct Fenwick {
public:
	Fenwick () = default;

	Fenwick (int n, T e = {}) { init(n, e); }

	template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
	Fenwick (const Iterator& l, const Iterator& r) { init(l, r); }

	void init (int n, T e = {}) {
		std::vector<T> _(n, e);
		init(_.begin(), _.end());
	}

	template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
	void init (const Iterator& l, const Iterator& r) {
		n = r - l;
		tr.assign(n + 1, T {});
		for(int i = 1; i <= n; ++i) {
			tr[i] += *(l + i - 1);
			if(i + lowbit(i) <= n) {
				tr[i + lowbit(i)] += tr[i];
			}
		}
	}

	void modify (int p, const T& v) {
		for(; p <= n; p += lowbit(p)) {
			tr[p] += v;
		}
	}

	T query (int p) {
		T res = {};
		for(; p; p -= lowbit(p)) {
			res += tr[p];
		}
		return res;
	}

	T query (int l, int r) {
		assert(l <= r && l != 0);
		return query(r) - query(l - 1);
	}

	int lower_bound (T k) {
		int x = 0;
		for(int i = 1 << std::__lg(n); i; i >>= 1)
			if(x + i <= n && tr[x + i] < k)
				k -= tr[x += i];
		return x + 1;
	}

	int upper_bound (T k) {
		int x = 0;
		for(int i = 1 << std::__lg(n); i; i >>= 1)
			if(x + i <= n && tr[x + i] <= k)
				k -= tr[x += i];
		return x + 1;
	}

private:
	int n;
	std::vector<T> tr;
	constexpr int lowbit(int x) { return x & -x; }
};

void Thephix() {
	int n, q;
	cin >> n >> q;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	vector<int> lft(n + 1), rgt(n + 1, n + 1), stk;
	for (int i = 1; i <= n; ++i) {
		while (!stk.empty() && a[stk.back()] < a[i]) {
			stk.pop_back();
		}
		if (!stk.empty()) lft[i] = stk.back();
		stk.push_back(i);
	}

	stk.clear();

	for (int i = n; i >= 1; --i) {
		while (!stk.empty() && a[stk.back()] > a[i]) {
			stk.pop_back();
		}
		if (!stk.empty()) rgt[i] = stk.back();
		stk.push_back(i);
	}

	vector<vector<int>> points(n + 2);
	for (int i = 1; i <= n; ++i) {
		points[rgt[i]].push_back(lft[i]);
	}

	vector<vector<array<int, 2>>> querys(n + 1);
	for (int i = 1; i <= q; ++i) {
		int l, r;
		cin >> l >> r;
		querys[r].push_back({ l, i });
	}
	
	Fenwick<int> tr(n + 1);
	vector<int> ok(q + 1);
	for (int i = 1; i <= n; ++i) {
		for (auto x : points[i]) {
			tr.modify(x + 1, 1);
		}
		for (auto [l, id] : querys[i]) {
			ok[id] = tr.query(l + 1, n + 1) == 0;
		}
	}

	for (int i = 1; i <= q; ++i) {
		cout << (ok[i] ? "YES\n" : "NO\n");
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
