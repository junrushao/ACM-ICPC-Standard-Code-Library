int minimalRepresentation(int N, char *s) { // s must be double-sized and 0-based
	int i, j, k, l; for (i = 0; i < N; ++i) s[i + N] = s[i]; s[N + N] = 0;
	for (i = 0, j = 1; j < N; ) {
		for (k = 0; k < N && s[i + k] == s[j + k]; ++k);
		if (k >= N) break; if (s[i + k] < s[j + k]) j += k + 1;
		else l = i + k, i = j, j = max(l, j) + 1;
	} return i; // [i, i + N) is the minimal representation
}
