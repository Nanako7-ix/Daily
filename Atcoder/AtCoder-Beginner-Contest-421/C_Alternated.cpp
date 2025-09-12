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
	int n;
	string s;
	cin >> n >> s;
	vector<int> p;
	for (int i = 0; i < 2 * n; ++i) {
		if (s[i] == 'A') p.push_back(i);
	}

	auto f = [&](auto pos) -> i64 {
		i64 ans = 0;
		for (int i = 0; i < n; ++i) {
			ans += abs(p[i] - pos(i));
		}
		return ans;
	};

	cout << min(
		f([](int x) { return x << 1; }),
		f([](int x) { return x << 1 | 1; })
	) << "\n";
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