#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 Mod = 998244353;

void Thephix() {
	int n;
	cin >> n;
	vector<int> a(n + 1);
	map<int, int> cnt;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		cnt[a[i]]++;
	}
	sort(a.begin() + 1, a.end());
	
	array<i64, 2> ans { 0, 1 + (a[1] != a[n]) };
	for (int i = 1; i <= n; ++i) {
		(ans[1] *= cnt[a[i]]--) %= Mod;
		for (int j = 1; j < i; ++j) {
			ans[0] += a[i] - a[j];
		}
	}
	cout << ans[0] << ' ' << ans[1] % Mod << "\n";
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
