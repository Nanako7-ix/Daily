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
	int n, k;
	cin >> n >> k;
	vector<int> a(2 * n + 1);
	iota(a.begin(), a.end(), 0);
	for (int i = 1; i <= k; ++i) {
		swap(a[2 * i - 1], a[2 * i]);
	}
	
	for (int i = 1; i <= 2 * n; ++i) {
		cout << a[i] << " \n"[i == 2 * n];
	}

	i64 sum1 = 0, sum2 = 0;
	for (int i = 2; i <= 2 * n; i += 2) {
		sum1 += abs(a[i] - a[i - 1]);
		sum2 += a[i] - a[i - 1];
	}
	assert(sum1 - abs(sum2) == 2 * k);
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
