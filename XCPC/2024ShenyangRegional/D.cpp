#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n;
	cin >> n;
	vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; ++i) {
		cin >> b[i];
	}

	vector<int> p(n + 1);
	for (int i = 1; i <= n; ++i) {
		p[a[i]] = b[i];
	}

	int ret = n & 1;
	vector<int> vis(n + 1);
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) continue;
		for (int j = i; !vis[j]; j = p[j]) {
			vis[j] = 1;
		}
		ret ^= 1;
	}

	cout << (ret ? 'A' : 'B');
	for (int i = 1; i < n; ++i) {
		char op; i64 l, r, d;
		cin >> op >> l >> r >> d;
		ret ^= (r - l) * d % 2;
		cout << (ret ? 'A' : 'B');
	}
	cout << '\n';
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int T = 1;
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
