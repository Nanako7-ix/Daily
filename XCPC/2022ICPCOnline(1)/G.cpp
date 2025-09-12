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
	int n, Max;
	cin >> n >> Max;
	array<i64, 4> t;
	cin >> t[0] >> t[1] >> t[2] >> t[3];

	map<pair<int, i64>, i64> dp;
	dp[{0, 0}] = 0;
	for (int i = 1; i <= n; ++i) {
		i64 val; cin >> val;
		map<pair<int, i64>, i64> ndp;
		for (auto& [_, ans] : dp) {
			auto& [x, y] = _;
			ndp[{ 0, y }] = max(ndp[{ 0, y }], ans);
			if (x + 1 < 5 && y + t[x] <= Max) {
				ndp[{ x + 1, y + t[x] }] = max(ndp[{ x + 1, y + t[x] }], ans + val);
			}
		}
		swap(dp, ndp);
	}

	i64 ans = 0;
	for (auto& [_, val] : dp) {
		ans = max(ans, val);
	}
	cout << ans << "\n";
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
