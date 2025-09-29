#include <bits/stdc++.h>
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

auto H = []() {
	constexpr int N = 100000;
	array<u64, N + 1> H {};
	mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
	for (int i = 1; i <= N; ++i) {
		H[i] = rng();
	}
	return H;
} ();

void Thephix() {
	int n, m1, m2;
	cin >> n >> m1 >> m2;

	map<int, array<vector<array<int, 2>>, 2>> E;
	for (int i = 1; i <= m1; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		E[w][0].push_back({ u, v });
	}
	for (int i = 1; i <= m2; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		E[w][1].push_back({ u, v });
	}

	array<u64, 2> Hash {};
	vector<array<u64, 2>> f(n + 1);
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < 2; ++j) {
			f[i][j] = H[i];
			Hash[j] ^= H[i];
		}
	}

	array<DSU, 2> dsu;
	dsu[0].init(n), dsu[1].init(n);

	for (auto& [w, e] : E) {
		for (int i = 0; i < 2; ++i) {
			for (auto [u, v] : e[i]) {
				u = dsu[i].find(u);
				v = dsu[i].find(v);
				if (u == v) continue;
				dsu[i].merge(u, v);
				Hash[i] ^= f[u][i] ^ f[v][i];
				f[u][i] += f[v][i];
				Hash[i] ^= f[u][i];
			}
		}
		
		if (Hash[0] != Hash[1]) {
			cout << "NO\n";
			return;
		}
	}

	cout << "YES\n";
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
