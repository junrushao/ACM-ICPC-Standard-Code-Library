LL multiplyMod(LL a, LL b, LL P) { // `需要保证 a 和 b 非负`
	LL t = (a * b - LL((long double)a / P * b + 1e-3) * P) % P;
	return t < 0 : t + P : t;
}