void exgcd(LL x, LL y, LL &a0, LL &b0, LL &g) {
	LL a1 = b0 = 0, b1 = a0 = 1, t;
	while (y != 0) {
		t = a0 - x / y * a1, a0 = a1, a1 = t;
		t = b0 - x / y * b1, b0 = b1, b1 = t;
		t = x % y, x = y, y = t;
	} if (x < 0) a0 = -a0, b0 = -b0, x = -x;
	g = x;
}