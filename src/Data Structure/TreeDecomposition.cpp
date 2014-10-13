int N, fa[MAXN], dep[MAXN], que[MAXN], size[MAXN], own[MAXN];
int LCA(int x, int y) { if (x == y) return x;
	for ( ; ; x = fa[own[x]]) {
		if (dep[x] < dep[y]) swap(x, y); if (own[x] == own[y]) return y;
		if (dep[own[x]] < dep[own[y]]) swap(x, y);
	} return -1;
}
void Decomposion() {
	static int path[MAXN]; int x, y, a, next, head = 0, tail = 0, cnt; // BFS omitted
	for (int i = 1; i <= N; ++i) if (own[a = que[i]] == -1)
		for (x = a, cnt = 0; ; x = next) { next = -1; own[x] = a; path[++cnt] = x;
			for (edge e(fir[x]); e; e = e->next) if ( (y = e->to) != fa[x] )
				if (next == -1 || size[y] > size[next]) next = y;
			if (next == -1) { tree[a].init(cnt, path); break; }
		}
}