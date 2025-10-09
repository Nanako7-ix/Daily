#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

array<int, 31> f = []() {
	for (int i = 1; i <= 30; ++i) {
		f[i] = i * (i + 1) / 2;
	}
	return f;
} ();

void Thephix() {
	int n, k;
	cin >> n >> k;
	k = f[n] - k;

	vector dp(n + 1, vector<int> (k + 1, -1));
	dp[0][0] = 0;
	for (int x = 1; x <= n; ++x) {
		for (int i = x; i <= n; ++i) {
			for (int j = f[x]; j <= k; ++j) {
				if (dp[i - x][j - f[x]] != -1) {
					dp[i][j] = x;
				}
			}
		}
	}

	if (dp[n][k] == -1) {
		cout << "0\n";
		return;
	}

	int x = n, y = k;
	while (dp[x][y]) {
		int len = dp[x][y];
		for (int i = x - len + 1; i <= x; ++i) {
			cout << i << " ";
		}
		x -= len, y -= f[len];
	}
	cout << "\n";
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
