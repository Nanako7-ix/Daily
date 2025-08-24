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
	i64 n;
	cin >> n;
	vector<i64> ans;
	for (i128 i = 10; i <= n; i *= 10) {
		if (n % (i + 1) == 0) {
			ans.push_back(n / (i + 1));
		}
	}
	int m = ans.size();
	cout << m << "\n";
	for (int i = m; i >= 1; --i) {
		cout << ans[i - 1] << " \n"[i == 1];
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