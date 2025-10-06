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

	auto query = [&](int x, int y) -> bool {
		cout << x << ' ' << y << endl;
		int ok; cin >> ok;
		return ok;
	};

	for (int d = n - 1; d >= 1; --d) {
		for (int i = 0; i < n; ++i) {
			int u = i + 1;
			int v = (i + d) % n + 1;
			if (query(u, v)) return;
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
