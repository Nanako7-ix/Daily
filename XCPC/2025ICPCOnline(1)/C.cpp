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
	int m, n;
	cin >> m >> n;
	map<int, vector<int>> a;
	for (int i = 1; i <= m; ++i) {
		int l, r;
		cin >> l >> r;
		a[l].push_back(r - 1);
	}

	int ans = n;
	priority_queue<int, vector<int>, greater<int>> q;
	auto it = a.begin();
	for (int i = 1; i < n; q.pop()) {
		if (q.empty() || (it != a.end() && it -> first == i)) {
			if (it == a.end()) break;
			auto& [l, pos] = *it;
			i = max(i, l);
			for (auto r : pos) q.push(r);
			it++;
		}
		if (i <= q.top()) ans--, i++;
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
