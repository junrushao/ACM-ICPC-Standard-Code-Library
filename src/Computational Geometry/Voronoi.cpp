#define Oi(e) ((e)->oi)
#define Dt(e) ((e)->dt)
#define On(e) ((e)->on)
#define Op(e) ((e)->op)
#define Dn(e) ((e)->dn)
#define Dp(e) ((e)->dp)
#define Other(e, p) ((e)->oi == p ? (e)->dt : (e)->oi)
#define Next(e, p) ((e)->oi == p ? (e)->on : (e)->dn)
#define Prev(e, p) ((e)->oi == p ? (e)->op : (e)->dp)
#define V(p1, p2, u, v) (u = p2->x - p1->x, v = p2->y - p1->y)
#define C2(u1, v1, u2, v2) (u1 * v2 - v1 * u2)
#define C3(p1, p2, p3) ((p2->x - p1->x) * (p3->y - p1->y) - (p2->y - p1->y) * (p3->x - p1->x))
#define Dot(u1, v1, u2, v2) (u1 * u2 + v1 * v2)
#define dis(a,b) (sqrt( (a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y) ))
const int maxn = 110024;
const int aix = 4;
const double eps = 1e-7;
int n, M, k;
struct gEdge {
	int u, v; double w;
	bool operator <(const gEdge &e1) const { return w < e1.w - eps; }
} E[aix * maxn], MST[maxn];
struct point {
	double x, y; int index; edge *in;
	bool operator <(const point &p1) const { return x < p1.x - eps || (abs(x - p1.x) <= eps && y < p1.y - eps); }
};
struct edge { point *oi, *dt; edge *on, *op, *dn, *dp; };

point p[maxn], *Q[maxn];
edge mem[aix * maxn], *elist[aix * maxn];
int nfree;
void Alloc_memory() { nfree = aix * n; edge *e = mem; for (int i = 0; i < nfree; i++) elist[i] = e++; }
void Splice(edge *a, edge *b, point *v) {
	edge *next;
	if (Oi(a) == v) next = On(a), On(a) = b; else next = Dn(a), Dn(a) = b;
	if (Oi(next) == v) Op(next) = b; else Dp(next) = b;
	if (Oi(b) == v) On(b) = next, Op(b) = a; else Dn(b) = next, Dp(b) = a;
}
edge *Make_edge(point *u, point *v) {
	edge *e = elist[--nfree];
	e->on = e->op = e->dn = e->dp = e; e->oi = u; e->dt = v;
	if (!u->in) u->in = e;
	if (!v->in) v->in = e;
	return e;
}
edge *Join(edge *a, point *u, edge *b, point *v, int side) {
	edge *e = Make_edge(u, v);
	if (side == 1) {
		if (Oi(a) == u) Splice(Op(a), e, u);
		else Splice(Dp(a), e, u);
		Splice(b, e, v);
	} else {
		Splice(a, e, u);
		if (Oi(b) == v) Splice(Op(b), e, v);
		else Splice(Dp(b), e, v);
	} return e;
}
void Remove(edge *e) {
	point *u = Oi(e), *v = Dt(e);
	if (u->in == e) u->in = e->on;
	if (v->in == e) v->in = e->dn;
	if (Oi(e->on) == u) e->on->op = e->op; else e->on->dp = e->op;
	if (Oi(e->op) == u) e->op->on = e->on; else e->op->dn = e->on;
	if (Oi(e->dn) == v) e->dn->op = e->dp; else e->dn->dp = e->dp;
	if (Oi(e->dp) == v) e->dp->on = e->dn; else e->dp->dn = e->dn;
	elist[nfree++] = e;
}
void Low_tangent(edge *e_l, point *o_l, edge *e_r, point *o_r, edge **l_low, point **OL, edge **r_low, point **OR) {
	for (point *d_l = Other(e_l, o_l), *d_r = Other(e_r, o_r); ; )
		if (C3(o_l, o_r, d_l) < -eps)      e_l = Prev(e_l, d_l), o_l = d_l, d_l = Other(e_l, o_l);
		else if (C3(o_l, o_r, d_r) < -eps) e_r = Next(e_r, d_r), o_r = d_r, d_r = Other(e_r, o_r);
		else break;
	*OL = o_l, *OR = o_r; *l_low = e_l, *r_low = e_r;
}
void Merge(edge *lr, point *s, edge *rl, point *u, edge **tangent) {
	double l1, l2, l3, l4, r1, r2, r3, r4, cot_L, cot_R, u1, v1, u2, v2, n1, cot_n, P1, cot_P;
	point *O, *D, *OR, *OL; edge *B, *L, *R;
	Low_tangent(lr, s, rl, u, &L, &OL, &R, &OR);
	for (*tangent = B = Join(L, OL, R, OR, 0), O = OL, D = OR; ; ) {
		edge *El = Next(B, O), *Er = Prev(B, D), *next, *prev;
		point *l = Other(El, O), *r = Other(Er, D);
		V(l, O, l1, l2); V(l, D, l3, l4); V(r, O, r1, r2); V(r, D, r3, r4);
		double cl = C2(l1, l2, l3, l4), cr = C2(r1, r2, r3, r4);
		bool BL = cl > eps, BR = cr > eps;
		if (!BL && !BR) break;
		if (BL) {
			double dl = Dot(l1, l2, l3, l4);
			for (cot_L = dl / cl; ; Remove(El), El = next, cot_L = cot_n) {
				next = Next(El, O); V(Other(next, O), O, u1, v1); V(Other(next, O), D, u2, v2);
				n1 = C2(u1, v1, u2, v2); if (!(n1 > eps)) break;
				cot_n = Dot(u1, v1, u2, v2) / n1;
				if (cot_n > cot_L) break;
			}
		} if (BR) {
			double dr = Dot(r1, r2, r3, r4);
			for (cot_R = dr / cr; ; Remove(Er), Er = prev, cot_R = cot_P) {
				prev = Prev(Er, D); V(Other(prev, D), O, u1, v1); V(Other(prev, D), D, u2, v2);
				P1 = C2(u1, v1, u2, v2); if (!(P1 > eps)) break;
				cot_P = Dot(u1, v1, u2, v2) / P1;
				if (cot_P > cot_R) break;
			}
		} l = Other(El, O); r = Other(Er, D);
		if (!BL || (BL && BR && cot_R < cot_L)) B = Join(B, O, Er, r, 0), D = r;
		else B = Join(El, l, B, D, 0), O = l;
	}
}
void Divide(int s, int t, edge **L, edge **R) {
	edge *a, *b, *c, *ll, *lr, *rl, *rr, *tangent;
	int n = t - s + 1;
	if (n == 2) *L = *R = Make_edge(Q[s], Q[t]);
	else if (n == 3) {
		a = Make_edge(Q[s], Q[s + 1]), b = Make_edge(Q[s + 1], Q[t]);
		Splice(a, b, Q[s + 1]);
		double v = C3(Q[s], Q[s + 1], Q[t]);
		if (v > eps)       c = Join(a, Q[s], b, Q[t], 0), *L = a, *R = b;
		else if (v < -eps) c = Join(a, Q[s], b, Q[t], 1), *L = c, *R = c;
		else *L = a, *R = b;
	} else if (n > 3) {
		int split = (s + t) / 2;
		Divide(s, split, &ll, &lr); Divide(split + 1, t, &rl, &rr);
		Merge(lr, Q[split], rl, Q[split + 1], &tangent);
		if (Oi(tangent) == Q[s]) ll = tangent;
		if (Dt(tangent) == Q[t]) rr = tangent;
		*L = ll; *R = rr;
	}
}
void Make_Graph() {
	edge *start, *e; point *u, *v;
	for (int i = 0; i < n; i++) {
		start = e = (u = &p[i])->in;
		do{ v = Other(e, u);
			if (u < v) E[M++].u = (u - p, v - p, dis(u, v)); // M < aix * maxn
		} while ((e = Next(e, u)) != start);
	}
}
int b[maxn];
int Find(int x) { while (x != b[x]) { b[x] = b[b[x]]; x = b[x]; } return x; }
void Kruskal() {
	memset(b, 0, sizeof(b)); sort(E, E + M);
	for (int i = 0; i < n; i++) b[i] = i;
	for (int i = 0, kk = 0; i < M && kk < n - 1; i++) {
		int m1 = Find(E[i].u), m2 = Find(E[i].v);
		if (m1 != m2) b[m1] = m2, MST[kk++] = E[i];
	}
}
void solve() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%lf%lf", &p[i].x, &p[i].y), p[i].index = i, p[i].in = NULL;
	Alloc_memory(); sort(p, p + n);
	for (int i = 0; i < n; i++) Q[i] = p + i;
	edge *L, *R; Divide(0, n - 1, &L, &R);
	M = 0; Make_Graph(); Kruskal();
}
int main() { solve(); return 0; }