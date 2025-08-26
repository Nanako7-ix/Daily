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
 * 话说这个贪心一点都不像是 1200 的
 * 思路是, 我每次考虑维护操作的区间
 * 然后直接跳这些区间的最优答案, 问题就是如何维护这些区间
 * 我们考虑按 l 排序, 那么一定是逐步加入区间的
 * 接着右端点怎么办呢, 其实是可以维护的:
 *    用一个堆维护右端点及其贡献
 *    如果这个右端点已经比当前的答案小
 *    那么就不考虑它的贡献
 *    我们用一个 multiset 维护一下当前有哪些贡献即可
 * 诶? 如果 r 小于当前答案, 那么它的贡献一定不如当前答案啊
 * 那其实可以不用删掉不合法的区间
 * 因为它的答案一定是很垃圾的, 自然不会被我们考虑进去
 * 而如果贡献比当前答案优, 产生这个贡献的右端点一定大于当前答案
 * 而由于我们只把左端点小于当前答案的区间放进去, 所以贡献一定是合法的
 * 再加上我们是按左端点排序的, 所以一定可以考虑所有的区间
 * 
 * 哦, 其实连堆都不用, 毕竟只需要维护最大值, 唉我是唐诗喵
 * void Thephix() {
 *	 int n, ans;
 *	 cin >> n >> ans;
 * 
 *	 vector<array<i64, 3>> a(n + 1);
 *	 for (int i = 1; i <= n; ++i) {
 *		 auto& [l, r, val] = a[i];
 *		 cin >> l >> r >> val;
 *	 }
 * 
 *	 sort(a.begin(), a.end());
 *	 for (int i = 1; i <= n; ++i) {
 *		 auto [l, r, val] = a[i];
 *		 if (l <= ans) {
 *			 ans = max<i64>(ans, val);
 *		 }
 *	 }
 * 
 *	 cout << ans << "\n";
 * }
 */

template<typename T>
struct Discrete {
	int ready;
	vector<T> a;

	Discrete() {
		init();
	}

	void init() {
		ready = 0, a.clear();
	}

	void insert(const T& v) {
		assert(!ready);
		a.push_back(v);
	}

	void work() {
		ready = 1;
		sort(a.begin(), a.end());
		a.erase(unique(a.begin(), a.end()), a.end());
	}

	int lower_bound(const T& v) {
		if(!ready) work();
		return ::lower_bound(a.begin(), a.end(), v) - a.begin() + 1;
	}

	int upper_bound(const T& v) {
		if(!ready) work();
		return ::upper_bound(a.begin(), a.end(), v) - a.begin() + 1;
	}

	T operator[](int k) {
		if(!ready) work();
		return a[k - 1];
	}

	int size() {
		if(!ready) work();
		return a.size();
	}
};

struct SegmentGraph {
	int n;
	vector<int> p;
	vector<vector<int>> adj;
			
	SegmentGraph() = default;
			
	SegmentGraph(int n) {
		init(n);
	}

	void init(int n) {
		this -> n = n;
		p.assign(n + 1, 0);
		adj.assign(4 << __lg(n), {});
		build(1, 1, n);
	}

	void build(int u, int l, int r) {
		if (l == r) {
			p[l] = u;
			return;
		}
		adj[u << 1].push_back(u);
		adj[u << 1 | 1].push_back(u);

		int m = (l + r) >> 1;
		build(u << 1, l, m);
		build(u << 1 | 1, m + 1, r);
	}

	void link(int L, int R, int v, int u, int l, int r) {
		if (L <= l && r <= R) {
			adj[u].push_back(p[v]);
			return;
		}
		int m = (l + r) >> 1;
		if (L <= m) {
			link(L, R, v, u << 1, l, m);
		}
		if (R >= m + 1) {
			link(L, R, v, u << 1 | 1, m + 1, r);
		}
	}

	void link(int l, int r, int v) {
		link(l, r, v, 1, 1, n);
	}

	int size() {
		return 4 << __lg(n);
	}
};

/**
 * 这是什么, 区间连边 ?
 * 线段树优化建图启动!
 */

void Thephix () {
	int n, k;
	cin >> n >> k;

	Discrete<int> dis;
	dis.insert(k);
	vector<array<int, 3>> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		auto& [l, r, val] = a[i];
		cin >> l >> r >> val;
		dis.insert(l);
		dis.insert(r);
		dis.insert(val);
	}

	SegmentGraph G(dis.size());
	for (int i = 1; i <= n; ++i) {
		auto [l, r, val] = a[i];
		l = dis.lower_bound(l);
		r = dis.lower_bound(r);
		val = dis.lower_bound(val);
		G.link(l, r, val);
	}

	queue<int> q;
	vector<int> vis(G.size());
	int s = G.p[dis.lower_bound(k)];
	q.push(s), vis[s] = 1;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto v : G.adj[u]) {
			if (vis[v]) continue;
			vis[v] = 1;
			q.push(v);
		}
	}

	for (int i = dis.size(); i >= 1; --i) {
		if (vis[G.p[i]]) {
			cout << dis[i] << "\n";
			return;
		}
	}
}

signed main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}