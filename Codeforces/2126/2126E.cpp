#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int inf = 1000;

void Thephix() {
	int n;
	cin >> n;
	vector<int> pre(n + 1), suf(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> pre[i];
	}
	for (int i = 1; i <= n; ++i) {
		cin >> suf[i];
	}

	for (int i = 1; i < n; ++i) {
		if (pre[i] % pre[i + 1]) {
			cout << "NO\n";
			return;
		}
	}

	for (int i = n; i > 1; --i) {
		if (suf[i] % suf[i - 1]) {
			cout << "NO\n";
			return;
		}
	}

	vector<int> fac;
	i64 x = pre[1], y = suf[n];
	for (int i = 2; i * i <= x; ++i) {
		if (x % i == 0) {
			fac.push_back(i);
			while (x % i == 0) {
				x /= i;
			}
		}
	}
	if (x != 1) fac.push_back(x);
	for (int i = 2; i * i <= y; ++i) {
		if (y % i == 0) {
			fac.push_back(i);
			while (y % i == 0) {
				y /= i;
			}
		}
	}
	if (y != 1) fac.push_back(y);

	sort(fac.begin(), fac.end());
	fac.erase(unique(fac.begin(), fac.end()), fac.end());

	for (auto x : fac) {
		vector<int> f(n + 2), g(n + 2);
		f[0] = g[n + 1] = inf;
		for (int i = 1, tmp; i <= n; ++i) {
			tmp = pre[i];
			while (tmp % x == 0) {
				f[i]++, tmp /= x;
			}
			tmp = suf[i];
			while (tmp % x == 0) {
				g[i]++, tmp /= x;
			}
		}

		for (int i = 1; i <= n; ++i) {
			if (f[i] < f[i - 1] && f[i] < g[i]) {
				cout << "NO\n";
				return;
			}
			if (g[i] < g[i + 1] && g[i] < f[i]) {
				cout << "NO\n";
				return;
			}
		}
	}

	cout << "YES\n";
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