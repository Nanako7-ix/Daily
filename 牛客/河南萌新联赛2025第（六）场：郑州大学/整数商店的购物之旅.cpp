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
  i64 a, b, x;
  cin >> a >> b >> x;
  auto check = [&](i64 m) {
    i64 d = 0, _m = m;
    while (_m) d++, _m /= 10;
    return x >= a * m + d * b;
  };
  i64 l = 0, r = min(x / a, 1'000'000'000LL), res = -1;
  while (l <= r) {
    i64 m = (l + r) >> 1;
    if (check(m)) {
      res = m, l = m + 1;
    } else r = m - 1;
  }
  assert(res != -1);
  cout << res << "\n";
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