#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n, m, k;
	cin >> n >> m >> k;
	m *= k;

	vector<string> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		a[i] = '$' + a[i];
	}

	map<string, int> cnt;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; j += k) {
			cnt[a[i].substr(j, k)]++;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1, x = 1; j <= m; ++x, j += k) {
			if (cnt[a[i].substr(j, k)] == 1) {
				cout << i << ' ' << x << "\n";
				return;
			}
		}
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
