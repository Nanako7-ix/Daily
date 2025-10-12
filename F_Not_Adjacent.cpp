#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

struct SplitMix {
	static u64 shift(u64 x) {
		static const u64 rng = std::random_device()();
		x += rng;
		x += 0x9E37'79B9'7F4A'7C15ULL;
		x = (x ^ (x >> 30)) * 0xBF58'476D'1CE4'E5B9ULL;
		x = (x ^ (x >> 27)) * 0x94D0'49BB'1331'11EBULL;
		return x ^ (x >> 31);
	}
	u64 operator() (const u64& x) const {
		return shift(x);
	}
};

template<std::integral K, typename V>
using HashMap = __gnu_pbds::gp_hash_table<K, V, SplitMix>;

void Thephix() {
	int n, m;
	cin >> n >> m;
	vector<i64> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	if (n == 1) {
		cout << 1 + (a[1] == 0) << "\n";
		return;
	}

	int half = (n + 1) / 2;
	i64 ans = 0;
	vector<HashMap<int, int>> L(n + 1);
	HashMap<int, int> pre;
	for (int i = 1; i <= half; ++i) {
		L[i][a[i]] = 1;
		for (int j = 1; j < i - 1; ++j) {
			for (auto [x, cnt] : L[j]) {
				L[i][(x + a[i]) % m] += cnt;
			}
		}
		ans += L[i][0];
	}

	vector<HashMap<int, int>> R(n + 1);
	
	for (int i = n; i > half; --i) {
		R[i][a[i]] = 1;
		for (int j = n; j > i + 1; --j) {
			for (auto [x, cnt] : R[j]) {
				R[i][(x + a[i]) % m] += cnt;
			}
		}
		ans += R[i][0];
	}

	cout << ans + 1 << "\n";
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
