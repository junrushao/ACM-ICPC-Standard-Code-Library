template <class T> double Romberg(const T&f, double a, double b, double eps = 1e-8) {
	vector<double> t; double h = b - a, last, now; int k = 1, i = 1;
	t.push_back(h * (f(a) + f(b)) / 2); // `梯形`
	do {
		last = t.back(); now = 0; double x = a + h / 2;
		for (int j = 0; j < k; ++j, x += h) now += f(x);
		now = (t[0] + h * now) / 2; double k1 = 4.0 / 3.0, k2 = 1.0 / 3.0;
		for (int j = 0; j < i; ++j, k1 = k2 + 1) {
			double tmp = k1 * now - k2 * t[j];
			t[j] = now; now = tmp; k2 /= 4 * k1 - k2; // `防止溢出`
		} t.push_back(now); k *= 2; h /= 2; ++i;
	} while (fabs(last - now) > eps);
	return t.back();
}