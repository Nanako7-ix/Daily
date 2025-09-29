#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 Mod = 1'000'000'007;

i64 power(i64 a, i64 b) {
	i64 res = 1;
	for (; b; b >>= 1, a = a * a % Mod) {
		if (b & 1) res = res * a % Mod;
	}
	return res;
}

void Thephix() {
	i64 n, k;
	cin >> n >> k;
	cout << power(2, n * k % (Mod - 1)) << "\n";
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
