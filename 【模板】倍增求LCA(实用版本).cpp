#include<bits/stdc++.h>
using namespace std;

const int MaxN = 500005;
int n, m, s;
struct Edge {
	int v, nxt;
}edge[MaxN << 1];
int head[MaxN], k = 0;
int vis[MaxN];
int f[MaxN][25];
int dep[MaxN];

void addedge(int u, int v)
{
	edge[++k].nxt = head[u];
	edge[k].v = v;
	head[u] = k;
}

void insert(int u, int v)
{
	addedge(u, v);
	addedge(v, u);
}

void dfs(int u, int fa)
{
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].v;
		if(v == fa) continue;
		f[v][0] = u;
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}

int lca(int x, int y)
{
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 20; i >= 0; i--) 
	if(dep[f[x][i]] >= dep[y]) x = f[x][i];
	if(x == y) return x;
	for(int i = 20; i >= 0; i--) {
		if(f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
	}
	return f[x][0];
}

int main()
{
	scanf("%d%d%d", &n, &m, &s);
	for(int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		insert(u, v);
	}
	dep[s] = 1; f[s][0] = 0;
	dfs(s, 0);
	for(int i = 1; i <= 20; i++) {
		for(int j = 1; j <= n; j++) {
			f[j][i] = f[f[j][i - 1]][i - 1];
		}
	}
	for(int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		printf("%d\n", lca(x, y));
	}
}
