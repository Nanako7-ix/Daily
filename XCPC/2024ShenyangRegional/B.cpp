#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	i64 n, m;
	cin >> n >> m;

	if (n == 1 && m == 1) {
		cout << "Yes\n0\n0\n";
		return;
	}

	if (std::gcd(n, m) != 1) {
		cout << "No\n";
		return;
	}

	cout << "Yes\n";
	for (int i = 0; i < n; ++i) {
		cout << (i * m + 1) % (n * m) << " \n"[i == n - 1];
	}
	for (int i = 0; i < m; ++i) {
		cout << (i * n + 1) % (n * m) << " \n"[i == m - 1];
	}
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
