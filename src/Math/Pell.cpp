pair<ULL, ULL> Pell(int n) {
	static ULL p[50] = {0, 1}, q[50] = {1, 0}, g[50] = {0, 0}, h[50] = {0, 1}, a[50];
	ULL t = a[2] = Sqrt(n);
	for (int i = 2; ; ++i) {
		g[i] = -g[i - 1] + a[i] * h[i - 1];
		h[i] = (n - g[i] * g[i]) / h[i - 1];
		a[i + 1] = (g[i] + t) / h[i];
		p[i] = a[i] * p[i - 1] + p[i - 2];
		q[i] = a[i] * q[i - 1] + q[i - 2];
		if (p[i] * p[i] - n * q[i] * q[i] == 1) return make_pair(p[i], q[i]);
	} return make_pair(-1, -1);
}
