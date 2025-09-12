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
	vector<i64> a(n + 1);
	i64 now = 1500;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		now += a[i];
		if (now >= 4000) {
			cout << i << "\n";
			return;
		}
	}
	cout << "-1\n";
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
