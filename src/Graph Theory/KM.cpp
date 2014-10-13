int N, Tcnt, w[MAXN][MAXN], slack[MAXN];
int lx[MAXN], linkx[MAXN], visy[MAXN], ly[MAXN], linky[MAXN], visx[MAXN]; // `初值全为0`
bool DFS(int x) { visx[x] = Tcnt;
	Rep(y, 1, N) if(visy[y] != Tcnt) { int t = lx[x] + ly[y] - w[x][y];
		if (t == 0) { visy[y] = Tcnt;
			if (!linky[y] || DFS(linky[y])) { linkx[x] = y; linky[y] = x; return true; }
		} else cMin(slack[y], t);
	} return false;
} void KM() {
	Tcnt = 0; Rep(x, 1, N) Rep(y, 1, N) cMax(lx[x], w[x][y]);
	Rep(S, 1, N) { Rep(i, 1, N) slack[i] = INF;
		for (++Tcnt; !DFS(S); ++Tcnt) { int d = INF;
			Rep(y, 1, N) if(visy[y] != Tcnt) cMin(d, slack[y]);
			Rep(x, 1, N) if(visx[x] == Tcnt) lx[x] -= d;
			Rep(y, 1, N) if(visy[y] == Tcnt) ly[y] += d; else slack[y] -= d;
		}
	}
}