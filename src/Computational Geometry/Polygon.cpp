struct Polygon { // stored in [0, n)
	int n; point ps[MAXN];
	Polygon cut(const point &a, const point &b) {
		static Polygon res; static point o; res.n = 0;
		for (int i = 0; i < n; ++i) {
			int s1 = sign(det(ps[i] - a, b - a));
			int s2 = sign(det(ps[(i + 1) % n] - a, b - a));
			if (s1 <= 0) res.ps[res.n++] = ps[i];
			if (s1 * s2 < 0) {
				lineIntersect(a, b, ps[i], ps[(i + 1) % n], o);
				res.ps[res.n++] = o;
			}
		} return res;
	}
	bool contain(const point &p) const { // 1 if on border or inner, 0 if outter
		static point A, B; int res = 0;
		for (int i = 0; i < n; ++i) {
			A = ps[i]; B = ps[(i + 1) % n];
			if (p.onSeg(A, B)) return 1;
			if (sign(A.y - B.y) <= 0) swap(A, B);
			if (sign(p.y - A.y) > 0) continue;
			if (sign(p.y - B.y) <= 0) continue;
			res += (int)(sign(det(B - p, A - p)) > 0);
		} return res & 1;
	}
	#define qs(x) (ps[x] - ps[0])
	bool convexContain(point p) const { // `counter-clockwise`
		point q = qs(n - 1); p = p - ps[0];
		if (!p.inAngle(qs(1), q)) return false;
		int L = 0, R = n - 1;
		while (L + 1 < R) { int M((L + R) >> 1);
			if (p.inAngle(qs(M), q)) L = M; else R = M;
		} if (L == 0) return false; point l(qs(L)), r(qs(R));
		return sign( fabs(det(l, p)) + fabs(det(p, r)) + fabs(det(r - l, p - l)) - det(l, r) ) == 0;
	}
	#undef qs
	double isPLAtan2(const point &a, const point &b) {
		double k = (b - a).alpha(); if (k < 0) k += 2 * PI;
		return k;
	}
	point isPL_Get(const point &a, const point &b, const point &s1, const point &s2) {
		double k1 = det(b - a, s1 - a), k2 = det(b - a, s2 - a);
		if (sign(k1) == 0) return s1;
		if (sign(k2) == 0) return s2;
		return (s1 * k2 - s2 * k1) / (k2 - k1);
	}
	int isPL_Dic(const point &a, const point &b, int l, int r) {
		int s = (det(b - a, ps[l] - a) < 0) ? -1 : 1;
		while (l <= r) {
			int mid = (l + r) / 2;
			if (det(b - a, ps[mid] - a) * s <= 0) r = mid - 1;
			else l = mid + 1;
		}
		return r + 1;
	}
	int isPL_Find(double k, double w[]) {
		if (k <= w[0] || k > w[n - 1]) return 0;
		int l = 0, r = n - 1, mid;
		while (l <= r) {
			mid = (l + r) / 2;
			if (w[mid] >= k) r = mid - 1;
			else l = mid + 1;
		} return r + 1;
	}
	bool isPL(const point &a, const point &b, point &cp1, point &cp2) {  // `$O (log N)$`
		static double w[MAXN * 2]; // `pay attention to the array size`
		for (int i = 0; i <= n; ++i) ps[i + n] = ps[i];
		for (int i = 0; i < n; ++i) w[i] = w[i + n] = isPLAtan2(ps[i], ps[i + 1]);
		int i = isPL_Find(isPLAtan2(a, b), w);
		int j = isPL_Find(isPLAtan2(b, a), w);
		double k1 = det(b - a, ps[i] - a), k2 = det(b - a, ps[j] - a);
		if (sign(k1) * sign(k2) > 0) return false; // `no intersection`
		if (sign(k1) == 0 || sign(k2) == 0) { // `intersect with a point or a line in the convex`
			if (sign(k1) == 0) {
				if (sign(det(b - a, ps[i + 1] - a)) == 0) cp1 = ps[i], cp2 = ps[i + 1];
				else cp1 = cp2 = ps[i];
				return true;
			}
			if (sign(k2) == 0) {
				if (sign(det(b - a, ps[j + 1] - a)) == 0) cp1 = ps[j], cp2 = ps[j + 1];
				else cp1 = cp2 = ps[j];
			}
			return true;
		}
		if (i > j) swap(i, j);
		int x = isPL_Dic(a, b, i, j), y = isPL_Dic(a, b, j, i + n);
		cp1 = isPL_Get(a, b, ps[x - 1], ps[x]);
		cp2 = isPL_Get(a, b, ps[y - 1], ps[y]);
		return true;
	}
	double getI(const point &O) const {
		if (n <= 2) return 0;
		point G(0.0, 0.0);
		double S = 0.0, I = 0.0;
		for (int i = 0; i < n; ++i) {
			const point &x = ps[i], &y = ps[(i + 1) % n];
			double d = det(x, y);
			G = G + (x + y) * d / 3.0;
			S += d;
		} G = G / S;
		for (int i = 0; i < n; ++i) {
			point x = ps[i] - G, y = ps[(i + 1) % n] - G;
			I += fabs(det(x, y)) * (x.norm() + dot(x, y) + y.norm());
		}
		return I = I / 12.0 + fabs(S * 0.5) * (O - G).norm();
	}
};
