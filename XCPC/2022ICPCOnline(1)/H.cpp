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
	constexpr i64 Mod = 20220911;
	
	auto dfs = [&](auto&& dfs) -> i64 {
		i64 ans = 0;
		while (true) {
			string s;
			cin >> s;
			if (s == "library") {
				ans = (ans + 1) % Mod;
			} else if (s == "fin") {
				return ans;
			} else if (s == "for") {
				i64 k;
				cin >> k >> s;
				assert(s == "times");
				return ans * k % Mod;
			} else if (s == "repeat") {
				ans += dfs(dfs);
				ans %= Mod;
			}
		}
	};

	cout << dfs(dfs) << "\n";
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
