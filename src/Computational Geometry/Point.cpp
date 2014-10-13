#define EPS 1e-7
#define PI 3.1415926535897932384626

inline int sign(const double &a, const double &eps = EPS) { return a < -eps ? -1 : int(a > eps); }
inline double sqr(const double &x) { return x * x; }
inline double Sqrt(const double &x) { return x < 0 ? 0 : sqrt(x); }

inline double arcSin(const double &a) {
	if (a <= -1.0) return -PI / 2;
	if (a >=  1.0) return PI / 2;
	return asin(a);
}

inline double arcCos(const double &a) {
	if (a <= -1.0) return PI;
	if (a >=  1.0) return 0;
	return acos(a);
}

struct point {
	double x, y;
	point(): x(0.0), y(0.0) {}
	point(const double &x, const double &y): x(x), y(y) {}
	point operator + (const point &rhs) const { return point(x + rhs.x, y + rhs.y); }
	point operator - (const point &rhs) const { return point(x - rhs.x, y - rhs.y); }
	point operator * (const double &k) const { return point(x * k, y * k); }
	point operator / (const double &k) const { return point(x / k, y / k); }
	double len() const { return hypot(x, y); }
	double norm() const { return x * x + y * y; }
	point unit() const { double k = len(); return point(x / k, y / k); }
	point rot(const double &a) const { return point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
	friend double dot(const point &a, const point &b) { return a.x * b.x + a.y * b.y; }
	friend double det(const point &a, const point &b) { return a.x * b.y - a.y * b.x; }
	friend double dist(const point &a, const point &b, const point &c) { // dist from C to AB
		return fabs(det(a - c, b - c) / (a - b).len());
	}
	friend double angle(const point &a, const point &b) { // angle between a and b
		return arcCos(dot(a, b) / a.len() / b.len());
	}
};

bool onSeg(const point &a, const point &b, const point &c) { // C is not strict on AB
	return sign(dot(a - c, b - c)) <= 0 && sign(det(b - a, c - a)) == 0;
}

bool lineIntersect(const point &a, const point &b, const point &c, const point &d, point &e) {
	double s1 = det(c - a, d - a);
	double s2 = det(d - b, c - b);
	if (!sign(s1 + s2)) return 0;
	e = (b - a) * (s1 / (s1 + s2)) + a;
	return 1;
}

bool segIntersect(const point &a, const point &b, const point &c, const point &d, point &e) { // A simpler version
	double s1 = det(c - a, d - a), s2 = det(d - b, c - b);
	if (!sign(s1 + s2)) return 0;
	e = (b - a) * (s1 / (s1 + s2)) + a;
	return onSeg(a, b, e) && onSeg(c, d, e);
}

// returns 0 if not intersect, 1 if proper intersect, 2 if improper intersect
int iCnt;
int segIntersectCheck(const point &a, const point &b, const point &c, const point &d, point &o) {
	static double s1, s2, s3, s4;
	int d1 = sign(s1 = det(b - a, c - a)), d2 = sign(s2 = det(b - a, d - a));
	int d3 = sign(s3 = det(d - c, a - c)), d4 = sign(s4 = det(d - c, b - c));
	if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) {
		o = (c * s2 - d * s1) / (s2 - s1);
		return 1;
	}
	iCnt = 0;
	if (d1 == 0 && onSeg(a, b, c)) o = c, ++iCnt;
	if (d2 == 0 && onSeg(a, b, d)) o = d, ++iCnt;
	if (d3 == 0 && onSeg(c, d, a)) o = a, ++iCnt;
	if (d4 == 0 && onSeg(c, d, b)) o = b, ++iCnt;
	return iCnt ? 2 : 0;
}
