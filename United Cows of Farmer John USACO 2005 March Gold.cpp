#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int Maxn=2e5+10;
const int Maxm=5e6+10;
int ls[Maxm],rs[Maxm];
int sum[Maxm],c[Maxn];
int nxt[Maxn],pre[Maxn];
int root[Maxn],a[Maxn];
int n,idcnt;
long long ans;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
inline void push_up(int x)
{
	sum[x]=sum[ls[x]]+sum[rs[x]];
}
void modify(int &x,int y,int l,int r,int pos)
{
	x=++idcnt,sum[x]=sum[y]+1;
	ls[x]=ls[y],rs[x]=rs[y];
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid)modify(ls[x],ls[y],l,mid,pos);
	else modify(rs[x],rs[y],mid+1,r,pos);
	push_up(x);
}
int query(int x,int y,int l,int r,int u,int v)
{
	if(u>v)return 0;
	if(u<=l && r<=v)return sum[x]-sum[y];
	int mid=(l+r)>>1,ret=0;
	if(u<=mid)ret=query(ls[x],ls[y],l,mid,u,v);
	if(mid<v)ret+=query(rs[x],rs[y],mid+1,r,u,v);
	return ret;
}
int main()
{
	n=read();
	for(int i=1;i<=n;++i)
	a[i]=read();
	for(int i=n;i;--i)
	nxt[i]=c[a[i]],c[a[i]]=i;
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;++i)
	pre[i]=c[a[i]],c[a[i]]=i;
	for(int i=1;i<=n;++i)
	{
		modify(root[i],root[i-1],0,n,nxt[i]);
		int tmp=query(root[i-1],root[pre[i]],0,n,i+1,n);
		tmp+=query(root[i-1],root[pre[i]],0,n,0,0);
		ans+=1ll*tmp;
	}
	printf("%lld\n",ans);
	return 0;
}

