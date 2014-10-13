namespace SCC {
	int code[MAXN * 2], seq[MAXN * 2], sCnt;
	void DFS_1(int x) { code[x] = 1;
		for (edge e(fir[x]); e; e = e->next) if (code[e->to] == -1) DFS_1(e->to);
		seq[++sCnt] = x;
	} void DFS_2(int x) { code[x] = sCnt;
		for (edge e(fir2[x]); e; e = e->next) if (code[e->to] == -1) DFS_2(e->to); }
	void SCC(int N) {
		sCnt = 0; for (int i = 1; i <= N; ++i) code[i] = -1;
		for (int i = 1; i <= N; ++i) if (code[i] == -1) DFS_1(i);
		sCnt = 0; for (int i = 1; i <= N; ++i) code[i] = -1;
		for (int i = N; i >= 1; --i) if (code[seq[i]] == -1) {
			++sCnt; DFS_2(seq[i]); }
	}
}//  true    -   2i - 1
//   false   -   2i
bool TwoSat() { SCC::SCC(N + N);
	// if code[2i - 1] = code[2i]: no solution
	// if code[2i - 1] > code[2i]: i selected. else i not selected
}