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
	vector<int> a(n + 1);
	vector<vector<int>> pos(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		pos[a[i]].push_back(i);
	}

	vector<int> dp(n + 1, n);
	for (int cnt = pos[1].size(), i = 0; i < cnt; ++i) {
		dp[pos[1][i]] = cnt - i - 1;
	}

	int none = pos[1].size();
	for (int i = 2; i <= n; ++i) {
		int cnt = pos[i].size();
		vector<int> p(pos[i - 1].size() + pos[i].size());

		merge(
			pos[i - 1].begin(), pos[i - 1].end(),
			pos[i].begin(), pos[i].end(),
			p.begin()
		);

		multiset<int> l, r;
		for (auto x : pos[i - 1]) {
			r.insert(dp[x]);
		}
		
		int del = 0;
		for (auto x : p) {
			if (a[x] == i - 1) {
				del++;
				r.extract(dp[x]);
				l.insert(dp[x] + del);
			}
			if (a[x] == i) {
				cnt--;
				dp[x] = none + cnt;
				if (!r.empty()) {
					dp[x] = min(dp[x], cnt + del + *r.begin());
				}
				if (!l.empty()) {
					dp[x] = min(dp[x], cnt + *l.begin());
				}
			}
		}

		cnt = pos[i].size();
		for (auto x : pos[i - 1]) {
			none = min(none, dp[x]);
		}
		none += cnt;
	}

	for (auto x : pos[n]) {
		none = min(none, dp[x]);
	}
	cout << none << "\n";
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int T = 1;
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
