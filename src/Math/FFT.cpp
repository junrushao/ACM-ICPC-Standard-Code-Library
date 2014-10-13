namespace FFT {
	#define mul(a, b) (Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x))
	struct Complex {}; // `something omitted`
	void FFT(Complex P[], int n, int oper) {
		for (int i = 1, j = 0; i < n - 1; i++) {
			for (int s = n; j ^= s >>= 1, ~j & s; );
			if (i < j) swap(P[i], P[j]);
		}
		for (int d = 0; (1 << d) < n; d++) {
			int m = 1 << d, m2 = m * 2;
			double p0 = PI / m * oper;
			Complex unit_p0(cos(p0), sin(p0));
			for (int i = 0; i < n; i += m2) {
				Complex unit(1.0, 0.0);
				for (int j = 0; j < m; j++) {
					Complex &P1 = P[i + j + m], &P2 = P[i + j];
					Complex t = mul(unit, P1);
					P1 = Complex(P2.x - t.x, P2.y - t.y);
					P2 = Complex(P2.x + t.x, P2.y - t.y);
					unit = mul(unit, unit_p0);
	}}}}
	vector<int> doFFT(const vector<int> &a, const vector<int> &b) {
		vector<int> ret(max(0, (int) a.size() + (int) b.size() - 1), 0);
		static Complex A[MAXB], B[MAXB], C[MAXB];
		int len = 1; while (len < (int)ret.size()) len *= 2;
		for (int i = 0; i < len; i++) A[i] = i < (int)a.size() ? a[i] : 0;
		for (int i = 0; i < len; i++) B[i] = i < (int)b.size() ? b[i] : 0;
		FFT(A, len, 1); FFT(B, len, 1);
		for (int i = 0; i < len; i++) C[i] = mul(A[i], B[i]);
		FFT(C, len, -1);
		for (int i = 0; i < (int)ret.size(); i++)
			ret[i] = (int) (C[i].x / len + 0.5);
		return ret;
	}
}