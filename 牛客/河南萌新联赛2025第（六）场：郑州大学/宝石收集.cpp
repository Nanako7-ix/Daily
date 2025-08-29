#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 inf = 1E18;

void Thephix() {
  int n, m;
  cin >> n >> m;
  vector<i64> dp(1 << n, inf);
  dp[0] = 0;
  for (int i = 1; i <= m; ++i) {
    int c, k;
    cin >> c >> k;
    int mask = 0;
    for (int j = 1; j <= k; ++j) {
      int x; cin >> x;
      mask |= 1 << x;
    }
    for (int s = 0; s < (1 << n); ++s) {
      dp[s | mask] = min(dp[s | mask], dp[s] + c);
    }
  }
  cout << dp[(1 << n) - 1] << "\n";
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