#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 inf = 4E18;

const double PI = acos(-1);
template<typename T> struct point {
    T x, y;
    point () : x(0), y(0) {}
    point (const T& x, const T& y) : x(x), y(y) { }
    template<typename U> operator point<U> () { return point<U> (U(x), U(y)); }
    point operator-() const { return point { -x, -y }; }
    point& operator+=(const point& o) & { x += o.x, y += o.y; return *this; }
    point& operator-=(const point& o) & { x -= o.x, y -= o.y; return *this; }
    point& operator*=(const T& k) { x *= k, y *= k; return *this; }
    point& operator/=(const T& k) { x /= k, y /= k; return *this; }
    point rotate (double a) { return point<double> (x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
    friend point operator+(point lhs, const point& rhs) { lhs += rhs; return lhs; }
    friend point operator-(point lhs, const point& rhs) { lhs -= rhs; return lhs; }
    friend point operator*(point p, const T& k) { p *= k; return p; }
    friend point operator/(point p, const T& k) { p /= k; return p; }
    friend point operator*(const T& k, point p) { p *= k; return p; }
    friend bool operator==(const point& lhs, const point& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
    friend istream& operator>>(istream& is, point& p) { return is >> p.x >> p.y; }
    friend ostream& operator<<(ostream& os, const point& p) { return os << "(" << p.x << ", " << p.y << ")"; }
};

template<typename T> struct Line {
    point<T> a, b;
    Line (const point<T>& a, const point<T>& b) : a(a), b(b) { }
};

template<typename T> struct compare {
    bool operator()(const point<T>& p1, const point<T>& p2) {
        return sign(p1) != sign(p2) ? sign(p1) == 1 : cross(p1, p2) > 0;
    }
    bool operator()(const Line<T>& l1, const Line<T>& l2) {
        return this -> operator()(l1.b - l1.a, l2.b - l2.a);
    }
};

template<typename T> T dot(const point<T>& a, const point<T>& b) { return a.x * b.x + a.y * b.y; }
template<typename T> T cross(const point<T>& a, const point<T>& b) { return a.x * b.y - a.y * b.x; }
template<typename T> T square(const point<T>& p) { return dot(p, p); }
template<typename T> int sign(const point<T>& p) { return p.y > 0 || (p.y == 0 && p.x > 0) ? 1 : -1; }
template<typename T> double length(const point<T> &p) { return std::sqrt(square(p)); }
template<typename T> double length(const Line<T> &l) { return length(l.a - l.b); }
template<typename T> point<T> normalize(const point<T> &p) { return p / length(p); }
template<typename T> bool parallel(const Line<T> &l1, const Line<T> &l2) { return cross(l1.b - l1.a, l2.b - l2.a) == 0; }
template<typename T> bool pointOnLineLeft(const point<T> &p, const Line<T> &l) { return cross(l.b - l.a, p - l.a) > 0; }
template<typename T> double distance(const point<T>& a, const point<T>& b) { return length(b - a); }
template<typename T> double distancePL(const point<T>& p, const Line<T>& l) { return std::abs(cross(p - l.a, l.b - l.a)) / length(l); }
template<typename T> double distancePS(const point<T>& p, const Line<T>& l) {
    if (dot(p - l.a, p.b - p.a) < 0) return length(p - l.a);
    if (dot(p - p.b, p.a - p.b) < 0) return length(p - l.b);
    return distancePL(p, l);
}
template<typename T> point<T> lineIntersection(const Line<T> &l1, const Line<T> &l2) {
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}
template<typename T> bool pointOnSegment(const point<T> &p, const Line<T> &l) {
    return cross(p - l.a, l.b - l.a) == 0 
        && std::min(l.a.x, l.b.x) <= p.x && p.x <= std::max(l.a.x, l.b.x)
        && std::min(l.a.y, l.b.y) <= p.y && p.y <= std::max(l.a.y, l.b.y);
}

template<typename T> auto Andrew(std::vector<point<T>> p) {
    std::sort(p.begin(), p.end(), [&](auto a, auto b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    
    std::vector<point<T>> hi, lo;
    for (auto p : p) {
        while (hi.size() > 1 && cross(hi.back() - hi[hi.size() - 2], p - hi.back()) >= 0) {
            hi.pop_back();
        }
        while (!hi.empty() && hi.back().x == p.x) {
            hi.pop_back();
        }
        hi.push_back(p);
        while (lo.size() > 1 && cross(lo.back() - lo[lo.size() - 2], p - lo.back()) <= 0) {
            lo.pop_back();
        }
        if (lo.empty() || lo.back().x < p.x) {
            lo.push_back(p);
        }
    }
    return std::pair {hi, lo};
}

void Thephix() {
    int n, m;
    cin >> n >> m;
    vector<array<i64, 4>> edges(m + 1);
    vector<vector<array<i64, 2>>> adj(n + 1);
    vector<vector<array<i64, 2>>> rev(n + 1);
    for (int i = 1; i <= m; ++i) {
        auto& [u, v, t, w] = edges[i];
        cin >> u >> v >> t >> w;
        adj[u].push_back({v, t});
        rev[v].push_back({u, t});
    }

    auto dijkstra = [&](int s, const vector<vector<array<i64, 2>>>& adj) {
        vector<i64> dp (n + 1, inf);
        vector<int> vis(n + 1);
        priority_queue<array<i64, 2>, vector<array<i64, 2>>, greater<array<i64, 2>>> q;
        q.push({ dp[s] = 0, s });
        while (!q.empty()) {
            auto [_, u] = q.top();
            q.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto [v, w] : adj[u]) {
                if (dp[u] + w < dp[v]) {
                    dp[v] = dp[u] + w;
                    q.push({ dp[v], v });
                }
            }
        }
        return dp;
    };

    auto dp1 = dijkstra(1, adj);
    auto dpn = dijkstra(n, rev);

    vector<point<i128>> points;
    for (int i = 1; i <= m; ++i) {
        auto [u, v, t, w] = edges[i];
        points.push_back({ w, dp1[u] + t + dpn[v] });
    }
    auto hull = Andrew(points).second;

    int q;
    cin >> q;
    vector<array<int, 2>> querys(q + 1);
    for (int i = 1; i <= q; ++i) {
        auto& [k, id] = querys[i];
        cin >> k, id = i;
    }
    sort(querys.begin() + 1, querys.end());

    vector<i64> ans(q + 1);
    for (int i = 1, j = 0; i <= q; ++i) {
        auto [k, id] = querys[i];
        while (
            j + 1 < (int) hull.size()
         && hull[j + 1].y - k * hull[j + 1].x <= hull[j].y - k * hull[j].x
        ) ++j;
        ans[id] = hull[j].y - k * hull[j].x;
    }

    for (int i = 1; i <= q; ++i) {
        cout << ans[i] << "\n";
    }
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