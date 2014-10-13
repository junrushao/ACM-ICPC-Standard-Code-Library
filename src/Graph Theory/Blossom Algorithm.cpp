namespace Blossom {
	int n, head, tail, S, T, lca;
	int match[MAXN], Q[MAXN], pred[MAXN], label[MAXN], inq[MAXN], inb[MAXN];
	vector<int> link[MAXN];
	inline void push(int x) { Q[tail++] = x; inq[x] = true; }
	int findCommonAncestor(int x, int y) {
		static bool inPath[MAXN]; for (int i = 0; i < n; ++i) inPath[i] = 0;
		for ( ; ; x = pred[ match[x] ]) { x = label[x]; inPath[x] = true; if (x == S) break; }
		for ( ; ; y = pred[ match[y] ]) { y = label[y]; if (inPath[y]) break; } return y;
	}
	void resetTrace(int x, int lca) {
		while (label[x] != lca) { int y = match[x]; inb[ label[x] ] = inb[ label[y] ] = true;
			x = pred[y]; if (label[x] != lca) pred[x] = y; }}
	void blossomContract(int x, int y) {
		lca = findCommonAncestor(x, y);
		Foru(i, 0, n) inb[i] = 0; resetTrace(x, lca); resetTrace(y, lca);
		if (label[x] != lca) pred[x] = y; if (label[y] != lca) pred[y] = x;
		Foru(i, 0, n) if (inb[ label[i] ]) { label[i] = lca; if (!inq[i]) push(i); }
	}
	bool findAugmentingPath() {
		Foru(i, 0, n) pred[i] = -1, label[i] = i, inq[i] = 0;
		int x, y, z; head = tail = 0;
		for (push(S); head < tail; ) for (int i = (int)link[x = Q[head++]].size() - 1; i >= 0; --i) {
			y = link[x][i]; if (label[x] == label[y] || x == match[y]) continue;
			if (y == S || (match[y] >= 0 && pred[ match[y] ] >= 0)) blossomContract(x, y);
			else if (pred[y] == -1) {
				pred[y] = x; if (match[y] >= 0) push(match[y]);
				else {
					for (x = y; x >= 0; x = z) {
					y = pred[x], z = match[y]; match[x] = y, match[y] = x;
				} return true; }}} return false;
	}
	int findMaxMatching() {
		int ans = 0; Foru(i, 0, n) match[i] = -1;
		for (S = 0; S < n; ++S) if (match[S] == -1) if (findAugmentingPath()) ++ans;
		return ans;
	}
}