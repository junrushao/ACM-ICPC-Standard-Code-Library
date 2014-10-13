int minCut(int N, int G[MAXN][MAXN]) { // 0-based
	static int weight[MAXN], used[MAXN]; int ans = INT_MAX;
	while (N > 1) {
		for (int i = 0; i < N; ++i) used[i] = false; used[0] = true;
		for (int i = 0; i < N; ++i) weight[i] = G[i][0];
		int S = -1, T = 0;
		for (int _r = 2; _r <= N; ++_r) { // N - 1 selections
			int x = -1;
			for (int i = 0; i < N; ++i) if (!used[i])
				if (x == -1 || weight[i] > weight[x]) x = i;
			for (int i = 0; i < N; ++i) weight[i] += G[x][i];
			S = T; T = x; used[x] = true;
		} ans = min(ans, weight[T]);
		for (int i = 0; i < N; ++i) G[i][S] += G[i][T], G[S][i] += G[i][T];
		G[S][S] = 0; --N;
		for (int i = 0; i <= N; ++i) swap(G[i][T], G[i][N]);
		for (int i = 0; i < N; ++i) swap(G[T][i], G[N][i]);
	} return ans;
}