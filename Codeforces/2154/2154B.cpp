#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

constexpr i64 inf = 1E18;

void Thephix() {
	int n;
	cin >> n;
	vector<i64> a(n + 2);
	i64 Max = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		Max = max(Max, a[i]);
		if (i % 2 == 0) a[i] = Max;
	}

	a[0] = a[n + 1] = inf;
	
	i64 ans = 0;
	for (int i = 1; i <= n; i += 2) {
		ans += max(a[i] - min(a[i - 1], a[i + 1]) + 1, 0LL);
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
