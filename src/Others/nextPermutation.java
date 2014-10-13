boolean nextPermutation(int[] is) {
	int n = is.length;
	for (int i = n - 1; i > 0; i--) {
		if (is[i - 1] < is[i]) {
			int j = n; while (is[i - 1] >= is[--j]);
			swap(is, i - 1, j); // swap is[i - 1], is[j]
			rev(is, i, n); // reverse is[i, n)
			return true;
		}
	} rev(is, 0, n);
	return false;
}
