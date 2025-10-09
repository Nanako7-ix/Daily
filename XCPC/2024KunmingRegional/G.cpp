#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

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
	i64 a, b;
	cin >> a >> b;

	vector<HashMap<i64, bool>> vis(a + 1);
	
	queue<array<i64, 3>> q;
	q.push({ a, b, 0 });
	while (!q.empty()) {
		auto& [x, y, t] = q.front();
		q.pop();

		int d = gcd(x, y);

		if (x == d || y == d) {
			cout << t + 2 << "\n";
			return;
		}

		if (vis[x - d][y] == 0) {
			vis[x - d][y] = 1;
			q.push({ x - d, y, t + 1 });
		}

		if (vis[x][y - d] == 0) {
			vis[x][y - d] = 1;
			q.push({ x, y - d, t + 1 });
		}
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
