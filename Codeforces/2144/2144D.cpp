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
	int n; i64 c;
	cin >> n >> c;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	sort(a.begin() + 1, a.end());

	int m = a[n];
	vector<int> pre(m + 1);
	for (int i = 1; i <= n; ++i) {
		pre[a[i]]++;
	}
	for (int i = 1; i <= m; ++i) {
		pre[i] += pre[i - 1];
	}

	i64 ans = -n * c;
	for (int i = 2; i <= m + 1; ++i) {
		i64 sum = -n * c;
		for (i64 k = 1; i * (k - 1) + 1 <= m; ++k) {
			int l = i * (k - 1) + 1, r = min<i64>(i * k, m);
			sum += (pre[r] - pre[l - 1]) * k;
			sum += c * min((pre[k] - pre[k - 1]), pre[r] - pre[l - 1]);
		}
		ans = max(ans, sum);
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
