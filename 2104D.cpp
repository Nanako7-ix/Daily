/**
 * Author:  Nanako7_ix
 * Created: 2025/04/28 23:06:09
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

vector<int> minp, primes;
vector<i64> sum;
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

int solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    if (n == 1) {
        return a[n] == 1;
    }

    sort(a.begin() + 1, a.end(), greater {});
    vector<i64> pre(n + 1);
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + a[i];
    }

    int l = 0, r = n, res = -1;
    auto check = [&](int x) {
        return pre[x] >= (x == 0 ? 0 : sum[x - 1]);
    };
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            res = mid, l = mid + 1;
        } else r = mid - 1;
    }

    assert(res != -1);
    return n - res;
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    cin >> T;

    sieve(6E6);
    for (auto p : primes) {
        if (sum.empty()) {
            sum.push_back(p);
        } else {
            sum.push_back(p + sum.back());
        }
    }

    while (T--) {
        cout << solve() << endl;
    }
    
    return 0;
}