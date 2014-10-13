vector<int> HigherResidue(int p, int N, int a) {
	if ((a %= p) == 0) return vector<int>(1, 0);
	int g = findPrimitiveRoot(p), m = modLog(g, a, p); // `$g ^ m \equiv a \pmod(p)$`
	if (m == -1) return vector<int>(0);
	LL B = p - 1, x, y, d; exgcd(N, B, x, y, d);
	if (m % d != 0) return vector<int>(0);
	vector<int> ret;
	x = (x * (m / d) % B + B) % B; // `g ^ B \pmod(p) \equiv g ^ (p - 1) \pmod(p) \equiv 1`
	for (int i = 0, delta = B / d; i < d; ++i) {
		x = (x + delta) % B; ret.push_back((int)powMod(g, x, p));
	} sort(ret.begin(), ret.end());
	ret.resize(unique(ret.begin(), ret.end()) - ret.begin());
	return ret;
}