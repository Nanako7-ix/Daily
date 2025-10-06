#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

struct DSU {
	int n, cnt;
	std::vector<int> f, siz;

	DSU() = default;

	DSU(int n) { init(n); }

	void init(int n) {
		this -> n = n;
		cnt = n;
		f.resize(n + 1);
		siz.assign(n + 1, 1);
		std::iota(f.begin(), f.end(), 0);
	}

	int find(int x) {
		if(f[x] == x) return x;
		return f[x] = find(f[x]);
	}

	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return false;
		siz[f[y] = x] += siz[y], cnt--;
		return true;
	}

	bool same(int x, int y) {
		return find(x) == find(y);
	}

	int size(int x) {
		return siz[find(x)];
	}

	int count() const {
		return cnt;
	}
};

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

struct SplitMix {
	static u64 shift(u64 x) {
		static const u64 rng = std::random_device()();
		x += rng;
		x += 0x9E37'79B9'7F4A'7C15ULL;
		x = (x ^ (x >> 30)) * 0xBF58'476D'1CE4'E5B9ULL;
		x = (x ^ (x >> 27)) * 0x94D0'49BB'1331'11EBULL;
		return x ^ (x >> 31);
	}
	u64 operator() (const u64& x) const {
		return shift(x);
	}
};

u64 code(u64 x, u64 y) { return x << 32 | y; }

template<std::integral K, typename V>
using HashMap = __gnu_pbds::gp_hash_table<K, V, SplitMix>;

constexpr int K = 548;

void Thephix() {
	int n, k, s, q;
	cin >> n >> k >> s >> q;
	VirtualTree tr(n);
	vector<vector<int>> adj(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		tr.add(u, v);
	}

	tr.work();
	auto& dep = tr.dep;

	vector<vector<int>> col(k + 1);
	for (int i = 1; i <= s; ++i) {
		int u, x;
		cin >> u >> x;
		col[x].push_back(u);
	}

	HashMap<i64, int> id;
	vector<int> ans(q + 1);
	vector<array<int, 2>> query(q + 1);
	for (int i = 1; i <= q; ++i) {
		auto& [u, v] = query[i];
		cin >> u >> v;
		if (u > v) swap(u, v);
		id[code(u, v)] = i;
	}

	DSU dsu(n);
	vector<int> vis(n + 1);
	vector<vector<int>> cc(n + 1);
	// 每个颜色需要单独考虑
	for (int c = 1; c <= k; ++c) {
		if (col[c].empty()) continue;
		for (auto u : col[c]) {
			vis[u] = 1;
		}

		// 利用虚树构建连通块
		vector<array<int, 2>> E;
		tr.build(col[c].begin(), col[c].end(), [&](int u, int v) {
			if (vis[u] && vis[v] && abs(dep[u] - dep[v]) == 1) {
				dsu.merge(u, v);
			}
		});
		
		// 找到需要的连通块
		for (auto& u : col[c]) {
			cc[dsu.find(u)].push_back(u);
		}

		// 枚举所有连通分量
		for (auto& rt : col[c]) {
			if (dsu.find(rt) != rt) {
				continue;
			}

			auto& x = cc[rt];
			int size = x.size();

			if (size > K) {
				// 暴力枚举所有查询，如果两个点在同一个连通块内，那么 ans++
				for (int i = 1; i <= q; ++i) {
					auto [u, v] = query[i];
					if (dsu.find(u) == rt && dsu.find(v) == rt) {
						ans[i] += 1;
					}
				}
			} else {
				// 暴力枚举连通块内的所有点，然后查看是否有这样的查询
				for (int i = 0; i < size; ++i) {
					for (int j = i; j < size; ++j) {
						int u = x[i], v = x[j];
						if (u > v) swap(u, v);
						if (auto it = id.find(code(u, v)); it != id.end()) {
							ans[it -> second]++;
						}
					}
				}
			}
		}

		for (auto& u : col[c]) {
			vis[u] = 0;
			// 只有有颜色的点才会连边
			dsu.f[u] = u, dsu.siz[u] = 1;
			cc[u].clear();
		}
	}

	for (int i = 1; i <= q; ++i) {
		auto& [u, v] = query[i];
		cout << ans[id[code(u, v)]] << " \n"[i == q];
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
