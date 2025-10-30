#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n;
	cin >> n;
	vector<i64> a(n + 1), d;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		d.push_back(a[i]);
	}
	
	sort(d.begin(), d.end());
	d.erase(unique(d.begin(), d.end()), d.end());
	for (int i = 1; i <= n; ++i) {
		a[i] = lower_bound(d.begin(), d.end(), a[i]) - d.begin() + 1;
	}
	
	vector<int> c(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> c[i];
	}

	int m = d.size();
	vector<i64> dp(m + 1);
	for (int i = 1; i <= n; ++i) {
		vector<i64> ndp(m + 1);
		for (int j = 0; j <= m; ++j) {
			i64 x = a[i] == j ? 0 : c[i];
			ndp[j] = x + dp[j];
		}
		for (int j = 1; j <= m; ++j) {
			ndp[j] = min(ndp[j], ndp[j - 1]);
		}
		swap(dp, ndp);
	}

	cout << dp[m] << "\n";
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
