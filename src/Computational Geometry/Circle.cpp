struct circle {
	point o;
	double r, r2; // r ^ 2
	circle(): o(), r(0.0), r2(0.0) {}
	circle(const point &o, const double &r): o(o), r(r), r2(r * r) {}
	bool inside(const point &a) { return sign((a - o).norm() - r2) <= 0; }
	bool intersectWithLine(const point &S, const point &T, point &A, point &B) const { // guarantee det(OA, OB) >= 0
		if (sign(det(o - S, T - S)) > 0)
			return intersectWithLine(T, S, A, B);
		double h = dist(S, T, o);
		if (sign(h - r) > 0) return false;
		double l = Sqrt(r2 - sqr(h));
		point mm = (T - S).unit().rot(-PI / 2) * h + o;
		point vv = (T - S).unit() * l;
		A = mm - vv;
		B = mm + vv;
		return true;
	}
	bool contain(const circle &b) const {
		return sign(b.r + (o - b.o).len() - r) <= 0;
	}

	bool disjunct(const circle &b) const {
		return sign(b.r + r - (o - b.o).len()) <= 0;
	}
};

bool twoCircleIntersect(const circle &a, const circle &b, point &A, point &B) { // a, b should not be the same
	if (a.contain(b) || b.contain(a) || a.disjunct(b)) return 0;
	double s1 = (a.o - b.o).len();
	double s2 = (a.r2 - b.r2) / s1;
	double aa = (s1 + s2) / 2;
	double bb = (s1 - s2) / 2;
	double h = Sqrt(a.r2 - sqr(aa));
	point mm = (b.o - a.o) * (aa / (aa + bb)) + a.o;
	point vv = (b.o - a.o).unit().rot(PI / 2) * h; // rot(x, y) => (y, -x)
	A = mm + vv;
	B = mm - vv;
	return 1;
}

double twoCircleIntersectArea(const circle &a, const circle &b) {
	if (a.r < b.r) return twoCircleIntersectArea(b, a);
	double ans = 0;
	double d = (a.o - b.o).len();
    if (d + EPS > a.r + b.r) return 0;
    if (d < a.r - b.r + EPS) return PI * b.r2;
    double a1 = arcCos((a.r2 + sqr(d) - b.r2) * 0.5 / a.r / d);
    double a2 = arcCos((b.r2 + sqr(d) - a.r2) * 0.5 / b.r / d);
    ans -= d * a.r * sin(a1);
    ans += a1 * a.r2 + a2 * b.r2;
    return ans;
}

circle minCircle(const point &a, const point &b) { return circle((a + b) * 0.5, (b - a).len() * 0.5); }

circle minCircle(const point &a, const point &b, const point &c) { // WARNING: Obtuse triangle is not considered
	double A = 2 * a.x - 2 * b.x;
	double B = 2 * a.y - 2 * b.y;
	double C = a.x * a.x + a.y * a.y - b.x * b.x - b.y * b.y;
	double D = 2 * a.x - 2 * c.x;
	double E = 2 * a.y - 2 * c.y;
	double F = a.x * a.x + a.y * a.y - c.x * c.x - c.y * c.y;
	point p((C * E - B * F) / (A * E - B * D), (A * F - C * D) / (A * E - B * D));
	return circle(p, (p - a).len());
}

circle minCircle(point P[], int N) {
	if (N == 1) return circle(P[1], 0.0);
	random_shuffle(P + 1, P + N + 1);
	circle O = minCircle(P[1], P[2]);
	Rep(i, 3, N) if(!O.inside(P[i])) {
		O = minCircle(P[1], P[i]);
		Foru(j, 2, i) if(!O.inside(P[j])) {
			O = minCircle(P[i], P[j]);
			Foru(k, 1, j) if(!O.inside(P[k]))
				O = minCircle(P[i], P[j], P[k]);
		}
	}
	return O;
}
