const int MAXN = 11000, MAXM = 1100;
//	`here MAXN is the MAX number of conditions, MAXM is the MAX number of vars`

int avali[MAXM], avacnt;
double A[MAXN][MAXM];
double b[MAXN], c[MAXM];
double* simplex(int n, int m) {
//	`here n is the number of conditions, m is the number of vars`
	m++;
	int r = n, s = m - 1;
	static double D[MAXN + 2][MAXM + 1];
	static int ix[MAXN + MAXM];
	for (int i = 0; i < n + m; i++) ix[i] = i;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m - 1; j++) D[i][j] = -A[i][j];
		D[i][m - 1] = 1;
		D[i][m] = b[i];
		if (D[r][m] > D[i][m]) r = i;
	}
	for (int j = 0; j < m - 1; j++) D[n][j] = c[j];
	D[n + 1][m - 1] = -1;
	for (double d; ; ) {
		if (r < n) {
			int t = ix[s]; ix[s] = ix[r + m]; ix[r + m] = t;
			D[r][s] = 1.0 / D[r][s];
			for (int j = 0; j <= m; j++) if (j != s) D[r][j] *= -D[r][s];
			avacnt = 0;
			for (int i = 0; i <= m; ++i)
				if(fabs(D[r][i]) > EPS)
					avali[avacnt++] = i;
			for (int i = 0; i <= n + 1; i++) if (i != r) {
				if(fabs(D[i][s]) < EPS) continue;
				double *cur1 = D[i], *cur2 = D[r], tmp = D[i][s];
				//for (int j = 0; j <= m; j++) if (j != s) cur1[j] += cur2[j] * tmp;
				for(int j = 0; j < avacnt; ++j) if(avali[j] != s) cur1[avali[j]] += cur2[avali[j]] * tmp;
				D[i][s] *= D[r][s];
			}
		}
		r = -1; s = -1;
		for (int j = 0; j < m; j++) if (s < 0 || ix[s] > ix[j]) {
			if (D[n + 1][j] > EPS || D[n + 1][j] > -EPS && D[n][j] > EPS) s = j;
		}
		if (s < 0) break;
		for (int i = 0; i < n; i++) if (D[i][s] < -EPS) {
			if (r < 0 || (d = D[r][m] / D[r][s] - D[i][m] / D[i][s]) < -EPS
					  || d < EPS && ix[r + m] > ix[i + m])
				r = i;
		}
		if (r < 0) return null; // `非有界`
	}
	if (D[n + 1][m] < -EPS) return null; // `无法执行`
	static double x[MAXM - 1];
	for (int i = m; i < n + m; i++) if (ix[i] < m - 1) x[ix[i]] = D[i - m][m];
	return x; // `值为 $D[n][m]$`
}
