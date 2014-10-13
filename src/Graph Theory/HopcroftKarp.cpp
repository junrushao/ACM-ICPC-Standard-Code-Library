int N, M, level[MAXN], matchX[MAXN], matchY[MAXN];
bool used[MAXN];
bool DFS(int x) {
	used[x] = true; for (edge e(fir[x]); e; e = e->next) {
		int y = e->to, z = matchY[y];
		if (z == -1 || (!used[z] && level[x] < level[z] && DFS(z))) {
			matchX[x] = y; matchY[y] = x; return true;
		}
	} return false;
}
int maxMatch() {
	for (int i = 0; i < N; ++i) used[i] = false;
	for (int i = 0; i < N; ++i) matchX[i] = -1;
	for (int i = 0; i < M; ++i) matchY[i] = -1;
	for (int i = 0; i < N; ++i) level[i] = -1;
	int match = 0, d;
	for ( ; ; match += d) {
		static int Q[MAXN * 2 + 1];
		int head = 0, tail = d = 0;
		for (int x = 0; x < N; ++x) level[x] = -1;
		for (int x = 0; x < N; ++x) if (matchX[x] == -1)
			level[x] = 0, Q[++tail] = x;
		while (head < tail)
			for (edge e(fir[x = Q[++head]]); e; e = e->next) {
				int y = e->to, z = matchY[y];
				if (z != -1 && level[z] < 0) level[z] = level[x] + 1, Q[++tail] = z;
			}
		for (int x = 0; x < N; ++x) used[x] = false;
		for (int x = 0; x < N; ++x) if (matchX[x] == -1) if (DFS(x)) ++d;
		if (d == 0) break;
	} return match;
}