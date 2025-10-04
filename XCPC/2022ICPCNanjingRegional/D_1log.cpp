#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 inf = 1E15;

void Thephix() {
	int n, k, m;
	i64 a1, d;
	cin >> n >> k >> m >> a1 >> d;

	vector<i64> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	auto check = [&](i64 x) -> bool {
		vector<int> f(n + 2);

		for (int i = 1; i <= n; ++i) {
			if (a[i] >= x) {
				f[1]++;
			} else if (a[i] + a1 + (min(m, i) - 1) * d >= x) {
				f[max(1, i - m + 1)]++;
				f[clamp<i64>(i - (d == 0 ? 0 : (x - a[i] - a1 + d - 1) / d), max(1, i - m + 1), i) + 1]--;
			}
		}
		
		for (int i = 1; i <= n - m + 1; ++i) {
			f[i] += f[i - 1];
			if (f[i] >= k) return true;
		}
		return false;
	};

	i64 l = 0, r = inf, ans = -1;
	while (l <= r) {
		i64 m = (l + r) >> 1;
		if (check(m)) {
			ans = m, l = m + 1;
		} else r = m - 1;
	}

	assert(ans != -1);
	cout << ans << "\n";
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
