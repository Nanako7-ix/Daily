#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

constexpr int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
constexpr int inf = 1E9;

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
	
	array<int, 2> p;
	vector a(n + 1, vector<int> (m + 1));
	for (int i = 1; i <= n; ++i) {
		string s; cin >> s;
		for (int j = 1; j <= m; ++j) {
			a[i][j] = s[j - 1] == '#';
			if (s[j - 1] == 'T') p = { i, j };
		}
	}

	auto pre = a;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			pre[i][j] += pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
		}
	}

	auto query = [&](int xl, int yl, int xr, int yr) {
		return pre[xr][yr] - pre[xl - 1][yr] - pre[xr][yl - 1] + pre[xl - 1][yl - 1];
	};

	int ans = inf;
	queue<array<int, 7>> que;
	vector vis(n + 1, vector (n + 1, vector (m + 1, vector<HashMap<int, HashMap<int, int>>> (m + 1))));
	vis[1][n][1][m][0][0] = 1;
	que.push({ 1, n, 1, m, 0, 0, 0 });
	while (!que.empty()) {
		auto [_xl, _xr, _yl, _yr, _x, _y, res] = que.front();
		que.pop();
		for (int k = 0; k < 4; ++k) {
			int x = _x + dir[k][0];
			int y = _y + dir[k][1];
			int xl = max(_xl, 1 + x);
			int xr = min(_xr, n + x);
			int yl = max(_yl, 1 + y);
			int yr = min(_yr, m + y);

			if (
				_xl <= p[0] + x &&
				p[0] + x <= _xr &&
				_yl <= p[1] + y &&
				p[1] + y <= _yr &&
				a[p[0] + x][p[1] + y]
			) { continue; }

			if (xl > xr || yl > yr || query(xl, yl, xr, yr) == 0) {
				ans = min(ans, res + 1);
				continue;
			}

			if (vis[xl][xr][yl][yr][x][y]) continue;

			vis[xl][xr][yl][yr][x][y] = 1;
			que.push({ xl, xr, yl, yr, x, y, res + 1 });
		}
	}

	if (ans == inf) ans = -1;
	cout << ans << "\n";
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
