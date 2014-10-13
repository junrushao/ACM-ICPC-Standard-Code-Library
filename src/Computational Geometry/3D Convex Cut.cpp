vector<vector<point> > convexCut(const vector<vector<point> > &pss, const point &p, const point &o) {
	vector<vector<point> > res;
	vector<point> sec;
	for (unsigned itr = 0, size = pss.size(); itr < size; ++itr) {
		const vector<point> &ps = pss[itr];
		int n = ps.size();
		vector<point> qs;
		bool dif = false;
		for (int i = 0; i < n; ++i) {
			int d1 = sign( dot(o, ps[i] - p) );
			int d2 = sign( dot(o, ps[(i + 1) % n] - p) );
			if (d1 <= 0) qs.push_back(ps[i]);
			if (d1 * d2 < 0) {
				point q;
				isFL(p, o, ps[i], ps[(i + 1) % n], q); // must return true
				qs.push_back(q);
				sec.push_back(q);
			}
			if (d1 == 0) sec.push_back(ps[i]);
			else dif = true;
			dif |= dot(o, det(ps[(i + 1) % n] - ps[i], ps[(i + 2) % n] - ps[i])) < -EPS;
		}
		if (!qs.empty() && dif)
			res.insert(res.end(), qs.begin(), qs.end());
	}
	if (!sec.empty()) {
		vector<point> tmp( convexHull2D(sec, o) );
		res.insert(res.end(), tmp.begin(), tmp.end());
	}
	return res;
}

vector<vector<point> > initConvex() {
	vector<vector<point> > pss(6, vector<point>(4));
	pss[0][0] = pss[1][0] = pss[2][0] = point(-INF, -INF, -INF);
	pss[0][3] = pss[1][1] = pss[5][2] = point(-INF, -INF,  INF);
	pss[0][1] = pss[2][3] = pss[4][2] = point(-INF,  INF, -INF);
	pss[0][2] = pss[5][3] = pss[4][1] = point(-INF,  INF,  INF);
	pss[1][3] = pss[2][1] = pss[3][2] = point( INF, -INF, -INF);
	pss[1][2] = pss[5][1] = pss[3][3] = point( INF, -INF,  INF);
	pss[2][2] = pss[4][3] = pss[3][1] = point( INF,  INF, -INF);
	pss[5][0] = pss[4][0] = pss[3][0] = point( INF,  INF,  INF);
	return pss;
}