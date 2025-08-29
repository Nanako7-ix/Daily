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
  i64 n; cin >> n;
  i64 l = 1, r = 1E18, res = -1;
  while (l <= r) {
    i64 m = (l + r) >> 1;

    auto check = [](i64 m) -> i64 {
      vector<int> dig;
      while (m) {
        dig.push_back(m % 10);
        m /= 10;
      }
      reverse(dig.begin(), dig.end());
      int len = dig.size();
      vector<array<i64 , 2>>  dp(len);
      vector<array<bool, 2>> vis(len);
      auto dfs = [&](auto&& dfs, int u, bool lim) -> i64 {
        if (u == len) return 1;
        if (!vis[u][lim]) {
          vis[u][lim] = 1;
          int r = lim ? dig[u] : 9;
          for (int i = 0; i <= r; ++i) {
            if (i == 7) continue;
            dp[u][lim] += dfs(dfs, u + 1, lim && i == r);
          }
        }
        return dp[u][lim];
      };
      return dfs(dfs, 0, 1) - 1;
    };
    
    if (check(m) >= n) {
      res = m, r = m - 1;
    } else l = m + 1;
  }

  assert(res != -1);
  cout << res << "\n";
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