#include <bits/stdc++.h>
using namespace std;
using f64 = double;
using i64 = long long;

void solve() {
    int n; f64 v;
    cin >> n >> v;

    // 0: plus 1: multi
    array<vector<f64>, 2> op;
    for (int i = 0; i < n; ++i) {
        char c; f64 x;
        cin >> c >> x;

        op[c == '*'].push_back(x);
    }

    for (auto& v : op) sort(v.begin(), v.end());

    int N = max(n * 2 / 3, 1);
    int m = op[1].size(); n = op[0].size();
    
    // for dp[i] mul i times
    vector<vector<array<f64, 2>>> dp(m + 1);
    for (int sta = 0; sta < 1 << N; ++sta) {
        int pc = popcount<unsigned>(sta);
        if (pc > n) continue;
        pc = N - pc;
        if (pc > m) continue;

        f64 cur = v, sum = 0;
        int addpos = n - 1, mulpos = m - 1;

        for (int i = 0; i < N; ++i) {
            if (sta >> i & 1) cur += op[0][addpos], --addpos;
            else cur *= op[1][mulpos], --mulpos;

            sum += cur;
        }

        dp[pc].push_back({sum, cur});
    }

    int M = n + m - N;
    auto get = [&](f64 s, f64 now, int add, int mul) -> f64 {
        f64 ans = 0;

        for (int sta = 0; sta < 1 << M; ++sta) {
            int pc = popcount<unsigned>(sta);
            if (add + pc > n) continue;
            pc = M - pc;
            if (mul + pc > m) continue;

            f64 cur = now, sum = 0;
            int addpos = n - 1 - add, mulpos = m - 1 - mul;
            for (int i = 0; i < M; ++i) {
                if (sta >> i & 1) cur += op[0][addpos], --addpos;
                else cur *= op[1][mulpos], --mulpos;

                sum += cur;
            }

            ans = max(ans, sum + s);
        }
        return ans;
    };

    f64 ans = 0;
    for (int i = 0; i <= m; ++i) {
        // remove some of dp[i]
        auto& v = dp[i];
        sort(v.begin(), v.end(), greater{});

        set<f64> s;
        int sz = v.size();
        for (int j = 0; j < sz; ++j) {
            auto it = s.lower_bound(v[j][1]);

            if (it != s.end()) continue;
            s.insert(v[j][1]);

            int add = N - i;
            ans = max(ans, get(v[j][0], v[j][1], add, i));
        }
    }

    cout << ans / (n + m) << "\n";
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(0);
    cout << fixed << setprecision(10);
    solve();
    return 0;
}