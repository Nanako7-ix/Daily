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
	int n, m;
	cin >> n >> m;
	vector<array<i64, 2>> a(n + 1);
	a[1] = { 1, 1 };
	for (int i = 2; i <= n; ++i) {
		i64 x = n - m, y = n - 1 + (i - 2) * (m - 1);
		a[i] = { x / gcd(x, y), y / gcd(x, y) };
	}
	
	reverse(a.begin() + 1, a.end());
	for (int i = 1; i <= n; ++i) {
		auto& [x, y] = a[i];
		cout << x << ' ' << y << "\n";
	}
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
