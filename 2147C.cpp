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
	string s;
	cin >> n >> s;
	
	const int l = 1, r = 2, all = 3;
	vector<int> p {0},  dp(n + 2);
	dp[0] = l;
	int ok = 1;
	for (int i = 1; i <= n; ++i) {
		if (s[i - 1] == '0') {
			int x = p.back();
			p.push_back(i);
			if (i - x == 1) {
				ok = 1;
				dp[i] = all;
			} else if (i - x == 2) {
				if (dp[x] == l) {
					dp[i] = r, ok = 0;
				} else if (dp[x] == r) {
					ok = 1, dp[i] = l;
				} else {
					dp[i] = all;
				}
			} else {
				if (ok == 0) {
					cout << "NO\n";
					return;
				}
				dp[i] = r;
				ok = 0;
			}
		}
	}

	if (ok == 0) {
		if (p.back() == n) {
			ok = 1;
		}
	}

	cout << (ok ? "YES\n" : "NO\n");
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
