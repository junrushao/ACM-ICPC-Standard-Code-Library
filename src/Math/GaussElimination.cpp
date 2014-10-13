#define Zero(x) (fabs(x) <= EPS)
bool GaussElimination(double G[MAXN][MAXM], int N, int M) {
	int rb = 1; memset(res, 0, sizeof(res));
	Rep(i_th, 1, N) { int maxRow = 0;
		Rep(row, rb, N) if (!Zero(G[row][i_th]))
			if (!maxRow || fabs(G[row][i_th]) > fabs(G[maxRow][i_th]))
				maxRow = row;
		if (!maxRow) continue;
		swapRow(G[rb], G[maxRow]);
		maxRow = rb++;
		Rep(row, 1, N) if (row != maxRow && !Zero(G[row][i_th])) {
			double coef = G[row][i_th] / G[maxRow][i_th];
			Rep(col, 0, M) G[row][col] -= coef * G[maxRow][col];
		}
	}
	Rep(row, 1, N) if (!Zero(G[row][0])) {
		int i_th = 1;
		for ( ; i_th <= M; ++i_th) if (!Zero(G[row][i_th])) break;
		if (i_th > N) return false;
		res[i_th] = G[row][0] / G[row][i_th];
	}
	return true;
}