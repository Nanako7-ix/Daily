#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 inf = 4E18;

void Thephix() {
	int n;
	string s;
	cin >> n >> s;
	s = '$' + s;
	
	array pos { vector<i64> {0}, vector<i64> {0} };
	for (int i = 1; i <= n; ++i) {
		if (s[i] == 'a') pos[0].push_back(i);
		if (s[i] == 'b') pos[1].push_back(i);
	}
	
	i64 ans = inf;
	
	int x = pos[0].size() - 1;
	for (int i = 1; i <= x; ++i) {
		pos[0][i] += pos[0][i - 1];
	}
	for (i64 i = 0; i <= x; ++i) {
		i64 res = 0;
		res += pos[0][i] - (1 + i) * i / 2;
		res += (n - (x - i) + 1 + n) * (x - i) / 2 - (pos[0][x] - pos[0][i]);
		ans = min(ans, res);
	}

	int y = pos[1].size() - 1;
	for (int i = 1; i <= y; ++i) {
		pos[1][i] += pos[1][i - 1];
	}
	for (i64 i = 0; i <= y; ++i) {
		i64 res = 0;
		res += pos[1][i] - (1 + i) * i / 2;
		res += (n - (y - i) + 1 + n) * (y - i) / 2 - (pos[1][y] - pos[1][i]);
		ans = min(ans, res);
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
