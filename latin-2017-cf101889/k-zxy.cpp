#include <bits/stdc++.h>

using namespace std;

const int inf=1e9;

int n,m,cnt,S,T,SS,TT,N;
char str[25][25];
int din[25][25],dout[25][25],mp[25][25];
int dotx[20],doty[20],toT[20];
int dx[5],dy[5];
int g[810],vh[810],dis[810],di[810],his[810],pre[810];

struct edge{
  int t,c,next;
}e[10000];

inline void add_edge(int x,int y,int z)
{
  e[++cnt].t=y;
  e[cnt].c=z;
  e[cnt].next=g[x];
  g[x]=cnt;

  e[++cnt].t=x;
  e[cnt].c=0;
  e[cnt].next=g[y];
  g[y]=cnt;
}

inline int isap()
{
  memset(vh,0,sizeof(vh));
  memset(dis,0,sizeof(dis));
  vh[0]=TT;
  for(int i=1;i<=TT;i++)di[i]=g[i];
  int flow=0,aug=inf,X=SS;
  while(dis[SS]<TT)
  {
    bool flag=false;
    his[X]=aug;

    for(int i=g[X];i;i=e[i].next)
      if(e[i].c&&dis[e[i].t]+1==dis[X])
      {
        aug=min(aug,e[i].c);
        flag=true;
        di[X]=i;
        pre[e[i].t]=i^1;
        X=e[i].t;

        if(X==TT)
        {
          flow+=aug;
          while(X!=SS)
          {
            e[pre[X]].c+=aug;
            e[pre[X]^1].c-=aug;
            X=e[pre[X]].t;
          }
          aug=inf;
        }
        break;
      }
    if(flag)continue;

    vh[dis[X]]--;
    if(vh[dis[X]]==0)break;

    int mi=TT,mii;
    for(int i=g[X];i;i=e[i].next)
      if(e[i].c&&dis[e[i].t]<mi)
      {
        mi=dis[e[i].t];
        mii=i;
      }

    dis[X]=mi+1;
    vh[dis[X]]++;
    di[X]=mii;

    if(X!=SS)
    {
      X=e[pre[X]].t;
      aug=his[X];
    }
  }
  return flow;
}

int main(){
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++){
    scanf("%s",str[i]+1);
    for(int j=1;j<=m;j++){
      if(str[i][j]=='o'){
        dotx[++N]=i;doty[N]=j;
      }
      din[i][j]=(i-1)*m+j;
      dout[i][j]=din[i][j]+n*m;
    }
  }

  if(N&1){
    printf("N\n");
    return 0;
  }

  S=2*n*m+1;T=S+1;SS=T+1;TT=SS+1;

  for(int i=N/2+1;i<=N;i++){
    toT[i]=1;
  }

  dx[0]=1;dy[0]=0;
  dx[1]=0;dy[1]=1;
  dx[2]=-1;dy[2]=0;
  dx[3]=0;dy[3]=-1;

  bool flag=false;

  do{
    cnt=1;
    memset(g,0,sizeof(g));
    add_edge(T,S,inf);
    for(int i=1;i<=N;i++){
      mp[dotx[i]][doty[i]]=toT[i];
    }

    for(int i=1;i<=n;i++)
      for(int j=1;j<=m;j++){
        add_edge(SS,dout[i][j],1);
        add_edge(din[i][j],TT,1);

        if(mp[i][j]==0||str[i][j]=='-')
          for(int k=0;k<4;k++)
            if(str[i+dx[k]][j+dy[k]]=='-'||(str[i+dx[k]][j+dy[k]]=='o'&&mp[i+dx[k]][j+dy[k]]==1))
              add_edge(dout[i][j],din[i+dx[k]][j+dy[k]],1);

        if(str[i][j]=='o'){
          if(mp[i][j]==0)
            add_edge(S,din[i][j],1);
          else
            add_edge(dout[i][j],T,1);
        }
      }

    if(isap()==n*m){
      flag=true;
      break;
    }

    if(N==0)break;
  }while(next_permutation(toT+2,toT+N+1));

  if(flag)
    printf("Y\n");
  else
    printf("N\n");

  return 0;
}
