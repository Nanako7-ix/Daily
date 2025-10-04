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
	i64 k, s;
	cin >> n >> k >> s;

	vector<i64> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	int cnt = 0;
	for (int i = 0; i <= n; ++i) {
		cnt += a[i] >= k;
	}

	i64 ans = 0, sum = 0;
	for (int l = 1, r = 0; l <= n; sum -= a[l++]) {
		while (r < n && (r < l || sum < s)) {
			cnt -= a[r] >= k;
			++r;
			sum += a[r];
		}
		if (sum >= s && a[l] >= k) ans += cnt;
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
