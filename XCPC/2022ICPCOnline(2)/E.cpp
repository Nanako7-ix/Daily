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

	int m = -1;
	for (int i = 2; true; ++i) {
		if (gcd(i, k) == 1) {
			m = i; break;
		}
	}

	i64 ans = k;
	if (m == 2) n--;
	else n -= 2, ans += m;
	cout << ans + (n + 1) / 2 * 2 + n / 2 * 3 << "\n";
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
