#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int N = 100000;
constexpr int M = 26;

void Thephix() {
	string s;
	cin >> s;
	int n = s.size();
	
	array<bitset<N>, M> bs;
	for (int i = 0; i < n; ++i) {
		bs[s[i] - 'a'][i] = 1;
	}

	int q; cin >> q;
	while (q--) {
		int op;
		cin >> op;
		if (op == 1) {
			int p; char ch;
			cin >> p >> ch;
			bs[s[p - 1] - 'a'][p - 1] = 0;
			s[p - 1] = ch;
			bs[s[p - 1] - 'a'][p - 1] = 1;
		} else {
			int l, r;
			string t;
			cin >> l >> r >> t;

			if (r - l + 1 < (int) t.size()) {
				cout << "0\n";
				continue;
			}
			
			int m = t.size();
			bitset<N> ans;
			ans = ~ans;
			for (int i = 0; i < m; ++i) {
				ans &= bs[t[i] - 'a'] >> i;
			}

			tie(l, r) = pair { l - 1, r - m };
			cout << (ans >> l).count() - (ans >> (r + 1)).count() << "\n";
		}
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
