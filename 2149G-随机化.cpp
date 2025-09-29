#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void Thephix() {
	int n, q;
	cin >> n >> q;
	vector<int> a(n + 1), x;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		x.push_back(a[i]);
	}

	sort(x.begin(), x.end());
	x.erase(unique(x.begin(), x.end()), x.end());

	int m = x.size();
	vector<vector<int>> p(m + 1);
	for (int i = 1; i <= n; ++i) {
		a[i] = lower_bound(x.begin(), x.end(), a[i]) - x.begin() + 1;
		p[a[i]].push_back(i);
	}
	
	while (q--) {
		int l, r;
		cin >> l >> r;
		set<int> S;
		for (int i = 1; i <= 64; ++i) {
			S.insert(a[(std::uniform_int_distribution(l, r)(rng))]);
		}
		int ok = 0;
		for (auto i : S) {
			if (upper_bound(p[i].begin(), p[i].end(), r) - lower_bound(p[i].begin(), p[i].end(), l) >= (r - l + 1) / 3 + 1) {
				cout << x[i - 1] << ' ';
				ok = 1;
			}
		}
		if (!ok) cout << -1;
		cout << "\n";
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
