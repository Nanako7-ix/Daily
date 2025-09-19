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

	for (int l = 2; l < n; ++l) {
		for (int r = l + 1; r <= n; ++r) {
			int s1 = accumulate(a.begin() + 1, a.begin() + l, 0LL) % 3;
			int s2 = accumulate(a.begin() + l, a.begin() + r, 0LL) % 3;
			int s3 = accumulate(a.begin() + r, a.end(), 0LL) % 3;
			if (s1 == s2 && s2 == s3) {
				cout << l - 1 << ' ' << r - 1 << "\n";
				return;
			} else if (s1 != s2 && s2 != s3 && s1 != s3) {
				cout << l - 1 << ' ' << r - 1 << "\n";
				return;
			}
		}
	}
	cout << "0 0\n";
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
