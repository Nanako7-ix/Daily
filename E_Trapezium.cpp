#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

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
    double angle() const { return atan2(y, x); }
    friend point operator+(point lhs, const point& rhs) { lhs += rhs; return lhs; }
    friend point operator-(point lhs, const point& rhs) { lhs -= rhs; return lhs; }
    friend point operator*(point p, const T& k) { p *= k; return p; }
    friend point operator/(point p, const T& k) { p /= k; return p; }
    friend point operator*(const T& k, point p) { p *= k; return p; }
    friend bool operator==(const point& lhs, const point& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
    friend auto operator<=>(const point& lhs, const point& rhs) = default;
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

using Point = point<i64>;

void Thephix() {
    int n;
    cin >> n;
    vector<Point> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<pair<Point, i64>> b;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            Point p = a[i] - a[j];
            if (sign(p) < 0) p = -p;
            b.emplace_back(
                p,
                dot(a[i] - a[j], a[i] - a[j])
            );
        }
    }
    
    sort(b.begin(), b.end(), [](pair<Point, i64> x, pair<Point, i64> y) {
        if (cross(x.first, y.first) == 0) {
            return x.second < y.second;
        } return compare<i64> {}.operator()(x.first, y.first);
    });
    
    int m = b.size();
    i64 ans = 0, ans2 = 0;
    for (int l = 0, r = -1; l < m; l = r + 1) {
        map<i64, i64> len;
        while (r + 1 < m && cross(b[l].first, b[r + 1].first) == 0) {
            r++;
            len[b[r].second]++;
        }
        i64 cnt = r - l + 1;
        ans += cnt * (cnt - 1) / 2;
        for (auto [x, y] : len) {
            ans2 += y * (y - 1) / 2;
        }
    }
    cout << ans - ans2 / 2 << "\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}