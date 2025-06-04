/**
 * Author:  Nanako7_ix
 * Created: 2025/05/07 19:55:19
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

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

struct Point {
    i64 x, y;
    Point () { x = y = 0; }
    Point (i64 x, i64 y) {
        this -> x = x;
        this -> y = y;
    }
    friend i64 cross(const Point& a, const Point& b) {
        return a.x * b.y - a.y * b.x;
    }
    friend i64 dot(const Point& a, const Point& b) {
        return a.x * b.x + a.y * b.y;
    }
};

void solve() {
    int n, m, p;
    cin >> n >> m >> p;
    vector<int> b(n + 1);
    for (int i = 2; i <= n; ++i) {
        cin >> b[i];
        b[i] += b[i - 1];
    }

    i64 ans = 0;
    vector<int> a(m + 1), x;
    for (int i = 1; i <= m; ++i) {
        int h, t;
        cin >> h >> t;
        int val = t - b[h];
        if (val < 0) ans -= val;
        x.push_back(a[i] = max(val, 0));
    }

    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    auto rank = [&](int val) {
        return lower_bound(x.begin(), x.end(), val) - x.begin() + 1;
    };
    n = x.size();

    vector<i64> cnt(n + 1), sum(n + 1);
    for (int i = 1; i <= m; ++i) {
        cnt[rank(a[i])]++;
        sum[rank(a[i])] += a[i];
    }

    for (int i = 1; i <= n; ++i) {
        cnt[i] += cnt[i - 1];
        sum[i] += sum[i - 1];
    }

    vector<i64> dp(n + 1, INF);
    dp[0] = 0;
    // dp[i] = min(dp[j] + sum[j] - cnt[j] * x[i - 1])) + cnt[i] * x[i - 1] - sum[i];
    auto X = [&](int i) { return cnt[i]; };
    auto Y = [&](int i) { return dp[i] + sum[i]; };
    auto check = [&](int i, int  j, int k) -> bool {
        Point p1 {X(j) - X(i), Y(j) - Y(i)};
        Point p2 {X(k) - X(j), Y(k) - Y(j)};
        if (cross(p2, p1) == 0) {
            return p2.y <= 0;
        } return cross(p2, p1) > 0; 
    };

    while (p--) {
        vector<i64> ndp(n + 1, INF);
        ndp[0] = 0;
        deque<int> q;
        for (int i = 1; i <= n; ++i) {
            // insert(i - 1);
            while (q.size() >= 2 && check(q[q.size() - 2], q[q.size() - 1], i - 1)) {
                q.pop_back();
            }
            q.push_back(i - 1);
            // ndp[i] = query(x[i - 1]);
            while (q.size() >= 2) {
                Point line {X(q[1]) - X(q[0]), Y(q[1]) - Y(q[0])};
                if (cross(line, Point(1LL, x[i - 1])) < 0) {
                    break;
                }
                q.pop_front();
            }
            int j = q[0];
            ndp[i] = dp[j] + (cnt[i] - cnt[j]) * x[i - 1] - sum[i] + sum[j];
        }
        swap(dp, ndp);
    }
    cout << ans + dp[n] << endl;
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