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
	i64 k, x;
	cin >> k >> x;
	vector<int> ans;
	[&](this auto&& f, i64 x, i64 y) {
		if (x == y) return;
		if (x < y) {
			ans.push_back(1);
			f(2 * x, y - x);
		} else {
			ans.push_back(2);
			f(x - y, 2 * y);
		}
	} (x, (1LL << (k + 1)) - x);

	cout << ans.size() << "\n";
	for (int i = ans.size() - 1; i >= 0; --i) {
		cout << ans[i] << " \n"[i == 0];
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
