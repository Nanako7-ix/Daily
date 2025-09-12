#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

std::vector<int> minp, P;

void sieve(int n) {
	minp.assign(n + 1, 0);
	P.clear();
	for (int i = 2; i <= n; ++i) {
		if (minp[i] == 0) {
			P.push_back(minp[i] = i);
		}
		for (i64 p : P) {
			if(i * p > n) break;
			minp[i * p] = p;
			if(i % p == 0) break;
		}
	}
}

void Thephix() {
	int n;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	
	int p = -1;
	for (int i = 1; i <= n; ++i) {
		if (a[i] == minp[a[i]]) {
			if (p == -1) {
				p = a[i];
			} else {
				cout << "-1\n";
				return;
			}
		}
	}

	if (p == -1) {
		cout << "2\n";
		return;
	}

	for (int i = 1; i <= n; ++i) {
		if (a[i] == p) continue;
		if (a[i] % 2 == 1) {
			a[i] -= minp[a[i]];
		}
		if (a[i] < 2 * p) {
			cout << "-1\n";
			return;
		}
	}
	cout << p << "\n";
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	sieve(4E5);
	
	int T = 1;
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
