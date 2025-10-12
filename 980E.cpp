#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

struct HLD {
	int n = 0, tot = 0;
	std::vector<std::vector<int>> adj;
	std::vector<int> dfn, idfn, siz, fa, top, dep;
	HLD () = default;
	HLD (int n) { init(n); }
	void init (int n) {
		this -> n = n;
		tot = 0;
		adj.assign(n + 1, {});
		dfn .assign(n + 1, 0);
		idfn.assign(n + 1, 0);
		siz.assign(n + 1, 0);
		fa .assign(n + 1, 0);
		top.assign(n + 1, 0);
		dep.assign(n + 1, 0);
	}
	void add (int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	void work (int root = 1) {
		dep[root] = 1;
		dfs1(root), dfs2(root);
	}
	void dfs1 (int u) {
		if (fa[u] != 0) {
			adj[u].erase(find(adj[u].begin(), adj[u].end(), fa[u]));
		}
		siz[u] = 1;
		for (auto& v : adj[u]) {
			dep[v] = dep[fa[v] = u] + 1;
			dfs1(v);
			siz[u] += siz[v];
			if (siz[v] > siz[adj[u][0]]) {
				std::swap(v, adj[u][0]);
			}
		}
	}
	void dfs2 (int u) {
		dfn[u] = ++tot;
		idfn[tot] = u;
		for (auto v : adj[u]) {
			top[v] = v == adj[u][0] ? top[u] : v;
			dfs2(v);
		}
	}
	int lca (int u, int v) {
		while (top[u] != top[v]) {
			if (dep[top[u]] > dep[top[v]]) {
				u = fa[top[u]];
			} else {
				v = fa[top[v]];
			}
		}
		return dep[u] < dep[v] ? u : v;
	}
	int jump (int u, int k) {
		assert(dep[u] >= k);
		int d = dep[u] - k;
		while (dep[top[u]] > d) {
			u = fa[top[u]];
		}
		return idfn[dfn[u] - dep[u] + d];
	}
	template<typename Func>
	void modify (int u, int v, Func modify) {
		while (top[u] != top[v]) {
			if (dep[top[u]] > dep[top[v]]) {
				modify(dfn[top[u]], dfn[u]);
				u = fa[top[u]];
			} else {
				modify(dfn[top[v]], dfn[v]);
				v = fa[top[v]];
			}
		}
		if (dep[u] < dep[v]) {
			modify(dfn[u], dfn[v]);
		} else {
			modify(dfn[v], dfn[u]);
		}
	}
	template<typename Func>
	void modify (int u, Func modify) {
		modify(dfn[u], dfn[u] + siz[u] - 1);
	}
	template<typename Func, typename T = std::invoke_result_t<Func, int, int>>
	T query (int u, int v, Func query, T res = {}) {
		while (top[u] != top[v]) {
			if (dep[top[u]] > dep[top[v]]) {
				res = query(dfn[top[u]], dfn[u]) + res;
				u = fa[top[u]];
			} else {
				res = query(dfn[top[v]], dfn[v]) + res;
				v = fa[top[v]];
			}
		}
		if (dep[u] < dep[v]) {  
			return query(dfn[u], dfn[v]) + res;
		} else {
			return query(dfn[v], dfn[u]) + res;
		}
	}
	template<typename Func, typename T = std::invoke_result_t<Func, int, int>>
	T query (int u, Func query) {
		return query(dfn[u], dfn[u] + siz[u] - 1);
	}
	bool isAncester (int f, int u) {
		return dfn[f] <= dfn[u] && dfn[u] < dfn[f] + siz[f];
	}
	int rootedParent (int rt, int u) {
		if (rt == u) return rt;
		if (!isAncester(u, rt)) return fa[u];
		auto it = std::upper_bound(adj[u].begin(), adj[u].end(), rt, [&](int x, int y) {
			return dfn[x] < dfn[y];
		}) - 1;
		return *it;
	}
	int rootedSize (int rt, int u) {
		if (rt == u) return n;
		if (!isAncester(u, rt)) return siz[u];
		return n - siz[rootedParent(rt, u)];
	}
	int rootedLca (int rt, int u, int v) {
		return lca(rt, u) ^ lca(u, v) ^ lca(v, rt);
	}
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
		init(n, [](int) { return Info {}; });
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
	int x;
	Tag (int x = 0) : x(x) {};
	void apply(const Tag& v) { if (v.x) x = v.x; }
};

struct Info {
	int len, cnt;
	Info() { len = cnt = 0; }
	Info(int) { len = 1, cnt = 0; }
	void apply(const Tag& v) { if (v.x) cnt = len; }
};

Info operator+ (const Info& x, const Info& y) {
	Info res;
	res.len = x.len + y.len;
	res.cnt = x.cnt + y.cnt;
	return res;
}

void Thephix() {
	int n, k;
	cin >> n >> k;

	HLD hld(n);
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		hld.add(u, v);
	}
	
	hld.work(n);
	auto& dep = hld.dep;
	auto& dfn = hld.dfn;
	LazySegmentTree<Info, Tag> seg(n, [](int) { return Info(0); });
	
	for (int i = n, x = n; i >= 1; --i) {
		int cnt = dep[i] - hld.query(n, i, [&](int l, int r) {
			return seg.query(l, r);
		}).cnt;
		if (x - cnt >= k) {
			x -= cnt;
			hld.modify(n, i, [&](int l, int r) {
				seg.modify(l, r, 1);
			});
		}
	}
	
	for (int i = 1; i <= n; ++i) {
		if (seg.query(dfn[i], dfn[i]).cnt == 0) {
			cout << i << ' ';
		}
	} cout << "\n";
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
