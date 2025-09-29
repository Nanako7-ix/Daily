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
	int n, k, L, R;
	cin >> n >> k >> L >> R;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	i64 ans = 0;
	map<int, int> S, T;
	for (int l = 1, rs = 0, rt = 0; l <= n; ++l) {
		while (rs < n && (int) S.size()  < k) {
			S[a[++rs]]++;
		}
		while (rt < n && (int) T.size() <= k) {
			T[a[++rt]]++;
		}

		if ((int) S.size() != k) break;
		if ((int) T.size() != k + 1) rt = n + 1;

		int x = max(l + L - 1, rs);
		int y = min(l + R - 1, rt - 1);
		ans += max(y - x + 1, 0);

		if (--S[a[l]] == 0) S.erase(a[l]);
		if (--T[a[l]] == 0) T.erase(a[l]);
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
