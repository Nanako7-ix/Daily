#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int N = 5, V = 6;
int   vis[7][7][7][7][7][3][32];
double dp[7][7][7][7][7][3][32];

void Thephix() {
	vector<int> val(V + 1);
	for (int i = 1; i <= V; ++i) {
		cin >> val[i];
	}
	
	auto dfs = [&](auto dfs, array<int, 5> a, int p, int s) -> double {
		array<array<int, 2>, 5> tmp;
		tmp[0] =	{ a[0], s >> 0 & 1 };
		tmp[1] =	{ a[1], s >> 1 & 1 };
		tmp[2] =	{ a[2], s >> 2 & 1 };
		tmp[3] =	{ a[3], s >> 3 & 1 };
		tmp[4] =	{ a[4], s >> 4 & 1 };
		sort(tmp.begin(), tmp.end());
		s = 0;
		a[0] = tmp[0][0], s |= tmp[0][1] << 0;
		a[1] = tmp[1][0], s |= tmp[1][1] << 1;
		a[2] = tmp[2][0], s |= tmp[2][1] << 2;
		a[3] = tmp[3][0], s |= tmp[3][1] << 3;
		a[4] = tmp[4][0], s |= tmp[4][1] << 4;
	
		if (!vis[a[0]][a[1]][a[2]][a[3]][a[4]][p][s]) {
			   vis[a[0]][a[1]][a[2]][a[3]][a[4]][p][s] = 1;
			double& ans = dp[a[0]][a[1]][a[2]][a[3]][a[4]][p][s];
			if (p == 0) {
				for (int i = 1; i <= V; ++i) {
					double res = 0;
					for (int j = 0; j < N; ++j)
						res += (val[a[j]] == val[i]) * val[i];
					ans = max(res, ans);
				}
			} else {
				for (int t = 0; t < 32; ++t) {
					if ((t & s) != t) continue;
					double res = 0;
					int cnt = 0;
					for (int a0 = 1; a0 <= V; ++a0) if ((t >> 0 & 1) || a[0] == a0)
					for (int a1 = 1; a1 <= V; ++a1) if ((t >> 1 & 1) || a[1] == a1)
					for (int a2 = 1; a2 <= V; ++a2) if ((t >> 2 & 1) || a[2] == a2)
					for (int a3 = 1; a3 <= V; ++a3) if ((t >> 3 & 1) || a[3] == a3)
					for (int a4 = 1; a4 <= V; ++a4) if ((t >> 4 & 1) || a[4] == a4)
					{
						cnt++;
						res += dfs(dfs, array<int, 5> { a0, a1, a2, a3, a4 }, p - 1, t);
					}
					ans = max(ans, res / cnt);
				}
			}
		}
		return dp[a[0]][a[1]][a[2]][a[3]][a[4]][p][s];
	};

	double ans = 0;
	int cnt = 0;
	for (int a0 = 1; a0 <= V; ++a0)
	for (int a1 = 1; a1 <= V; ++a1)
	for (int a2 = 1; a2 <= V; ++a2)
	for (int a3 = 1; a3 <= V; ++a3)
	for (int a4 = 1; a4 <= V; ++a4)
	{
		cnt++;
		double res = dfs(dfs, array<int, 5> { a0, a1, a2, a3, a4 }, 2, 31);
		ans += res;
	}
	
	cout << fixed << setprecision(20) << ans / cnt << "\n";
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