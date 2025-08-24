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
	int n, m, q;
	cin >> n >> m >> q;
	vector<array<i64, 2>> a;
	for (int i = 1; i <= n; ++i) {
		int x; cin >> x;
		a.push_back({x, 0});
	}
	for (int i = 1; i <= m; ++i) {
		int x; cin >> x;
		a.push_back({x, 1});
	}

	sort(a.begin(), a.end(), greater {});
	array cnt { vector<int> (n + m + 1), vector<int> (n + m + 1)};
	array sum { vector<i64> (n + m + 1), vector<i64> (n + m + 1)};
	for (int i = 1; i <= n + m; ++i) {
		cnt[0][i] = cnt[0][i - 1], cnt[1][i] = cnt[1][i - 1];
		sum[0][i] = sum[0][i - 1], sum[1][i] = sum[1][i - 1];
		cnt[a[i - 1][1]][i]++;
		sum[a[i - 1][1]][i] += a[i - 1][0];
	}

	for (int i = 1; i <= q; ++i) {
		int x, y, z;
		cin >> x >> y >> z;
		int l = 0, r = z, res = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (cnt[0][mid] <= x && cnt[1][mid] <= y) {
				res = mid, l = mid + 1;
			} else r = mid - 1;
		}
		assert(res != -1);
		i64 ans = sum[0][res] + sum[1][res];
		x -= cnt[0][res], y -= cnt[1][res];
		z -= cnt[0][res] + cnt[1][res];

		if (x == 0) {
			y = min(y, z);
			int p = lower_bound(cnt[1].begin(), cnt[1].end(), cnt[1][res] + y) - cnt[1].begin();
			ans += sum[1][p] - sum[1][res];
		} else {
			x = min(x, z);
			int p = lower_bound(cnt[0].begin(), cnt[0].end(), cnt[0][res] + x) - cnt[0].begin();
			ans += sum[0][p] - sum[0][res];
		}

		cout << ans << "\n";
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