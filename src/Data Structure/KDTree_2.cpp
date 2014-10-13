struct Point { int x, y, id; };
struct Rectangle {
	int lx, rx, ly, ry;
	void set(const Point &p) { lx = rx = p.x; ly = ry = p.y; }
	void merge(const Rectangle &o) {
		lx = min(lx, o.lx); rx = max(rx, o.rx); ly = min(ly, o.ly); ry = max(ry, o.ry);
	}
	LL dist(const Point &p) { LL res = 0;
		res += max(sqr(rx - p.x), sqr(lx - p.x));
		res += max(sqr(ry - p.y), sqr(ly - p.y));
		return res;
	}
}; struct Node { Point p; Rectangle rect; };
const int MAX_N = 111111;
const LL INF = 1LL << 60;
int n, m;
Point a[MAX_N], b[MAX_N ];
Node tree[MAX_N * 3];
Point p; // `p is the query point`
pair<LL, int> result[22];
void build(int k, int s, int t, bool d) {
	int mid = (s + t) >> 1;
	nth_element(a + s, a + mid , a + t, d ? cmpX : cmpY);
	tree[k].p = a[mid];
	tree[k].rect.set(a[mid]);
	if (s < mid)
		build(k << 1, s, mid , d ^ 1), tree[k].rect.merge(tree[k << 1]. rect);
	if (mid + 1 < t)
		build(k << 1 | 1, mid + 1, t, d ^ 1), tree[k].rect.merge(tree[k << 1 | 1]. rect);
}
void query(int k, int s, int t, bool d, int kth) {
	if (tree[k].rect.dist(p) < result[kth].first) return;
	pair<LL, int> tmp(dist(tree[k].p, p), -tree[k].p.id);
	for (int i = 1; i <= kth; i++) if (tmp > result[i]) {
		for (int j = kth + 1; j > i; j--) result[j] = result[j - 1]; result[i] = tmp;
		break;
	}
	int mid = (s + t) >> 1;
	if ((d && cmpX(p, tree[k].p)) || (!d && cmpY(p, tree[k].p))) {
		if (mid + 1 < t) query(k << 1 | 1, mid + 1, t, d ^ 1, kth);
		if (s < mid)     query(k << 1, s, mid , d ^ 1, kth);
	} else {
		if (s < mid)     query(k << 1, s, mid , d ^ 1, kth);
		if (mid + 1 < t) query(k << 1 | 1, mid + 1, t, d ^ 1, kth);
	}
}
void example(int n) {
	scan(a); build(1, 0, n, 0); // `init, $a[0 \ldots n - 1]$`
	scan(p, k);	// `query`
	Rep(j, 1, k) result[j].first = -1;
	query(1, 0, n, 0, k); ans = -result[k].second + 1;
}