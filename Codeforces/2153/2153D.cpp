#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

constexpr i64 inf = 1E18;

template<typename Iter>
i64 solve(Iter l, Iter r) {
	int n = r - l;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		a[i] = l[i - 1];
	}

	vector<array<i64, 2>> dp(n + 1, { inf, inf });
	dp[0] = { 0, 0 };
	for (int i = 2; i <= n; ++i) {
		for (int len = 2; len <= 2 + (i != 2); ++len) {
			vector<i64> x;
			for (int j = i - len + 1; j <= i; ++j) {
				x.push_back(a[j]);
			}
			sort(x.begin(), x.end());
			i64 sum = 0;
			for (int j = 0; j < len; ++j) {
				sum += abs(x[1] - x[j]);
			}
			dp[i][len - 2] = min(dp[i - len][0], dp[i - len][1]) + sum;
		}
	}
	return *min_element(dp[n].begin(), dp[n].end());
}

void Thephix() {
	int n;
	cin >> n;
	vector<int> a(2 * n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		a[i + n] = a[i];
	}

	cout << min({
		solve(a.begin() + 1, a.begin() + n + 1),
		solve(a.begin() + 2, a.begin() + n + 2),
		solve(a.begin() + 3, a.begin() + n + 3),
		solve(a.begin() + 4, a.begin() + n + 4)
	}) << "\n";
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
