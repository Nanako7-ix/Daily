/**
 * Author:  Nanako7_ix
 * Created: 2025/05/01 01:23:06
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

template<typename T, typename Func>
class SparseTable {
private:
    int n;
    Func op;
    std::vector<std::vector<T>> st;
public:
    SparseTable () = default;

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    SparseTable (const Iterator& l, const Iterator& r, Func&& f) : op(f) {
        init(l, r);
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    void init (const Iterator& l, const Iterator& r) {
        n = r - l;
        st.assign(std::__lg(n) + 1, std::vector<T> (n + 1));
        for (int i = 1; i <= n; ++i) {
            st[0][i] = *(l + i - 1);
        }
        for (int i = 1; i <= std::__lg(n); ++i) {
            for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
                st[i][j] = op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    T operator () (int l, int r) {
        if (l > r) return 0;
        assert(l <= r);
        int k = std::__lg(r - l + 1);
        return op(st[k][l], st[k][r - (1 << k) + 1]);
    }

    T query (int l, int r) {
        T res {};  
        int len = r - l + 1;
        for (int i = 0, k = l; i <= std::__lg(len); ++i) {
            if(len >> i & 1) {
                res = k == l ? st[i][l] : op(res, st[i][k]);
                k += 1 << i;
            }
        }
        return res;
    }
};

template<typename Iterator, typename Func>
SparseTable (const Iterator&, const Iterator&, Func&&) ->
SparseTable<typename std::iterator_traits<Iterator>::value_type, Func>;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int gcd3(int x, int y, int z) {
    return gcd(gcd(x, y), z);
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }

    vector<int> p;
    for (int i = n, Gcd = 0; i >= 1; --i) {
        if (gcd(Gcd, a[i]) != Gcd) {
            p.push_back(i);
            Gcd = gcd(Gcd, a[i]);
        }
    }
    for (int i = n, Gcd = 0; i >= 1; --i) {
        if (gcd(Gcd, b[i]) != Gcd) {
            p.push_back(i);
            Gcd = gcd(Gcd, b[i]);
        }
    }

    p.push_back(0);
    sort(p.begin(), p.end(), greater {});
    p.erase(unique(p.begin(), p.end()), p.end());

    vector<int> prea(n + 1), preb(n + 1), sufa(n + 2), sufb(n + 2);
    for (int i = 1; i <= n; ++i) {
        prea[i] = gcd(prea[i - 1], a[i]);
        preb[i] = gcd(preb[i - 1], b[i]);
    }
    for (int i = n; i >= 1; --i) {
        sufa[i] = gcd(sufa[i + 1], a[i]);
        sufb[i] = gcd(sufb[i + 1], b[i]);
    }

    SparseTable Ga(a.begin() + 1, a.end(), [](int x, int y) {
        return gcd(x, y);
    });
    SparseTable Gb(b.begin() + 1, b.end(), [](int x, int y) {
        return gcd(x, y);
    });

    array<i64, 2> ans {};
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < (int) p.size(); ++j) {
            int l = max(p[j], i) + 1, r = p[j - 1];
            if (l > r) break;
            i64 F1 = gcd3(prea[i - 1], Gb(i, l - 1), sufa[l]);
            i64 F2 = gcd3(preb[i - 1], Ga(i, l - 1), sufb[l]);

            ans[0] = max(ans[0], F1 + F2);
        }
        ans[0] = max<i64> (ans[0], gcd(prea[i - 1], sufb[i]) + gcd(preb[i - 1], sufa[i]));
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < (int) p.size(); ++j) {
            int l = max(p[j], i) + 1, r = p[j - 1];
            if (l > r) break;
            
            i64 F1 = gcd3(prea[i - 1], Gb(i, l - 1), sufa[l]);
            i64 F2 = gcd3(preb[i - 1], Ga(i, l - 1), sufb[l]);

            if (F1 + F2 != ans[0]) continue;

            auto check = [&](int x) {
                int f1 = gcd3(prea[i - 1], Gb(i, x - 1), sufa[x]);
                int f2 = gcd3(preb[i - 1], Ga(i, x - 1), sufb[x]);
                return f1 + f2 == ans[0];
            };

            int lo = l, hi = r, res = -1;
            while (lo <= hi) {
                int mid = (lo + hi) >> 1;
                if (check(mid)) {
                    res = mid, lo = mid + 1;
                } else hi = mid - 1;
            }

            ans[1] += res - l + 1;
        }
        if (gcd(prea[i - 1], sufb[i]) + gcd(preb[i - 1], sufa[i]) == ans[0]) {
            ans[1]++;
        }
    }
    cout << ans[0] << ' ' << ans[1] << endl;
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}