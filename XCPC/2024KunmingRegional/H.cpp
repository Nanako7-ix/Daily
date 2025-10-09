#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr double pi = numbers::pi_v<double>;

void Thephix() {
	int n, k;
	cin >> n >> k;
	vector<double> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		int x, y;
		cin >> x >> y;
		a[i] = atan2(y, x);
	}

	sort(a.begin() + 1, a.end());
	for (int i = 1; i <= n; ++i) {
		a.push_back(2 * pi + a[i]);
	}

	double ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans = max(ans, a[i + k] - a[i]);
	}
	cout << ans << "\n";
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);
	cout << fixed << setprecision(20);

	int T = 1;
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
