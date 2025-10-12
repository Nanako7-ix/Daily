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
	vector<i64> a(n + 1);
	a[0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < i; ++j) {
			i64 x = a[j];
			while (x) {
				a[i] += x % 10;
				x /= 10;
			}
		}
	}
	cout << a[n] << "\n";
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
