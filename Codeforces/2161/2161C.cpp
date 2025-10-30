#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	i64 n, x;
	cin >> n >> x;
	vector<i64> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	sort(a.begin() + 1, a.end());

	i64 ans = 0;
	vector<i64> res;
	for (i64 l = 1, r = n, now = 0; l <= r; ) {
		if (a[r] >= x - now) {
			ans += a[r];
			res.push_back(a[r--]);
		} else {
			res.push_back(a[l++]);
		}
		now = (now + res.back()) % x;
	}

	cout << ans << "\n";
	for (auto x : res) {
		cout << x << " ";
	}
	cout << "\n";
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
