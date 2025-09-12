#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 inf = 1'000'000'000;

void Thephix() {
	int n;
	cin >> n;
	vector<array<i64, 2>> a(n + 1);
	i64 Min = 4E18, Max = -4E18;
	for (i64 i = 1; i <= n; ++i) {
		cin >> a[i][0] >> a[i][1];
		Min = min(Min, a[i][0] + a[i][1]);
		Max = max(Max, a[i][0] - a[i][1]);
	}

	auto D = [&](i64 val) -> i64 {
		cout << "? D " << val << endl;
		i64 x; cin >> x;
		return x;
	};
	auto L = [&](i64 val) -> i64 {
		cout << "? L " << val << endl;
		i64 x; cin >> x;
		return x;
	};
	auto R = [&](i64 val) -> i64 {
		cout << "? R " << val << endl;
		i64 x; cin >> x;
		return x;
	};

	i64 add, del;
	D(inf), D(inf), L(inf);
	Min -= L(inf);
	
	R(inf), R(inf), R(inf);
	Max += R(inf);
	
	auto [x, y] = pair { Min + Max, Min - Max };
	x /= 2, y /= 2;
	cout << "! " << x << ' ' << y + 4 * inf << endl;
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
