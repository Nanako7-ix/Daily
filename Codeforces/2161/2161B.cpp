#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n;
	cin >> n;
	set<int> add, del, x, y;
	for (int i = 1; i <= n; ++i) {
		string s; cin >> s;
		for (int j = 1; j <= n; ++j) {
			if (s[j - 1] == '#') {
				add.insert(i + j);
				del.insert(i - j);
				x.insert(i);
				y.insert(j);
			}
		}
	}

	if (add.size() == 0) {
		cout << "YES\n";
		return;
	}

	int Min_add = *add.begin(), Max_add = *add.rbegin();
	int Min_del = *del.begin(), Max_del = *del.rbegin();
	int Min_x = *x.begin(), Max_x = *x.rbegin();
	int Min_y = *y.begin(), Max_y = *y.rbegin();
	// cout << Min_add << ' ' << Max_add << "\n";
	// cout << Min_del << ' ' << Max_del << "\n";
	if (Max_add - Min_add <= 1 || Max_del - Min_del <= 1) {
		cout << "YES\n";
		return;
	}
	if (Max_x - Min_x <= 1 && Max_y - Min_y <= 1) {
		cout << "YES\n";
		return;
	}
	cout << "NO\n";
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int T = 1;
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
