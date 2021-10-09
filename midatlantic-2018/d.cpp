#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2*40*40 + 2;
const int M = N*6;
namespace Flow {
  int par[N], first[N], nxt[2*M], ep[2*M], m;
  ll flo[2*M], cap[2*M], cost[2*M];
  void init() { m = 0; memset(first,-1,sizeof first); memset(flo,0,sizeof flo); }
  void add_edge(int a, int b, ll c=1, ll p=0) { //a,b - nodes, c, p - cap, price
    nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, cost[m] =  p, ++m;
    nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m; }
  int L[N], cur[N];
  bool bfs(int s, int t) {
    memset(L, INF, sizeof L);
    queue<int> q; q.push(s); L[s] = 0;
    while (!q.empty()) { int u = q.front(); q.pop();
      for (int v, e = cur[u] = first[u]; e != -1; e = nxt[e])
        if (L[v=ep[e^1]] == INF && flo[e] < cap[e])
          q.push(v), L[v] = L[u]+1;
    } return L[t] < INF; }
  ll dfs(int u, int t, ll f) {
    if (u == t) return f;
    ll cf, df = 0;
    for (int v, e = cur[u]; e != -1 && df < f; cur[u] = e = nxt[e])
      if (flo[e] < cap[e] && L[v=ep[e^1]] == L[u]+1) {
        cf = dfs(v, t, min(cap[e]-flo[e], f-df));
        flo[e] += cf; flo[e^1] -= cf; df += cf;
      } return df; }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n,m;
  cin>>n>>m;
  swap(n,m);
  string g[n];
  for(int i=0;i<n;i++) {
    cin>>g[i];
  }

  auto get = [&](int i, int j, int k) {
    return (i*m + j)*2 + k;
  };

  const int s = n*m*2;
  const int t = s+1;
  Flow::init();
  for(int i=0;i<n;i++) {
    for(int j=0;j<m;j++) {
      if(i>0) Flow::add_edge(get(i,j,0), get(i-1,j,1), INF);
      if(j>0) Flow::add_edge(get(i,j,0), get(i,j-1,1), INF);
      if(i+1<n) Flow::add_edge(get(i,j,0), get(i+1,j,1), INF);
      if(j+1<m) Flow::add_edge(get(i,j,0), get(i,j+1,1), INF);
      if(g[i][j]=='A') {
        Flow::add_edge(get(i,j,1), get(i,j,0), INF);
        Flow::add_edge(s, get(i,j,1), INF);
      } else if(g[i][j]=='B') {
        Flow::add_edge(get(i,j,1), get(i,j,0), INF);
        Flow::add_edge(get(i,j,0), t, INF);
      } else {
        Flow::add_edge(get(i,j,1), get(i,j,0), g[i][j]-'0');
      }
    }
  }

  ll ans = 0;
  while(Flow::bfs(s,t)) {
    ans += Flow::dfs(s,t,INF);
  }
  cout<<ans<<nl;

  return 0;
}
