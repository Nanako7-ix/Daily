#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

constexpr int N = 500000 + 5;
i64 sum[N], val[N], siz[N], phi[N];
int ls[N], rs[N], fa[N], tot = 0;

int Node(int x) {
	int u = ++tot;
	val[u] = sum[u] = x;
	siz[u] = 1, phi[u] = rng();
	ls[u] = rs[u] = fa[u] = 0;
	return u;
}

void pull(int u) {
	siz[u] = siz[ls[u]] + 1 + siz[rs[u]];
	sum[u] = sum[ls[u]] + val[u] + sum[rs[u]];
}

void split(int u, int k, int& x, int& y, int fx = 0, int fy = 0) {
	if (!(x = y = u)) return;
	if (siz[ls[u]] + 1 <= k) {
		fa[u] = fx;
		split(rs[u], k - siz[ls[u]] - 1, rs[u], y, u, fy);
	} else {
		fa[u] = fy;
		split(ls[u], k, x, ls[u], fx, u);
	}
	pull(u);
}

int merge(int x, int y) {
	if (!x || !y) return x | y;
	if (phi[x] < phi[y]) {
		rs[x] = merge(rs[x], y);
		if (rs[x]) fa[rs[x]] = x;
		pull(x);
		return x;
	} else {
		ls[y] = merge(x, ls[y]);
		if (ls[y]) fa[ls[y]] = y;
		pull(y);
		return y;
	}
}

int rk(int x) {
	int res = siz[ls[x]] + 1;
	for (int u = x; fa[u]; u = fa[u]) {
		if (u == rs[fa[u]]) {
			res += siz[ls[fa[u]]] + 1;
		}
	}
	return res;
}

void print(int u) {
	if (u == 0) return;
	print(ls[u]);
	cerr << val[u] << ' ';
	print(rs[u]);
}

void Thephix() {
	int n;
	cin >> n;
	int root = Node(0);
	vector<int> p(n + 1);
	p[0] = root;
	for (int i = 1; i <= n; ++i) {
		int op; cin >> op;
		if (op == 1) {
			int x, t1, t2;
			cin >> x;
			split(root, rk(p[x]), t1, t2);
			root = merge(merge(t1, p[i] = Node(i)), t2);
		} else {
			int x, y;
			cin >> x >> y;
			x = rk(p[x]), y = rk(p[y]);
			if (x > y) swap(x, y);
			y--;

			int t1, t2;
			split(root, y, root, t2);
			split(root, x, t1, root);
			cout << sum[root] << "\n";
			root = merge(t1, t2);
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