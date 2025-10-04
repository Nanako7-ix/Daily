#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

void Thephix() {
	int t;
	cin >> t;

	auto [n, m] = pair { 4 * t + 5, 13 * t + 19 };
	vector a(n + 1, vector<char> (m + 1, '.'));

	for (int i = 1; i <= m; ++i) {
		a[1][i] = a[n][i] = '*';
	}
	for (int i = 1; i <= n; ++i) {
		a[i][1] = a[i][m] = '*';
	}

	int x = t + 2, y = t + 3;
	
	for (int i = 0; i < 2 * t + 3; ++i) {
		a[i + x][y] = '@';
		a[i + x][i + y] = '@';
		a[i + x][y + 2 * t + 2] = '@';
	}

	y += 3 * t + 4;
	for (int i = 0; i < 2 * t + 3; ++i) {
		a[i + x][y] = '@';
		a[x][y + i] = '@';
		a[x + t + 1][y + i] = '@';
	}

	y += 3 * t + 4;
	for (int i = 0; i < 2 * t + 3; ++i) {
		a[i + x][y] = '@';
		a[x + 2 * t + 2][y + i] = '@';
	}

	y += 3 * t + 4;
	for (int i = 0; i < 2 * t + 3; ++i) {
		a[x][y + i] = '@';
		a[x + t + 1][y + i] = '@';
		a[x + 2 * t + 2][y + i] = '@';

		if (i < t + 1) {
			a[x + i][y] = '@';
		} else {
			a[x + i][y + 2 * t + 2] = '@';
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cout << a[i][j];
		}
		cout << "\n";
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
