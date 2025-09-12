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
	int n, m;
	cin >> n >> m;
	vector<string> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	int ans = 0;
	for (int x1 = 0; x1 < n - 1; ++x1) {
		for (int y1 = 0; y1 < m - 1; ++y1) {
			int x2 = x1 + 1;
			int y2 = y1 + 1;
			ans += a[x1][y1] == 'c' && a[x1][y2] == 'c' && a[x2][y1] == 'p' && a[x2][y2] == 'c';
		}
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
