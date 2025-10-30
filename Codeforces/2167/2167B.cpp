#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n;
	string s, t;
	cin >> n >> s >> t;
	sort(s.begin(), s.end());
	sort(t.begin(), t.end());
	
	if (s == t) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
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
