//Dinic
//Testado em:
//FASTFLOW SPOJ
//

#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;

const int MAXV = 5010;
const int MAXE = 60010;

typedef long long flow_t;

const int inf = 0x3f3f3f3f;
const flow_t flowinf = 30000LL*100000000000LL;

struct graph {
	int dest[MAXE];
	flow_t cap[MAXE], flow[MAXE];
	int N,M, s, t;
	int tempAdj[MAXE];
	int *adj[MAXV+1];

	graph(): M(0) {}

	void addEdge(int a, int b, flow_t c, bool dir) {
		dest[M] = b; flow[M] = 0; cap[M] = c; M++;
		dest[M] = a; flow[M] = 0; cap[M] = dir?0:c; M++;
	}

	void commit() {
		vector<int> temp(M); // First temp will have the degree
		for (int j = 0; j < M; ++j) ++temp[dest[j]];
		adj[0] = tempAdj;
		for (int i = 0; i < N; ++i) adj[i+1] = adj[i] + temp[i];
		// Now temp gets the "next to input" index
		for (int i = 1; i < N; ++i) temp[i] += temp[i-1];
		// Finally, fill the tempAdj structure
		for (int j = 0; j < M; ++j) tempAdj[--temp[dest[j^1]]] = j;
	}
	// Dinic specific:
	int *currEdge[MAXV];
	int d[MAXV];
	bool bfs() {
		fill_n(d, N, inf);
		copy(adj, adj+N, currEdge);
		
		d[s] = 0;
		queue<int> Q; Q.push(s);

		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			for (int *i = adj[u]; i != adj[u+1]; ++i)
				if (cap[*i]-flow[*i] > 0 && d[dest[*i]] == inf) {
					int v = dest[*i];
					d[v] = d[u]+1;
					Q.push(v);
				}
		}
		return d[t] != inf;
	}

	flow_t dfs(int u, flow_t f) {
		if (u == t) return f;
		for (int*& i = currEdge[u]; i != adj[u+1]; ++i) {
			if (d[dest[*i]] != d[u]+1 || cap[*i] == flow[*i]) continue;

			flow_t tmpF = dfs(dest[*i], min(f, cap[*i] - flow[*i]));

			if (tmpF) {
				flow[*i] += tmpF;
				flow[*i ^ 1] -= tmpF;
				return tmpF;
			}
		}
		return flow_t(0);
	}

	flow_t dinic() {
		flow_t maxFlow = 0;
		while (bfs()) {
			flow_t flow = 0;
			while ((flow=dfs(s,flowinf))) maxFlow += flow;
		}
		return maxFlow;
	}
};

