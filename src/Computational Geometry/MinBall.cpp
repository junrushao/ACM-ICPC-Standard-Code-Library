int outCnt; point out[4], res; double radius;
void ball() {
	static point q[3];
	static double m[3][3], sol[3], L[3], det;
	int i, j; res = point(0.0, 0.0, 0.0); radius = 0.0;
	switch (outCnt) {
	case 1: res = out[0]; break;
	case 2: res = (out[0] + out[1]) * 0.5; radius = (res - out[0]).norm();
		break;
	case 3:
		q[0] = out[1] - out[0]; q[1] = out[2] - out[0];
		for (i = 0; i < 2; ++i) for (j = 0; j < 2; ++j)
			m[i][j] = dot(q[i], q[j]) * 2.0;
		for (i = 0; i < 2; ++i) sol[i] = dot(q[i], q[i]);
		det = m[0][0] * m[1][1] - m[0][1] * m[1][0];
		if (sign(det) == 0) return;
		L[0] = (sol[0] * m[1][1] - sol[1] * m[0][1]) / det;
		L[1] = (sol[1] * m[0][0] - sol[0] * m[1][0]) / det;
		res = out[0] + q[0] * L[0] + q[1] * L[1];
		radius = (res - out[0]).norm();
		break;
	case 4:
		q[0] = out[1] - out[0]; q[1] = out[2] - out[0]; q[2] = out[3] - out[0];
		for (i = 0; i < 3; ++i) for (j = 0; j < 3; ++j) m[i][j] = dot(q[i], q[j]) * 2;
		for (i = 0; i < 3; ++i) sol[i] = dot(q[i], q[i]);
		det = m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0]
		    + m[0][2] * m[2][1] * m[1][0] - m[0][2] * m[1][1] * m[2][0]
		    - m[0][1] * m[1][0] * m[2][2] - m[0][0] * m[1][2] * m[2][1];
		if (sign(det) == 0) return;
		for (j = 0; j < 3; ++j) { for (i = 0; i < 3; ++i) m[i][j] = sol[i];
			L[j] = (m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0]
				  + m[0][2] * m[2][1] * m[1][0] - m[0][2] * m[1][1] * m[2][0]
				  - m[0][1] * m[1][0] * m[2][2] - m[0][0] * m[1][2] * m[2][1]) / det;
			for (i = 0; i < 3; ++i) m[i][j] = dot(q[i], q[j]) * 2;
		} res = out[0];
		for (i = 0; i < 3; ++i) res += q[i] * L[i]; radius = (res - out[0]).norm();
	}
}
void minball(int n, point pt[]) {
	ball();
	if (outCnt < 4) for (int i = 0; i < n; ++i)
		if ((res - pt[i]).norm() > +radius + EPS) {
			out[outCnt] = pt[i]; ++outCnt; minball(i, pt); --outCnt;
			if (i > 0) {
				point Tt = pt[i];
				memmove(&pt[1], &pt[0], sizeof(point) * i);
				pt[0] = Tt;
			}
		}
}
pair<point, double> main(int npoint, point pt[]) { // 0-based
	random_shuffle(pt, pt + npoint); radius = -1;
	for (int i = 0; i < npoint; i++) { if ((res - pt[i]).norm() > EPS + radius) {
		outCnt = 1; out[0] = pt[i]; minball(i, pt); } }
	return make_pair(res, sqrt(radius));
}