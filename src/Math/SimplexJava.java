double[] simplex(double[][] A, double[] b, double[] c) {
	int n = A.length, m = A[0].length + 1, r = n, s = m - 1;
	double[][] D = new double[n + 2][m + 1];
	int[] ix = new int[n + m];
	for (int i = 0; i < n + m; i++) ix[i] = i;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m - 1; j++) D[i][j] = -A[i][j];
		D[i][m - 1] = 1; D[i][m] = b[i]; if (D[r][m] > D[i][m]) r = i;
	}
	for (int j = 0; j < m - 1; j++) D[n][j] = c[j];
	D[n + 1][m - 1] = -1;
	for (double d; ; ) {
		if (r < n) {
			int t = ix[s]; ix[s] = ix[r + m]; ix[r + m] = t; D[r][s] = 1.0 / D[r][s];
			for (int j = 0; j <= m; j++) if (j != s) D[r][j] *= -D[r][s];
			for (int i = 0; i <= n + 1; i++) if (i != r) {
				for (int j = 0; j <= m; j++) if (j != s) D[i][j] += D[r][j] * D[i][s];
				D[i][s] *= D[r][s];
			}
		} r = -1; s = -1;
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
	} if (D[n + 1][m] < -EPS) return null; // `无法执行`
	double[] x = new double[m - 1];
	for (int i = m; i < n + m; i++) if (ix[i] < m - 1) x[ix[i]] = D[i - m][m];
	return x; // `值为 D[n][m]`
}