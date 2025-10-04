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
std::vector<i64> f;
constexpr i64 Mod = 998244353;

void sieve(int n) {
	int cnt = 0;
	minp.assign(n + 1, 0);
	f.assign(n + 1, 0);
	P.clear();
	for (int i = 2; i <= n; ++i) {
		if (minp[i] == 0) {
			P.push_back(minp[i] = i);
		} else {
			cnt++;
			f[i] = 1LL * i * cnt % Mod;
		}

		for (i64 p : P) {
			if(i * p > n) break;
			minp[i * p] = p;
			if(i % p == 0) break;
		}
	}

	for (int i = 1; i <= n; ++i) {
		(f[i] += f[i - 1]) %= Mod;
	}
}

void Thephix() {
	int l, r;
	cin >> l >> r;
	cout << (f[r] - f[l - 1] + Mod) % Mod << "\n";
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	sieve(5E6);

	int T = 1;
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
