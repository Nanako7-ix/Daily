#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int a, b, c;
	cin >> a >> b >> c;
	for (int i = 0; i <= 30; ++i) {
		int x = a >> i & 1;
		int y = b >> i & 1;
		int z = c >> i & 1;
		if (x + y + z == 2) {
			cout << "NO\n";
			return;
		}
	}
	cout << "YES\n";
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
