#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	string s;
	cin >> s;

	for (int i = 0; i < (int) s.size(); ++i) {
		if (s[i] == '2') continue;
		s[i] ^= i & 1;
	}

	array<int, 3> cnt {};
	for (auto& ch : s) {
		cnt[ch - '0']++;
	}

	int ans = abs(cnt[0] - cnt[1]);
	if (cnt[2] > ans) {
		cout << (cnt[2] + ans) % 2 << "\n";
	} else {
		cout << ans - cnt[2] << "\n";
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
