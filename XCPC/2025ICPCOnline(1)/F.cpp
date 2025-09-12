#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int n = 41;
int vis[100][100];

void Thephix() {
	int x, y;
	cin >> x >> y;

	auto mark = [&](int i, int j) -> void {
		vis[i][j] = 1;
		cout << i << ' ' << j << endl;
		cin >> x >> y;
		if (x == 0 && y == 0) exit(0);
	};

	mark(n - 4, n), mark(n, n - 4);
	mark(n - 3, n), mark(n, n - 3);
	mark(n - 2, n), mark(n, n - 2);
	mark(n - 1, n), mark(n, n - 1);
	mark(n, n);
	
	while (true) {
		int ok = 0;
		if (n - y <= 4) {
			for (int i : { x, x - 1, x + 1, x - 2, x + 2, x - 3, x + 3, x - 4, x + 4 }) {
				if (i < 1 || i > n) continue;
				if (vis[i][n] == 0) {
					mark(i, n), ok = 1;
					break;
				}
			} if (ok) continue;
		}

		if (n - x <= 4) {
			for (int i : { y, y - 1, y + 1, y - 2, y + 2, y - 3, y + 3, y - 4, y + 4 }) {
				if (i < 1 || i > n) continue;
				if (vis[n][i] == 0) {
					mark(n, i), ok = 1;
					break;
				}
			} if (ok) continue;
		}

		for (int i : { x, x - 2, x + 2, x - 4, x + 4 }) {
			if (i % 2 == 0 || i < 1 || i > n) continue;
			if (vis[i][n] == 0) {
				mark(i, n), ok = 1;
				break;
			}
		} if (ok) continue;

		for (int i : { x - 1, x + 1, x + 3, x - 3 }) {
			if (i % 2 == 0 || i < 1 || i > n) continue;
			if (vis[i][n] == 0) {
				mark(i, n), ok = 1;
				break;
			}
		} if (ok) continue;

		for (int i : { y, y - 2, y + 2, y - 4, y + 4 }) {
			if (i % 2 == 0 || i < 1 || i > n) continue;
			if (vis[n][i] == 0) {
				mark(n, i), ok = 1;
				break;
			}
		} if (ok) continue;

		for (int i : { y - 1, y + 1, y + 3, y - 3 }) {
			if (i % 2 == 0 || i < 1 || i > n) continue;
			if (vis[n][i] == 0) {
				mark(n, i), ok = 1;
				break;
			}
		} if (ok) continue;

		for (int i = 1; i <= n; ++i) {
			if (vis[i][n] == 0) {
				mark(i, n), ok = 1;
				break;
			}
		} if (ok) continue;

		for (int i = 1; i <= n; ++i) {
			if (vis[n][i] == 0) {
				mark(n, i), ok = 1;
				break;
			}
		} if (ok) continue;

		break;
	}

	int l = 1, r = n - 1;
	while (l <= r) {
		int m = (l + r) >> 1;
		for (int i = 1; i < n; ++i) {
			if (vis[m][i] == 0) mark(m, i);
		}
		if (x < m) {
			r = m - 1;
		} else l = m + 1;
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
