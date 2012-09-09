//Kruskal
//Testado em:
//Live Archive 4296
//UVa 10034	  

#include <algorithm>
#include <string.h>
using namespace std;

#define MAXV 3010
#define MAXE 100010

template <typename T>

struct edge {
	int a,b;
	T w;

	edge(int pa=0, int pb=0, T pw=0) :
		a(pa), b(pb), w(pw) {}
	bool operator<(const edge& e) const {
		return this->w<e.w;
	}
};

int rank[MAXV];
int rep[MAXV];
edge<double> ls[MAXE];
int n,m;

int find(int a) {
	if (a!=rep[a])
		rep[a]=find(rep[a]);
	return rep[a];
}

bool unio(int a, int b) {
	a=find(a), b=find(b);
	if (a==b)	
		return false;

	if (rank[a]>=rank[b]) {
		rep[b]=a;
		if (rank[a]==rank[b]) rank[a]++;
	}
	else rep[a]=b;
	
	return true;
}

double kruskal() {
	memset(rank,0,sizeof(rank));
	sort(ls,ls+m);	

	for (int i=0; i<n; i++)
		rep[i]=i;

	double sum=0;
	for (int i=0; i<m; i++)
		if (unio(ls[i].a, ls[i].b)) 
			sum+=ls[i].w;
	return sum;
}
