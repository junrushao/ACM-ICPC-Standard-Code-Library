int Num[10005][205], Path[10005][205], dev[10005], from[10005], value[10005], dist[205], Next[205], Graph[205][205];
int N, M, K, s, t, tot, cnt; bool forbid[205], hasNext[10005][205];
struct cmp {
	bool operator()(const int &a, const int &b) {
		int *i, *j; if (value[a] != value[b]) return value[a] > value[b];
		for (i = Path[a], j = Path[b]; (*i) == (*j); i++, j++);
		return (*i) > (*j);
	}
};
void Check(int idx, int st, int *path, int &res) {
	int i, j; for (i = 0; i < N; i++) dist[i] = 1000000000, Next[i] = t;
	dist[t] = 0; forbid[t] = true; j = t;
	for ( ; ; ) {
		for (i = 0; i < N; i++) if (!forbid[i] && (i != st || !hasNext[idx][j]) && (dist[j] + Graph[i][j] < dist[i] || (dist[j] + Graph[i][j] == dist[i] && j < Next[i])))
			Next[i] = j, dist[i] = dist[j] + Graph[i][j];
		j = -1; for (i = 0; i < N; i++) if (!forbid[i] && (j == -1 || dist[i] < dist[j])) j = i;
		if (j == -1) break; forbid[j] = 1; if (j == st) break;
	} res += dist[st]; for (i = st; i != t; i = Next[i], path++) (*path) = i; (*path) = i;
}
int main() {
	int i, j, k, l;
	while (scanf("%d%d%d%d%d", &N, &M, &K, &s, &t) && N) {
		priority_queue<int, vector<int>, cmp> Q;
		for (i = 0; i < N; i++) for (j = 0; j < N; j++) Graph[i][j] = 1000000000;
		for (i = 0; i < M; i++) { scanf("%d%d%d", &j, &k, &l); Graph[j - 1][k - 1] = l; }
		s--; t--;
		memset(forbid, false, sizeof(forbid)); memset(hasNext[0], false, sizeof(hasNext[0]));
		Check(0, s, Path[0], value[0]); dev[0] = 0; from[0] = 0; Num[0][0] = 0; Q.push(0);
		cnt = 1; tot = 1;
		for (i = 0; i < K; i++) {
			if (Q.empty()) break; l = Q.top(); Q.pop();
			for (j = 0; j <= dev[l]; j++) Num[l][j] = Num[from[l]][j];
			for (; Path[l][j] != t; j++) {
				memset(hasNext[tot], false, sizeof(hasNext[tot])); Num[l][j] = tot++;
			} for (j = 0; Path[l][j] != t; j++) hasNext[Num[l][j]][Path[l][j + 1]] = true;
			for (j = dev[l]; Path[l][j] != t; j++) {
				memset(forbid, false, sizeof(forbid)); value[cnt] = 0;
				for (k = 0; k < j; k++) {
					forbid[Path[l][k]] = true;
					Path[cnt][k] = Path[l][k];
					value[cnt] += Graph[Path[l][k]][Path[l][k + 1]];
				} Check(Num[l][j], Path[l][j], &Path[cnt][j], value[cnt]);
				if (value[cnt] > 2000000) continue;
				dev[cnt] = j; from[cnt] = l; Q.push(cnt); cnt++;
			}
		}
		if (i < K || value[l] > 2000000) printf("None\n");
		else {
			for (i = 0; Path[l][i] != t; i++) printf("%d-", Path[l][i] + 1);
			printf("%d\n", t + 1);
		}
	} return 0;
}