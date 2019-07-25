#include<bits/stdc++.h>
using namespace std;

const int N = 10005, E = 200010, inf = 0x7fffffff;
struct Edge {
	int v, nxt, w;
}edge[E];
int head[N], k = 1;
int n, m, s, t, max_flow;
int d[N];

void addedge(int u, int v, int w)
{
	edge[++k].v = v;
	edge[k].w = w;
	edge[k].nxt = head[u];
	head[u] = k;
}

bool bfs() {
	memset(d, 0, sizeof(d));
	queue<int>q;
	q.push(s);
	d[s] = 1;
	while(q.size()) {
		int u = q.front(); q.pop();
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].v, w = edge[i].w;
			if(d[v] || !w) continue;
			q.push(v);
			d[v] = d[u] + 1;
			if(v == t) return 1;
		}
	}
	return 0;
}

int dfs(int u, int flow)
{
	if(u == t) return flow;
	int rest = flow;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].v, w = edge[i].w;
		if(d[v] != d[u] + 1 || !w) continue;
		int k = dfs(v, min(rest, w));
		if(!k) d[v] = 0;
		else {
			edge[i].w -= k;
			edge[i ^ 1].w += k;
			rest -= k;
		}
	}
	return flow - rest;
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for(int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		addedge(u, v, w);
		addedge(v, u, 0);
	}
	int now = 0;
	while(bfs()) 
		while(now = dfs(s, inf))
			max_flow += now;
	printf("%d", max_flow);
}
