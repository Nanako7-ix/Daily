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
	vector<int> c(m + 1);
	for (int i = 1; i <= m; ++i) {
		cin >> c[i];
	}
	int Min = *min_element(c.begin() + 1, c.end());

	vector<tuple<int, string, int>> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		auto& [w, s, id] = a[i];
		cin >> w >> s;
		id = i;
	}
	sort(a.begin() + 1, a.end(), greater {});

	int now = 0;
	map<string, int> cnt;
	vector<int> ans(n + 1);
	for (int i = 1; i <= n; ++i) {
		auto& [w, s, id] = a[i];
		if (cnt[s] < Min) {
			now++, cnt[s]++;
		}
		ans[id] = now;
	}
	for (int i = 1; i <= n; ++i) {
		cout << ans[i] << "\n";
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
