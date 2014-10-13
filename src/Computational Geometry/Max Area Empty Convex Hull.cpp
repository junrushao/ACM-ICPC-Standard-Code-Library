inline bool toUpRight(const point &a, const point &b) {
	int c = sign(b.y - a.y); if (c > 0) return true;
	return c == 0 && sign(b.x - a.x) > 0;
}
inline bool cmpByPolarAngle(const point &a, const point &b) { // `counter-clockwise, shorter first if they share the same polar angle`
	int c = sign(det(a, b)); if (c != 0) return c > 0;
	return sign(b.len() - a.len()) > 0;
}
double maxEmptyConvexHull(int N, point p[]) {
	static double dp[MAXN][MAXN];
	static point vec[MAXN];
	static int seq[MAXN]; // `empty triangles formed with $(0, 0), vec[o], vec[ seq[i] ]$`
	double ans = 0.0;
	Rep(o, 1, N) {
		int totVec = 0;
		Rep(i, 1, N) if (toUpRight(p[o], p[i])) vec[++totVec] = p[i] - p[o];
		sort(vec + 1, vec + totVec + 1, cmpByPolarAngle);
		Rep(i, 1, totVec) Rep(j, 1, totVec) dp[i][j] = 0.0;
		Rep(k, 2, totVec) {
			int i = k - 1;
			while (i > 0 && sign( det(vec[k], vec[i]) ) == 0) --i;
			int totSeq = 0;
			for (int j; i > 0; i = j) {
				seq[++totSeq] = i;
				for (j = i - 1; j > 0 && sign(det(vec[i] - vec[k], vec[j] - vec[k])) > 0; --j);
				double v = det(vec[i], vec[k]) * 0.5;
				if (j > 0) v += dp[i][j];
				dp[k][i] = v;
				cMax(ans, v);
			} for (int i = totSeq - 1; i >= 1; --i) cMax( dp[k][ seq[i] ], dp[k][seq[i + 1]] );
		}
	} return ans;
}