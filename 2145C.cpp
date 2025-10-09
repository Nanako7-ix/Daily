#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n;
	string s;
	cin >> n >> s;

	vector<int> pre(n + 1);
	for (int i = 1; i <= n; ++i) {
		pre[i] = pre[i - 1] + (s[i - 1] == 'a' ? 1 : -1);
	}

	if (pre[n] == 0) {
		cout << "0\n";
		return;
	}

	int ans = n;
	map<int, int> pos;
	pos[0] = 1;
	for (int r = 1; r <= n; ++r) {
		int l = pos[pre[r] - pre[n]];
		if (l != 0) ans = min(ans, r - l + 1);
		pos[pre[r]] = r + 1;
	}

	if (ans == n) ans = -1;
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
