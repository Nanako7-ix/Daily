#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 inf = 4E18;

void Thephix() {
	int n;
	cin >> n;
	vector<i64> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	auto f = [&](int x, int y) -> i64 {
		return (a[x] - a[y]) * (a[x] - a[y]);
	};

	vector dp(n + 1, vector<i64> (n + 1, -inf));
	dp[1][1] = 0;
	for (int i = 2; i <= n; ++i) {
		for (int j = 2; j <= i; ++j) {
			for (int k = 1; k < i; ++k) {
				dp[i][j] = max(dp[i][j], dp[k][j - 1] + f(i, k));
			}
		}
	}

	for (int k = 1; k <= n; ++k) {
		cout << dp[n][max(2, n - 2 * k)] << "\n";
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
