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

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    vector<array<int, 3>> query(q + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> query[i][0] >> query[i][1];
        query[i][2] = i;
    }

    int block = sqrt(n);
    sort(a.begin() + 1, a.end(), [&](const array<int, 3>& x, const array<int, 3>& y) {
        if(x[0] / block != y[0] / block) {
            return x[1] < y[1];
        } return x[0] / block < y[0] / block;
    });

    vector<array<i64, 2>> ans(q + 1);
    vector<i64> cnt(n + 1);
    array<i64, 4> lst {};
    array<i64, 2> now {};
    int l = 1, r = 0;
    auto add = [&](int x) -> void {
        cnt[x]++;
        if(cnt[x] >= 2) {
            i64 res = (cnt[x] - 1) * cnt[x] / 2 * x;
            if(res > now[0] || res == now[0] && x < now[1]) {
                now[0] = res, now[1] = x;
            }
        }
    };
    auto clear = [&]() -> void {
        while(l <= r) {
            cnt[a[l++]]--;
        }
        now[0] = now[1] = 0;
    };

    for(int i = 1; i <= q; ++i) {
        auto [ql, qr, id] = query[i];
        int cur = ql / block;
        if(qr / block == cur) {
            clear();
            l = ql, r = ql - 1;
            while(r < qr) add(a[++r]);
            ans[id] = now;
        } else if() {
            
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}