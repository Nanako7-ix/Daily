#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n, k;
	string s;
	cin >> n >> k >> s;
	s = ' ' + s;

	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (s[i] == '0') continue;
		int ok = 0;
		for (int j = max(1, i - k + 1); j < i; ++j) {
			if (s[j] == '1') {
				ok = 1;
				break;
			}
		}
		ans += ok == 0;
	}
	cout << ans << "\n";
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
