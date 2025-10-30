#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n, k, m;
	cin >> n >> k >> m;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	sort(a.begin() + 1, a.end());

	auto get = [&](int p, int len) {
		return pair {
			max(0, p - len + 1),
			min(m, p + len - 1)
		};
	};

	auto check = [&](int x) {
		auto [l, r] = get(a[1], x);
		int ans = r - l + 1, last = r;
		for (int i = 2; i <= n; ++i) {
			auto [l, r] = get(a[i], x);
			l = max(l, last + 1);
			ans += r - l + 1;
			last = r;
		}
		return m + 1 - ans >= k;
	};

	int l = 0, r = m, res = -1;
	while (l <= r) {
		int x = (l + r) >> 1;
			if (check(x)) {
			res = x, l = x + 1;
		} else r = x - 1;
	}

	assert(res != -1);
	for (int i = 0, j = 1; k; ) {
		int ok = 1;
		while (j <= n) {
			auto [l, r] = get(a[j], res);
			if (r < i) ++j;
			else break;
		}
		if (j <= n) {
			auto [l, r] = get(a[j], res);
			if (i >= l) ok = 0, i = r + 1;
		}
		if (ok == 1) {
			cout << i << " \n"[k == 1];
			++i, --k;
		}
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
