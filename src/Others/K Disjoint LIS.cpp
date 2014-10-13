int G[MAXN][MAXN];
void insertYoung(int v) {
	for (int x = 1, y = INT_MAX; ; ++x) {
		Down(y, *G[x]); while (y > 0 && G[x][y] >= v) --y;
		if (++y > *G[x]) { ++*G[x]; G[x][y] = v; break; }
		else swap(G[x][y], v);
	}
}
int solve(int N, int seq[]) {
	Rep(i, 1, N) *G[i] = 0;
	Rep(i, 1, N) insertYoung(seq[i]);
	printf("%d\n", *G[1] + *G[2]);
	return 0;
}