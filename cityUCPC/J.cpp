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
	string s;
	cin >> n >> k >> s;

	if (k == 0) {
		string t;
		for (auto ch : s) {
			if (t.empty() || t.back() != ch) {
				t.push_back(ch);
			} else t.pop_back();
		}
		cout << t.size() << "\n";
	} else {
		cout << n % 2 << "\n";
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
