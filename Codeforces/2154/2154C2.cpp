#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
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

struct SplitMix {
	static u64 shift(u64 x) {
		x += 0x9E37'79B9'7F4A'7C15ULL;
		x = (x ^ (x >> 30)) * 0xBF58'476D'1CE4'E5B9ULL;
		x = (x ^ (x >> 27)) * 0x94D0'49BB'1331'11EBULL;
		return x ^ (x >> 31);
	}
	u64 operator() (const u64& x) const {
		static const u64 rng = std::random_device()();
		return shift(x + rng);
	}
};

template<std::integral K, typename V>
using HashMap = __gnu_pbds::gp_hash_table<K, V, SplitMix>;

constexpr int inf = 2E9;

void Thephix() {
	int n;
	cin >> n;
	vector<array<i64, 2>> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i][0];
	}
	for (int i = 1; i <= n; ++i) {
		cin >> a[i][1];
	}

	HashMap<int, int> cnt;
	for (int i = 1; i <= n; ++i) {
		for (int x = a[i][0]; x != 1;) {
			int p = minp[x];
			if (cnt[p] == 1) {
				cout << "0\n";
				return;
			}
			cnt[p] += 1;
			while (x % p == 0) x /= p;
		}
	}

	bool even = 0;
	array<int, 2> Min { inf, inf };
	for (int i = 1; i <= n; ++i) {
		auto [x, y] = a[i];
		if (x % 2 == 0) {
			even = 1;
			continue;
		}
		if (y < Min[0]) {
			Min[1] = Min[0];
			Min[0] = y;
		} else if (y < Min[1]) {
			Min[1] = y;
		}
	}
	
	i64 ans = Min[0] + (even ? 0 : Min[1]);

	for (int i = 1; i <= n; ++i) {
		auto [x, y] = a[i];

		int Max = ans / y;
		if (Max == 0) continue;

		for (int z = x; z != 1; ) {
			int p = minp[z];
			cnt[p]--;
			while (z % p == 0) z /= p;
		}

		if (Max <= (int) cnt.size() / 20) {
			for (int j = 1; j <= Max; ++j) {
				i64 res = 0;
				for (int z = x + j; z != 1;) {
					int p = minp[z];
					if (
						auto it = cnt.find(p);
					  it != cnt.end() && it -> second != 0
					) {
						res = y * j;
						break;
					}
					while (z % p == 0) z /= p;
				}
				if (res != 0) {
					ans = min(ans, res);
					break;
				}
			}
		} else {
			for (auto [p, exist] : cnt) {
				if (!exist) continue;
				int need = (x + p - 1) / p * p - x;
				ans = min(ans, need * y);
			}
		}

		for (int z = x; z != 1; ) {
			int p = minp[z];
			cnt[p]++;
			while (z % p == 0) z /= p;
		}
	}

	cout << ans << endl;
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;

	sieve(4E5);
	
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
