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

u64 code(u64 u, u64 v) {
	if (u > v) swap(u, v);
	return u << 32 | v;
}

pair<int, int> decode(u64 x) {
	int u = x >> 32;
	int v = x & 0xFFFFFFFF;
	if (u > v) swap(u, v);
	return { u, v };
}

template<std::integral K, typename V>
using HashMap = __gnu_pbds::gp_hash_table<K, V, SplitMix>;

void Thephix() {
	int k, m, n;
	cin >> k >> m >> n;

	vector<int> a(n + 1);
	for (int i = 1; i <= k; ++i) {
		int x;
		cin >> x;
		a[x] = 1;
	}

	int res = 0;
	vector<int> f(n + 1);
	HashMap<i64, int> cnt;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;

		if (u == v) {
			(a[u] ? res : f[u])++;
			continue;
		}
		
		if (a[u] && a[v]) res++;
		else if (a[u]) f[v]++;
		else if (a[v]) f[u]++;
		else cnt[code(u, v)]++;
	}

	int ans = 0;
	for (auto [x, cnt] : cnt) {
		auto [u, v] = decode(x);
		ans = max(ans, res + f[u] + f[v] + cnt);
	}

	sort(f.begin() + 1, f.end(), greater());
	ans = max(ans, res + f[1] + f[2]);
	cout << ans << "\n";
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
