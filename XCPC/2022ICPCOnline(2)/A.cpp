#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

int power(int a, int b, int p) {
	int res = 1;
	for (a %= p; b; b >>= 1, a = a * a % p) {
		if (b & 1) res = res * a % p;
	}
	return res;
}

void Thephix() {
	int n, m;
	cin >> n;
	m = min(100, n);
	vector<vector<i64>> f(m + 1);
	for (int i = 1; i <= m; ++i) {
		f[i].assign(i + 1, 0);
		for (int j = 1; j <= i; ++j) {
			cin >> f[i][j];
		}
	}

	int q;
	cin >> q;
	while (q--) {
		int p;
		cin >> p;
		i64 ans = 0;
		if (n <= 100) {
			auto& a = f[m];
			for (int i = 1; i <= m; ++i) {
				ans += a[i] * power(10, n - i, p) % p;
				ans %= p;
			}
		} else {
			auto& a = f[p - 1];
			for (int i = 1; i <= p - 1; ++i) {
				ans += a[i] * power(10, (n - i) % (p - 1), p);
				ans %= p;
			}
		}
		cout << ans << '\n';
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
