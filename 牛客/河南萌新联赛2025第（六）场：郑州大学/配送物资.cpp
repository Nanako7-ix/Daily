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
  vector<vector<int>> adj(n + 1);
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> dep(n + 1);
  vector<vector<int>> fa(__lg(n) + 1, vector<int> (n + 1));
  auto jxt = [&](auto&& jxt, int u) -> void {
    dep[u] = dep[fa[0][u]] + 1;
    for (auto& v : adj[u]) {
      if (v == fa[0][u]) continue;
      fa[0][v] = u;
      jxt(jxt, v);
    }
  }; jxt(jxt, 1);

  for (int i = 1; i <= __lg(n); ++i) {
    for (int u = 1; u <= n; ++u) {
      fa[i][u] = fa[i - 1][fa[i - 1][u]];
    }
  }

  vector<int> ans(n + 1);
  for (int u = 1; u <= n; ++u) {
    int x; cin >> x;
    x = max(1, dep[u] - x);
    int v = u;
    for (int i = __lg(n); i >= 0; --i) {
      if (dep[fa[i][v]] < x) continue;
      v = fa[i][v];
    }
    ans[u]++, ans[fa[0][v]]--;
  }
  
  auto dfs = [&](auto&& dfs, int u) -> void {
    for (auto& v : adj[u]) {
      if (v == fa[0][u]) continue;
      dfs(dfs, v);
      ans[u] += ans[v];
    }
  }; dfs(dfs, 1);

  for (int i = 1; i <= n; ++i) {
    cout << ans[i] << " \n"[i == n];
  }
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