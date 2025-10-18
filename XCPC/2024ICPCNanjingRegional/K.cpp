#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n, m, k, w;
	cin >> n >> m >> k >> w;

	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	
	vector<int> b(m + 3);
	for (int i = 2; i <= m + 1; ++i) {
		cin >> b[i];
	}
	b[1] = 0, b[m + 2] = w + 1;
	
	sort(a.begin() + 1, a.end());
	sort(b.begin() + 1, b.end());
	
	vector<int> ans;
	auto solve = [&](int l, int r) {
		if (l > r) return true;
		int x = lower_bound(a.begin() + 1, a.end(), l) - a.begin();
		int y = upper_bound(a.begin() + 1, a.end(), r) - a.begin() - 1;
		if (x > y) return true;
		vector<int> res;
		for (int i = x; i <= y; ++i) {
			res.push_back(a[i]);
			while (i + 1 <= y && a[i + 1] <= res.back() + k - 1) ++i;
		}
		int len = res.size(), lim = r;
		for (int i = len - 1; i >= 0; --i) {
			if (res[i] + k - 1 > lim) {
				res[i] = lim - k + 1;
				lim = res[i] - 1;
			}
		}
		for (auto x : res) ans.push_back(x);
		return res[0] >= l;
	};
	
	for (int i = 1; i < m + 2; ++i) {
		int l = b[i], r = b[i + 1];
		if (!solve(l + 1, r - 1)) {
			cout << "-1\n";
			return;
		}
	}

	cout << ans.size() << "\n";
	for (int x : ans) cout << x << ' ';
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
