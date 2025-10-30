#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n;
	cin >> n;
	array<int, 2> cnt {};
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		cnt[a[i] % 2]++;
	}

	if (cnt[0] && cnt[1]) {
		sort(a.begin() + 1, a.end());
	}

	for (int i = 1; i <= n; ++i) {
		cout << a[i] << " \n"[i == n];
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
