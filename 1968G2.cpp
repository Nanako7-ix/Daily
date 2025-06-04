/**
 * Author: Nanako7_ix
 * Created: 2025/04/24 12:33:33
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

vector<int> Zfunction(string s) {
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    for(int i = 1, j = 1; i < n; ++i) {
        z[i] = max(0, min(z[i - j], j + z[j] - i));
        while(i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
        if(i + z[i] > j + z[j]) j = i;
    }
    return z;
};

void solve() {
    int n, l, r;
    cin >> n >> l >> r;
    string s;
    cin >> s;

    vector Z = Zfunction(s);
    SparseTable Max(Z.begin(), Z.end(), [](int x, int y) {
        return max(x, y);
    });

    vector<int> f(n + 1);
    for (int len = 1; len <= n; ++len) {
        for (int i = 1; i <= n; ++i) {
            int lo = i, hi = n, res = -1;
            while (lo <= hi) {
                int mid = (lo + hi) >> 1;
                if (Max(i, mid) >= len) {
                    res = mid, hi = mid - 1;
                } else lo = mid + 1;
            }
            if (res == -1) break;
            f[len]++, i = res + len - 1;
        }
    }

    for (int i = l; i <= r; ++i) {
        cout << upper_bound(f.begin() + 1, f.end(), i, greater {}) - f.begin() - 1 << " \n"[i == r];
    }
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