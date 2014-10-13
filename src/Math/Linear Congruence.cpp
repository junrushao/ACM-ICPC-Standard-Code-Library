// Warning: Pay Attention to Integer Overflow !

int gcd(int a, int b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	if (a == 0 || b == 0) return a + b;
	for (int c; (c = a % b) != 0; a = b, b = c);
	return b;
}

int powMod(int a, int d, int MOD) {
	int res = 1;
	for ( ; d; d >>= 1) {
		if (d & 1)
			res = res * a % MOD;
		a = a * a % MOD;
	}
	return res;
}

int modInv(int a, int p) {
	if (a <= 1) return a % p;
	int ret = -(p / a) * modInv(p % a, p) % p;
	return (ret == 0) ? (ret) : (ret + p);
}

bool congruence(int n, int A[], int B[], int M[], int &x, int &m) {
	x = 0;
	m = 1;
	for (int i = 0; i < n; ++i) {
		int a = A[i] * m, b = B[i] - A[i] * x, d = gcd(a, M[i]);
		if (b % d != 0)
			return false;
		x += m * (b / d * modInv(a / d, M[i] / d) % (M[i] / d));
		m *= M[i] / d;
	}
	x %= m;
	return true;
}
