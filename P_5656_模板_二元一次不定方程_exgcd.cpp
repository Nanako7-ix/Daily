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

constexpr i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    if(b == 0) {
        assert(a != 0);
        x = a / abs(a), y = 0;
        return abs(a);
    }
    i64 d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

constexpr i64 safeMod(i64 a, i64 b) { if((a %= b) <= 0) a += b; return a; }

void solve() {
    i64 a, x, b, y, c;
    cin >> a >> b >> c;
    i64 d = exgcd(a, b, x, y);
    if(c % d) {
        cout << "-1\n";
    } else {
        c /= d, a /= d, b /= d;
        x *= c, y *= c;
        i64 minx, miny, maxx, maxy, k;
        minx = safeMod(x, b);
        k = (minx - x) / b;
        maxy = y - k * a;

        miny = safeMod(y, a);
        k = (miny - y) / a;
        maxx = x - k * b;
        
        if(maxx <= 0 || maxy <= 0) {
            cout << minx << ' ' << miny << endl;
        } else {
            cout << (maxx - minx) / b + 1 << ' ';
            cout << minx << ' ' << miny << ' ' << maxx << ' ' << maxy << endl;
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}