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
	int n;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	vector<array<i64, 2>> pre(n + 1);
	vector<i64> ndp(n + 1), dp(n + 1);
	for (int i = 1; i <= n; ++i) {
		pre[i] = pre[i - 1];
		pre[i][i % 2] += a[i];
		ndp[i] = pre[i][0] - pre[i][1];
		dp[i] = ndp[i] - ndp[i - 1];
	}

	vector<i64> Max(n + 1);
	i64 ans = 0;
	for (int i = 1; i <= n; ++i) {
		dp[i] += dp[i - 1];
		if (i % 2 == 1) {
			i64 x = i == 1 ? 0 : Max[i - 2] - dp[i];
			i64 y = i == n ? 0 : Max[i - 1] - dp[i + 1] - dp[i];
			i64 res = max({x, y, 0LL});
			ans += res;
			for (int j = i; j <= n; ++j) {
				ndp[j] += res;
			}
			dp[i] += res;
		}
		Max[i] = max(dp[i], Max[i - 1]);
	}
	cout << ans << "\n";
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