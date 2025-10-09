#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n, k;
	string s;
	cin >> n >> k >> s;

	if (n == k) {
		cout << string(n, '-') << "\n";
		return;
	}

	array<int, 3> cnt {};
	for (auto& ch : s) {
		cnt[ch - '0']++;
	}

	vector<char> ans(n + 1, '+');
	for (int i = 1; i <= cnt[0]; ++i) {
		ans[i] = '-';
	}
	for (int i = 1; i <= cnt[1]; ++i) {
		ans[n - i + 1] = '-';
	}
	for (int i = 1; i <= cnt[2]; ++i) {
		ans[i + cnt[0]] = '?';
		ans[n - cnt[1] + 1 - i] = '?';
	}

	for (int i = 1; i <= n; ++i) {
		cout << ans[i];
	}
	cout << "\n";
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
