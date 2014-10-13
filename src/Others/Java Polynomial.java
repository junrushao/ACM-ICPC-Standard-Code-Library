class Polynomial {
	final static Polynomial ZERO = new Polynomial(new int[] { 0 });
	final static Polynomial ONE = new Polynomial(new int[] { 1 });
	final static Polynomial X = new Polynomial(new int[] { 0, 1 });
	int[] coef;
	static Polynomial valueOf(int val) { return new Polynomial(new int[] { val }); }
	Polynomial(int[] coef) { this.coef = Arrays.copyOf(coef, coef.length); }
	Polynomial add(Polynomial o, int mod); // omitted
	Polynomial subtract(Polynomial o, int mod); // omitted
	Polynomial multiply(Polynomial o, int mod); // omitted
	Polynomial scale(int o, int mod)；// omitted
	public String toString() {
		int n = coef.length; String ret = "";
		for (int i = n - 1; i > 0; --i) if (coef[i] != 0)
			ret += coef[i] + "x^" + i + "+";
		return ret + coef[0];
	}
	static Polynomial lagrangeInterpolation(int[] x, int[] y, int mod) {
		int n = x.length; Polynomial ret = Polynomial.ZERO;
		for (int i = 0; i < n; ++i) {
			Polynomial poly = Polynomial.valueOf(y[i]);
			for (int j = 0; j < n; ++j) if (i != j) {
				poly = poly.multiply(
					Polynomial.X.subtract(Polynomial.valueOf(x[j]), mod), mod);
				poly = poly.scale(powMod(x[i] - x[j] + mod, mod - 2, mod), mod);
			} ret = ret.add(poly, mod);
		} return ret;
	}
}