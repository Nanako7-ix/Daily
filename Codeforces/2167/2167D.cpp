#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

array<i64, 56> P { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263	};

void Thephix() {
	int n;
	cin >> n;
	vector<i64> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	for (auto x : P) {
		for (int i = 1; i <= n; ++i) {
			if (gcd(a[i], x) == 1) {
				cout << x << "\n";
				return;
			}
		}
	}
	__gcd(1, 2);
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
