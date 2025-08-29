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
	vector<i64> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	// 我现在让它是 (k + 1) 的倍数，那么 +k 一次就是 val--
	// 极限情况是 k 次
	for (int i = 1; i <= n; ++i) {
		a[i] += a[i] % (k + 1) * k;
	}
	for (int i = 1; i <= n; ++i) {
		cout << a[i] << " \n"[i == n];
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