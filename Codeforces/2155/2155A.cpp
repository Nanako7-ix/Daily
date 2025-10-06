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
	int x, y = 0;
	cin >> x;

	int ans = 1;
	while (x != 1 || y != 1) {
		int dx = x / 2;
		int dy = y / 2;
		x = x - dx;
		y = y - dy + dx;
		ans += dx + dy;
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
