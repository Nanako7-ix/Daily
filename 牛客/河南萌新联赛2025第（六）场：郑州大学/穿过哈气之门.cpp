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
  int n, m;
  cin >> n >> m;
  vector<int> a(n + 1), b(m + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  i64 ans = 0, cnt = 0;
  for (int l = 1, r = 0; l <= n; cnt -= --b[a[l++]] == 0) {
    while (r + 1 <= n && cnt != m) {
      cnt += b[a[++r]]++ == 0;
    }
    if (cnt == m) ans += n - r + 1;
  }
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