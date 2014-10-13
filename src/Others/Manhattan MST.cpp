const int INF = 1000000005;
struct TreeEdge {
	int x, y, z; void make(int _x, int _y, int _z) { x = _x; y = _y; z = _z; }
} data[maxn * 4];
int n, x[maxn], y[maxn], px[maxn], py[maxn], id[maxn], tree[maxn], node[maxn], val[maxn], fa[maxn];
bool operator < (const TreeEdge& x, const TreeEdge& y) { return x.z < y.z; }
bool cmp1(int a, int b) { return x[a] < x[b]; }
bool cmp2(int a, int b) { return y[a] < y[b]; }
bool cmp3(int a, int b) { return (y[a] - x[a] < y[b] - x[b] || (y[a] - x[a] == y[b] - x[b] && y[a] > y[b])); }
bool cmp4(int a, int b) { return (y[a] - x[a] > y[b] - x[b] || (y[a] - x[a] == y[b] - x[b] && x[a] > x[b])); }
bool cmp5(int a, int b) { return (x[a] + y[a] > x[b] + y[b] || (x[a] + y[a] == x[b] + y[b] && x[a] < x[b])); }
bool cmp6(int a, int b) { return (x[a] + y[a] < x[b] + y[b] || (x[a] + y[a] == x[b] + y[b] && y[a] > y[b])); }
void Change_X() {
	for (int i = 0; i < n; ++i) val[i] = x[i];
	for (int i = 0; i < n; ++i) id[i] = i;
	sort(id, id + n, cmp1);
	int cntM = 1, last = val[id[0]]; px[id[0]] = 1;
	for (int i = 1; i < n; ++i) {
		if (val[id[i]] > last) ++cntM, last = val[id[i]];
		px[id[i]] = cntM;
	}
}
void Change_Y() {
	for (int i = 0; i < n; ++i) val[i] = y[i];
	for (int i = 0; i < n; ++i) id[i] = i;
	sort(id, id + n, cmp2);
	int cntM = 1, last = val[id[0]]; py[id[0]] = 1;
	for (int i = 1; i < n; ++i) {
		if (val[id[i]] > last)
			++cntM, last = val[id[i]];
		py[id[i]] = cntM;
	}
}
inline int Cost(int a, int b) { return abs(x[a] - x[b]) + abs(y[a] - y[b]); }
int find(int x) { return (fa[x] == x) ? x : (fa[x] = find(fa[x])); }
int main() {
	for (int i = 0; i < n; ++i) scanf("%d%d", x + i, y + i);
	Change_X(); Change_Y();
	int cntE = 0; for (int i = 0; i < n; ++i) id[i] = i;
	sort(id, id + n, cmp3);
	for (int i = 1; i <= n; ++i) tree[i] = INF, node[i] = -1;
	for (int i = 0; i < n; ++i) {
		int Min = INF, Tnode = -1;
		for (int k = py[id[i]]; k <= n; k += k & (-k))
			if (tree[k] < Min) Min = tree[k], Tnode = node[k];
		if (Tnode >= 0) data[cntE++].make(id[i], Tnode, Cost(id[i], Tnode));
		int tmp = x[id[i]] + y[id[i]];
		for (int k = py[id[i]]; k; k -= k & (-k))
			if (tmp < tree[k]) tree[k] = tmp, node[k] = id[i];
	} sort(id, id + n, cmp4);
	for (int i = 1; i <= n; ++i) tree[i] = INF, node[i] = -1;
	for (int i = 0; i < n; ++i) {
		int Min = INF, Tnode = -1;
		for (int k = px[id[i]]; k <= n; k += k & (-k))
			if (tree[k] < Min) Min = tree[k], Tnode = node[k];
		if (Tnode >= 0) data[cntE++].make(id[i], Tnode, Cost(id[i], Tnode));
		int tmp = x[id[i]] + y[id[i]];
		for (int k = px[id[i]]; k; k -= k & (-k))
			if (tmp < tree[k]) tree[k] = tmp, node[k] = id[i];
	}
	sort(id, id + n, cmp5);
	for (int i = 1; i <= n; ++i) tree[i] = INF, node[i] = -1;
	for (int i = 0; i < n; ++i) {
		int Min = INF, Tnode = -1;
		for (int k = px[id[i]]; k; k -= k & (-k))
			if (tree[k] < Min) Min = tree[k], Tnode = node[k];
		if (Tnode >= 0) data[cntE++].make(id[i], Tnode, Cost(id[i], Tnode));
		int tmp = -x[id[i]] + y[id[i]];
		for (int k = px[id[i]]; k <= n; k += k & (-k))
			if (tmp < tree[k]) tree[k] = tmp, node[k] = id[i];
	} sort(id, id + n, cmp6);
	for (int i = 1; i <= n; ++i) tree[i] = INF, node[i] = -1;
	for (int i = 0; i < n; ++i) {
		int Min = INF, Tnode = -1;
		for (int k = py[id[i]]; k <= n; k += k & (-k))
			if (tree[k] < Min) Min = tree[k], Tnode = node[k];
		if (Tnode >= 0) data[cntE++].make(id[i], Tnode, Cost(id[i], Tnode));
		int tmp = -x[id[i]] + y[id[i]];
		for (int k = py[id[i]]; k; k -= k & (-k))
			if (tmp < tree[k]) tree[k] = tmp, node[k] = id[i];
	}
	long long Ans = 0; sort(data, data + cntE);
	for (int i = 0; i < n; ++i) fa[i] = i;
	for (int i = 0; i < cntE; ++i) if (find(data[i].x) != find(data[i].y)) {
		Ans += data[i].z;
		fa[fa[data[i].x]] = fa[data[i].y];
	} cout << Ans << endl;
}