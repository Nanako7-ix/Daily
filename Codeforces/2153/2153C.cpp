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
	map<i64, int> cnt;
	for (int i = 1; i <= n; ++i) {
		int x; cin >> x;
		cnt[x]++;
	}
	
	vector<i64> a { 0, 0 };
	i64 len = 0, f = 0;
	for (auto& [x, y] : cnt) {
		if (y % 2 == 1) {
			y--, a.push_back(x);
		}
		f += y / 2;
		len += 1LL * x * y;
	}
	
	if (len == 0) {
		cout << "0\n";
		return;
	}

	sort(a.begin(), a.end());
	int sz = a.size();
	i64 ans = 0;
	for (int i = f == 1, j = 0; i < sz; ++i) {
		while (j + 1 < sz && a[j + 1] - a[i] < len) {
			++j;
		}
		if (i != j) ans = max(ans, len + a[i] + a[j]);
	}
	cout << ans << "\n";
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
