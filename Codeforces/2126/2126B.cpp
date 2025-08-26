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
	int n, k;
	cin >> n >> k;
	int now = 0, ans = 0;
	for (int i = 1; i <= n; ++i) {
		int x; cin >> x;
		if (now == -1) {
			now = 0;
		} else if (x == 0) {
			now++;
		} else {
			now = 0;
		}
		if (now == k) {
			ans++, now = -1;
		}
	}
	cout << ans << "\n";
}

signed main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}