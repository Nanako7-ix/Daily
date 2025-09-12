#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

i64 f(i64 n) {
	vector<int> dig;
	while (n) {
		dig.push_back(n % 10);
		n /= 10;
	}
	reverse(dig.begin(), dig.end());
	while (!dig.empty()) {
		n = n * 10 + dig.back();
		dig.pop_back();
	}
	return n;
}

void Thephix() {
	const int n = 10;
	vector<i64> a(n + 1);
	cin >> a[1] >> a[2];
	for (int i = 3; i <= n; ++i) {
		a[i] = f(a[i - 1] + a[i - 2]);
	}
	cout << a[n] << "\n";
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