#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

struct SAM {
public:
	SAM (int n = 0) {
		t.reserve(n);
		t.assign(2, Node {});
		t[0].next.fill(1);
		t[0].len = -1;
		substr = 0;
	}

	int newNode() {
		t.emplace_back();
		return t.size() - 1;
	}

	int extend(int p, int c) {
		if (t[p].next[c]) {
			int q = t[p].next[c];
			if (t[q].len == t[p].len + 1) {
				return q;
			}
			int r = newNode();
			t[r].len = t[p].len + 1;
			t[r].link = t[q].link;
			t[r].next = t[q].next;
			t[q].link = r;
			while (t[p].next[c] == q) {
				t[p].next[c] = r;
				p = t[p].link;
			}
			return r;
		}

		int cur = newNode();
		t[cur].len = t[p].len + 1;
		while (!t[p].next[c]) {
			t[p].next[c] = cur;
			p = t[p].link;
		}

		t[cur].link = extend(p, c);
		substr += t[cur].len - t[t[cur].link].len;
		return cur;
	}

	int len(int p) {
		return t[p].len;
	}

	int link(int p) {
		return t[p].link;
	}

	int next(int p, int x) {
		return t[p].next[x];
	}
			
	int size() {
		return t.size();
	}

	i64 count () {
		return substr;
	}

	auto getTree() -> std::vector<std::vector<int>> {
		int n = t.size();
		std::vector<std::vector<int>> adj(n);
		for (int i = 2; i < n; ++i) {
			adj[t[i].link].push_back(i);
		}
		return adj;
	}

private:
	static constexpr int N = 26;
	struct Node {
		int len;
		int link;
		std::array<int, N> next;
		Node() : len(), link(), next() {}
	};

	i64 substr;
	std::vector<Node> t;
};

template<typename Info>
struct DynamicSegmentTree {
	int n, lo, hi, cnt;
	vector<Info> info;
	vector<int> ls, rs;

	DynamicSegmentTree () = default;
	DynamicSegmentTree (int n, int lo, int hi) { init(n, lo, hi); }

	void init (int n, int lo, int hi) {
		this -> n = n;
		this -> lo = lo;
		this -> hi = hi;
		cnt = 0;
		info.assign((n + hi - lo) << 4, Info {});
		ls.assign((n + hi - lo) << 4, 0);
		rs.assign((n + hi - lo) << 4, 0);
	}

	void pull(int u) {
		info[u] = info[ls[u]] + info[rs[u]];
	}

	template<typename Func>
	void modify(int p, Func&& op, int& u, int l, int r) {
		if(u == 0) u = ++cnt;
		if(l == r) {
			op(info[u]);
			return;
		}
		int m = (l + r) >> 1;
		if(p <= m) modify(p, op, ls[u], l, m);
		else modify(p, op, rs[u], m + 1, r);
		pull(u);
	}

	template<typename Func>
	void modify(int& u, int p, Func&& op) {
		modify(p, op, u, lo, hi);
	}

	Info query(int L, int R, int u, int l, int r) {
		if(u == 0) return Info {};
		if(L <= l && r <= R) {
			return info[u];
		}
		int m = (l + r) >> 1;
		if(R <= m) return query(L, R, ls[u], l, m);
		if(L > m) return query(L, R, rs[u], m + 1, r);
		return query(L, R, ls[u], l, m) + query(L, R, rs[u], m + 1, r);
	}

	Info query(int u, int l, int r) {
		return query(l, r, u, lo, hi);
	}

	template<typename Func>
	int merge(int x, int y, int l, int r, Func&& opt) {
		if(!x || !y) return x | y;
		if(l == r) {
			info[x] = opt(info[x], info[y]);
		} else {
			int m = (l + r) >> 1;
			ls[x] = merge(ls[x], ls[y], l, m, opt);
			rs[x] = merge(rs[x], rs[y], m + 1, r, opt);
			pull(x);
		}
		return x;
	}

	template<typename Func>
	void merge(int& x, int y, Func&& opt) {
		x = merge(x, y, lo, hi, opt);
	}
};
#undef ls
#undef rs

void Thephix() {
	int n;
	cin >> n;

	SAM sam(n);
	vector<int> p(n + 1); p[0] = 1;
	vector<vector<int>> adj(n + 1);
	for (int u = 1; u <= n; ++u) {
		int op, fa;
		char ch;
		cin >> op;
		if (op == 1) {
			fa = 0;
			cin >> ch;
		} else {
			cin >> fa >> ch;
		}
		adj[fa].push_back(u);
		p[u] = sam.extend(p[fa], ch - 'a');
	}

	int idx = 0;
	vector<int> dfn(n + 1), siz(n + 1);
	[&](this auto&& dfs, int u) -> int {
		dfn[u] = idx++;
		siz[u] = 1;
		for (auto v : adj[u]) {
			siz[u] += dfs(v);
		}
		return siz[u];
	} (0);

	int m = sam.size() - 1;
	vector<int> root(m + 1);
	DynamicSegmentTree<int> seg(m, 1, n);
	for (int i = 1; i <= n; ++i) {
		seg.modify(root[p[i]], dfn[i], [](int& cnt) { cnt++; });
		if (dfn[i] + siz[i] <= n) {
			seg.modify(root[p[i]], dfn[i] + siz[i], [](int& cnt) { cnt--; });
		}
	}

	int q;
	cin >> q;
	vector<vector<pair<int, int>>> query(m + 1);
	for (int i = 1; i <= q; ++i) {
		int x;
		string s;
		cin >> x >> s;
		int u = 1, len = s.size(), ok = 1;
		for (int i = 0; i < len; ++i) {
			int v = sam.next(u, s[i] - 'a');
			if (v == 0) {
				ok = 0; break;
			}
			u = v;
		}
		if (ok) query[u].push_back({x, i});
	}

	vector<int> ans(q + 1);
	adj = sam.getTree();
	[&](this auto&& dfs, int u) -> void {
		for (auto v : adj[u]) {
			dfs(v);
			seg.merge(root[u], root[v], plus<int> {});
		}
		for (auto [x, id] : query[u]) {
			ans[id] = seg.query(root[u], 1, dfn[x]);
		}
	} (1);

	for (int i = 1; i <= q; ++i) {
		cout << ans[i] << "\n";
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