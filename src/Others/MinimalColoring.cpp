const int MAXN = 133;

namespace MinimalColoring {
	// seems to be 0-based ?
	int n, s, t, b[MAXN], res[MAXN], id[MAXN];
	int minLimit;
	bool g[MAXN][MAXN];

	void coloring() { // answer is stored in res[]
		for (int i = 0; i <= n; ++i) b[i] = 0;
		for (int i = 0; i <= n; ++i) res[i] = 0;
		for (int i = 0; i <= n; ++i) id[i] = i;
		for (s = 0, t = 1; t <= n; ++t) {
			int p = t;
			for (int i = t; i < n; ++i) {
				if (g[ id[t - 1] ][ id[i] ]) ++b[ id[i] ];
				if (b[ id[p] ] < b[ id[i] ]) p = i;
			}
			swap(id[t], id[p]);
			if (b[ id[t] ] == 0) {
				minLimit = n + 1;
				dfs(new int[n], s, 0);
				s = t;
			}
		}
	}

	void dfs(int *is, int p, int k) {
		if (k >= minLimit) return;
		if (p == t) {
			for (int i = s; i < t; i++) res[id[i]] = is[i];
			minLimit = k;
		}
		else {
			bool used = new bool[k + 1];
			for (int i = 0; i < p; i++) if (g[ id[p] ][ id[i] ]) used[ is[i] ] = true;
			for (int i = 0; i <= k; i++) if (!used[i]) {
				int backUp = is[p];
				is[p] = i;
				dfs(is, p + 1, max(k, i + 1));
				is[p] = backUp;
			}
			delete[] used;
		}
	}

}
