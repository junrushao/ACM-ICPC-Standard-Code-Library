#define x first   // `upperHull $\leftarrow (x, y)$`
#define y second  // `lowerHull $\leftarrow (x, -y)$`
typedef map<int, int> mii;
typedef map<int, int>::iterator mit;
struct point { point(const mit &p): x(p->first), y(p->second) {} };
inline bool checkInside(mii &a, const point &p) { // `border inclusive`
	int x = p.x, y = p.y; mit p1 = a.lower_bound(x);
	if (p1 == a.end()) return false; if (p1->x == x) return y <= p1->y;
	if (p1 == a.begin()) return false; mit p2(p1--);
	return sign(det(p - point(p1), point(p2) - p)) >= 0;
} inline void addPoint(mii &a, const point &p) { // `no collinear points`
	int x = p.x, y = p.y; mit pnt = a.insert(make_pair(x, y)).first, p1, p2;
	for (pnt->y = y; ; a.erase(p2)) {
		p1 = pnt; if (++p1 == a.end()) break;
		p2 = p1;  if (++p1 == a.end()) break;
		if (det(point(p2) - p, point(p1) - p) < 0) break;
	} for ( ; ; a.erase(p2)) {
		if ((p1 = pnt) == a.begin()) break;
		if (--p1 == a.begin()) break; p2 = p1--;
		if (det(point(p2) - p, point(p1) - p) > 0) break;
	}
}