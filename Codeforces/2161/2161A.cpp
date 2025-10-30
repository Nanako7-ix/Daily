#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int x, lim, d, n;
	string s;
	cin >> x >> lim >> d >> n >> s;

	int ans = 0;
	for (int i = 0; i < n; ++i) {
		int div = s[i] - '0';
		if (div == 1 || x < lim) {
			ans++;
			x = max(x - d, 0);
		}
	}
	cout << ans << "\n";
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int T = 1;
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
