#include<bits/stdc++.h>
using namespace std;

#define lc u<<1,l,mid//右儿子 
#define rc u<<1|1,mid+1,r//左儿子 
#define maxn 100005//最大值 

struct node {
	int l,r;
	long long val;//值 
	long long add,mul;//lazytag
}t[maxn<<2];//四倍内存 
int n,m,p;

inline void push_up(int u)
{
	t[u].val=(t[u<<1].val+t[u<<1|1].val)%p; 
} 

inline void build(int u,int l,int r)
{
	t[u].l=l;
	t[u].r=r;
	t[u].add=0;
	t[u].mul=1;
	if(l==r) {
		cin>>t[u].val;//读入值;
		return; 
	}
	int mid=(l+r)>>1;
	build(lc);
	build(rc);//递归建子树
	push_up(u);
	t[u].val=t[u].val%p;
	return;
}

inline void push_down(int root){
	int l=t[root].l;
	int r=t[root].r;
    int m=(l+r)/2;
    t[root*2].val=(t[root*2].val*t[root].mul+t[root].add*(m-l+1))%p;
    t[root*2+1].val=(t[root*2+1].val*t[root].mul+t[root].add*(r-m))%p;
    t[root*2].mul=(t[root*2].mul*t[root].mul)%p;
    t[root*2+1].mul=(t[root*2+1].mul*t[root].mul)%p;
    t[root*2].add=(t[root*2].add*t[root].mul+t[root].add)%p;
    t[root*2+1].add=(t[root*2+1].add*t[root].mul+t[root].add)%p;
    t[root].mul=1;
    t[root].add=0;
    return ;
}

inline void update_1(int root, int stdl, int stdr, int l, int r, long long k)
{
    if(r<stdl || stdr<l){
        return ;
    }
    if(l<=stdl && stdr<=r){
        t[root].val=(t[root].val*k)%p;
        t[root].mul=(t[root].mul*k)%p;
        t[root].add=(t[root].add*k)%p;
        return ;
    }
    push_down(root);
    int m=(stdl+stdr)>>1;
    update_1(root<<1,stdl,m,l,r,k);
    update_1(root<<1|1,m+1,stdr,l,r,k);
    t[root].val=(t[root<<1].val+t[root<<1|1].val)%p;
    return ;
}

void update_2(int u,int l,int r,int a,int b,long long val)
{
	if(l>=a && r<=b)
	{
		t[u].add=(t[u].add+val)%p;
		t[u].val=(t[u].val+val*(r-l+1))%p;
		return;
	}
	push_down(u);
	int mid=(l+r)>>1;
	if(a<=mid) update_2(lc,a,b,val);
	if(b>mid) update_2(rc,a,b,val);
	t[u].val=t[u<<1].val+t[u<<1|1].val;
}

inline long long query(int u,int l,int r,int a,int b)
{
	if(a==l&&b==r) return t[u].val;
	push_down(u);
	int mid=(l+r)>>1;
	long long ans=0;
	if(b<=mid) ans+=query(lc,a,b);
	else if(a>mid) ans+=query(rc,a,b);
	else ans=ans+query(lc,a,mid)+query(rc,mid+1,b);
	ans=ans%p;
	return ans;
}

int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m>>p;
	build(1,1,n);
	for(register int i=1;i<=m;i++) {
		int opt,l,r,x;
		cin>>opt;
		if(opt==1) {
			cin>>l>>r>>x;
			update_1(1,1,n,l,r,x);
		}
		else if(opt==2) {
			cin>>l>>r>>x;
			update_2(1,1,n,l,r,x);
		}
		else if(opt==3) {
			cin>>l>>r;
			cout<<query(1,1,n,l,r)<<endl;
		}
	}
}
