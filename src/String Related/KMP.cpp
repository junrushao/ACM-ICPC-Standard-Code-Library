void KMP(char *a, int la, char *b, int lb, int *next, int *ext) {
	--a; --b; --next; --ext;
	for (int i = 2, j = next[1] = 0; i <= la; i++) {
		while (j && a[j + 1] != a[i]) j = next[j]; if (a[j + 1] == a[i]) ++j; next[i] = j;
	} for (int i = 1, j = 0; i <= lb; ++i) {
		while (j && a[j + 1] != b[i]) j = next[j]; if (a[j + 1] == b[i]) ++j; ext[i] = j;
		if (j == la) j = next[j];
	}
} void ExKMP(char *a, int la, char *b, int lb, int *next, int *ext) {
	next[0] = la; for (int &j = next[1] = 0; j + 1 < la && a[j] == a[j + 1]; ++j);
	for (int i = 2, k = 1; i < la; ++i) {
		int p = k + next[k], l = next[i - k]; if (l < p - i) next[i] = l;
		else for (int &j = next[k = i] = max(0, p - i); i + j < la && a[j] == a[i + j]; ++j);
	} for (int &j = ext[0] = 0; j < la && j < lb && a[j] == b[j]; ++j);
	for (int i = 1, k = 0; i < lb; ++i) {
		int p = k + ext[k], l = next[i - k]; if (l < p - i) ext[i] = l;
		else for (int &j = ext[k = i] = max(0, p - i); j < la && i + j < lb && a[j] == b[i + j]; ++j);
	}
}