struct Point { int x, y; };
struct Rectangle {
	int lx , rx , ly , ry;
	void set(const Point &p) { lx = rx = p.x; ly = ry = p.y; }
	void merge(const Point &o) {
		lx = min(lx, o.x); rx = max(rx, o.x); ly = min(ly, o.y); ry = max(ry, o.y);
	} void merge(const Rectangle &o) {
		lx = min(lx , o.lx); rx = max(rx , o.rx); ly = min(ly , o.ly); ry = max(ry , o.ry);
	} LL dist(const Point &p) {
		LL res = 0;
		if (p.x < lx) res += sqr(lx - p.x); else if (p.x > rx) res += sqr(p.x - rx);
		if (p.y < ly) res += sqr(ly - p.y); else if (p.y > ry) res += sqr(p.y - ry);
		return res;
	}
};
struct Node { int child[2]; Point p; Rectangle rect; };
const int MAX_N = 1111111;
const LL INF = 100000000;
int n, m, tot, root; LL result;
Point a[MAX_N], p; Node tree[MAX_N];
int build(int s, int t, bool d) {
	int k = ++tot, mid = (s + t) >> 1;
	nth_element(a + s, a + mid , a + t, d ? cmpXY : cmpYX);
	tree[k].p = a[mid]; tree[k].rect.set(a[mid]); tree[k].child[0] = tree[k].child[1] = 0;
	if (s < mid)
		tree[k].child[0] = build(s, mid , d ^ 1), tree[k].rect.merge(tree[tree[k].child[0]].rect);
	if (mid + 1 < t)
		tree[k].child[1] = build(mid + 1, t, d ^ 1), tree[k].rect.merge(tree[tree[k].child[1]].rect);
	return k;
}
int insert(int root, bool d) {
	if (root == 0) {
		tree[++tot].p = p; tree[tot].rect.set(p); tree[tot].child[0] = tree[tot].child[1] = 0;
		return tot;
	} tree[root].rect.merge(p);
	if ((d && cmpXY(p, tree[root].p)) || (!d && cmpYX(p, tree[root].p)))
		 tree[root].child[0] = insert(tree[root].child[0], d ^ 1);
	else tree[root].child[1] = insert(tree[root].child[1], d ^ 1);
	return root;
}
void query(int k, bool d) {
	if (tree[k].rect.dist(p) >= result) return;
	cMin(result, dist(tree[k].p, p));
	if ((d && cmpXY(p, tree[k].p)) || (!d && cmpYX(p, tree[k].p))) {
		if (tree[k].child[0]) query(tree[k].child[0], d ^ 1);
		if (tree[k].child[1]) query(tree[k].child[1], d ^ 1);
	} else {
		if (tree[k].child[1]) query(tree[k].child[1], d ^ 1);
		if (tree[k].child[0]) query(tree[k].child[0], d ^ 1);
	}
}
void example(int n) {
	root = tot = 0; scan(a); root = build(0, n, 0); // `init, $a[0 \ldots n - 1]$`
	scan(p); root = insert(root, 0); // `insert`
	scan(p); result = INF; ans = query(root, 0); // `query`
}