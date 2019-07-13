#include<bits/stdc++.h>
using namespace std;

struct node {
    int v,u;
    int val;
}n[200001];
int N,M;
int cnt,ans;
int pa[200001];

bool cmp(node a,node b){return a.val<b.val;}
int find(int x) {return x==pa[x]? x:pa[x]=find(pa[x]);}

void kruskal()
{
    for(int i=1;i<=M;i++) pa[i]=i;
    for(int i=1;i<=M;i++) {
        int x=find(n[i].u),y=find(n[i].v);
        if(x!=y) {
            ans+=n[i].val;
            cnt++;
            pa[x]=pa[y];
            if(cnt==N-1) return;
        }
    }
}

int main()
{
    cin>>N>>M;
    for(int i=1;i<=M;i++) cin>>n[i].u>>n[i].v>>n[i].val;
    sort(n+1,n+1+M,cmp);
    kruskal();
    cout<<ans<<endl;
}
