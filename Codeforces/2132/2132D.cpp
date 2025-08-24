#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

i64 cnt(i64 n) {
	i64 m = n, len = 0;
	while (m) len++, m /= 10;
	i64 ans = 0, pow = 1;
	for (i64 i = 1; i <= len; ++i, pow *= 10) {
		if (i == len) {
			ans += i * (n - pow + 1);
		} else {
			ans += i * (pow * 9);
		}
	}
	return ans;
}

i64 sum(i64 n) {
	vector<int> dig;
	while (n) {
		dig.push_back(n % 10);
		n /= 10;
	}
	reverse(dig.begin(), dig.end());
	
	int len = dig.size();
	vector  dp(len, vector (2, vector<i64> (len * 9)));
	vector vis(len, vector (2, vector<int> (len * 9)));
	return [&](this auto&& jxt, int u, bool lim, int sum) -> i64 {
		if (u == len) return sum;
		if (!vis[u][lim][sum]) {
			vis[u][lim][sum] = 1;
			int r = lim ? dig[u] : 9;
			for (int i = 0; i <= r; ++i) {
				dp[u][lim][sum] += jxt (
					u + 1,
					lim && i == r,
					sum + i
				);
			}
		}
		return dp[u][lim][sum];
	} (0, 1, 0);
}

void Thephix() {
	i64 n;
	cin >> n;
	
	i64 l = 1, r = n, res = -1;
	while (l <= r) {
		i64 m = (l + r) >> 1;
		if (cnt(m) <= n) {
			res = m, l = m + 1;
		} else r = m - 1;
	}
	assert(res != -1);
	
	n -= cnt(res);

	i64 rest = res + 1;
	vector<int> dig;
	while (rest) {
		dig.push_back(rest % 10);
		rest /= 10;
	}
	
	i64 ans = 0;
	while (n) {
		ans += dig.back();
		dig.pop_back(), n--;
	}
	
	cout << ans + sum(res) << "\n";
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