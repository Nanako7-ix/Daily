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
  int n;
  cin >> n;
  array<array<int, 3>, 3> ans {};
  for (int i = 1; i <= n; ++i) {
    int x, p = -1; cin >> x;
    for (int j = 0; j < 3; ++j) {
      if (ans[j][0] >= x) {
        p = j; break;
      }
    }
    for (int j = 0; j < 3; ++j) {
      if (j != p) {
        ans[j][2]++;
        if (ans[j][2] == 3) {
          ans[j][2] = 0;
          ans[j][0] += 2;
        }
      } else {
        ans[j][0]++, ans[j][1]++, ans[j][2] = 0;
      }
    }
  }
  cout << ans[0][1] << ' ' << ans[1][1] << ' ' << ans[2][1] << "\n";
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