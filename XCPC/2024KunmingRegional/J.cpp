#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n;
	string s;
	cin >> n >> s;

	vector<int> p(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> p[i];
	}

	if (n == 2) {
		cout << "Alice\n";
		return;
	}

	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		cnt += p[i] != i;
	}

	if (s == "Alice") {
		if (cnt > 2) {
			cout << "Bob\n";
		} else {
			cout << "Alice\n";
		}
		return;
	}

	for (int i = 2; i <= n; ++i) {
		cnt -= p[i] != i;
		cnt -= p[i - 1] != i - 1;
		swap(p[i], p[i - 1]);
		cnt += p[i] != i;
		cnt += p[i - 1] != i - 1;
		
		if (cnt > 2) {
			cout << "Bob\n";
			return;
		}
		
		cnt -= p[i] != i;
		cnt -= p[i - 1] != i - 1;
		swap(p[i], p[i - 1]);
		cnt += p[i] != i;
		cnt += p[i - 1] != i - 1;
	}
	cout << "Alice\n";
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
