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
	int n, cnt = 0;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		cnt += a[i] == 0;
	}
	if (cnt == 1) {
		int p = -1;
		set<int> s;
		for (int i = 1; i <= n; ++i) {
			s.insert(i);
		}
		for (int i = 1; i <= n; ++i) {
			if (a[i] == 0) p = i;
			else s.erase(a[i]);
		}
		assert(s.size() == 1);
		a[p] = *s.begin();
	}
	
	vector<int> p;
	for (int i = 1; i <= n; ++i) {
		if (a[i] != i || a[i] == 0) {
			p.push_back(i);
		}
	}
	if (p.empty()) {
		cout << 0 << "\n";
	} else {
		cout << p.back() - p[0] + 1 << "\n";
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
