vector<int> eulerianWalk(int N, int S) {
	static int res[MAXM], stack[MAXN]; static edge cur[MAXN];
	int rcnt = 0, top = 0, x; for (int i = 1; i <= N; ++i) cur[i] = fir[i];
	for (stack[top++] = S; top; ) {
		for (x = stack[--top]; ; ) {
			edge &e = cur[x]; if (e == NULL) break;
			stack[top++] = x; x = e->to; e = e->next;
			// 对于无向图需要删掉反向边
		} res[rcnt++] = x;
	} reverse(res, res + rcnt); return vector<int>(res, res + rcnt);
}