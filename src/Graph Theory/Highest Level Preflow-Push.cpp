namespace Network {
	int S, T, Ncnt, hsize, heap[MAXN], h[MAXN], inq[MAXN], Q[MAXN], vh[MAXN * 2 + 1];
	LL E[MAXN]; edge cur[MAXN];
	inline void pushFlow(int x, int y, edge e) {
		int d = (int)min(E[x], (LL)e->c);
		E[x] -= d; e->c -= d; E[y] += d; e->op->c += d;
	} inline bool heapCmp(int x, int y) { return h[x] < h[y]; }
	inline void hpush(int x) {
		inq[x] = true; heap[++hsize] = x; push_heap(heap + 1, heap + hsize + 1, heapCmp);
	} inline void hpop(int x) {
		inq[x] = false; pop_heap(heap + 1, heap + hsize + 1, heapCmp); --hsize;
	} LL maxFlow() {
		int head = 0, tail = 0, x, y, h0;
		memset(h, 63, sizeof(int) * (Ncnt + 1));
		memset(vh, 0, sizeof(int) * (2 * Ncnt + 2));
		memset(E, 0, sizeof(LL) * (Ncnt + 1));
		memset(inq, 0, sizeof(int) * (Ncnt + 1));
		memcpy(cur, fir, sizeof(edge) * (Ncnt + 1));
		for (Q[++tail] = T, h[T] = 0; head < tail; )
			for (edge e(fir[x = Q[++head]]); e; e = e->next) if (e->op->c)
				if (h[y = e->to] >= INF) h[y] = h[x] + 1, Q[++tail] = y;
		if (h[S] >= Ncnt) return 0;
		h[S] = Ncnt; E[S] = LL_INF;
		for (int i = 1; i <= Ncnt; ++i) if (h[i] <= Ncnt) ++vh[ h[i] ];
		hsize = 0;
		for (edge e(fir[S]); e; e = e->next) if (e->c && h[y = e->to] < Ncnt) {
			pushFlow(S, y, e); if (!inq[y] && y != S && y != T) hpush(y);
		} while (hsize) {
			bool good = false;
			for (edge &e(cur[x = heap[1]]); e; e = e->next) if (e->c)
				if (h[x] == h[y = e->to] + 1) {
					good = true; pushFlow(x, y, e); if (E[x] == 0) hpop(x);
					if (inq[y] == false && y != S && y != T) hpush(y);
					break;
				}
			if (!good) { // relabel
				hpop(x); --vh[ h0 = h[x] ];
				int &minH = h[x] = INF; cur[x] = NULL;
				for (edge e(fir[x]); e; e = e->next) if (e->c)
					if ( cMin(minH, h[e->to] + 1) ) cur[x] = fir[x];
				hpush(x); ++vh[ h[x] ];
				if (vh[h0] == 0 && h0 < Ncnt) {
					hsize = 0;
					for (int i = 1; i <= Ncnt; ++i) {
						if (h[i] > h0 && h[i] < Ncnt) --vh[ h[i] ], ++vh[ h[i] = Ncnt + 1 ];
						if (i != S && i != T && E[i]) heap[++hsize] = i;
					} make_heap(heap + 1, heap + hsize + 1, heapCmp);
				}
			}
		} return E[T];
	}
}