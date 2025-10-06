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
	vector<int> f(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> f[i];
		f[i] -= 1;
	}

	cout << 
	[&]() -> bool {
		vector<char> a(n + 1);
		a[1] = 'L';
		int cnt = 0;
		for (int i = 2; i <= n; ++i) {
			int d = f[i] - f[i - 1];
			if (d == 1) {
				if (a[i - 1] != 'L') return false;
				a[i] = 'L';
			} else if (d == -1) {
				if (a[i - 1] != 'R') return false;
				a[i] = 'R';
			} else if (d == 0) {
				a[i] = a[i - 1] ^ ('L' ^ 'R');
			} else {
				return false;
			}
			cnt += a[i] == 'R';
		}
		return f[1] == cnt;
	} () +
	[&]() -> bool {
		vector<char> a(n + 1);
		a[1] = 'R';
		int cnt = 0;
		for (int i = 2; i <= n; ++i) {
			int d = f[i] - f[i - 1];
			if (d == 1) {
				if (a[i - 1] != 'L') return false;
				a[i] = 'L';
			} else if (d == -1) {
				if (a[i - 1] != 'R') return false;
				a[i] = 'R';
			} else if (d == 0) {
				a[i] = a[i - 1] ^ ('L' ^ 'R');
			} else {
				return false;
			}
			cnt += a[i] == 'R';
		}
		return f[1] == cnt;
	} ()
	<< "\n";
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
