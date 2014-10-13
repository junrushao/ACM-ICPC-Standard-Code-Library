int modLog(int A, int B, int C) {
	static pii baby[MAX_SQRT_C + 11];
	int d = 0; LL k = 1, D = 1; B %= C;
	for (int i = 0; i < 100; ++i, k = k * A % C) // `$[0, \log C]$`
		if (k == B) return i;
	for (int g; ; ++d) {
		g = gcd(A, C); if (g == 1) break;
		if (B % g != 0) return -1;
		B /= g; C /= g; D = (A / g * D) % C;
	} int m = (int) ceil(sqrt((double) C)); k = 1;
	for (int i = 0; i <= m; ++i, k = k * A % C) baby[i] = pii(k, i);
	sort(baby, baby + m + 1); // [0, m]
	int n = unique(baby, baby + m + 1, equalFirst) - baby, am = powMod(A, m, C);
	for (int i = 0; i <= m; ++i) {
		LL e, x, y; exgcd(D, C, x, y, e); e = x * B % C;
		if (e < 0) e += C;
		if (e >= 0) {
			int k = lower_bound(baby, baby + n, pii(e, -1)) - baby;
			if (baby[k].first == e) return i * m + baby[k].second + d;
		} D = D * am % C;
	} return -1;
}