vector<int> solve(int p, int N, int a) {
	if ((a %= p) == 0) return vector<int>(1, 0);
	int g = findPrimitiveRoot(p), m = modLog(g, a, p); // g ^ m = a (mod p)
	if (m == -1) return vector<int>(0);
	LL B = p - 1, x, y, d; exgcd(N, B, x, y, d);
	if (m % d != 0) return vector<int>(0);
	vector<int> ret; x = (x * (m / d) % B + B) % B; // g ^ B mod p = g ^ (p - 1) mod p = 1
	for (int i = 0, delta = B / d; i < d; ++i) {
		x = (x + delta) % B; ret.push_back((int)powMod(g, x, p));
	} sort(ret.begin(), ret.end());
	ret.resize(unique(ret.begin(), ret.end()) - ret.begin());
	return ret;
}