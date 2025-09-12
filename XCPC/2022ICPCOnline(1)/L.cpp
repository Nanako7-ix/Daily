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
	string s, t;
	cin >> s >> t;

	array<vector<int>, 26> pos {};
	for (int i = 0; i < (int) t.size(); ++i) {
		pos[t[i] - 'a'].push_back(i);
	}

	int ans = 0;
	string p; swap(s, p);
	for (int i = 0; i < (int) p.size(); ++i) {
		if (pos[p[i] - 'a'].empty()) {
			ans++;
		} else s.push_back(p[i]);
	}

	int n = s.size();
	s = ' ' + s;
	vector dp(n + 1, array<int, 26> {});
	for (int i = 1; i <= n; ++i) {
		int ch = s[i] - 'a';
		dp[i] = dp[i - 1];
		dp[i][ch] = max(dp[i][ch], 1);
		for (int j = 0; j < 26; ++j) {
			if (pos[j].empty()) continue;
			if (ch == j) {
				if (pos[ch].size() == 1) {
					dp[i][ch] = max(dp[i][ch], dp[i - 1][j] + 1);
				}
			} else {
				if (pos[ch].back() < pos[j][0]) {
					dp[i][ch] = max(dp[i][ch], dp[i - 1][j] + 1);
				}
			}
		}
	}

	cout << ans + *max_element(dp[n].begin(), dp[n].end()) << "\n";
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
