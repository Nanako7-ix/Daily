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
	int n, k;
	cin >> n >> k;
	vector<vector<char>> a(n + 1, vector<char> (n + 1, 'U'));

	k = n * n - k;

	if (k == 1) {
		cout << "NO\n";
		return;
	}
	
	if (k != 0) {
		int x = k / n, y = k % n;

		for (int i = 0; i < x; ++i) {
			for (int j = 1; j < n; ++j) {
				a[n - i][j] = 'R';
			} a[n - i][n] = 'L';
		}
		for (int j = 1; j < y; ++j) {
			a[n - x][j] = 'R';
		} a[n - x][y] = 'L';
		
		if (y == 1) {
			a[n - x + 1][n] = 'U';
			a[n - x + 1][n - 1] = 'L';
			a[n - x][y] = 'R';
			a[n - x][y + 1] = 'L';
		}
	}
	
	cout << "YES\n";
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << a[i][j];
		} cout << "\n";
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
