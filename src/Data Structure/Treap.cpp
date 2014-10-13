struct node { int key, prio, size; node *ch[2]; } base[MAXN], *top, *root, *null, nil;
typedef node *tree;
tree newNode(int key) {
	static int seed = 3312;
	top->key = key; top->prio = seed = int(seed * 48271LL % 2147483647);
	top->size = 1; top->ch[0] = top->ch[1] = null; return top++;
}
void Rotate(tree &x, int d) {
	tree y = x->ch[!d]; x->ch[!d] = y->ch[d]; y->ch[d] = x; y->size = x->size;
	x->size = x->ch[0]->size + 1 + x->ch[1]->size; x = y;
}
void Insert(tree &t, int key) {
	if (t == null) t = newNode(key);
	else { int d = t->key < key; Insert(t->ch[d], key); ++t->size;
		if (t->ch[d]->prio < t->prio) Rotate(t, !d);
	}
}
void Delete(tree &t, int key) {
	if (t->key != key) { Delete(t->ch[t->key < key], key); --t->size; }
	else if (t->ch[0] == null) t = t->ch[1];
	else if (t->ch[1] == null) t = t->ch[0];
	else { int d = t->ch[0]->prio < t->ch[1]->prio;
		Rotate(t, d); Delete(t->ch[d], key); --t->size;
	}
}