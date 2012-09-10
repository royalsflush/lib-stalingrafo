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

int lastEdge[MAXV];
int currEdge[MAXV];
int d[MAXV];
int n,m;
int s,t;
queue<int> q;

struct edge {
	flow_t c,f;
	int src,dst,prev;
	edge() {}
	edge(flow_t c, int a, int b, int p):c(c), src(a), dst(b), prev(p), f(0) {}
};
edge ls[MAXE];

void newEdge(int a, int b, flow_t cap, bool dir) {
	ls[m++] = edge(cap, a, b, lastEdge[a]);
	lastEdge[a] = m-1;
	ls[m++] = edge(dir?0:cap, b, a, lastEdge[b]);
	lastEdge[b] = m-1;
}

bool bfs() {
	memset(d,0x3f,sizeof(d));
	q.empty();

	for (int i=0; i<n; i++)
		currEdge[i]=lastEdge[i];

	q.push(s);
	d[s]=0;

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int i=lastEdge[u]; i!=-1; i=ls[i].prev) 
			if (ls[i].c-ls[i].f>0 && d[ls[i].dst]==inf) {
				int v=ls[i].dst;
				d[v]=d[u]+1;
				q.push(v);
			}
	}

	return d[t]!=inf;
}

flow_t dfs(int u, flow_t flow) {
	if (u==t) return flow;

	for (int& i=currEdge[u]; i!=-1; i=ls[i].prev) {
		if (d[ls[i].dst]!=d[u]+1 || (ls[i].c-ls[i].f==0))
			continue;

		flow_t tmpF = dfs(ls[i].dst, min(flow,ls[i].c-ls[i].f));

		if (tmpF) {
			ls[i].f+=tmpF;
			ls[i^1].f-=tmpF;
			return tmpF;
		}
	}

	return 0LL;
}

void initGraph(int n) {
	fill_n(lastEdge, n, -1);
	m = 0;
}

flow_t dinic() {
	flow_t maxFlow=0;

	while (bfs()) {
		flow_t flow=0;
		while ((flow=dfs(s,flowinf)))
			maxFlow+=flow;
	}

	return maxFlow;
}
