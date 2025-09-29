#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

int f(i64 n) {
	return std::__lg(n & -n);
}

void Thephix() {
	i64 n, m;
	cin >> n >> m;
	int l = max(f(n), f(m));
	int r = max(f(n), f(m)) + 1;
	
	int talk;
	if (n > m) {
		talk = l % 2 == 1 ? l : r;
	} else {
		talk = l % 2 == 1 ? r : l;
	}

	cout << (talk + 1) / 2 << ' ' << (n < m) << "\n";
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
