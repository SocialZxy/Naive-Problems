#include<bits/stdc++.h>
using namespace std;

const int MaxN = 2005;
const int MaxM = 2 * MaxN * MaxN;
struct Edge {
	int v, nxt;
}edge[MaxM];
int head[MaxN], k = 0;
int n, m, e;
int f[MaxN];
bool vis[MaxN];
int ans = 0;

void addedge(int u, int v)
{
	edge[++k].v = v;
	edge[k].nxt = head[u];
	head[u] = k;
}

void insert(int u, int v)
{
	addedge(u, v);
	addedge(v, u);
}

bool dfs(int u)
{
	if(vis[u]) return;
	vis[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].v;
		if(!f[v] || dfs(f[v])) {
			f[v] = u;
			return 1;
		}
	}
	return 0;
}

int main()
{
	scanf("%d%d%d", &n, &m, &e);
	for(int i = 1; i <= e; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		if(u > n || v > m) continue;
		insert(u, v + n);
	}
	for(int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		ans += dfs(i);
	}
	printf("%d", ans);
}
