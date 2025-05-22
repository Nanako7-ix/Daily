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
 * Created: 2025/05/23 00:08:17
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

void solve() {
    int n, k, q;
    cin >> n >> k >> q;
    string s;
    cin >> s;

    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    array<i64, 26> f {};
    for (int i = 0; i < 26; ++i) {
        f[i] = rng();
    }

    i64 Hash = 0;
    array<int, 26> Cnt {};
    vector<u64> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        int& x = Cnt[s[i - 1] - 'a'];
        Hash -= f[s[i - 1] - 'a'] * x;
        x = (x + 1) % k;
        Hash += f[s[i - 1] - 'a'] * x;
        a[i] = Hash;
    }

    auto b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int m = b.size();
    for (int i = 0; i <= n; ++i) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
    }

    vector<array<int, 3>> query(q + 1);
    for (int i = 1; i <= q; ++i) {
        cin >> query[i][0] >> query[i][1];
        query[i][0]--;
        query[i][2] = i;
    }
    const int block = 550;
    sort(query.begin(), query.end(), [](const array<int, 3>& x, const array<int, 3>& y) {
        if (x[0] / block == y[0] / block) {
            return x[0] / block % 2 == 0 ? x[1] < y[1] : x[1] > y[1];
        } return x[0] / block < y[0] / block;
    });
    
    i64 sum = 0;
    vector<i64> cnt(m + 1);
    int l = 1, r = 0;
    auto add = [&](int x) {
        sum -= cnt[x] * (cnt[x] - 1) / 2;
        cnt[x]++;
        sum += cnt[x] * (cnt[x] - 1) / 2;
    };
    auto del = [&](int x) {
        sum -= cnt[x] * (cnt[x] - 1) / 2;
        cnt[x]--;
        sum += cnt[x] * (cnt[x] - 1) / 2;        
    };

    vector<i64> ans(q + 1);
    for (int i = 1; i <= q; ++i) {
        auto [ql, qr, id] = query[i];
        while (l > ql) add(a[--l]);
        while (r < qr) add(a[++r]);
        while (l < ql) del(a[l++]);
        while (r > qr) del(a[r--]);
        ans[id] = sum;
    }

    for (int i = 1; i <= q; ++i) {
        cout << ans[i] << endl;
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