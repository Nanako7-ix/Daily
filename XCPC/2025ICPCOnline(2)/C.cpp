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
struct MaxFlow {
	struct edge {
		int v;
		T cap;
		edge(int v, T cap) : v(v), cap(cap) {}
	};

	int n;
	std::vector<edge> e;
	std::vector<std::vector<int>> g;
	std::vector<int> cur, h;

	MaxFlow(int n) { init(n); }

	void init(int n) {
		this -> n = n;
		g.assign(n + 1, {});
	}

	void add(int u, int v, T cap) {
		g[u].push_back(e.size());
		e.emplace_back(v, cap);
		g[v].push_back(e.size());
		e.emplace_back(u, 0);
	}

	bool bfs(int s, int t) {
		std::queue<int> q;
		h.assign(n + 1, 0);
		h[s] = 1;
		q.push(s);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (auto i : g[u]) {
				auto [v, cap] = e[i];
				if (cap > 0 && h[v] == 0) {
					h[v] = h[u] + 1;
					if (v == t) return true;
					q.push(v);
				}
			}
		}
		return false;
	}

	T dfs(int u, int t, T f) {
		if (u == t) return f;
		T r = f;
		for (int& i = cur[u]; i < (int) g[u].size(); ++i) {
			int j = g[u][i];
			auto& [v, cap] = e[j];
			if (cap > 0 && h[v] == h[u] + 1) {
				T aug = dfs(v, t, std::min(r, cap));
				r -= aug;
				e[j].cap -= aug;
				e[j ^ 1].cap += aug;
				if (r == 0) break;
			}
		}
		return f - r;
	}

	T flow(int s, int t) {
		T ans = 0;
		while (bfs(s, t)) {
			cur.assign(n + 1, 0);
			ans += dfs(s, t, std::numeric_limits<T>::max());
		}
		return ans;
	}

	std::vector<int> cut() {
		std::vector<int> x(n + 1);
		for (int i = 1; i <= n; ++i) {
			x[i] = h[i] != 0;
		}
		return x;
	}

	auto edges() -> std::vector<tuple<int, int, T, T>> {
		std::vector<tuple<int, int, T, T>> E;
		for (int i = 0; i < (int) e.size(); i += 2) {
			E.emplace_back(
				e[i + 1].v,
				e[i].v,
				e[i].cap + e[i + 1].cap,
				e[i + 1].cap
			);
		}
		return E;
	}
};

constexpr int inf = 1E9;
constexpr int n = 3;

void Thephix() {
	int sum;
	array<int, 8> f {};

	cin >> sum;
	for (int i = 1; i < 8; ++i) {
		cin >> f[i];
	}

	MaxFlow<int> g(9);
	int s = 8, t = 9;
	g.add(s, 4, f[3]), g.add(4, 1, inf), g.add(4, 2, inf);
	g.add(s, 5, f[5]), g.add(5, 1, inf), g.add(5, 3, inf);
	g.add(s, 6, f[6]), g.add(6, 2, inf), g.add(6, 3, inf);
	g.add(s, 7, f[7]), g.add(7, 1, inf), g.add(7, 2, inf), g.add(7, 3, inf);

	auto check = [&](int x) -> bool {
		array<int, 3> need {
			max(x - f[1], 0),
			max(x - f[2], 0),
			max(x - f[4], 0)
		};

		auto G = g;
		G.add(1, t, need[0]);
		G.add(2, t, need[1]);
		G.add(3, t, need[2]);

		return G.flow(s, t) == need[0] + need[1] + need[2];
	};

	int l = 0, r = sum / 3, res = -1;
	while (l <= r) {
		int m = (l + r) >> 1;
		if (check(m)) {
			res = m, l = m + 1;
		} else r = m - 1;
	}

	cout << res << "\n";
}

void __Thephix() {
	array<int, 1 << n> f {};
	for (int i = 0; i < (1 << n); ++i) {
		cin >> f[i];
	} f[0] = 0;

	int x = inf;
	for (int s = 1; s < (1 << n); ++s) {
		int sum = 0;
		for (int t = 1; t < (1 << n); ++t) {
			if (t & s) sum += f[t];
		}
		x = min(x, sum / popcount<u32>(s));
	}

	cout << x << "\n";
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
