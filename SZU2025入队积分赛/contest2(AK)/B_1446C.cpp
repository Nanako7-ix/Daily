#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
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

template<int H>
struct Trie {
    int cnt = 0;
    vector<int> siz;
    vector<array<int, 2>> ch;

    Trie(int n = 2e6) {
      siz.reserve(n), siz.assign(1, 0);
      ch.reserve(n), ch.assign(1, {});
    }

    void insert(const bitset<H>& x) {
      int p = 0;
      siz[0]++;
      for(int i = H - 1; i >= 0; --i) {
        if(!ch[p][x[i]]) {
          ch.push_back({}), siz.push_back(0);
          ch[p][x[i]] = ++cnt;
        }
        siz[p = ch[p][x[i]]]++;
      }
    }

    void erase(const bitset<H>& x) {
      int p = 0;
      siz[0]--;
      for(int i = H - 1; i >= 0; --i) {
        assert(ch[p][x[i]]);
        siz[p = ch[p][x[i]]]--;
      }
    }

    int find(const bitset<H>& x) {
      int p = 0;
      for(int i = H - 1; i >= 0; --i) {
        if(!ch[p][x[i]]) return -1;
        p = ch[p][x[i]];
      }
      return p;
    }

    u64 max(bitset<H> x) {
      for(int i = H - 1, p = 0; i >= 0; --i) {
        if(ch[p][~x[i]] && siz[ch[p][~x[i]]]) {
          p = ch[p][~x[i]], x[i] = 1;
        } else p = ch[p][x[i]], x[i] = 0;
      }
      return x.to_ullong();
    }

    u64 min(bitset<H> x) {
      for(int i = H - 1, p = 0; i >= 0; --i) {
        if(ch[p][x[i]] && siz[ch[p][x[i]]]) {
          p = ch[p][x[i]], x[i] = 0;
        } else p = ch[p][!x[i]], x[i] = 1;
      }
      return x.to_ullong();
    }
};

void solve() {
    int n;
    cin >> n;
    Trie<30> tr;
    for(int i = 1; i <= n; ++i) {
        int x; cin >> x;
        tr.insert(x);
    }
    cout << [&](this auto&& dfs, int u) -> int {
        if(!tr.ch[u][0] && !tr.ch[u][1]) return 0;
        if(tr.ch[u][0] && !tr.ch[u][1]) return dfs(tr.ch[u][0]);
        if(tr.ch[u][1] && !tr.ch[u][0]) return dfs(tr.ch[u][1]);
        int l = tr.siz[tr.ch[u][0]], r = tr.siz[tr.ch[u][1]];
        return min(l - 1 + dfs(tr.ch[u][1]), dfs(tr.ch[u][0]) + r - 1);
    } (0) << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}