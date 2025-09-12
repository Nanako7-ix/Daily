#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

array<vector<int>, 16> ans;

void Thephix() {
	i64 x, y;
	cin >> x >> y;
	
	for (int i = 1; i <= 15; ++i) {
		auto it = lower_bound(ans[i].begin(), ans[i].end(), x);
		if (it != ans[i].end() && *it <= y) {
			cout << *it << "\n";
			return;
		}
	}

	cout << "-1\n";
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	cin >> T;

	constexpr int N = 1E9;
	for (int i = 1; i <= 15; ++i) {
		auto dfs = [&](auto&& dfs, int len, int pc, int now) {
			if (len == -1) {
				if (pc != 0) return;
				i64 val = (now << 1 | 1) << i;
				if (val <= N) {
					ans[i].push_back(val);
				}
				return;
			}
			for (int i = 0; i <= (pc != 0); ++i) {
				dfs(dfs, len - 1, pc - i, now << 1 | i);
			}
		}; dfs(dfs, 30 - (i + 1), i - 1, 0);
	}

	while (T--) {
		Thephix();
	}

	return 0;
}
