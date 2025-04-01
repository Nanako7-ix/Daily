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
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    map<int, int> cnt1;
    if(a == 0) {
        while(b) {
            cnt1[__lg(b)]++;
            b -= 1 << __lg(b);
        }
    } else {
        while(a != b) {
            int lowbit = a & -a;
            if(a + lowbit > b) break;
            cnt1[__lg(lowbit)]++;
            a += lowbit;
        }
        b -= a;
        while(b) {
            cnt1[__lg(b)]++;
            b -= 1 << __lg(b);
        }
    }
    map<int, int> cnt2;
    if(c == 0) {
        while(d) {
            cnt2[__lg(d)]++;
            d -= 1 << __lg(d);
        }
    } else {
        while(c != d) {
            int lowbit = c & -c;
            if(c + lowbit > d) break;
            cnt2[__lg(lowbit)]++;
            c += lowbit;
        }
        d -= c;
        while(d) {
            cnt2[__lg(d)]++;
            d -= 1 << __lg(d);
        }
    }
    i64 ans = 0;
    for(auto [i, x] : cnt1) {
        for(auto [j, y] : cnt2) {
            ans += x * y << abs(i - j);
        }
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}