struct Event { point p; double alpha; int add; // `构造函数省略`
	bool operator < (const Event &other) const { return alpha < other.alpha; } };
void circleKCover(circle *c, int N, double *area) { // `$area[k]$ : 至少被覆盖$k$次`
	static bool overlap[MAXN][MAXN], g[MAXN][MAXN];
	Rep(i, 0, N + 1) area[i] = 0.0; Rep(i, 1, N) Rep(j, 1, N) overlap[i][j] = c[i].contain(c[j]);
	Rep(i, 1, N) Rep(j, 1, N) g[i][j] = !(overlap[i][j] || overlap[j][i] || c[i].disjunct(c[j]));
	Rep(i, 1, N) { static Event events[MAXN * 2 + 1]; int totE = 0, cnt = 1;
		Rep(j, 1, N) if (j != i && overlap[j][i]) ++cnt;
		Rep(j, 1, N) if (j != i && g[i][j]) {
			circle &a = c[i], &b = c[j]; double l = (a.o - b.o).norm();
			double s = ((a.r - b.r) * (a.r + b.r) / l + 1) * 0.5;
			double t = sqrt(-(l - sqr(a.r - b.r)) * (l - sqr(a.r + b.r)) / (l * l * 4.0));
			point dir = b.o - a.o, nDir = point(-dir.y, dir.x);
			point aa = a.o + dir * s + nDir * t;
			point bb = a.o + dir * s - nDir * t;
			double A = atan2(aa.y - a.o.y, aa.x - a.o.x);
			double B = atan2(bb.y - a.o.y, bb.x - a.o.x);
			events[totE++] = Event(bb, B, 1); events[totE++] = Event(aa, A, -1); if (B > A) ++cnt;
		} if (totE == 0) { area[cnt] += PI * c[i].rSquare; continue; }
		sort(events, events + totE); events[totE] = events[0];
		Foru(j, 0, totE) {
			cnt += events[j].add; area[cnt] += 0.5 * det(events[j].p, events[j + 1].p);
			double theta = events[j + 1].alpha - events[j].alpha; if (theta < 0) theta += 2.0 * PI;
			area[cnt] += 0.5 * c[i].rSquare * (theta - sin(theta));
}}}