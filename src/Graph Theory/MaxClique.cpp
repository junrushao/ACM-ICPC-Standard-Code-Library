namespace MaxClique { // 1-based
	int g[MAXN][MAXN], len[MAXN], list[MAXN][MAXN], mc[MAXN], ans, found;
	void DFS(int size) {
		if (len[size] == 0) { if (size > ans) ans = size, found = true; return; }
		for (int k = 0; k < len[size] && !found; ++k) {
			if (size + len[size] - k <= ans) break;
			int i = list[size][k]; if (size + mc[i] <= ans) break;
			for (int j = k + 1, len[size + 1] = 0; j < len[size]; ++j) if (g[i][list[size][j]])
				list[size + 1][len[size + 1]++] = list[size][j];
			DFS(size + 1);
		}
	}
	int work(int n) {
		mc[n] = ans = 1; for (int i = n - 1; i; --i) { found = false; len[1] = 0;
			for (int j = i + 1; j <= n; ++j) if (g[i][j]) list[1][len[1]++] = j;
			DFS(1); mc[i] = ans;
		} return ans;
	}
}