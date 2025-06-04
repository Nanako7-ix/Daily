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
const double pi = acos(-1);

namespace Geometry {
    template<typename T>
    struct Point {
        T x, y;
    
        Point () : x(0), y(0) {}
        Point (const T& x, const T& y) {
            this -> x = x;
            this -> y = y;
        }
    
        template<typename U>
        operator Point<U> () {
            return Point<U> (U(x), U(y));
        }
    
        Point operator-() const {
            return Point { -x, -y };
        }
        Point& operator+=(const Point& o) & {
            x += o.x;
            y += o.y;
            return *this;
        }
        Point& operator-=(const Point& o) & {
            x -= o.x;
            y -= o.y;
            return *this;
        }
        Point& operator*=(const T& k) {
            x *= k;
            y *= k;
            return *this;
        }
        Point& operator/=(const T& k) {
            x /= k;
            y /= k;
            return *this;
        }
        friend Point operator+(Point lhs, const Point& rhs) {
            lhs += rhs;
            return lhs;
        }
        friend Point operator-(Point lhs, const Point& rhs) {
            lhs -= rhs;
            return lhs;
        }
        friend Point operator*(Point p, const T& k) {
            p *= k;
            return p;
        }
        friend Point operator/(Point p, const T& k) {
            p /= k;
            return p;
        }
        friend Point operator*(const T& k, Point p) {
            p *= k;
            return p;
        }
        friend bool operator==(const Point& lhs, const Point& rhs) {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }
        friend istream& operator>>(istream& is, Point& p) {
            return is >> p.x >> p.y;
        }
        friend ostream& operator<<(ostream& os, const Point& p) {
            return os << "(" << p.x << ", " << p.y << ")";
        }
    };
    
    template<typename T>
    struct Line {
        Point<T> a;
        Point<T> b;
        Line (const Point<T>& a, const Point<T>& b) {
            this -> a = a;
            this -> b = b;
        }
    };
    
    template<typename T>
    T dot(const Point<T>& a, const Point<T>& b) {
        return a.x * b.x + a.y * b.y;
    }
    
    template<typename T>
    T cross(const Point<T>& a, const Point<T>& b) {
        return a.x * b.y - a.y * b.x;
    }
    
    template<typename T>
    T square(const Point<T>& p) {
        return dot(p, p);
    }
    
    template<typename T>
    double length(const Point<T> &p) {
        return std::sqrt(square(p));
    }
    
    template<typename T>
    double length(const Line<T> &l) {
        return length(l.a - l.b);
    }
    
    template<typename T>
    Point<T> normalize(const Point<T> &p) {
        return p / length(p);
    }
    
    template<typename T>
    bool parallel(const Line<T> &l1, const Line<T> &l2) {
        return cross(l1.b - l1.a, l2.b - l2.a) == 0;
    }
    
    template<typename T>
    double distance(const Point<T>& a, const Point<T>& b) {
        return length(b - a);
    }
    
    template<typename T>
    double distancePL(const Point<T>& p, const Line<T>& l) {
        return std::abs(cross(p - l.a, l.b - l.a)) / length(l);
    }
    
    template<typename T>
    double distancePS(const Point<T>& p, const Line<T>& l) {
        if (dot(p - l.a, p.b - p.a) < 0) {
            return length(p - l.a);
        }
        if (dot(p - p.b, p.a - p.b) < 0) {
            return length(p - l.b);
        }
        return distancePL(p, l);
    }
    
    template<typename T>
    Point<T> rotate(const Point<T>& p) {
        return Point<T> { -p.y, p.x };
    }
    
    template<typename T>
    int sgn(const Point<T>& p) {
        return p.y > 0 || (p.y == 0 && p.x > 0) ? 1 : -1;
    }
    
    template<typename T>
    struct comPare {
        bool operator()(const Point<T>& p1, const Point<T>& p2) {
            if (sgn(p1) != sgn(p2)) return sgn(p1) == 1;
            return cross(p1, p2) > 0;
        }
        bool operator()(const Line<T>& l1, const Line<T>& l2) {
            return this -> operator()(l1.b - l1.a, l2.b - l2.a);
        }
    };
    
    template<typename T>
    bool pointOnLineLeft(const Point<T> &p, const Line<T> &l) {
        return cross(l.b - l.a, p - l.a) > 0;
    }
    
    template<typename T>
    Point<T> lineIntersection(const Line<T> &l1, const Line<T> &l2) {
        return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
    }
    
    template<typename T>
    bool pointOnSegment(const Point<T> &p, const Line<T> &l) {
        return cross(p - l.a, l.b - l.a) == 0 
            && std::min(l.a.x, l.b.x) <= p.x && p.x <= std::max(l.a.x, l.b.x)
            && std::min(l.a.y, l.b.y) <= p.y && p.y <= std::max(l.a.y, l.b.y);
    }
    
    template<typename T>
    bool pointInPolygon(const Point<T> &a, const std::vector<Point<T>> &p) {
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
}

using namespace Geometry;
using point = Point<double>;

void solve() {
    int n;
    double x, y, r;
    cin >> n >> x >> y >> r;

    array<point, 4> v {
        point {+x/2, +y/2},
        point {+x/2, -y/2},
        point {-x/2, +y/2},
        point {-x/2, -y/2}
    };

    vector<point> a;
    for (int i = 1; i <= n; ++i) {
        double tx, ty, theta;
        cin >> tx >> ty >> theta;
        for (auto p : v) {
            // a.push_back(point(tx, ty) + p.rotate(-theta));
        }
    }
    for (auto x : a) {
        cout << x.x << ' ' << x.y << endl;
    }

    // cout << ans + 2 * pi * r << endl;
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