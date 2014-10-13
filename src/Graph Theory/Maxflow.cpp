namespace Maxflow {
	int h[MAXNODE], vh[MAXNODE], S, T, Ncnt; edge cur[MAXNODE], pe[MAXNODE];
	void init(int _S, int _T, int _Ncnt) { S = _S; T = _T; Ncnt = _Ncnt; }
	int maxflow() {
		static int Q[MAXNODE]; int x, y, augc, flow = 0, head = 0, tail = 0; edge e;
		Rep(i, 0, Ncnt) cur[i] = fir[i]; Rep(i, 0, Ncnt) h[i] = INF; Rep(i, 0, Ncnt) vh[i] = 0;
		for (Q[++tail] = T, h[T] = 0; head < tail; ) {
			x = Q[++head]; ++vh[ h[x] ];
			for (e = fir[x]; e; e = e->next) if (e->op->c)
				if (h[y = e->to] >= INF) h[y] = h[x] + 1, Q[++tail] = y;
		} for (x = S; h[S] < Ncnt; ) {
			for (e = cur[x]; e; e = e->next) if (e->c)
				if (h[y = e->to] + 1 == h[x]) { cur[x] = pe[y] = e; x = y; break; }
			if (!e) {
				if (--vh[ h[x] ] == 0) break; h[x] = Ncnt; cur[x] = NULL;
				for (e = fir[x]; e; e = e->next) if (e->c)
					if ( cMin( h[x], h[e->to] + 1  ) ) cur[x] = e;
				++vh[ h[x] ];
				if (x != S) x = pe[x]->op->to;
			} else if (x == T) { augc = INF;
				for (x = T; x != S; x = pe[x]->op->to) cMin(augc, pe[x]->c);
				for (x = T; x != S; x = pe[x]->op->to) {
					pe[x]->c -= augc; pe[x]->op->c += augc;
				} flow += augc;
			}
		} return flow;
	}
}