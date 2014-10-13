struct node { int len; node *fa, *go[26]; } base[MAXNODE], *top = base, *root, *que[MAXNODE];
typedef node *tree;
inline tree newNode(int len) {
	top->len = len; top->fa = NULL; memset(top->go, 0, sizeof(top->go)); return top++;
} inline tree newNode(int len, tree fa, tree *go) {
	top->len = len; top->fa = fa; memcpy(top->go, go, sizeof(top->go)); return top++;
} void construct(char *A, int N) {
	tree p = root = newNode(0), q, up, fa;
	for (int i = 0; i < N; ++i) {
		int w = A[i] - 'a'; up = p; p = newNode(i + 1);
		for ( ; up && !up->go[w]; up = up->fa) up->go[w] = p;
		if (!up) p->fa = root;
		else { q = up->go[w];
			if (up->len + 1 == q->len) p->fa = q;
			else { fa = newNode(up->len + 1, q->fa, q->go);
				for (p->fa = q->fa = fa; up && up->go[w] == q; up = up->fa) up->go[w] = fa;
			}
		}
	} static int cnt[MAXLEN]; memset(cnt, 0, sizeof(int) * (N + 1));
	for (tree i(base); i != top; ++i) ++cnt[i->len];
	Rep(i, 1, N) cnt[i] += cnt[i - 1];
	for (tree i(base); i != top; ++i) Q[ cnt[i->len]-- ] = i;
}