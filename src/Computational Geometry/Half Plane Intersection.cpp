struct Border {
	point p1, p2; double alpha;
	Border() : p1(), p2(), alpha(0.0) {}
	Border(const point &a, const point &b): p1(a), p2(b), alpha( atan2(p2.y - p1.y, p2.x - p1.x) ) {}
	bool operator == (const Border &b) const { return sign(alpha - b.alpha) == 0; }
	bool operator < (const Border &b) const {
		int c = sign(alpha - b.alpha); if (c != 0) return c > 0;
		return sign(det(b.p2 - b.p1, p1 - b.p1)) >= 0;
	}
};
point isBorder(const Border &a, const Border &b) { // a and b should not be parallel
	point is; lineIntersect(a.p1, a.p2, b.p1, b.p2, is); return is;
}
bool checkBorder(const Border &a, const Border &b, const Border &me) {
	point is; lineIntersect(a.p1, a.p2, b.p1, b.p2, is);
	return sign(det(me.p2 - me.p1, is - me.p1)) > 0;
}
double HPI(int N, Border border[]) {
	static Border que[MAXN * 2 + 1]; static point ps[MAXN];
	int head = 0, tail = 0, cnt = 0; // [head, tail)
	sort(border, border + N); N = unique(border, border + N) - border;
	for (int i = 0; i < N; ++i) {
		Border &cur = border[i];
		while (head + 1 < tail && !checkBorder(que[tail - 2], que[tail - 1], cur)) --tail;
		while (head + 1 < tail && !checkBorder(que[head], que[head + 1], cur)) ++head;
		que[tail++] = cur;
	} while (head + 1 < tail && !checkBorder(que[tail - 2], que[tail - 1], que[head])) --tail;
	while (head + 1 < tail && !checkBorder(que[head], que[head + 1], que[tail - 1])) ++head;
	if (tail - head <= 2) return 0.0;
	Foru(i, head, tail) ps[cnt++] = isBorder(que[i], que[(i + 1 == tail) ? (head) : (i + 1)]);
	double area = 0; Foru(i, 0, cnt) area += det(ps[i], ps[(i + 1) % cnt]);
	return fabs(area * 0.5); // or (-area * 0.5)
}