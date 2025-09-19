#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<typename T>
struct Point {
	using value_type = T;
	T x, y;
	Point () : x(0), y(0) {}
	Point (const T& x, const T& y) : x(x), y(y) { }
	
	T   dot(const Point& o) const { return x * o.x + y * o.y; }
	T cross(const Point& o) const { return x * o.y - y * o.x; }

	Point  operator- () const { return Point { -x, -y }; }
	Point& operator+=(const Point& o) & { x += o.x, y += o.y; return *this; }
	Point& operator-=(const Point& o) & { x -= o.x, y -= o.y; return *this; }
	Point& operator*=(const T& k) & { x *= k, y *= k; return *this; }
	Point& operator/=(const T& k) & { x /= k, y /= k; return *this; }
	
	friend Point operator+(Point x, const Point& y) { return x += y; }
	friend Point operator-(Point x, const Point& y) { return x -= y; }
	friend Point operator*(Point p, const T& k) { return p *= k; }
	friend Point operator*(const T& k, Point p) { return p *= k; }
	friend Point operator/(Point p, const T& k) { return p /= k; }
	
	friend bool operator== (const Point& x, const Point& y) { return x.x == y.x && x.y == y.y; }
	friend auto operator<=>(const Point& x, const Point& y) = default;
	
	friend istream& operator>> (istream& is, Point& p) { return is >> p.x >> p.y; }
	friend ostream& operator<< (ostream& os, const Point& p) { return os << "(" << p.x << ", " << p.y << ")"; }

	T square() const { return dot(*this); }
};

template<typename Iter, typename point = std::iterator_traits<Iter>::value_type>
auto Andrew(Iter l, Iter r) {
	std::vector p(l, r);
	std::sort(p.begin(), p.end());

	int n = r - l, x = 0, y = 0;
	std::vector<point> u(n), d(n);
	for (auto p : p) {
		while (x > 1 && (u[x - 1] - u[x - 2]).cross(p - u[x - 1]) >= 0) x--;
		while (x && p.x == u[x - 1].x) x--;
		u[x++] = p;
		while (y > 1 && (d[y - 1] - d[y - 2]).cross(p - d[y - 1]) <= 0) y--;
		if (y == 0 || d[y - 1].x < p.x) d[y++] = p;
	}
	u.resize(x), d.resize(y);

	return std::pair { u, d };
}

template<typename Iter, typename point = std::iterator_traits<Iter>::value_type>
auto Area(Iter l, Iter r) {
	using T = point::value_type;
	T ans = 0;
	int n = r - l;
	for (int i = 0; i < n; ++i) {
		int j = (i + 1) % n;
		ans += l[i].cross(l[j]);
	}
	return std::abs(ans);
}

using point = Point<i64>;

constexpr double PI = acos(-1);

void Thephix() {
	int n, R2, R3;
	cin >> n >> R2 >> R3;

	vector<point> p(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> p[i];
	}

	auto [u, d] = Andrew(p.begin() + 1, p.end());

	reverse(u.begin(), u.end());
	if (u.back() == d[0]) u.pop_back();
	if (u[0] == d.back()) d.pop_back();
	p.clear();
	p.insert(p.end(), u.begin(), u.end());
	p.insert(p.end(), d.begin(), d.end());

	double S = Area(p.begin(), p.end()) / 2.0;

	n = p.size();
	double C = 0;
	for (int i = 0; i < n; ++i) {
		int j = (i + 1) % n;
		C += sqrt((p[i] - p[j]).square());
	}

	double V = 0;
	V += (S + PI * R2 * R2 + C * R2) * (2 * R3);
	V += C * PI * R3 * R3 / 2.0;
	V += PI * PI * R2 * R3 * R3 + 4 * PI * R3 * R3 * R3 / 3.0;
	cout << V << endl;
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	cin >> T;

	cout << fixed << setprecision(18);
	
	while (T--) {
		Thephix();
	}

	return 0;
}
