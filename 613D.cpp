#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

struct VirtualTree {
	int n, tot;
	std::vector<std::vector<int>> adj, st;
	std::vector<int> fa, dep, dfn, siz;
	
	VirtualTree (int n) { init(n); }
	
	void init (int n) {
		this -> n = n;
		tot = 0;
		adj.assign(n + 1, {});
		st.assign(std::__lg(n) + 1, std::vector<int> (n + 1));
		fa.assign(n + 1, 0);
		dep.assign(n + 1, 0);
		dfn.assign(n + 1, 0);
		siz.assign(n + 1, 0);
	}
	
	void add (int u, int v) {
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	
	void dfs (int u) {
		if(fa[u] != 0) adj[u].erase(find(adj[u].begin(), adj[u].end(), fa[u]));
		siz[u] = 1;
		st[0][dfn[u] = ++tot] = u;
		for(auto v : adj[u]) {
			dep[v] = dep[fa[v] = u] + 1;
			dfs(v);
			siz[u] += siz[v];
		}
	}
	
	int merge (int x, int y) {
		return dep[x] < dep[y] ? x : y;
	}
	
	void work (int rt = 1) {
		dep[rt] = 1;
		dfs(rt);
		for(int i = 1; i <= std::__lg(n); ++i) {
			for(int j = 1; j + (1 << i) - 1 <= n; ++j) {
				st[i][j] = merge(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
			}
		}
	}
	
	int lca (int u, int v) {
		if(u == v) return u;
		u = dfn[u], v = dfn[v];
		if(u > v) std::swap(u, v);
		int len = std::__lg(v - u);
		return fa[merge(st[len][u + 1], st[len][v - (1 << len) + 1])];
	}

	template<typename Iter, typename Func>
	int build(Iter l, Iter r, Func&& link) {
		std::vector p(l, r);
		std::sort(p.begin(), p.end(), [&](int x, int y) {
			return dfn[x] < dfn[y];
		});

		std::vector<int> stk;
		stk.push_back(1);

		int len = p.size(), x = p[0] == 1;
		for (int i = p[0] == 1; i < len; ++i) {
			int u = p[i];
			int w = lca(u, stk.back());
			if (w != stk.back()) {
				while (stk.size() >= 2 && dep[w] <= dep[stk[stk.size() - 2]]) {
					link(stk[stk.size() - 2], stk.back());
					x |= stk[stk.size() - 2] == 1;
					stk.pop_back();
				}
				
				if (stk.back() != w) {
					link(w, stk.back());
					stk.pop_back();
					stk.push_back(w);
				}
			}
			stk.push_back(u);
		}

		len = stk.size();
		for (int i = !x; i < len - 1; ++i) {
			link(stk[i], stk[i + 1]);
		}
		return stk[!x];
	}
};

void Thephix() {
	int n;
	cin >> n;
	VirtualTree tr(n);
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		tr.add(u, v);
	}

	int q; cin >> q;
	vector<vector<int>> adj(n + 1);
	while (q--) {
		int k;
		cin >> k;
		vector<int> p(k + 1);
		for (int i = 1; i <= k; ++i) {
			cin >> p[i];
		}

		vector<array<int, 2>> E;
		int rt = tr.build(p.begin() + 1, p.end(), [&](int u, int v) {
			E.push_back({ u, v });
			adj[u].push_back(v);
			adj[v].push_back(u);
		});

		[&](this auto&& dfs, int u, int fa) -> void {
			for (auto& v : adj[u]) {
				if (v == fa) continue;
				dfs(v, u);
			}
		} (rt, 0);

		for (auto& [u, v] : E) {
			adj[u].pop_back();
			adj[v].pop_back();
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
