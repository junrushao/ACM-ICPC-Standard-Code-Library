// len[i] : the max length of palindrome whose mid point is (i / 2)
void Manacher(int n, char cs[], int len[]) { // 0-based, len[] must be double sized
	for (int i = 0; i < n + n; ++i) len[i] = 0;
	for (int i = 0, j = 0, k; i < n * 2; i += k, j = max(j - k, 0)) {
		while (i - j >= 0 && i + j + 1 < n * 2 && cs[(i - j) / 2] == cs[(i + j + 1) / 2]) j++;
		len[i] = j; for (k = 1; i - k >= 0 && j - k >= 0 && len[i - k] != j - k; k++)
			len[i + k] = min(len[i - k], j - k);
	}
}