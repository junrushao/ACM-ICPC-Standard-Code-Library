int N; point p[maxn];
bool cmpByX(const point &a, const point &b) { return sign(a.x - b.x) < 0;  }
bool cmpByY(const int &a, const int &b) { return p[a].y < p[b].y;  }
double minimalDistance(point *c, int n, int *ys) {
	double ret = 1e+20;
	if (n < 20) {
		Foru(i, 0, n) Foru(j, i + 1, n) cMin(ret, (c[i] - c[j]).len() );
		sort(ys, ys + n, cmpByY); return ret; 
	} static int mergeTo[maxn];
	int mid = n / 2; double xmid = c[mid].x;
	ret = min(minimalDistance(c, mid, ys), minimalDistance(c + mid, n - mid, ys + mid));
	merge(ys, ys + mid, ys + mid, ys + n, mergeTo, cmpByY);
	copy(mergeTo, mergeTo + n, ys);
	Foru(i, 0, n) {
		while (i < n && sign(fabs(p[ys[i]].x - xmid) - ret) > 0) ++i;
		int cnt = 0;
		Foru(j, i + 1, n)
			if (sign(p[ys[j]].y - p[ys[i]].y - ret) > 0) break;
			else if (sign(fabs(p[ys[j]].x - xmid) - ret) <= 0) {
				ret = min(ret, (p[ys[i]] - p[ys[j]]).len());
				if (++cnt >= 10) break;
			}
	} return ret; 
}
double work() {
	sort(p, p + n, cmpByX); Foru(i, 0, n) ys[i] = i; return minimalDistance(p, n, ys);
}