namespace StableMatching {
	int pairM[MAXN], pairW[MAXN], p[MAXN];
	// init: pairM[0...n - 1] = pairW[0...n - 1] = -1, p[0...n - 1] = 0
	void stableMatching(int n, int orderM[MAXN][MAXN], int preferW[MAXN][MAXN]) {
		for (int i = 0; i < n; i++) while (pairM[i] < 0) {
			int w = orderM[i][p[i]++], m = pairW[w];
			if (m == -1) pairM[i] = w, pairW[w] = i;
			else if (preferW[w][i] < preferW[w][m])
				pairM[m] = -1, pairM[i] = w, pairW[w] = i, i = m;
		}
	}
}