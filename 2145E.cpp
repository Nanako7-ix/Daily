#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int A, B;
	cin >> A >> B;

	int n;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		int x, y;
		cin >> x >> y;
		a[i] = max(x - A, 0) + max(y - B, 0);
	}
	
	int q;
	cin >> q;
	for (int i = 1; i <= q; ++i) {
		int p, x, y;
		cin >> p >> x >> y;
		a[p] = max(x - A, 0) + max(y - B, 0);
		// kth < k
	}
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
