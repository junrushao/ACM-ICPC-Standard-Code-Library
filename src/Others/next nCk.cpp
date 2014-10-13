void nCk(int n, int k) {
	for (int comb = (1 << k) - 1; comb < (1 << n); ) {
		int x = comb & -comb, y = comb + x;
		comb = (((comb & ~y) / x) >> 1) | y;
	}
}