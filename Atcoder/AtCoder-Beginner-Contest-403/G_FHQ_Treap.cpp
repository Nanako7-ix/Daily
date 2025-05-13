/**
 * Author:  Nanako7_ix
 * Created: 2025/04/29 16:26:27
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

struct Node {
    static mt19937 rng;
    i64 val, odd, even;
    int key;
    int size;
    unique_ptr<Node> l;
    unique_ptr<Node> r;
    
    Node(int v) : val(v), odd(v), even(0), key(rng()), size(1), l(nullptr), r(nullptr) {}
};

mt19937 Node::rng(chrono::steady_clock::now().time_since_epoch().count());
using NodePtr = unique_ptr<Node>;

inline void update(Node* p) {
    if (p == nullptr) return;
    p->size = p->odd = p->even = 0;
    if (p->l) {
        p->size += p->l->size;
        p->odd += p->l->odd;
        p->even += p->l->even;
    }
    (p->size % 2 == 1 ? p->even : p->odd) += p->val;
    p->size += 1;
    if (p->r) {
        (p->size % 2 == 1 ? p->even : p->odd) += p->r->odd;
        (p->size % 2 == 1 ? p->odd : p->even) += p->r->even;
        p->size += p->r->size;
    }
}

void split(NodePtr& root, int val, NodePtr& l, NodePtr& r) {
    if (!root) {
        l = nullptr;
        r = nullptr;
        return;
    }
    
    NodePtr temp = move(root);
    
    if (temp->val <= val) {
        split(temp->r, val, temp->r, r);
        l = move(temp);
    } else {
        split(temp->l, val, l, temp->l);
        r = move(temp);
    }
    
    if (l) update(l.get());
    if (r) update(r.get());
}

void splitByRank(NodePtr& root, int k, NodePtr& l, NodePtr& r) {
    if (!root) {
        l = nullptr;
        r = nullptr;
        return;
    }
    
    int leftSize = root->l ? root->l->size : 0;
    
    NodePtr temp = move(root);
    
    if (leftSize + 1 <= k) {
        splitByRank(temp->r, k - leftSize - 1, temp->r, r);
        l = move(temp);
    } else {
        splitByRank(temp->l, k, l, temp->l);
        r = move(temp);
    }
    
    if (l) update(l.get());
    if (r) update(r.get());
}

NodePtr merge(NodePtr l, NodePtr r) {
    if (!l) return move(r);
    if (!r) return move(l);
    
    if (l->key > r->key) {
        l->r = merge(move(l->r), move(r));
        update(l.get());
        return move(l);
    } else {
        r->l = merge(move(l), move(r->l));
        update(r.get());
        return move(r);
    }
}

NodePtr insert(NodePtr root, int val) {
    NodePtr l = nullptr, r = nullptr;
    split(root, val, l, r);

    auto newNode = make_unique<Node>(val);
    return merge(merge(move(l), move(newNode)), move(r));
}

void solve() {
    NodePtr root = nullptr;

    i64 n, last = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        i64 x; cin >> x;
        x = (x + last) % 1000000000 + 1;
        root = insert(move(root), x);
        cout << root->odd << endl;
        last = root->odd;
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