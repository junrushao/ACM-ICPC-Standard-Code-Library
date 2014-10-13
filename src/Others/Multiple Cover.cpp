struct node { int x, y; node *l, *r, *u, *d; } base[MAX * MAX], *top, *head;
typedef node *link;
int row, col, nGE, ans, stamp, cntc[MAX], vis[MAX];
void removeExact(link c) { c->l->r = c->r; c->r->l = c->l;
	for (link i = c->d; i != c; i = i->d)
		for (link j = i->r; j != i; j = j->r) j->d->u = j->u, j->u->d = j->d, --cntc[j->y];
}
void resumeExact(link c) {
	for (link i = c->u; i != c; i = i->u)
		for (link j = i->l; j != i; j = j->l) j->d->u = j, j->u->d = j, ++cntc[j->y];
	c->l->r = c; c->r->l = c;
}
void removeRepeat(link c) { for (link i = c->d; i != c; i = i->d) i->l->r = i->r, i->r->l = i->l; }
void resumeRepeat(link c) { for (link i = c->u; i != c; i = i->u) i->l->r = i; i->r->l = i; }
int calcH() { int y, res = 0; ++stamp;
	for (link c = head->r; (y = c->y) <= row && c != head; c = c->r) if (vis[y] != stamp) {
		vis[y] = stamp; ++res; for (link i = c->d; i != c; i = i->d)
			for (link j = i->r; j != i; j = j->r) vis[j->y] = stamp;
	} return res;
}
void DFS(int dep) { if (dep + calcH() >= ans) return;
	if (head->r->y > nGE || head->r == head) { if (ans > dep) ans = dep; return; }
	link c = NULL;
	for (link i = head->r; i->y <= nGE && i != head; i = i->r)
		if (!c || cntc[i->y] < cntc[c->y]) c = i;
	for (link i = c->d; i != c; i = i->d) {
		removeRepeat(i);
		for (link j = i->r; j != i; j = j->r) if (j->y <= nGE) removeRepeat(j);
		for (link j = i->r; j != i; j = j->r) if (j->y  > nGE) removeExact(base + j->y);
		DFS(dep + 1);
		for (link j = i->l; j != i; j = j->l) if (j->y  > nGE) resumeExact(base + j->y);
		for (link j = i->l; j != i; j = j->l) if (j->y <= nGE) resumeRepeat(j);
		resumeRepeat(i);
	}
}