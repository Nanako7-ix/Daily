/**
 * Author:  Nanako7_ix
 * Created: 2025/04/30 21:19:55
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

template<typename T>
struct Point {
    T x, y;
    Point() {
        x = y = T {};
    }
    Point(T x, T y) {
        this -> x = x;
        this -> y = y;
    }
    Point operator-() const {
        return Point { -x, -y };
    }
    Point& operator+=(const Point& o) & {
        x += o.x;
        y += o.y;
        return *this;
    }
    Point& operator-=(const Point& o) & {
        x -= o.x;
        y -= o.y;
        return *this;
    }
    Point& operator*=(const T& k) {
        x = k * x;
        y = k * y;
        return *this;
    }
    friend Point operator+(Point lhs, const Point& rhs) {
        lhs += rhs;
        return lhs;
    }
    friend Point operator-(Point lhs, const Point& rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend Point operator*(Point p, const T& k) {
        p *= k;
        return p;
    }
    friend Point operator*(const T& k, Point p) {
        p *= k;
        return p;
    }
    friend T dot(const Point& lhs, const Point& rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }
    friend T cross(const Point& lhs, const Point& rhs) {
        return lhs.x * rhs.y - lhs.y * rhs.x;
    }
};


void solve() {
    int n, m;
    cin >> n >> m;
    vector<i64> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i]++;
    }

    sort(a.begin(), a.end());
    int N = a[n] + 2 * m - 1;
    vector<i64> cnt(N + 1), sum(N + 1);
    for (int i = 1; i <= n; ++i) {
        cnt[a[i]]++;
        sum[a[i]] += a[i];
    }
    for (int i = 1; i <= N; ++i) {
        cnt[i] += cnt[i - 1];
        sum[i] += sum[i - 1];
    }

    /**
     * dp[i] 表示最后最后一次发车在 i, 只考虑发车前到达的人, 至少需要等待多久
     * dp[i] = min(dp[j] + (cnt[i] - cnt[j]) * i - sum[i] + sum[j])
     *       = min(dp[j] - cnt[j] * i + sum[j]) + cnt[i] * i - sum[i]
     * 如果我能求出 min(dp[j] - cnt[j] * i + sum[j]) 那么我就能求出 dp[i]
     * 
     * 斜率优化核心: min/max(Y(j) - K(i) * X(j))
     * 也就是需要求斜率固定的一族直线的最小/最大截距
     * 而求解这个可以通过维护凸包来解决
     * 
     * 在本题中, K(i) = i, Y(j) = dp[j] + sum[j], X(j) = cnt[j]
     * 注意到, K(i) 具有单调性, 那么就可以把单调栈二分优化成单调队列
     */
    vector<i64> dp(N + 1);

    deque<int> q;
    auto X = [&](int p) { return cnt[p]; };
    auto Y = [&](int p) { return dp[p] + sum[p]; };
    auto check = [&](int i, int  j, int k) -> bool {
        Point p1 {X(j) - X(i), Y(j) - Y(i)};
        Point p2 {X(k) - X(j), Y(k) - Y(j)};
        if (cross(p2, p1) == 0) {
            return p2.y <= 0;
        } return cross(p2, p1) > 0; 
    };
    auto insert = [&](int p) -> void {
        while (q.size() >= 2 && check(q[q.size() - 2], q[q.size() - 1], p)) {
            q.pop_back();
        }
        q.push_back(p);
    };
    auto query = [&](i64 k) {
        while (q.size() >= 2) {
            Point line(X(q[1]) - X(q[0]), Y(q[1]) - Y(q[0]));
            if (cross(line, Point(1LL, k)) < 0) {
                break;
            }
            q.pop_front();
        }
        return Y(q[0]) - k * X(q[0]);
    };

    i64 ans = INF;
    for (int i = 1; i <= N; ++i) {
        if (i <= m) {
            dp[i] = i * cnt[i] - sum[i];
        } else {
            insert(i - m);
            dp[i] = query(i) + cnt[i] * i - sum[i];
        }
        if (i >= a[n]) {
            ans = min(ans, dp[i]);
        }
    }
    cout << ans << endl;
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