#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

int rk(char ch) {
	if (ch == 'D') return 0;
	if (ch == 'C') return 1;
	if (ch == 'H') return 2;
	if (ch == 'S') return 3;
	__builtin_unreachable();
}

const array f = {
	vector<array<int, 3>> {
		{ 0, 0, 0 }
	},

	vector<array<int, 3>> {
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
	},

	vector<array<int, 3>> {
		{ 2, 0, 0 },
		{ 0, 2, 0 },
		{ 0, 0, 2 },
		{ 1, 1, 0 },
		{ 1, 0, 1 },
		{ 0, 1, 1 },
	},

	vector<array<int, 3>> {
		{ 3, 0, 0 },
		{ 0, 3, 0 },
		{ 0, 0, 3 },
		{ 2, 1, 0 },
		{ 1, 2, 0 },
		{ 2, 0, 1 },
		{ 1, 0, 2 },
		{ 0, 2, 1 },
		{ 0, 1, 2 },
		{ 1, 1, 1 },
	},
};

void Thephix() {
	int n;
	cin >> n;

	array<int, 4> cnt {};
	for (int i = 1; i <= n; ++i) {
		string s;
		cin >> s;
		cnt[rk(s[1])]++;
	}
	
	array<int, 6> exist {};
	for (int i = 0; i < 6; ++i) {
		cin >> exist[i];
	}	

	int ans = 0;
	array<int, 4> del { 0, 0, 0, 0 };
	[&](this auto&& dfs, int p) -> void {
		if (p == 6) {
			int res = 0;
			for (int i = 0; i < 4; ++i) {
				res += cnt[i] / 5;
			}
			ans = max(ans, res);
			return;
		}

		// 什么都不做
		dfs(p + 1);
		if (exist[p] == 0) return;

		// 做些什么
		if (p < 4) {
			for (int i = del[p] + 1; i <= 3; ++i) {
				for (auto& g : f[i]) {
					int ok = 1;
					for (int j = 0, k = 0; j < 4; ++j) {
						if (j == p) continue;
						if (cnt[j] < g[k]) {
							ok = 0; break;
						}
						k++;
					}
					if (ok == 0) continue;

					for (int j = 0, k = 0; j < 4; ++j) {
						if (j == p) continue;
						del[j] += g[k];
						cnt[j] -= g[k];
						k++;
					}
					cnt[p] += i;

					dfs(p + 1);

					for (int j = 0, k = 0; j < 4; ++j) {
						if (j == p) continue;
						del[j] -= g[k];
						cnt[j] += g[k];
						k++;
					}
					cnt[p] -= i;
				}
			}
		} else {
			for (int i = 0; i < 4; ++i) {
				if (cnt[i] == 0) continue;
				for (int j = 0; j < 4; ++j) {
					if (i == j || del[j]) continue;
					cnt[i]--, cnt[j]++, del[i]++;
					dfs(p + 1);
					cnt[i]++, cnt[j]--, del[i]--;
				}
			}
		}
	} (0);

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
