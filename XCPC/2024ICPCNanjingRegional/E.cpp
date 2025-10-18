#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

constexpr string p = "nanjing";
constexpr int len = p.size();

void Thephix() {
	int n, k;
	cin >> n >> k;

	string s;
	cin >> s;
	s += s;

	if (n < len) {
		cout << "0\n";
		return;
	}

	vector<int> cnt(2 * n + 1);
	for (int i = 0; i <= 2 * n - len; ++i) {
		cnt[i + 1] = cnt[i] + (s.substr(i, len) == p);
	}

	int ans = 0;
	for (int i = 0; i < min(n, k + 1); ++i) {
		ans = max(ans, cnt[i + n - len + 1] - cnt[i]);
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
