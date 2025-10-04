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
	int n, k;
	cin >> n >> k;
	n += 2;

	vector<int> a(n + 1);
	for (int i = 2; i < n; ++i) {
		cin >> a[i];
	}

	string s;
	cin >> s;
	s = "$1" + s + "1";

	vector<int> pos;
	for (int i = 1; i <= n; ++i) {
		if (s[i] == '1') pos.push_back(i);
	}

	vector<i64> pre = [&]() -> vector<i64> {
		vector<i64> dp(n + 1);
		deque<int> que;
		dp[1] = a[1];
		que.push_back(1);
		for (int i = 2; i <= n; ++i) {
			if (i - que.front() > k) que.pop_front();
			dp[i] = dp[que.front()] + a[i];
			if (s[i] == '1') que.clear();
			else while (!que.empty() && dp[i] <= dp[que.back()]) {
				que.pop_back();
			}
			que.push_back(i);
		}
		return dp;
	} ();

	vector<i64> suf = [&]() -> vector<i64> {
		vector<i64> dp(n + 1);
		deque<int> que;
		dp[n] = a[n];
		que.push_back(n);
		for (int i = n - 1; i >= 1; --i) {
			if (que.front() - i > k) que.pop_front();
			dp[i] = dp[que.front()] + a[i];
			if (s[i] == '1') que.clear();
			else while (!que.empty() && dp[i] <= dp[que.back()]) {
				que.pop_back();
			}
			que.push_back(i);
		}
		return dp;
	} ();

	i64 ans = pre[n];
	
	int q; cin >> q;
	while (q--) {
		int p, v;
		cin >> p >> v;
		p++;
		if (s[p] == '1') {
			cout << ans + v - a[p] << "\n";
			continue;
		}

		auto it = lower_bound(pos.begin(), pos.end(), p);
		int l = *prev(it), r = *it;

		i64 ans = inf;

		// 考虑新的选择中，带有 a[p]
		i64 min_pre = inf, min_suf = inf;
		for (int i = max(l, p - k); i < p; ++i) {
			min_pre = min(min_pre, pre[i]);
		}
		for (int i = min(r, p + k); i > p; --i) {
			min_suf = min(min_suf, suf[i]);
		}
		ans = min(ans, min_pre + v + min_suf);

		// 考虑新的选择中，不带有 a[p]
		i64 Min = inf;
		for (int i = max(l, p + 1 - k), j = p; i < p; ++i) {
			while (j + 1 <= r && j - i < k) {
				Min = min(Min, suf[++j]);
			}
			ans = min(ans, pre[i] + Min);
		}

		cout << ans << "\n";
	}
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
