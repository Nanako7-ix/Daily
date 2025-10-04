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
	int n, q;
	cin >> n >> q;
	vector<int> a(n + 1), d(n + 1);
	vector<array<int, 2>> cnt(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		d[i] = d[i - 1] + (a[i] == a[i - 1]);
		cnt[i] = cnt[i - 1];
		cnt[i][a[i]]++;
	}

	while (q--) {
		int l, r;
		cin >> l >> r;
		if ((cnt[r][0] - cnt[l - 1][0]) % 3 != 0) {
			cout << "-1\n";
			continue;
		}
		if ((cnt[r][1] - cnt[l - 1][1]) % 3 != 0) {
			cout << "-1\n";
			continue;
		}
		int ans = 0;
		ans += ((cnt[r][0] - cnt[l - 1][0])) / 3;
		ans += (cnt[r][1] - cnt[l - 1][1]) / 3;
		if (d[r] == d[l]) ans++;
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
