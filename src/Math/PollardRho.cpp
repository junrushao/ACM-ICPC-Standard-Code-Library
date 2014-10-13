LL pollardRho(LL n, LL seed) {
	LL x, y, head = 1, tail = 2; x = y = random() % (n - 1) + 1;
	for ( ; ; ) {
		x = addMod(multiplyMod(x, x, n), seed, n);
		if (x == y) return n; LL d = gcd(myAbs(x - y), n);
		if (1 < d && d < n) return d;
		if (++head == tail) y = x, tail <<= 1;
}} vector<LL> divisors;
void factorize(LL n) { // `需要保证 n > 1`
	if (isPrime(n)) divisors.push_back(n);
	else { LL d = n;
		while (d >= n) d = pollardRho(n, random() % (n - 1) + 1);
		factorize(n / d); factorize(d);
}}