#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int N = 100000;
constexpr int n = 12000;
constexpr int B = 120;

int query(vector<int> a) {
	cout << "? " << a.size() << " ";
	for (auto x : a) cout << x << ' ';
	cout << endl;
	int ans; cin >> ans;
	return ans;
}

array<pair<int, int>, N + 1> f {};

void Thephix() {
	int cnt = query(vector<int> (n, B));
	if (cnt == 0) {
		// [1, B) 直接测试 [1, 1, ..., 1]
		cnt = query(vector<int> (n, 1));
		for (int i = 1; i < B; ++i) {
			if (cnt == (n + i - 1) / i) {
				cout << "! " << i << endl;
				return;
			}
		}
	}

	auto [l, r] = f[cnt];
	if (l == r) {
		cout << "! " << l << endl;
		return;
	}
	vector<int> a((r - l) * 2);
	for (int i = 0; i < r - l; ++i) {
		a[i << 1] = l;
		a[i << 1 | 1] = i + 1;
	}
	cnt = query(a);
	cout << "! " << 2 * r - l - cnt << endl;
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	cin >> T;

	f.fill({N, 1});
	int len = 0;
	for (int i = B; i <= N; ++i) {
		int x = i / B;
		x = (n + x - 1) / x;
		auto& [l, r] = f[x];
		l = min(l, i);
		r = max(r, i);
		len = max(len, r - l);
	}
	set<int> S;
	for (int i = 1; i < B; ++i) {
		S.insert((n + i - 1) / i);
	}
	cerr << (S.size() == B - 1) << endl;
	cerr << 2 * len + n << endl;

	while (T--) {
		Thephix();
	}

	return 0;
}