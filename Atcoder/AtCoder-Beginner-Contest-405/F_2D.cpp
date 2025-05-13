/**
 *
 * $$$$$$\  $$$$$$\  $$$$$$\  $$\       $$\       $$$$$$\  
 * $$  __$$\ \_$$  _|$$  __$$\ $$ |      $$ |     $$  __$$\ 
 * $$ /  \__|  $$ |  $$ /  $$ |$$ |      $$ |     $$ /  $$ |
 * $$ |        $$ |  $$$$$$$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |        $$ |  $$  __$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |  $$\   $$ |  $$ |  $$ |$$ |      $$ |     $$ |  $$ |
 * $$$$$$  | $$$$$$\ $$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$  |
 * \______/  \______|\__|  \__|\________|\________|\______/ 
 *
 * Author:  Nanako7_ix
 * Created: 2025/05/14 00:00:39
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

template<typename Info>
struct Fenwick {
private:
    int n;
    std::vector<Info> tr;
    vector<int> a;
    constexpr int lowbit(int x) {
        return x & -x;
    }
public:
    Fenwick () = default;

    Fenwick (int n, Info e = {}) { init(n, e); }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    Fenwick (const Iterator& l, const Iterator& r) { init(l, r); }

    void init (int n, Info e = {}) {
        vector<Info> _(n, e);
        init(_.begin(), _.end());
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    void init (const Iterator& l, const Iterator& r) {
        n = r - l;
        tr.assign(n + 1, Info {});
        a.assign(n + 1, Info {});
        for(int i = 1; i <= n; ++i) {
            a[i] = *(l + i - 1);
            tr[i] += *(l + i - 1);
            if(i + lowbit(i) <= n) {
                tr[i + lowbit(i)] += tr[i];
            }
        }
    }

    void modify (int p, const Info& v) {
        a[p] += v;
        for(; p <= n; p += lowbit(p)) {
            tr[p] += v;
        }
    }

    Info query (int p) {
        Info res{};
        for(; p; p -= lowbit(p)) {
            res += tr[p];
        }
        return res;
    }

    Info query (int l, int r) {
        assert(l <= r && l != 0);
        return query(r) - query(l - 1);
    }

    int lower_bound (Info k) {
        int x = 0;
        for(int i = 1 << std::__lg(n); i; i >>= 1)
            if(x + i <= n && tr[x + i] < k)
                k -= tr[x += i];
        return x + 1;
    }

    int upper_bound (Info k) {
        int x = 0;
        for(int i = 1 << std::__lg(n); i; i >>= 1)
            if(x + i <= n && tr[x + i] <= k)
                k -= tr[x += i];
        return x + 1;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    n <<= 1;

    map<int, vector<array<int, 2>>> L, R;
    for (int i = 1; i <= m; ++i) {
        int l, r;
        cin >> l >> r;
        L[l].push_back({r, 0});
        R[r].push_back({l, 0});
    }
    
    int q; cin >> q;
    for (int i = 1; i <= q; ++i) {
        int l, r;
        cin >> l >> r;
        L[l].push_back({r, i});
        R[r].push_back({l, i});
    }
    
    vector<i64> ans(q + 1);
    Fenwick<int> tr(n);
    for (int l = 1; l <= n; ++l) {
        for (auto [r, id] : L[l]) {
            if (id == 0) {
                tr.modify(r, 1);
            } else {
                ans[id] += tr.query(r) - tr.query(l);
            }
        }
    }
    tr.init(n);
    for (int r = n; r >= 1; --r) {
        for (auto [l, id] : R[r]) {
            if (id == 0) {
                tr.modify(l, 1);
            } else {
                ans[id] += tr.query(r) - tr.query(l);
            }
        }
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