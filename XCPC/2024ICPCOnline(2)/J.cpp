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
	i64 ans = 0;
	vector<array<i64, 2>> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		i64 w, v, c;
		cin >> w >> v >> c;
		ans += v;
		a[i] = { w, c };
	}
	sort(a.begin() + 1, a.end(), [](array<i64, 2> x, array<i64, 2> y) {
		return x[0] * y[1] > y[0] * x[1];
	});
	
	vector<i64> suf(n + 2);
	for (int i = n; i >= 1; --i) {
		suf[i] = suf[i + 1] + a[i][1];
	}
	for (int i = 1; i <= n; ++i) {
		ans -= a[i][0] * suf[i + 1];
	}
	cout << ans << "\n";
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
