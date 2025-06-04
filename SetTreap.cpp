#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

struct Node {
    int val;
    int key;
    int size;
    unique_ptr<Node> l;
    unique_ptr<Node> r;
    
    Node(int v) : val(v), key(rand()), size(1), l(nullptr), r(nullptr) {}
};

inline void update(Node* p) {
    if (p) {
        p->size = 1;
        if (p->l) p->size += p->l->size;
        if (p->r) p->size += p->r->size;
    }
}

void split(unique_ptr<Node>& root, int val, unique_ptr<Node>& l, unique_ptr<Node>& r) {
    if (!root) {
        l = nullptr;
        r = nullptr;
        return;
    }
    
    unique_ptr<Node> temp = move(root);
    
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

void splitByRank(unique_ptr<Node>& root, int k, unique_ptr<Node>& l, unique_ptr<Node>& r) {
    if (!root) {
        l = nullptr;
        r = nullptr;
        return;
    }
    
    int leftSize = root->l ? root->l->size : 0;
    
    unique_ptr<Node> temp = move(root);
    
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

unique_ptr<Node> merge(unique_ptr<Node> l, unique_ptr<Node> r) {
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

inline unique_ptr<Node> insert(unique_ptr<Node> root, int val) {
    unique_ptr<Node> l = nullptr, r = nullptr;
    split(root, val, l, r);
    
    auto newNode = make_unique<Node>(val);
    return merge(merge(move(l), move(newNode)), move(r));
}

unique_ptr<Node> remove(unique_ptr<Node> root, int val) {
    if (!root) return nullptr;
    
    unique_ptr<Node> l = nullptr, m = nullptr, r = nullptr;
    split(root, val, l, r);
    split(l, val - 1, l, m);
    
    if (m) {
        if (!m->l && !m->r) {
            m = nullptr;
        } else {
            unique_ptr<Node> temp = nullptr;
            splitByRank(m, 1, temp, m);
        }
    }
    
    return merge(merge(move(l), move(m)), move(r));
}

int kth(const Node* root, int k) {
    if (!root) return -1;
    
    int leftSize = root->l ? root->l->size : 0;
    
    if (leftSize + 1 == k) {
        return root->val;
    } else if (leftSize >= k) {
        return kth(root->l.get(), k);
    } else {
        return kth(root->r.get(), k - leftSize - 1);
    }
}

int getRank(const Node* root, int val) {
    if (!root) return 1;
    
    if (val <= root->val) {
        return getRank(root->l.get(), val);
    } else {
        int leftSize = root->l ? root->l->size : 0;
        return leftSize + 1 + getRank(root->r.get(), val);
    }
}

int getPrev(unique_ptr<Node>& root, int val) {
    if (!root) return -0x7fffffff;
    
    unique_ptr<Node> l = nullptr, r = nullptr;
    unique_ptr<Node> rootCopy = move(root);
    
    split(rootCopy, val - 1, l, r);
    
    int res = -0x7fffffff;
    if (l) {
        Node* p = l.get();
        while (p->r) p = p->r.get();
        res = p->val;
    }
    
    root = merge(move(l), move(r));
    return res;
}

int getNext(unique_ptr<Node>& root, int val) {
    if (!root) return 0x7fffffff;
    
    unique_ptr<Node> l = nullptr, r = nullptr;
    unique_ptr<Node> rootCopy = move(root);
    
    split(rootCopy, val, l, r);
    
    int res = 0x7fffffff;
    if (r) {
        Node* p = r.get();
        while (p->l) p = p->l.get();
        res = p->val;
    }
    
    root = merge(move(l), move(r));
    return res;
}

void inorder(const Node* root) {
    if (!root) return;
    inorder(root->l.get());
    cout << root->val << " ";
    inorder(root->r.get());
}

bool checkTree(const Node* root) {
    if (!root) return true;
    
    if (root->l && root->l->val > root->val) {
        cout << "BST property violated: " << root->l->val << " > " << root->val << endl;
        return false;
    }
    
    if (root->r && root->r->val <= root->val) {
        cout << "BST property violated: " << root->r->val << " <= " << root->val << endl;
        return false;
    }
    
    return checkTree(root->l.get()) && checkTree(root->r.get());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    srand(time(nullptr));
    
    unique_ptr<Node> root = nullptr;

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        root = insert(move(root), x);
    }

    int ans = 0, lst = 0;
    for (int i = 0; i < m; ++i) {
        int op, x;
        cin >> op >> x;
        x ^= lst;
        
        switch (op) {
            case 1:
                root = insert(move(root), x);
                break;
            case 2:
                root = remove(move(root), x);
                break;
            case 3:
                lst = getRank(root.get(), x);
                ans ^= lst;
                break;
            case 4:
                lst = kth(root.get(), x);
                ans ^= lst;
                break;
            case 5:
                lst = getPrev(root, x);
                ans ^= lst;
                break;
            case 6:
                lst = getNext(root, x);
                ans ^= lst;
                break;
        }
    }

    cout << ans << endl;

    return 0;
}