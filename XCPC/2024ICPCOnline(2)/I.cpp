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
	array<int, 32> a {};
	for (int i = 0; i < 32; ++i) {
		a[i] = n >> i & 1;
	}
	
	if (a[0] == 0 && a[1] == 0) {
		cout << "NO\n";
		return;
	}

	cout << "YES\n";
	for (int i = 31; i >= 0; --i) {
		if (a[i] != 0) continue;
		int next = -1;
		for (int j = i; j >= 0; --j) {
			if (a[j] == 1) {
				next = j;
				break;
			}
		}
		if (next == -1) {
			assert(i == 0);
		} else {
			a[i] = 1;
			for (int j = i - 1; j >= next; --j) {
				a[j] = -1;
			}
		}
	}

	for (int i = 0; i < 32; i += 8) {
		for (int j = 0; j < 8; ++j) {
			cout << a[i + j] << " \n"[j == 7];
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
