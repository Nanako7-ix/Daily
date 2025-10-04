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
	i64 A, B, C, n;
	cin >> A >> B >> C >> n;

	if (C == n) {
		cout << "Yes\n";
		return;
	}
	
	auto f = [&](i64 x, i64 y) -> bool {
		if (n == (x - C)) return true;
		if (x != y && (n - (x - C)) % (x - y) == 0 && (n - (x - C)) % (x - y) >= 0) {
			return true;
		}
		if (x != y && (n - C) % (x - y) == 0 && (n - C) % (x - y) >= 0) {
			return true;
		}
		return false;
	};
	
	if (f(B, A - B) || f(A - B, B)) {
		cout << "Yes\n";
	} else {
		cout << "No\n";
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
