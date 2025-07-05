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
 * Created: 2025/07/01 23:11:55
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

vector<vector<int>> fact;
void sieve(int n) {
    fact.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            fact[j].push_back(i);
        }
    }
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    auto& fac = fact[m];
    int N = fac.size();
    vector<pair<int, vector<int>>> a(N, pair {0, vector<int> (n + 1, 0)});
    for (int i = 0; i < N; ++i) {
        a[i].second[0] = inf;
    }
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        for (int j = 0; j < N; ++j) {
            a[j].second[i] = x % fac[j];
            a[j].first += a[j].second[i] < a[j].second[i - 1];
        }
    }

    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int p, x;
            cin >> p >> x;
            for (int i = 0; i < N; ++i) {
                if (p != 1) {
                    a[i].first -= a[i].second[p] < a[i].second[p - 1] && x % fac[i] >= a[i].second[p - 1];
                    a[i].first += a[i].second[p] >= a[i].second[p - 1] && x % fac[i] < a[i].second[p - 1];
                }
                if (p != n) {
                    a[i].first -= a[i].second[p + 1] < a[i].second[p] && a[i].second[p + 1] >= x % fac[i];
                    a[i].first += a[i].second[p + 1] >= a[i].second[p] && a[i].second[p + 1] < x % fac[i];
                }
                a[i].second[p] = x % fac[i];
            }
        } else {
            int k;
            cin >> k;
            k = gcd(k, m);

            int cnt = m / k;
            k = lower_bound(fac.begin(), fac.end(), k) - fac.begin();
            if (a[k].first <= cnt) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    sieve(5E5);

    while (T--) {
        solve();
    }

    return 0;
}