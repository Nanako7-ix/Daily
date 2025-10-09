#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n, m;
	cin >> n >> m;
	vector<int> a(n), b(m);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	for (int i = 0; i < m; ++i) {
		cin >> b[i];
	}

	sort(a.begin(), a.end(), greater());
	sort(b.begin(), b.end(), greater());

	int cnt = a.back() == 1;
	for (int i = 0; i < n; ++i) {
		cnt += a[i] > 1;
		a[i]--;
	}

	for (int k = 0; !b.empty(); ++k) {
		if (!a.empty() && a.back() <= k) {
			a.pop_back();
		} else {
			int x = max(b.back() - k, 0);
			b.pop_back();
			if ((cnt -= x) < 0) {
				cout << "NO\n";
				return;
			}
		}
	}

	cout << "YES\n";
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
