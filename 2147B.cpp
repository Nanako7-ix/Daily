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
	vector<int> a(2 * n + 1);
	for (int i = n, p = 1; i >= 1; --i) {
		while (a[p]) ++p;
		a[p] = i;
		int ok = 0;
		for (int x = p; x <= 2 * n; x += i) {
			if (a[x]) continue;
			a[x] = i, ok = 1;
		}
		assert(ok);
	}
	for (int i = 1; i <= 2 * n; ++i) {
		cout << a[i] << " \n"[i == 2 * n];
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
