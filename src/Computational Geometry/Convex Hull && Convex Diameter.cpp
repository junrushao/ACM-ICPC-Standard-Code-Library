vector<point> convexHull(int n, point ps[]) { // `counter-clockwise, strict`
	static point qs[MAXN * 2];
	sort(ps, ps + n, cmpByXY);
	if (n <= 2) return vector(ps, ps + n);
	int k = 0;
	for (int i = 0; i < n; qs[k++] = ps[i++])
		while (k > 1 && det(qs[k - 1] - qs[k - 2], ps[i] - qs[k - 1]) < EPS) --k;
	for (int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--])
		while (k > t && det(qs[k - 1] - qs[k - 2], ps[i] - qs[k - 1]) < EPS) --k;
	return vector<point>(qs, qs + k);
}
double convexDiameter(int n, point ps[]) {
	if (n < 2) return 0; if (n == 2) return (ps[1] - ps[0]).len();
	double k, ans = 0;
	for (int x = 0, y = 1, nx, ny; x < n; ++x) {
		for(nx = (x == n - 1) ? (0) : (x + 1); ; y = ny) {
			ny = (y == n - 1) ? (0) : (y + 1);
			if ( sign(k = det(ps[nx] - ps[x], ps[ny] - ps[y])) <= 0) break;
		} ans = max(ans, (ps[x] - ps[y]).len());
		if (sign(k) == 0) ans = max(ans, (ps[x] - ps[ny]).len());
	} return ans;
}