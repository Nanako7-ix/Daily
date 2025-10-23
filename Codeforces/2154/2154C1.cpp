#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

std::vector<i64> minp, P;

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

	map<int, int> cnt0, cnt1;

	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		
		int x = a[i];
		while (x != 1) {
			int p = minp[x];
			cnt0[p]++;
			while (x % p == 0) {
				x /= p;
			}
		}

		x = a[i] + 1;
		while (x != 1) {
			int p = minp[x];
			cnt1[p]++;
			while (x % p == 0) {
				x /= p;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	
	for (auto [x, cnt] : cnt0) {
		if (cnt > 1) {
			cout << "0\n";
			return;
		}
	}

	for (auto [x, cnt] : cnt0) {
		if (cnt1[x]) {
			cout << "1\n";
			return;
		}
	}

	cout << "2\n";
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;

	sieve(2E5 + 1);
	
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
