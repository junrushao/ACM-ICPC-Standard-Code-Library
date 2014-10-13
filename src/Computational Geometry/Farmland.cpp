struct node { int begin[MAXN], *end; } a[MAXN]; // `按对 $p[i]$ 的极角的 atan2 值排序`
bool check(int n, point p[], int b1, int b2, bool vis[MAXN][MAXN]) {
	static pii l[MAXN * 2 + 1]; static bool used[MAXN];
	int tp(0), *k, p, p1, p2; double area(0.0);
	for (l[0] = pii(b1, b2); ; ) {
		vis[p1 = l[tp].first][p2 = l[tp].second] = true;
		area += det(p[p1], p[p2]);
		for (k = a[p2].begin; k != a[p2].end; ++k) if (*k == p1) break;
		k = (k == a[p2].begin) ? (a[p2].end - 1) : (k - 1);
		if ((l[++tp] = pii(p2, *k)) == l[0]) break;
	} if (sign(area) < 0 || tp < 3) return false;
	Rep(i, 1, n) used[i] = false;
	for (int i = 0; i < tp; ++i) if (used[p = l[i].first]) return false; else used[p] = true;
	return true; // `a face with tp vertices`
}
int countFaces(int n, point p[]) {
	static bool vis[MAXN][MAXN]; int ans = 0;
	Rep(x, 1, n) Rep(y, 1, n) vis[x][y] = false;
	Rep(x, 1, n) for (int *itr = a[x].begin; itr != a[x].end; ++itr) if (!vis[x][*itr])
		if (check(n, p, x, *itr, vis)) ++ans;
	return ans;
}