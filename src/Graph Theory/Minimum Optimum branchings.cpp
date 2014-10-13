namespace EdmondsAlgorithm { // O(ElogE + V^2) !!! 0-based !!!
	struct enode { int from, c, key, delta, dep; enode *ch[2], *next;
	} ebase[maxm], *etop, *fir[maxn], nil, *null, *inEdge[maxn], *chs[maxn];
	typedef enode *edge; typedef enode *tree;	
	int n, m, setFa[maxn], deg[maxn], que[maxn];
	inline void pushDown(tree x) { if (x->delta) {
		x->ch[0]->key += x->delta; x->ch[0]->delta += x->delta;
		x->ch[1]->key += x->delta; x->ch[1]->delta += x->delta; x->delta = 0;
	}}
	tree merge(tree x, tree y) {
		if (x == null) return y; if (y == null) return x;
		if (x->key > y->key) swap(x, y); pushDown(x); x->ch[1] = merge(x->ch[1], y);
		if (x->ch[0]->dep < x->ch[1]->dep) swap(x->ch[0], x->ch[1]);
		x->dep = x->ch[1]->dep + 1; return x;
	}
	void addEdge(int u, int v, int w) {
		etop->from = u; etop->c = etop->key = w; etop->delta = etop->dep = 0;
		etop->next = fir[v]; etop->ch[0] = etop->ch[1] = null;
		fir[v] = etop; inEdge[v] = merge(inEdge[v], etop++);
	}
	void deleteMin(tree &r) { pushDown(r); r = merge(r->ch[0], r->ch[1]); }
	int findSet(int x) { return setFa[x] == x ? x : setFa[x] = findSet(setFa[x]); }
	void clear(int V, int E) {
		null = &nil; null->ch[0] = null->ch[1] = null; null->dep = -1;
		n = V; m = E; etop = ebase; Foru(i, 0, V) fir[i] = NULL; Foru(i, 0, V) inEdge[i] = null;
	}
	int solve(int root) { int res = 0, head, tail;
		for (int i = 0; i < n; ++i) setFa[i] = i;
		for ( ; ; ) { memset(deg, 0, sizeof(int) * n); chs[root] = inEdge[root];
			for (int i = 0; i < n; ++i) if (i != root && setFa[i] == i) {
				while (findSet(inEdge[i]->from) == findSet(i)) deleteMin(inEdge[i]);
				++deg[ findSet((chs[i] = inEdge[i])->from) ];
			}
			for (int i = head = tail = 0; i < n; ++i)
				if (i != root && setFa[i] == i && deg[i] == 0) que[tail++] = i;
			while (head < tail) {
				int x = findSet(chs[que[head++]]->from);
				if (--deg[x] == 0) que[tail++] = x;
			} bool found = false;
			for (int i = 0; i < n; ++i) if (i != root && setFa[i] == i && deg[i] > 0) {
				int j = i; tree temp = null; found = true;
				do {setFa[j = findSet(chs[j]->from)] = i;
					deleteMin(inEdge[j]); res += chs[j]->key;
					inEdge[j]->key -= chs[j]->key; inEdge[j]->delta -= chs[j]->key;
					temp = merge(temp, inEdge[j]);
				} while (j != i); inEdge[i] = temp;
			} if (!found) break;
		} for (int i = 0; i < n; ++ i) if (i != root && setFa[i] == i) res += chs[i]->key;
		return res;
	}
}
namespace ChuLiu { // O(V ^ 3) !!! 1-based !!!
	int n, used[maxn], pass[maxn], eg[maxn], more, que[maxn], g[maxn][maxn];
	void combine(int id, int &sum) { int tot = 0, from, i, j, k;
		for ( ; id != 0 && !pass[id]; id = eg[id]) que[tot++] = id, pass[id] = 1;
		for (from = 0; from < tot && que[from] != id; from++);
		if (from == tot) return; more = 1;
		for (i = from; i < tot; i++) {
			sum += g[eg[que[i]]][que[i]]; if (i == from) continue;
			for (j = used[que[i]] = 1; j <= n; j++) if (!used[j])
				if (g[que[i]][j] < g[id][j]) g[id][j] = g[que[i]][j];
		}
		for (i = 1; i <= n; i++) if (!used[i] && i != id)
			for (j = from; j < tot; j++) {
				k = que[j]; if (g[i][id] > g[i][k] - g[eg[k]][k])
				g[i][id] = g[i][k] - g[eg[k]][k];
			}
	}
	void clear(int V) { n = V; Rep(i, 1, V) Rep(j, 1, V) g[i][j] = inf; }
	int solve(int root) {
		int i, j, k, sum = 0; memset(used, 0, sizeof(int) * (n + 1));
		for (more = 1; more; ) {
			more = 0; memset(eg, 0, sizeof(int) * (n + 1));
			for (i = 1; i <= n; i++) if (!used[i] && i != root) {
				for (j = 1, k = 0; j <= n; j++) if (!used[j] && i != j)
					if (k == 0 || g[j][i] < g[k][i]) k = j;
				eg[i] = k;
			} memset(pass, 0, sizeof(int) * (n + 1));
			for (i = 1; i <= n; i++) if (!used[i] && !pass[i] && i != root)
				combine(i, sum);
		} for (i = 1; i <= n; i++) if (!used[i] && i != root) sum += g[eg[i]][i];
		return sum;
	}
}
