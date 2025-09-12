#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 inf = 1E12;

void Thephix() {
	int n;
	cin >> n;
	vector<array<i64, 3>> dp(n + 1, { -inf, -inf, -inf });
	dp[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		int val; cin >> val;

		if (dp[i - 1][0] == val) {
			dp[i][0] = dp[i - 1][0];
		} else if (dp[i - 1][0] < val) {
			dp[i][0] = dp[i - 1][0] + 1;
		} else {
			dp[i][0] = dp[i - 1][0] - 1;
		}

		dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]);

		dp[i][2] = max(dp[i - 1][1], dp[i - 1][2]);
		if (dp[i][2] == val) {
			dp[i][2] = dp[i][2];
		} else if (dp[i][2] < val) {
			dp[i][2] = dp[i][2] + 1;
		} else {
			dp[i][2] = dp[i][2] - 1;
		}
	}

	cout << max(dp[n][1], dp[n][2]) << "\n";
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
