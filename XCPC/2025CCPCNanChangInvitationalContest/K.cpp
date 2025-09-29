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
	array<vector<int>, 4> pos {};
	array<int, 4> cnt {};
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		pos[a[i] % 4].push_back(i);
		cnt[a[i] % 4]++;
	}	
	
	vector<int> ans;
	int x = min(cnt[1], cnt[3]);
	cnt[1] -= x, cnt[3] -= x;
	for (int i = 1; i <= x; ++i)  {
		ans.push_back(pos[3].back());
		pos[3].pop_back();
		ans.push_back(pos[1].back());
		pos[1].pop_back();
	}

	if (cnt[1] == 0) {
		if (cnt[3] / 2 <= cnt[2] + 1) {
			while (!pos[3].empty()) {
				ans.push_back(pos[3].back()), pos[3].pop_back();
				ans.push_back(pos[3].back()), pos[3].pop_back();
				ans.push_back(pos[2].back()), pos[2].pop_back();
			}
		} else {
			cout << "-1\n";
			return;
		}
	} else if (cnt[3] == 0) {
		if (cnt[1] / 2 <= cnt[2]) {
			while (!pos[1].empty()) {
				ans.push_back(pos[2].back()), pos[2].pop_back();
				ans.push_back(pos[1].back()), pos[1].pop_back();
				ans.push_back(pos[1].back()), pos[1].pop_back();
			}
		} else {
			cout << "-1\n";
			return;
		}
	}

	for (auto x : pos[2]) {
		ans.push_back(x);
	}
	for (auto x : pos[0]) {
		ans.push_back(x);
	}
	for (auto x : ans) {
		cout << x << ' ';
	}
	cout << "\n";
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
