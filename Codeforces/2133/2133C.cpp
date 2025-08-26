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
	int n;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cout << "? " << i << " " << n << " ";
		for (int j = 1; j <= n; ++j) {
			cout << j << " ";
		}
		cout << endl;
		cin >> a[i];
	}
	int m = *max_element(a.begin() + 1, a.end());
	vector<int> ans;
	vector<vector<int>> p(m + 1);
	for (int i = 1; i <= n; ++i) {
		p[a[i]].push_back(i);
	}

	int u = p[m][0];
	ans.push_back(u);
	while (a[u] != 1) {
		for (int v : p[a[u] - 1]) {
			cout << "? " << u << " 2 " << u << ' ' << v << endl;
			int len; cin >> len;
			if (len == 2) {
				ans.push_back(u = v);
				break;
			}
		}
	}
	cout << "! " << m << ' ';
	for (auto x : ans) {
		cout << x << ' ';
	}
	cout << endl;
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