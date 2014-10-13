tree merge(tree a, tree b) {
	if (a == null) return b; 
	if (b == null) return a;
	if (a->key > b->key) swap(a, b);
	a->rc = merge(a->rc, b);
	a->rc->fa = a;
	if (a->lc->dist < a->rc->dist) swap(a->lc, a->rc);
	a->dist = a->rc->dist + 1;
	return a;
}
void erase(tree t) {
	tree x = t->fa, y = merge(t->lc, t->rc);
	if (y != null) y->fa = x;
	if (x == null) root = y;
	else
	for ((x->lc == t ? x->lc : x->rc) = y; x != null; y = x, x = x->fa) {
		if (x->lc->dist < x->rc->dist) swap(x->lc, x->rc);
		if (x->rc->dist + 1 == x->dist) return;
		x->dist = x->rc->dist + 1;
	}
}
