#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

#define nl '\n'
const int INF = 0x3f3f3f3f;
const int N = 300;
const int M = N*N;

ll n, mm, a[N], b[N], s[N], c[N][N];

int par[N], first[N], nxt[2*M], ep[2*M], m;
ll flo[2*M], cap[2*M], cost[2*M];

void init() { m=0;memset(first,-1,sizeof first); memset(flo, 0, sizeof flo); }
void add_edge(int a, int b, ll c=1, ll p=0) {
  nxt[m] = first[ep[m] = a], first[ep[m]] = m, cap[m] = c, cost[m] = p, ++m;
  nxt[m] = first[ep[m] = b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m;
}

int L[N], cur[N];
bool bfs(int s, int t) {
  memset(L,INF, sizeof L);
  queue<int> q; q.push(s); L[s] = 0;
  while(!q.empty()) {
    int u=q.front(); q.pop();
    for(int v, e=cur[u] = first[u]; e!= -1;e=nxt[e])
      if(L[v=ep[e^1]] == INF && flo[e] < cap[e])
        q.push(v), L[v] = L[u]+1;
  }
  return L[t] < INF;
}

ll dfs(int u, int t, ll f) {
  if (u==t) return f;
  ll cf, df=0;
  for(int v, e=cur[u];e!=-1 && df < f; cur[u] = e = nxt[e]) {
    if (flo[e] < cap[e] && L[v=ep[e^1]] ==L[u]+1) {
      cf = dfs(v, t, min(cap[e]-flo[e], f-df));
      flo[e]+=cf; flo[e^1]-=cf;df+=cf;
    }
  }
  return df;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  for(int it=1;it<=T;it++) {
    init();
    cin >> n >> mm;
    int S = 2*n+1;
    int T = 2*n+2;
    ll tot = 0;
    for(int i=0;i<n;i++) {
      cin >> a[i] >> b[i] >> s[i];
      ll req = (s[i]+mm-1)/mm;
      add_edge(S, i, req);
      add_edge(i+n, T, req);
      tot+=req;
    }
    for(int i=0;i<n;i++) {
      for(int j=0;j<n;j++) {
        cin >> c[i][j];
      }
    }
    for(int i=0;i<n;i++) {
      for(int j=0;j<n;j++) {
        if (b[i] + c[i][j] < a[j]){
          //cerr << "adding edge " << i << " " << j <<endl;
          add_edge(i, n+j, INF);
        }
      }
    }
    ll flow = 0; while(bfs(S,T)) flow+=dfs(S,T, INF);
    //cerr << "FLOW IS "<< flow << endl;
    ll ans = tot-flow;
    cout << "Case " << it << ": " << ans <<endl;
  }
  return 0;
}
