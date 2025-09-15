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

	int lft = 1, rgt = n;
	for (int i = 2; i <= n; ++i) {
		if (a[i] > a[lft]) {
			lft++;
		} else break;
	}
	for (int i = n - 1; i >= 1; --i) {
		if (a[i] > a[rgt]) {
			rgt--;
		} else break;
	}

	auto win = [&](auto&& win, int x, int y) -> bool {
		if (x + 1 == y) return false;
		int Max = max(x >= 1 ? a[x] : 0, y <= n ? a[y] : 0);
		
		int ok = 0;
		if (a[x + 1] > Max && a[y - 1] > Max) {
			ok |= !win(win, x + 1, y);
			ok |= !win(win, x, y - 1);
		} else if (a[x + 1] > Max) {
			ok |= (lft - x) & 1;
		} else if (a[y - 1] > Max) {
			ok |= (y - rgt) & 1;
		}
		return ok;
	};

	if (win(win, 0, n + 1)) {
		cout << "Alice\n";
	} else {
		cout << "Bob\n";
	}
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
