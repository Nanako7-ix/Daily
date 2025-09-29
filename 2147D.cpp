#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

auto get1(const map<i64, i64>& f) {
	vector<i64> a;
	for (auto [x, y] : f) {
		a.push_back(y);
	}
	sort(a.begin(), a.end(), greater {});

	i64 alice = 0, bob = 0, who = 1;
	for (int i = 0; i < (int) a.size(); ++i) {
		if (i & 1) bob += a[i];
		else alice += a[i];
		who ^= 1;
	}
	return tuple { alice, bob, who };
}

auto get2(const map<i64, i64>& f) {
	i64 alice = 0, bob = 0;
	for (auto [x, y] : f) {
		alice += x / 2 * y;
		bob += x / 2 * y;
	}
	return tuple { alice, bob };
}

void Thephix() {
	int n;
	cin >> n;
	map<i64, i64> odd, even;
	for (int i = 1; i <= n; ++i) {
		int x; cin >> x;
		if (x % 2 == 1) {
			odd[x]++, even[x - 1]++;
		} else even[x]++;
	}

	auto [alice1, bob1, x] = get1(odd);
	auto [alice2, bob2] = get2(even);

	if (x == 0) swap(alice2, bob2);
	cout << alice1 + alice2 << ' ' << bob1 + bob2 << "\n";
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
