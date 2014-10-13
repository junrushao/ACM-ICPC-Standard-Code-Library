int isPL(point a, point b, vector<point> &res) { // `点逆时针给出，无三点共线`
	static double theta[MAXN];
	for (int i = 0; i < n; ++i) theta[i] = (list[(i + 1) % n] - list[i]).atan2();
	double delta = theta[0];
	for (int i = 0; i < n; ++i) theta[i] = normalize(theta[i] - delta);
	int x = lower_bound(theta, theta + n, normalize((b - a).atan2() - delta)) - theta;
	int y = lower_bound(theta, theta + n, normalize((a - b).atan2() - delta)) - theta;
	for (int k = 0; k <= 1; ++k, swap(a, b), swap(x, y)) {
		if (y < x) y += n;
		int l = x, r = y, m;
		while (l + 1 < r) {
			if (sign(det(b - a, list[(m = (l + r) / 2) % n] - a)) < 0) l = m;
			else r = m;
		}
		l %= n, r %= n;
		if (sign(det(b - a, list[r] - list[l])) == 0) {
			if (sign(det(b - a, list[l] - a)) == 0)
			return -l; // `直线与 $(list[l], list[r])$ 重合`
		}
		else {
			point p; lineIntersect(list[l], list[r], a, b, p);
			if (p.onSeg(list[l], list[r]))
			res.push_back(p);
		}
	}
	return res.size();
}
