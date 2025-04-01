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

template<typename T>
struct CartesianTree {
    int rt;
    vector<T> w;
    vector<int> ls, rs;
    template<typename Iterator, typename Func, typename = _RequireInputIter<Iterator>>
    CartesianTree(const Iterator& l, const Iterator& r, Func&& f) : w(l, r) {
        int n = r - l;
        ls.assign(n + 1, 0);
        rs.assign(n + 1, 0);
        vector<int> stk;
        for(int i = 1; i <= n; ++i) {
            while(!stk.empty() && f(operator[](i), operator[](stk.back()))) {
                ls[i] = stk.back();
                stk.pop_back();
            }
            if(!stk.empty()) rs[stk.back()] = i;
            stk.push_back(i);
        }
        while(stk.size() != 1) stk.pop_back();
        rt = stk.back();
    }
    const T& operator[](int i) {
        return w[i - 1];
    }
};

template<typename Iterator, typename Func>
CartesianTree(const Iterator&, const Iterator&, Func&&) ->
CartesianTree<typename std::iterator_traits<Iterator>::value_type>;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    vector<vector<int>> pos(2 * n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    vector<int> le(n + 1), ri;
    vector<int> stk;
    for(int i = 1; i <= n; ++i) {
        while(!stk.empty() && a[i] < a[stk.back()]) {
            stk.pop_back();
        }
    }

    CartesianTree tr(a.begin() + 1, a.end(), greater<int> {});
    auto ls = [&](int u) { return tr.ls[u]; };
    auto rs = [&](int u) { return tr.rs[u]; };

    i64 ans = 0, sum = 0;
    [&](this auto &&dfs, int u, int fa) {
        if(u == 0) return;
        assert(a[ls(u)] < a[u]);
        dfs(ls(u), u);
        dfs(rs(u), u);
    } (tr.rt, 0);

    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}