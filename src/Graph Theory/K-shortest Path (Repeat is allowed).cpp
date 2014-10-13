#define for_each(it, v) for (vector<Edge*>::iterator it = (v).begin(); it != (v).end(); ++it)
const int MAX_N = 10000, MAX_M = 50000, MAX_K = 10000, INF = 1000000000;
struct Edge { int from, to, weight; };
struct HeapNode { Edge* edge; int depth; HeapNode* child[4]; }; // child[0..1] for heap G, child[2..3] for heap out edge

int n, m, k, s, t; Edge* edge[MAX_M];
int dist[MAX_N]; Edge* prev[MAX_N];
vector<Edge*> graph[MAX_N]; vector<Edge*> graphR[MAX_N];
HeapNode* nullNode; HeapNode* heapTop[MAX_N];

HeapNode* createHeap(HeapNode* curNode, HeapNode* newNode) {
	if (curNode == nullNode) return newNode; HeapNode* rootNode = new HeapNode;
	memcpy(rootNode, curNode, sizeof(HeapNode));
	if (newNode->edge->weight < curNode->edge->weight) {
		rootNode->edge = newNode->edge; rootNode->child[2] = newNode->child[2]; rootNode->child[3] = newNode->child[3];
		newNode->edge = curNode->edge; newNode->child[2] = curNode->child[2]; newNode->child[3] = curNode->child[3];
	} if (rootNode->child[0]->depth < rootNode->child[1]->depth) rootNode->child[0] = createHeap(rootNode->child[0], newNode);
	else rootNode->child[1] = createHeap(rootNode->child[1], newNode);
	rootNode->depth = max(rootNode->child[0]->depth, rootNode->child[1]->depth) + 1;
	return rootNode;
}
bool heapNodeMoreThan(HeapNode* node1, HeapNode* node2) { return node1->edge->weight > node2->edge->weight; }

int main() {
	scanf("%d%d%d", &n, &m, &k); scanf("%d%d", &s, &t); s--, t--;
	while (m--) { Edge* newEdge = new Edge;
		int i, j, w; scanf("%d%d%d", &i, &j, &w);
		i--, j--; newEdge->from = i; newEdge->to = j; newEdge->weight = w;
		graph[i].push_back(newEdge); graphR[j].push_back(newEdge);
	}
	//Dijkstra
	queue<int> dfsOrder; memset(dist, -1, sizeof(dist));
	typedef pair<int, pair<int, Edge*> > DijkstraQueueItem;
	priority_queue<DijkstraQueueItem, vector<DijkstraQueueItem>, greater<DijkstraQueueItem> > dq;
	dq.push(make_pair(0, make_pair(t, (Edge*) NULL)));
	while (!dq.empty()) {
		int d = dq.top().first; int i = dq.top().second.first;
		Edge* edge = dq.top().second.second; dq.pop();
		if (dist[i] != -1) continue;
		dist[i] = d; prev[i] = edge; dfsOrder.push(i);
		for_each(it, graphR[i]) dq.push(make_pair(d + (*it)->weight, make_pair((*it)->from, *it)));
	}
	//Create edge heap
	nullNode = new HeapNode; nullNode->depth = 0; nullNode->edge = new Edge; nullNode->edge->weight = INF;
	fill(nullNode->child, nullNode->child + 4, nullNode);
	while (!dfsOrder.empty()) {
		int i = dfsOrder.front(); dfsOrder.pop();
		if (prev[i] == NULL) heapTop[i] = nullNode;
		else heapTop[i] = heapTop[prev[i]->to];
		vector<HeapNode*> heapNodeList;
		for_each(it, graph[i]) { int j = (*it)->to; if (dist[j] == -1) continue;
			(*it)->weight += dist[j] - dist[i]; if (prev[i] != *it) {
				HeapNode* curNode = new HeapNode;
				fill(curNode->child, curNode->child + 4, nullNode);
				curNode->depth = 1; curNode->edge = *it;
				heapNodeList.push_back(curNode);
			}
		} if (!heapNodeList.empty()) { //Create heap out
			make_heap(heapNodeList.begin(), heapNodeList.end(), heapNodeMoreThan);
			int size = heapNodeList.size();
			for (int p = 0; p < size; p++) {
				heapNodeList[p]->child[2] = 2 * p + 1 < size ? heapNodeList[2 * p + 1] : nullNode;
				heapNodeList[p]->child[3] = 2 * p + 2 < size ? heapNodeList[2 * p + 2] : nullNode;
			} heapTop[i] = createHeap(heapTop[i], heapNodeList.front());
		}
	} //Walk on DAG
	typedef pair<long long, HeapNode*> DAGQueueItem;
	priority_queue<DAGQueueItem, vector<DAGQueueItem>, greater<DAGQueueItem> > aq;
	if (dist[s] == -1) printf("NO\n");
	else { printf("%d\n", dist[s]);
		if (heapTop[s] != nullNode) aq.push(make_pair(dist[s] + heapTop[s]->edge->weight, heapTop[s]));
	} k--; while (k--) {
		if (aq.empty()) { printf("NO\n"); continue; }
		long long d = aq.top().first; HeapNode* curNode = aq.top().second; aq.pop();
		printf("%I64d\n", d);
		if (heapTop[curNode->edge->to] != nullNode)
			aq.push(make_pair(d + heapTop[curNode->edge->to]->edge->weight, heapTop[curNode->edge->to]));
		for (int i = 0; i < 4; i++) if (curNode->child[i] != nullNode)
			aq.push(make_pair(d - curNode->edge->weight + curNode->child[i]->edge->weight, curNode->child[i]));
	} return 0;
}