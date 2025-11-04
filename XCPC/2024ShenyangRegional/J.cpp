#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	array<pair<string, int>, 8> a;
	for (int i = 0; i < 8; ++i) {
		auto& [name, x] = a[i];
		cin >> name >> x;
	}

	for (int i = 0; i < 8; i += 2) {
		if (a[i].second < a[i + 1].second) {
			swap(a[i], a[i + 1]);
		}
	}

	for (int i = 0; i < 8; i += 4) {
		if (a[i].second < a[i + 2].second) {
			swap(a[i], a[i + 2]);
		}
	}

	for (int i = 0; i < 8; i += 8) {
		if (a[i].second < a[i + 4].second) {
			swap(a[i], a[i + 4]);
		}
	}

	cout << a[0].first << " beats " << a[4].first << '\n';
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int T = 1;
	// cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
