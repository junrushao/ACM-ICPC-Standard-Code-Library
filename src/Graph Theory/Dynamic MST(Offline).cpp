const int maxn = 100000 + 5;
const int maxm = 1000000 + 5;
const int maxq = 1000000 + 5;
const int qsize = maxm + 3 * maxq;
int n, m, Q, x[qsize], y[qsize], z[qsize], qx[maxq], qy[maxq], a[maxn], *tz;
int kx[maxn], ky[maxn], kt, vd[maxn], id[maxm], app[maxm];
bool extra[maxm];
void init() {
	scanf("%d%d", &n, &m); for (int i = 0; i < m; i++) scanf("%d%d%d", x + i, y + i, z + i);
	scanf("%d", &Q); for (int i = 0; i < Q; i++) { scanf("%d%d", qx + i, qy + i); qx[i]--; }
}
int find(int x) {
	int root = x, next; while (a[root]) root = a[root];
	while ((next = a[x]) != 0) a[x] = root, x = next; return root;
}
inline bool cmp(const int &a, const int &b) { return tz[a] < tz[b]; }
void solve(int *qx, int *qy, int Q, int n, int *x, int *y, int *z, int m, long long ans) {
	int ri, rj;
	if (Q == 1) {
		for (int i = 1; i <= n; i++) a[i] = 0; z[qx[0]] = qy[0];
		for (int i = 0; i < m; i++) id[i] = i;
		tz = z; sort(id, id + m, cmp);
		for (int i = 0; i < m; i++) {
			ri = find(x[id[i]]); rj = find(y[id[i]]);
			if (ri != rj) ans += z[id[i]], a[ri] = rj;
		} printf("%I64d\n", ans);
		return;
	} int tm = kt = 0, n2 = 0, m2 = 0;
	for (int i = 1; i <= n; i++) a[i] = 0;
	for (int i = 0; i < Q; i++) {
		ri = find(x[qx[i]]); rj = find(y[qx[i]]); if (ri != rj) a[ri] = rj;
	}
	for (int i = 0; i < m; i++) extra[i] = true;
	for (int i = 0; i < Q; i++) extra[qx[i]] = false;
	for (int i = 0; i < m; i++) if (extra[i]) id[tm++] = i;
	tz = z; sort(id, id + tm, cmp);
	for (int i = 0; i < tm; i++) {
		ri = find(x[id[i]]); rj = find(y[id[i]]);
		if (ri != rj)
			a[ri] = rj, ans += z[id[i]], kx[kt] = x[id[i]], ky[kt] = y[id[i]], kt++;
	}
	for (int i = 1; i <= n; i++) a[i] = 0;
	for (int i = 0; i < kt; i++) a[find(kx[i])] = find(ky[i]);
	for (int i = 1; i <= n; i++) if (a[i] == 0) vd[i] = ++n2;
	for (int i = 1; i <= n; i++) if (a[i] != 0) vd[i] = vd[find(i)];
	int *Nx = x + m, *Ny = y + m, *Nz = z + m;
	for (int i = 0; i < m; i++) app[i] = -1;
	for (int i = 0; i < Q; i++)
		if (app[qx[i]] == -1)
			Nx[m2] = vd[x[qx[i]]], Ny[m2] = vd[y[qx[i]]], Nz[m2] = z[qx[i]], app[qx[i]] = m2, m2++;
	for (int i = 0; i < Q; i++) {
		z[qx[i]] = qy[i];
		qx[i] = app[qx[i]];
	}
	for (int i = 1; i <= n2; i++) a[i] = 0;
	for (int i = 0; i < tm; i++) {
		ri = find(vd[x[id[i]]]); rj = find(vd[y[id[i]]]);
		if (ri != rj)
			a[ri] = rj, Nx[m2] = vd[x[id[i]]], Ny[m2] = vd[y[id[i]]], Nz[m2] = z[id[i]], m2++;
	}
	int mid = Q / 2;
	solve(qx, qy, mid, n2, Nx, Ny, Nz, m2, ans);
	solve(qx + mid, qy + mid, Q - mid, n2, Nx, Ny, Nz, m2, ans);
}
void work() { if (Q) solve(qx, qy, Q, n, x, y, z, m, 0); }
int main() { init(); work(); return 0; }