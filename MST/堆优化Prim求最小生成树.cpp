#include<bits/stdc++.h>
using namespace std;

const int MaxM = 200005 * 2;
const int MaxN = 5005;
struct Edge {
	int v, nxt, w;
}edge[MaxM];
int head[MaxN], k = 0;
int n, m;
int ans = 0, cnt = 0;
int vis[MaxN], dis[MaxN];

void addedge(int u, int v, int w)
{
	edge[++k].w = w;
	edge[k].v = v;
	edge[k].nxt = head[u];
	head[u] = k;
}

void prim()
{
	priority_queue< pair<int, int> >q;
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
	dis[1] = 0;
	q.push(make_pair(0, 1));
	while(q.size()) {
		int u = q.top().second; q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		ans += dis[u];
		cnt++;
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].v;
			int w = edge[i].w;
			if(dis[v] > w && !vis[v]) {
				dis[v] = w;
				q.push(make_pair(-dis[v], v));
			}
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		addedge(u, v, w), addedge(v, u, w);
	}
	prim();
	if(cnt == n) printf("%d", ans);
	else printf("orz");
 } 
