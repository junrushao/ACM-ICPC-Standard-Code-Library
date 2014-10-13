void construct() {
	static tree Q[MAX_NODE]; int head = 0, tail = 0;
	for (root->fail = root, Q[++tail] = root; head < tail; ) {
		tree x = Q[++head];
//		if (x->fail->danger) x->danger = true;
		Rep(d, 0, sigma - 1) if (!x->next[d])
			x->next[d] = (x == root) ? (root) : (x->fail->next[d]);
		else {
			x->next[d]->fail = (x == root) ? (root) : (x->fail->next[d]);
			Q[++tail] = x->next[d];
		}
	}
}