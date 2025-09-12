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
	vector<int> a(n + 1), dp(n + 3);
	vector<int> p(n + 1);
	iota(p.begin(), p.end(), 0);

	auto query = [&](int x) -> int {
		cout << "throw " << x << endl;
		cin >> x;
		return x;
	};

	auto swap = [&](int x) {
		cout << "swap " << x << endl;
		std::swap(a[x], a[x + 1]);
		std::swap(p[x], p[x + 1]);
	};
	
	dp[n] = 1;	
	for (int i = n - 1; i >= 1; --i) {
		if (dp[i + 1] == dp[i + 2]) {
			dp[i] = dp[i + 1] + 1;
		} else if (query(i) - 1 == dp[i + 1]) {
			a[i] = 1, dp[i] = dp[i + 1] + 1;
		} else {
			a[i] = 2, dp[i] = dp[i + 2] + 1;
		}
	}

	for (int i = 2; i <= n; ++i) {
		if (a[i] == 0) {
			swap(i - 1);
			assert(dp[i + 1] == dp[i + 2]);
			assert(dp[i] - 1 == dp[i + 1]);
			if (query(i - 1) == dp[i] + 1) {
				a[i - 1] = 1;
			} else a[i - 1] = 2;
		}
	}

	for (int i = n; i >= 2; --i) {
		dp[i] = dp[i + a[i]] + 1;
	}

	if (a[1] == 0) {
		if (dp[2] == dp[3]) {
			swap(1);
			if (query(2) == dp[3] + 1) {
				a[2] = 1;
			} else a[2] = 2;
		} else {
			if (query(1) == dp[2] + 1) {
				a[1] = 1;
			} else a[1] = 2;
		}
	}

	cout << "! ";
	vector<int> ans(n + 1);
	for (int i = 1; i <= n; ++i) {
		ans[p[i]] = a[i];
	}
	for (int i = 1; i <= n; ++i) {
		cout << ans[i] << " ";
	}
	cout << endl;
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