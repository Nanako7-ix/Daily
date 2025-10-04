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
		cin >> a[i];
	}

	i64 sum = 1, cnt = 1, f = 0;
	for (int i = 1; i <= n; ++i) {
		int x = a[i];
		if (x == 1) {
			sum++, cnt++;
		} else if (x == -1) {
			if (cnt >= 2) {
				cnt--;
			} else if (f > 0) {
				sum++, cnt++, f--;
			} else {
				cout << "-1\n";
				return;
			}
		} else {
			if (cnt >= 2) {
				cnt--, f++;
			} else cnt++, sum++;
		}
	}

	int g = gcd(sum, cnt);
	cout << sum / g << ' ' << cnt / g << "\n";
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
