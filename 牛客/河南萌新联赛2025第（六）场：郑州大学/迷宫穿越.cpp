#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int inf = 1E7;
constexpr int dir[4][2] = {
  {1, 0}, {-1, 0}, {0, 1}, {0, -1}
};

void Thephix() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> a(n + 1, vector<int> (m + 1));
  for (int i = 1; i <= n; ++i) {
    string s; cin >> s;
    for (int j = 1; j <= m; ++j) {
      a[i][j] = s[j - 1] == '#';
    }
  }
  
  vector  dp(n + 1, vector (m + 1, vector<int> (k + 1, inf)));
  vector vis(n + 1, vector (m + 1, vector<int> (k + 1,   0)));
  queue<array<int, 3>> q;
  q.push({1, 1, k});
  vis[1][1][k] = 1, dp[1][1][k] = 0;
  while (!q.empty()) {
    auto [x, y, cnt] = q.front();
    q.pop();
    for (int i = 0; i < 4; ++i) {
      int tx = x + dir[i][0];
      int ty = y + dir[i][1];
      if (tx < 1 || tx > n || ty < 1 || ty > m || cnt - a[tx][ty] < 0 || vis[tx][ty][cnt - a[tx][ty]]) {
        continue;
      }
      vis[tx][ty][cnt - a[tx][ty]] = 1;
      dp[tx][ty][cnt - a[tx][ty]] = dp[x][y][cnt] + 1;
      q.push({tx, ty, cnt - a[tx][ty]});
    }
  }
  int ans = *min_element(dp[n][m].begin(), dp[n][m].end());
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