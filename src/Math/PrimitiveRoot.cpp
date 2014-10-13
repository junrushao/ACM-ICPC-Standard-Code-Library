vector<int> findPrimitiveRoot(int N) {
	if (N <= 4) return vector<int>(1, max(1, N - 1));
	static int factor[100];
	int phi = N, totF = 0;
	{ // `check no solution and calculate phi`
		int M = N, k = 0;
		if (~M & 1) M >>= 1, phi >>= 1;
		if (~M & 1) return vector<int>(0);
		for (int d = 3; d * d <= M; ++d) if (M % d == 0) {
			if (++k > 1) return vector<int>(0);
			for (phi -= phi / d; M % d == 0; M /= d);
		} if (M > 1) {
			if (++k > 1) return vector<int>(0); phi -= phi / M;
		}
	} { // `factorize phi`
		int M = phi;
		for (int d = 2; d * d <= M; ++d) if (M % d == 0) {
			for ( ; M % d == 0; M /= d); factor[++totF] = d;
		} if (M > 1) factor[++totF] = M;
	} vector<int> ans;
	for (int g = 2; g <= N; ++g) if (Gcd(g, N) == 1) {
		bool good = true;
		for (int i = 1; i <= totF && good; ++i)
			if (powMod(g, phi / factor[i], N) == 1) good = false;
		if (!good) continue;
		for (int i = 1, gp = g; i <= phi; ++i, gp = (LL)gp * g % N)
			if (Gcd(i, phi) == 1) ans.push_back(gp);
		break;
	} sort(ans.begin(), ans.end());
	return ans;
}