/**
 * Author: Nanako7_ix
 * Created: 2025/04/28 21:26:54
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define setpre(x) fixed << setprecision(x)
#define debug(x) cerr << #x << " = " << x << "\n"
#define endl "\n"
using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

template<int N>
struct Trie {
  int cnt = 0;
  vector<int> f, g, bad;
  vector<array<int, N>> nxt;
  static int rank(char c) {
    return c - 'a';
  }
  Trie(int n = 2e6) {
    f.reserve(n), f.assign(1, 0);
    bad.reserve(n), bad.assign(1, 0);
    nxt.reserve(n), nxt.assign(1, {});
  }

  void insert(string s, int op) {
    int n = s.size(), p = 0;
    for (int i = 0; i < n; ++i) {
      int x = rank(s[i]);
      if (nxt[p][x] == 0) {
        nxt[p][x] = ++cnt;
        f.push_back(0);
        nxt.push_back({});
        bad.push_back(0);
      }
      p = nxt[p][x];
      if (bad[p]) return;
    }
    if (op == 2) {
        f[0]++, p = 0;
        for (int i = 0; i < n; ++i) {
            int x = rank(s[i]);
            p = nxt[p][x];
            f[p]++;
        }
    } else {
        int d = f[p];
        f[0] -= d, p = 0;
        for (int i = 0; i < n; ++i) {
            int x = rank(s[i]);
            p = nxt[p][x];
            f[p] -= d;
        }
        bad[p] = 1;
    }
  }
};

void solve() {
    int n;
    cin >> n;
    Trie<26> tr;
    for (int i = 1; i <= n; ++i) {
        int op;
        string s;
        cin >> op >> s;
        tr.insert(s, op);
        cout << tr.f[0] << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    // cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}