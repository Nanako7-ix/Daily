#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	i64 n, k;
	cin >> n >> k;

	i64 x = 1;
	while (true) {
		i64 d = (x + k - 2) / (k - 1);
		if (x + d > n) break;
		i64 t = min((n - x) / d, k - 2 - (x - 1) / d);
		if (t == 0) t = 1;
		x += d * t;
	}
	cout << x << "\n";
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
