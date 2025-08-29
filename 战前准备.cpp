/**
 *
 *  $$$$$$\  $$$$$$\  $$$$$$\  $$\       $$\       $$$$$$\  
 * $$  __$$\ \_$$  _|$$  __$$\ $$ |      $$ |     $$  __$$\ 
 * $$ /  \__|  $$ |  $$ /  $$ |$$ |      $$ |     $$ /  $$ |
 * $$ |        $$ |  $$$$$$$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |        $$ |  $$  __$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |  $$\   $$ |  $$ |  $$ |$$ |      $$ |     $$ |  $$ |
 *  $$$$$$ | $$$$$$\ $$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$  |
 * \______/  \______|\__|  \__|\________|\________|\______/ 
 *
 * Author:  Nanako7_ix
 * Created: 2025/07/11 20:59:55
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define debug(x) cerr << "\033[31m" << #x << " = " << x << "\033[0m\n"
using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64 = double;

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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), ok(n + 1);
    vector<vector<int>> pos(m + 1);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i]++;
        pos[a[i]].push_back(i);
    }

    SparseTable Max(a.begin() + 1, a.end(), [](int x, int y) {
        return max(x, y);
    });

    for (int i = m; i >= 1; --i) {
        for (auto p : pos[i]) {
            if (i == m) {
                ok[p] = 1;
                continue;
            }
            if (Max(p, n) <= i) {
                int l = 1, r = p, res = -1;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (Max(1, mid) > i) {
                        res = mid, r = mid - 1;
                    } else l = mid + 1;
                }
                assert(res != -1);
                ok[p] = ok[res] && a[res] == i + 1;
            } else {
                int l = p, r = n, res = -1;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (Max(p, mid) > i) {
                        res = mid, r = mid - 1;
                    } else l = mid + 1;
                }
                assert(res != -1);
                ok[p] = ok[res] && a[res] == i + 1;
            }
        }
    }

    int ans = 0;
    for (auto p : pos[1]) {
        ans += ok[p];
    }
    cout << ans << "\n";
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