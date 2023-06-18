#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE long long
#define OUTPUT_DATA_TYPE long long
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){register char stack[40];register int i=0;if(x<0){x=-x;putchar('-');}if(x==0){putchar('0');return;}while(x){stack[i++]=x%10;x/=10;}while(i){putchar(stack[--i]+'0');}return;}

struct EDGE{
    int to,next;
    long long w;
    EDGE(){
        next=-1;
        return;
    }
}e[200010<<1];

int tot,path[200010],fir[200010];
long long sum[200010],q[200010],l[200010],dp[200010];

void addEdge(int u,int v,long long w){
    e[tot].to=v;
    e[tot].w=w;
    e[tot].next=fir[u];
    fir[u]=tot;
    ++tot;
    return;
}


struct BST_NODE{
    long long max;
    std::stack<long long> backs;

    BST_NODE(){
        max=0x3f3f3f3f3f3f3f3fll;
    }

    void back(){
        max=backs.top();
        backs.pop();
        return;
    }

    void insert(long long x){
        backs.push(max);
        max=std::min(max,x);
        return;
    }
};

struct BST{
    BST_NODE tree[200010];
    int size;

    inline int lowbit(int x){
        return x&-x;
    }

    void insert(register int pos,long long x){
        pos=size-pos+1;
        while(pos<=size){
            tree[pos].insert(x);
            pos+=lowbit(pos);
        }
        return;
    }

    void backto(register int pos){
        pos=size-pos+1;
        while(pos<=size){
            tree[pos].back();
            pos+=lowbit(pos);
        }
        return;
    }

    int getAns(register int pos,long long x){
        long long ans=0x3f3f3f3f3f3f3f3f;
        pos=size-pos+1;
        while(pos){
            ans=std::min(ans,tree[pos].max);
            pos-=lowbit(pos);
        }
        return ans;
    }
}bit;

void dfs(int u,int p,int i){
    register int j,head;
    path[i]=u;
    head=std::lower_bound(sum+1,sum+i,sum[i]-l[u])-sum;

    if(u==1) dp[u]=0;
    else dp[u]=bit.getAns(head,i);

    bit.insert(i,dp[u]+q[u]);

    dp[u]+=sum[i];

    for(j=fir[u];~j;j=e[j].next){
        if(e[j].to!=p){
            sum[i+1]=sum[i]+e[j].w;
            dfs(e[j].to,u,i+1);
        }
    }

    bit.backto(i);
    return;
}

signed main(){
	#ifndef ONLINE_JUDGE
	freopen("fish.in", "r", stdin);
	freopen("fish.out", "w", stdout);
	#endif

    memset(fir,-1,sizeof(fir));
    register int i,u,v,w;
    int n=read();
    bit.size=n;
    for(i=2;i<=n;++i)
        l[i]=read();

    for(i=2;i<=n;++i)
        q[i]=read();

    for(i=1;i<n;++i){
        u=read();
        v=read();
        w=read();
        addEdge(u,v,w);
        addEdge(v,u,w);
    }

    dfs(1,1,1);

    for(i=1;i<=n;++i){
        print(dp[i]>=0x3f3f3f3f?-1:dp[i]);putchar(' ');
    }

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}