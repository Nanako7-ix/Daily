#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

i64 pow_3(int k) {
	i64 res = 1;
	while (k--) res *= 3;
	return res;
}

void Thephix() {
	int n, k;
	cin >> n >> k;
	vector<int> dig;
	while (n) {
		dig.push_back(n % 3);
		n /= 3;
	}

	k -= accumulate(dig.begin(), dig.end(), 0);
	if (k < 0) {
		cout << "-1\n";
		return;
	}

	int m = dig.size() - 1;
	i64 ans = dig[0] * 3;
	for (int i = 1; i <= m; ++i) {
		ans += dig[i] * (pow_3(i + 1) + i * pow_3(i - 1));
	}

	for (int i = m; k >= 2 && i >= 1; --i) {
		int x = min(k / 2, dig[i]);
		k -= 2 * x;
		dig[i - 1] += 3 * x;
		ans -= pow_3(i - 1) * x;
	}
	cout << ans << "\n";
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