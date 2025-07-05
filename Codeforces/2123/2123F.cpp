/**
 *
 *  $$$$$$\  $$$$$$\  $$$$$$\  $$\       $$\       $$$$$$\  
 * $$  __$$\ \_$$  _|$$  __$$\ $$ |      $$ |     $$  __$$\ 
 * $$ /  \__|  $$ |  $$ /  $$ |$$ |      $$ |     $$ /  $$ |
 * $$ |        $$ |  $$$$$$$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |        $$ |  $$  __$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |  $$\   $$ |  $$ |  $$ |$$ |      $$ |     $$ |  $$ |
 *  $$$$$$ | $$$$$$\ $$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$  |
 * \______/  \______|\__|  \__|\________|\________|\______/ 
 *
 * Author:  Nanako7_ix
 * Created: 2025/07/01 22:38:28
 * 好想和 めぐる 一起打 xcpc 啊
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
using f64 = double;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

vector<int> minp, primes;
void sieve(int N) {
    minp.assign(N + 1, 0);
    primes.clear();
    for(int i = 2; i <= N; ++i) {
        if(!minp[i]) primes.emplace_back(minp[i] = i);
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(i % p == 0) break;
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> vis(n + 1), bel(n + 1);
    vector<vector<int>> next(n + 1);
    for (int i = 2; i <= n; ++i) {
        int x = i;
        while (x != 1) {
            int p = minp[x];
            while (x % p == 0) {
                x /= p;
            }
            if (vis[p] == 0 || x == 1) {
                vis[p] = 1, bel[i] = p;
                next[p].push_back(i);
                break;
            }
        }
    }

    cout << 1 << " ";
    for (int i = 2; i <= n; ++i) {
        auto it = upper_bound(next[bel[i]].begin(), next[bel[i]].end(), i);
        if (it == next[bel[i]].end()) {
            cout << bel[i] << " \n"[i == n];
        } else {
            cout << *it << " \n"[i == n];
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;
    sieve(1E5);
    while (T--) {
        solve();
    }

    return 0;
}