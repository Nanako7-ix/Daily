/**
 * Author:  Nanako7_ix
 * Created: 2025/05/09 00:57:52
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

template<typename T> bool pointInPolygon(const point<T> &a, const std::vector<point<T>> &p) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (pointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
            return true;
        }
    }

    int t = 0;
    for (int i = 0; i < n; i++) {
        auto u = p[i], v = p[(i + 1) % n];
        if (u.x < a.x && a.x <= v.x && pointOnLineLeft(a, Line(u, v))) {
            t ^= 1;
        }
        if (v.x < a.x && a.x <= u.x && pointOnLineLeft(a, Line(v, u))) {
            t ^= 1;
        }
    }    
    return t == 1;
}

template<typename T> auto getHull(std::vector<point<T>> p) {
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
    return std::make_pair(hi, lo);
}

using Point = point<double>;

void solve() {
    int n;
    double x, y, r;
    cin >> n >> y >> x >> r;
    x -= 2 * r, y -= 2 * r;

    array<Point, 4> v {
        point {+x/2, +y/2},
        point {+x/2, -y/2},
        point {-x/2, +y/2},
        point {-x/2, -y/2}
    };

    vector<Point> a;
    for (int i = 1; i <= n; ++i) {
        double tx, ty, theta;
        cin >> tx >> ty >> theta;
        for (auto p : v) {
            a.push_back(Point(tx, ty) + p.rotate(theta));
        }
    }

    auto [hi, lo] = getHull(a);
    double ans = length(Line(hi[0], lo[0])) + length(Line(hi.back(), lo.back()));
    for (int i = 1; i < (int) hi.size(); ++i) {
        ans += length(Line(hi[i], hi[i - 1]));
    }
    for (int i = 1; i < (int) lo.size(); ++i) {
        ans += length(Line(lo[i], lo[i - 1]));
    }

    cout << fixed << setprecision(2) << ans + 2 * PI * r << endl;
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