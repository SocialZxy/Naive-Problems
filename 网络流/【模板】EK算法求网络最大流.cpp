#include<bits/stdc++.h>
using namespace std;

const int MaxN = 1e4 + 5;
const int inf = 0x3f3f3f3f; 
const int MaxM = 2e5 + 5;
int n, m, s, t, ans; 
struct Edge {
	int v, nxt, w;
}edge[MaxM];
int head[MaxN], k = 1;
int vis[MaxN], now[MaxN], pre[MaxN];

void addedge(int u, int v, int w)
{
	edge[++k].v = v;
	edge[k].w = w;
	edge[k].nxt = head[u];
	head[u] = k;
}

bool bfs()
{
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	q.push(s);
	vis[s] = 1;
	now[s] = inf;
	while(q.size()) {
		int u = q.front();
		q.pop();
		//printf("%d ", u);
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].v, w = edge[i].w;
			if(vis[v] || !w) continue;
			now[v] = min(now[u], w);
			pre[v] = i;
			if(v == t) return 1;
			q.push(v);
			vis[v] = 1;
		}
	}
	return 0;
}

void update()
{
	ans += now[t];
	int x = t;
	while(x != s) {
		int i = pre[x];
		edge[i].w -= now[t];
		edge[i ^ 1].w += now[t];
		x = edge[i ^ 1].v;
	}
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
	while(bfs()) update();
	printf("%d", ans);
	return 0;
}
