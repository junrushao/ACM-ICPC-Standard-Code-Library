namespace DLX {
	struct node { int x, y; node *l, *r, *u, *d; } base[MAX * MAX], *top, *head;
	typedef node *link;
	int row, col, nGE, ans, stamp, cntc[MAX], vis[MAX];
	vector<link> eachRow[MAX], eachCol[MAX];
	inline void addElement(int x, int y) {
		top->x = x; top->y = y; top->l = top->r = top->u = top->d = NULL;
		eachRow[x].push_back(top); eachCol[y].push_back(top++);
	}
	void init(int _row, int _col, int _nGE) {
		row = _row; col = _col; nGE = _nGE; top = base; stamp = 0;
		for (int i = 0; i <= col; ++i) vis[i] = 0;
		for (int i = 0; i <= row; ++i) eachRow[i].clear();
		for (int i = 0; i <= col; ++i) eachCol[i].clear();
		for (int i = 0; i <= col; ++i) addElement(0, i);
		head = eachCol[0].front();
	}
	void build() {
		for (int i = 0; i <= row; ++i) {
			vector<link> &v = eachRow[i];
			sort(v.begin(), v.end(), cmpByY);
			int s = v.size();
			for (int j = 0; j < s; ++j) {
				link l = v[j], r = v[(j + 1) % s]; l->r = r; r->l = l;
			}
		}
		for (int i = 0; i <= col; ++i) {
			vector<link> &v = eachCol[i];
			sort(v.begin(), v.end(), cmpByX);
			int s = v.size();
			for (int j = 0; j < s; ++j) {
				link u = v[j], d = v[(j + 1) % s]; u->d = d; d->u = u;
			}
		} for (int i = 0; i <= col; ++i) cntc[i] = (int) eachCol[i].size() - 1;
	}
	void removeExact(link c) {
		c->l->r = c->r; c->r->l = c->l;
		for (link i = c->d; i != c; i = i->d)
			for (link j = i->r; j != i; j = j->r) {
				j->d->u = j->u; j->u->d = j->d; --cntc[j->y];
			}
	}
	void resumeExact(link c) {
		for (link i = c->u; i != c; i = i->u)
			for (link j = i->l; j != i; j = j->l) {
				j->d->u = j; j->u->d = j; ++cntc[j->y];
			}
		c->l->r = c; c->r->l = c;
	}
	void removeRepeat(link c) {
		for (link i = c->d; i != c; i = i->d) {
			i->l->r = i->r; i->r->l = i->l;
		}
	}
	void resumeRepeat(link c) {
		for (link i = c->u; i != c; i = i->u) {
			i->l->r = i; i->r->l = i;
		}
	}
	int calcH() {
		int y, res = 0; ++stamp;
		for (link c = head->r; (y = c->y) <= row && c != head; c = c->r) {
			if (vis[y] != stamp) {
				vis[y] = stamp; ++res;
				for (link i = c->d; i != c; i = i->d)
					for (link j = i->r; j != i; j = j->r) vis[j->y] = stamp;
			}
		} return res;
	}
	void DFS(int dep) { if (dep + calcH() >= ans) return;
		if (head->r->y > nGE || head->r == head) {
			if (ans > dep) ans = dep; return;
		} link c = NULL;
		for (link i = head->r; i->y <= nGE && i != head; i = i->r)
			if (!c || cntc[i->y] < cntc[c->y]) c = i;
		for (link i = c->d; i != c; i = i->d) {
			removeRepeat(i);
			for (link j = i->r; j != i; j = j->r) if (j->y <= nGE) removeRepeat(j);
			for (link j = i->r; j != i; j = j->r) if (j->y  > nGE) removeExact(base + j->y);
			DFS(dep + 1);
			for (link j = i->l; j != i; j = j->l) if (j->y  > nGE) resumeExact(base + j->y);
			for (link j = i->l; j != i; j = j->l) if (j->y <= nGE) resumeRepeat(j);
			resumeRepeat(i);
		}
	}
	int solve() { build(); ans = INF; DFS(0); return ans; }
}