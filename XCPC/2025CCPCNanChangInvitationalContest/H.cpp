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
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	vector<i64> f(n + 1);
	for (int i = 1; i <= n; ++i) {
		f[i] = a[i] - i;
		if (f[i] < 0) {
			cout << "-1\n";
			return;
		}
	}

	for (int i = n - 1; i >= 1; --i) {
		f[i] = min(f[i + 1], f[i]);
	}
	
	i64 sum = 0, p = 0;
	for (int i = 1; i <= n; ++i) {
		i64 x = min({ sum, f[i] - (p + 1 - i) });
		sum -= x, p += x + 1;
		assert(p <= a[i]);
		sum += a[i] - p;
	}

	cout << p + sum << "\n";
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
