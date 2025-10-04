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
	int n, m, k;
	string s;
	cin >> n >> m >> k >> s;

	int N = 2 * n, M = 2 * m;
	vector<vector<int>> pre(N + 1, vector<int> (M + 1));
	pre[1 + n][1 + m] = 1;
	
	int len = s.size();
	int xL = 1, yL = 1, xR = n, yR = m;
	for (int i = 0, x = 1, y = 1; i < len; ++i) {
		if (s[i] == 'U') x++;
		if (s[i] == 'D') x--;
		if (s[i] == 'L') y++;
		if (s[i] == 'R') y--;
		if (x + n >= 1 && x + n <= N && y + m >= 1 && y + m <= M) {
			pre[x + n][y + m] = 1;
		}
		xL = max(xL, x), xR = min(xR, x + n - 1);
		yL = max(yL, y), yR = min(yR, y + m - 1);
	}

	if (xL > xR || yL > yR) {
		if (k == 0) {
			cout << n * m << '\n';
		} else cout << "0\n";
		return;
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			pre[i][j] += pre[i - 1][j];
			pre[i][j] += pre[i][j - 1];
			pre[i][j] -= pre[i - 1][j - 1];
		}
	}

	auto query = [&](int xl, int yl, int xr, int yr) -> int {
		xl += n, yl += m, xr += n, yr += m;
		return pre[xr][yr] - pre[xl - 1][yr] - pre[xr][yl - 1] + pre[xl - 1][yl - 1];
	};

	int ans = 0;
	int need = (xR - xL + 1) * (yR - yL + 1) - k;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (query(xL - i + 1, yL - j + 1, xR - i + 1, yR - j + 1) == need) {
				ans++;
			}
		}
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
