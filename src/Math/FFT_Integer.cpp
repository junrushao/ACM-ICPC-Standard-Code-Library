namespace FFT {
//	`替代方案: $23068673( = 11 * 2 ^ {21} + 1)$, 原根为 $3$`
	const int MOD = 786433, PRIMITIVE_ROOT = 10; // `$3 * 2 ^ {18} + 1$`
	const int MAXB = 1 << 20;
	int getMod(int downLimit) { // `或者现场自己找一个MOD`
		for (int c = 3; ; ++c) { int t = (c << 21) | 1;
			if (t >= downLimit && isPrime(t)) return t;
	}}
	int modInv(int a) { return a <= 1 ? a : (long long) (MOD - MOD / a) * modInv(MOD % a) % MOD; }
	void NTT(int P[], int n, int oper) {
		for (int i = 1, j = 0; i < n - 1; i++) {
			for (int s = n; j ^= s >>= 1, ~j & s;);
			if (i < j) swap(P[i], P[j]);
		}
		for (int d = 0; (1 << d) < n; d++) {
			int m = 1 << d, m2 = m * 2;
			long long unit_p0 = powMod(PRIMITIVE_ROOT, (MOD - 1) / m2);
			if (oper < 0) unit_p0 = modInv(unit_p0);
			for (int i = 0; i < n; i += m2) {
				long long unit = 1;
				for (int j = 0; j < m; j++) {
					int &P1 = P[i + j + m], &P2 = P[i + j];
					int t = unit * P1 % MOD;
					P1 = (P2 - t + MOD) % MOD; P2 = (P2 + t) % MOD;
					unit = unit * unit_p0 % MOD;
	}}}}
	vector<int> mul(const vector<int> &a, const vector<int> &b) {
		vector<int> ret(max(0, (int) a.size() + (int) b.size() - 1), 0);
		static int A[MAXB], B[MAXB], C[MAXB];
		int len = 1; while (len < (int)ret.size()) len <<= 1;
		for (int i = 0; i < len; i++) A[i] = i < (int)a.size() ? a[i] : 0;
		for (int i = 0; i < len; i++) B[i] = i < (int)b.size() ? b[i] : 0;
		NTT(A, len, 1); NTT(B, len, 1);
		for (int i = 0; i < len; i++) C[i] = (long long) A[i] * B[i] % MOD;
		NTT(C, len, -1); for (int i = 0, inv = modInv(len); i < (int)ret.size(); i++) ret[i] = (long long) C[i] * inv % MOD;
		return ret;
	}
}