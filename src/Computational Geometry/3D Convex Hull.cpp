namespace ConvexHull3D {
	#define volume(a, b, c, d) (mix(ps[b] - ps[a], ps[c] - ps[a], ps[d] - ps[a]))
	vector<Facet> getHull(int n, point ps[]) {
		static int mark[MAXN][MAXN], a, b, c;
		int stamp = 0;
		bool exist = false;
		vector<Facet> facet;
		random_shuffle(ps, ps + n);
		for (int i = 2; i < n && !exist; i++) {
			point ndir = det(ps[0] - ps[i], ps[1] - ps[i]);
			if (ndir.len() < EPS) continue;
			swap(ps[i], ps[2]);
			for (int j = i + 1; j < n && !exist; j++)
				if (sign(volume(0, 1, 2, j)) != 0) {
					exist = true;
					swap(ps[j], ps[3]);
					facet.push_back(Facet(0, 1, 2));
					facet.push_back(Facet(0, 2, 1));
				}
		}
		if (!exist) return ConvexHull2D(n, ps);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				mark[i][j] = 0;
		stamp = 0;
		for (int v = 3; v < n; ++v) {
			vector<Facet> tmp;
			++stamp;
			for (unsigned i = 0; i < facet.size(); i++) {
				a = facet[i].a;
				b = facet[i].b;
				c = facet[i].c;
				if (sign(volume(v, a, b, c)) < 0)
					mark[a][b] = mark[a][c] = 
					mark[b][a] = mark[b][c] = 
					mark[c][a] = mark[c][b] = stamp;
				else tmp.push_back(facet[i]);
			} facet = tmp;
			for (unsigned i = 0; i < tmp.size(); i++) {
				a = facet[i].a; b = facet[i].b; c = facet[i].c;
				if (mark[a][b] == stamp) facet.push_back(Facet(b, a, v));
				if (mark[b][c] == stamp) facet.push_back(Facet(c, b, v));
				if (mark[c][a] == stamp) facet.push_back(Facet(a, c, v));
			}
		} return facet;
	}
	#undef volume
}
namespace Gravity {
	using ConvexHull3D::Facet;
	point findG(point ps[], const vector<Facet> &facet) {
		double ws = 0; point res(0.0, 0.0, 0.0), o = ps[ facet[0].a ];
		for (int i = 0, size = facet.size(); i < size; ++i) {
			const point &a = ps[ facet[i].a ], &b = ps[ facet[i].b ], &c = ps[ facet[i].c ];
			point p = (a + b + c + o) * 0.25;
			double w = mix(a - o, b - o, c - o);
			ws += w;
			res = res + p * w;
		} res = res / ws;
		return res;
	}
}
