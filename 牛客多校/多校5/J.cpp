#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int dir[4][2] = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}
};

void Thephix() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a  (n + 1, vector<int> (m + 1));
    vector<vector<int>> vis(n + 1, vector<int> (m + 1));
    vector<vector<i64>> dp (n + 1, vector<i64> (m + 1, 4E18));
    queue<array<int, 2>> q;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            if (a[i][j] == 1) {
                q.push({i, j});
                vis[i][j] = 1;
                dp[i][j] = 0;
            }
        }
    }
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int tx = x + dir[i][0];
            int ty = y + dir[i][1];
            if (tx < 1 || tx > n || ty < 1 || ty > m || vis[tx][ty]) {
                continue;
            }
            dp[tx][ty] = dp[x][y] + 1;
            vis[tx][ty] = 1;
            q.push({tx, ty});
        }
    }

    auto check = [&](int dis) -> bool {
        vector<int> add, sub;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (dp[i][j] > dis) {
                    add.push_back(i + j);
                    sub.push_back(i - j);
                }
            }
        }
        if (add.size() == 0) return true;
        
        int add_min = *min_element(add.begin(), add.end());
        int add_max = *max_element(add.begin(), add.end());
        int sub_min = *min_element(sub.begin(), sub.end());
        int sub_max = *max_element(sub.begin(), sub.end());
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (add_min >= i + j - dis
                 && add_max <= i + j + dis
                 && sub_min >= i - j - dis
                 && sub_max <= i - j + dis
                ) return true;
            }
        }
        return false;
    };

    auto another_check = [&](int dis) -> bool {
        int add_L = -1E9, add_R = 1E9; 
        int sub_L = -1E9, sub_R = 1E9; 
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (dp[i][j] > dis) {
                    add_L = max(add_L, i + j - dis);
                    add_R = min(add_R, i + j + dis);
                    sub_L = max(sub_L, i - j - dis);
                    sub_R = min(sub_R, i - j + dis);
                }
            }
        }
        if (add_L == add_R && sub_L == sub_R && (add_L - sub_L) % 2 != 0) {
            return false;
        }
        return add_L <= add_R && sub_L <= sub_R;
    };
    
    int l = 0, r = n + m - 1, res = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (another_check(mid)) {
            res = mid, r = mid - 1;
        } else l = mid + 1;
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