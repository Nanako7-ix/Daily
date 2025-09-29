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
	int n, q;
	cin >> n >> q;

	vector<string> a(n);
	for (int i = 1; i < n; ++i) {
		cin >> a[i];
	}

	if (n <= 20) {
		vector dp(n + 1, vector<int> (n + 1));
		for (int i = 1; i < n; ++i) {
			for (int j = 0; j < n - i; ++j) {
				dp[i][i + j + 1] = a[i][j] == '1' ? 1 : n;
				dp[i + j + 1][i] = n + 1 - dp[i][i + j + 1];
			}
		}

		for (int k = 1; k <= n; ++k) {
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
				}
			}
		}
		
		while (q--) {
			int u, v;
			cin >> u >> v;
			if (dp[u][v] == n) {
				cout << "-1\n";
			} else {
				cout << dp[u][v] - 1 << "\n";
			}
		}
	} else {
		while (q--) {
			int u, v;
			cin >> u >> v;
			if (u < v) {
				cout << (a[u][v - u - 1] == '1' ? "0\n" : "1\n");
			} else {
				cout << (a[v][u - v - 1] == '1' ? "1\n" : "0\n");
			}
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
