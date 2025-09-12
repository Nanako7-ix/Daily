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
	string s;
	cin >> n >> k >> s;
	int ans = 0, sum = 0;
	for (int i = 0; i < n; ++i) {
		if (s[i] == '1') {
			sum++;
		} else sum = 0;
		ans = max(ans, sum);
	}
	if (ans >= k) {
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
	for (int i = 0, l = 1, r = n; i < n; ++i) {
		if (s[i] == '0') {
			cout << r-- << " \n"[i == n - 1];
		} else cout << l++ << " \n"[i == n - 1];
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