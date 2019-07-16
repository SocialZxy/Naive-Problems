#include<bits/stdc++.h>
using namespace std;
const int maxn=10000+5;
const int w=4;
const int base=10000;

struct big
{
	int a[maxn],n;	
	int& operator [](int x){return a[x];} 
	
	void qd0(){while(n>1&&a[n]==0)n--;}//去前导0 
	void append(int x){a[++n]=x;qd0();}//末尾添加x，用于除法 
	
	big(){n=1;memset(a,0,sizeof(a));}//无参构造函数用于big初始化 
	big(char *s)//用字符串s有参构造函数初始化big 
	{
		memset(a,0,sizeof(a));
		n=0;
		int strn=strlen(s);
		reverse(s,s+strn);
		for(int i=0,quan=1;i<strn;quan*=10,i++)
		{
			if(i%w==0){++n,quan=1;}
			a[n]+=(s[i]-'0')*quan;
		}
		qd0();
	}
	void print()//输出 
	{
		printf("%d",a[n]);
		for (int i=n-1;i;i--)
		{
			printf("%04d",a[i]);
		}
	}
};

bool operator <(big &a,big &b) 
{
	if(a.n<b.n) return true;
	if(a.n==b.n)
	{
		for (int i=a.n;i>=1;i--)
		{
			if(a[i]!=b[i]) return a[i]<b[i];
		}
	}
	return false;
}

big operator -(big &a,big &b)//必须保证a>=b 
{
	big c=a;
	for (int i=1;i<=c.n;i++)
	{
		c[i]-=b[i];
		if(c[i]<0){//借位 
			c[i]+=base;
			c[i+1]--;
		}
	}
	c.qd0();
	return c;
}

big operator +(big &a,big &b)
{
	big c;
	c.n=max(a.n,b.n);
	for (int i=1;i<=c.n;i++)
	{
		c[i]+=a[i]+b[i];
		c[i+1]+=c[i]/base;//进位 
		c[i]%=base;//取模 
	}
	if(c[c.n+1])c.n++;//进位 
	return c;
}

big operator *(big &a,big &b)
{
	big c;
	c.n=a.n+b.n;
	for (int i=1;i<=a.n;i++)
		for (int j=1;j<=b.n;j++)
		{
			c[i+j-1]+=a[i]*b[j];
			c[i+j]+=c[i+j-1]/base;//进位 
			c[i+j-1]%=base;//取模 
		}
	c.qd0();
	return c;
}

void div(big &a,big &b,big &d,big &r)//a/b=d,a%d=r
{
	d=big();
	r=big();
	
}

void init()
{
    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
}


void readdata()
{
	big a,b,c;
	char s[maxn];
	scanf("%s",s);
	a=big(s);
	scanf("%s",s);
	b=big(s);
	/*加法
	c=a+b; 
	减法 
	if(a<b){
		putchar('-');c=b-a;
	}
	else c=a-b;
	*/
	c=a*b;
	
	c.print();
}


void work()
{
}

int main()
{
    init();
    readdata();
    work();
    return 0;
}
