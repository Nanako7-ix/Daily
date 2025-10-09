#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	cout << "Yes\n";

	int n, m, tot = 0;
	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		vector<int> a(m);
		for (int j = 0; j < m; ++j) {
			a[(i * (m & 1) + j) % m] = ++tot;
		}
		for (int j = 0; j < m; ++j) {
			cout << a[j] << " \n"[j == m - 1];
		}
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
