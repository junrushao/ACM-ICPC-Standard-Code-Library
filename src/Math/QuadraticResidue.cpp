inline int normalize(LL a, int P) { a %= P; return a < 0 ? a + P : a; }
vector<int> QuadraticResidue(LL a, LL b, LL c, int P) {
	int h, t; LL r1, r2, delta, pb = 0;
	a = normalize(a, P); b = normalize(b, P); c = normalize(c, P);
	if (P == 2) { vector<int> res;
		if (c % P == 0) res.push_back(0);
		if ((a + b + c) % P == 0) res.push_back(1);
		return res;
	} delta = b * rev(a + a, P) % P;
	a = normalize(-c * rev(a, P) + delta * delta, P);
	if (powMod(a, P / 2, P) + 1 == P) return vector<int>(0);
	for (t = 0, h = P / 2; h % 2 == 0; ++t, h /= 2);
	r1 = powMod(a, h / 2, P);
	if (t > 0) { do b = random() % (P - 2) + 2;
		while (powMod(b, P / 2, P) + 1 != P); }
	for (int i = 1; i <= t; ++i) {
		LL d = r1 * r1 % P * a % P;
		for (int j = 1; j <= t - i; ++j) d = d * d % P;
		if (d + 1 == P) r1 = r1 * pb % P; pb = pb * pb % P;
	} r1 = a * r1 % P; r2 = P - r1;
	r1 = normalize(r1 - delta, P); r2 = normalize(r2 - delta, P);
	if (r1 > r2) swap(r1, r2); vector<int> res(1, r1);
	if (r1 != r2) res.push_back(r2);
	return res;
}