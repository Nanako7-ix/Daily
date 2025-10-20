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

void Thephix() {
	int n;
	cin >> n;

	vector<array<int, 3>> a(n + 1);
	array<HashMap<int, int>, 3> cnt;
	for (int i = 1; i <= n; ++i) {
		auto& [x, y, z] = a[i];
		cin >> x >> y >> z;
		cnt[0][x]++;
		cnt[1][y]++;
		cnt[2][z]++;
	}

	vector<int> b(n + 1);
	for (int i = 1; i <= n; ++i) {
		auto& [x, y, z] = a[i];
		b[max({ cnt[0][x], cnt[1][y], cnt[2][z] })]++;
	}

	for (int i = 1; i <= n; ++i) {
		b[i] += b[i - 1];
	}
	for (int i = 0; i < n; ++i) {
		cout << b[i] << " \n"[i == n - 1];
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
