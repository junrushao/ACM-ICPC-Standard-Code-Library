class Chordal { // 1-Based, G is the Graph, must be sorted before call Check_Chordal
public: // Construct will sort it automatically
	int v[Maxn], id[Maxn];  bool inseq[Maxn]; priority_queue<pair<int, int> > pq;
	vector<int> Construct_Perfect_Elimination_Sequence(vector<int> *G, int n) { // O(m + nlogn)
		vector<int> seq(n + 1, 0);
		for (int i = 0; i <= n; ++i) inseq[i] = false, sort(G[i].begin(), G[i].end()), v[i] = 0;
		int cur = n; pair<int, int> Mx; while(!pq.empty()) pq.pop(); pq.push(make_pair(0, 1));
		for (int i = n; i >= 1; --i) {
			while (!pq.empty() && (Mx = pq.top(), inseq[Mx.second] || Mx.first != v[Mx.second])) pq.pop();
			id[Mx.second] = cur;
			int x = seq[cur--] = Mx.second, sz = (int)G[Mx.second].size(); inseq[x] = true;
			for (int j = 0; j < sz; ++j) {
				int y = G[x][j]; if(!inseq[y]) pq.push(make_pair(++v[y], y));
			}
		} return seq;
	}
	bool Check_Chordal(vector<int> *G, vector<int> &seq, int n) { // O(n + mlogn), plz gen seq first 
		bool isChordal = true;
		for (int i = n - 1; i >= 1 && isChordal; --i) {
			int x = seq[i], sz, y = -1;
			if ((sz = (int)G[x].size()) == 0) continue;
            for(int j = 0; j < sz; ++j) {
				if (id[G[x][j]] < i) continue;
				if (y == -1 || id[y] > id[G[x][j]]) y = G[x][j];
			} if (y == -1) continue;
			for (int j = 0; j < sz; ++j) {
				int y1 = G[x][j]; if (id[y1] < i) continue;
				if (y1 == y || binary_search(G[y].begin(), G[y].end(), y1)) continue;
				isChordal = false; break;
			}
		} return isChordal;
	}
};