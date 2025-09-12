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

	auto edges() -> std::vector<std::tuple<int, int, T, T>> {
		std::vector<std::tuple<int, int, T, T>> E;
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

constexpr i64 inf = 1E18;

void Thephix() {
	int n, m;
	cin >> n >> m;

	vector<array<i64, 2>> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i][0] >> a[i][1];
	}
	i64 sum = a[1][1];
	vector<array<i64, 3>> b(m + 1);
	for (int i = 1; i <= m; ++i) {
		cin >> b[i][0] >> b[i][1] >> b[i][2];
		if (b[i][0] == 1 || b[i][1] == 1) {
			sum += b[i][2];
		}
	}

	a[1][0] = min(a[1][0], sum);
	for (int i = 2; i <= n; ++i) {
		a[i][0] = min(a[i][0], a[1][0] - 1);
	}

	int s = n + m + 1, t = s + 1;
	MaxFlow<i128> flow(t + 1);
	for (int i = 1; i <= n; ++i) {
		flow.add(s, i, a[i][0]);
		flow.add(i, t, a[i][1]);
	}
	for (int i = 1; i <= m; ++i) {
		auto [x, y, w] = b[i];
		flow.add(x, n + i, inf);
		flow.add(y, n + i, inf);
		flow.add(n + i, t, w);
	}

	i64 cost = 0;
	for (int i = 1; i <= n; ++i) {
		cost += a[i][1];
	}
	for (int i = 1; i <= m; ++i) {
		cost += b[i][2];
	}

	if (flow.flow(s, t) == cost) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
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
