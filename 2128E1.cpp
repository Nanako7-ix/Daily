#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

/**
 * 一个解法是考虑倒序枚举答案 v
 * 如何 check:
 *    考虑将大于等于 v 的部分记为 1, 小于 v 的部分记为 -1
 *    如果那么如果存在一个区间的和大于等于 0
 *    说明区间内 v 大于等于至少 ceil(n, 2) 的数
 *    这表明该区间存在一个 medium 大于等于 v
 *    而我是倒序枚举的, 所以找到的这个中位数一定是最大的 medium
 * 计算最大子段和这个不是线段树秒了吗?
 * 别急, 还有区间长度限制
 * 那完蛋了, 似乎不太可做了
 * 
 * 好, 注意到这个 check 是具有单调性的 !
 * 因为我们的 check 的本质是判断 v 是否小于等于最大的 medium
 * 所以我们可以使用二分.
 * 
 * 二分为我们节省的时间, 正好让我可以 O(n) check
 * 考虑一下如何 O(n) check:
 * 坏了 我不会 感觉这应该是一个很简单的问题 但是怎么不会呢
 * 
 * 好了我会了, 因为这是一个区间和的问题, 所以不妨前缀和优化
 * 你直接枚举右端点, 然后在 r - k + 1 以左的位置维护一下最小值及其出现位置
 * 然后如果 pre[r] - pre[p] 满足条件就可以直接退出了
 */

void Thephix() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    auto check = [&](int v) -> bool {
        vector<int> pre(n + 1);
        for (int i = 1; i <= n; ++i) {
            pre[i] = pre[i - 1] + (a[i] >= v ? 1 : -1);
        }
        int Min = 0;
        for (int l = 1, r = k; r <= n; ++l, ++r) {
            if (pre[r] - Min >= 0) {
                return true;
            }
            Min = min(Min, pre[l]);
        }
        return false;
    };

    int lo = 1, hi = n, res = -1;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (check(mid)) {
            res = mid;
            lo = mid + 1;
        } else hi = mid - 1;
    }

    assert(res != -1);
    cout << res << " ";

    vector<int> pre(n + 1);
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + (a[i] >= res ? 1 : -1);
    }
    int Min = 0, p = 0;
    for (int l = 1, r = k; r <= n; ++l, ++r) {
        if (pre[r] - Min >= 0) {
            cout << p + 1 << ' ' << r << "\n";
            return; 
        }
        if (pre[l] < Min) {
            Min = pre[l], p = l;
        }
    }
    assert(0);
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}