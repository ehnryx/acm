#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

////////////////////////////////////////////////////////////////////////////////
// Maximum flow
////////////////////////////////////////////////////////////////////////////////
//*!
namespace FLOW {
const int N = 1004;
const int M = 2008;
//*/
// data structures and helper functions common to all flow routines
int par[N], first[N], nxt[2*M], ep[2*M], m;
ll flo[2*M], cap[2*M], cost[2*M];
void init() { m = 0; memset(first,-1,sizeof first); memset(flo,0,sizeof flo); }
void add_edge(int a, int b, ll c=1, ll p=0) { //a,b - nodes, c, p - cap, price
  nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, cost[m] =  p, ++m;
  nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m; }
 
// Max flow without costs, USAGE: 1) init(); 2) add edges, 3) ll flow=0; and 4)
// for (ll del=INF; del; del/=2) while (ll df=mf_update(s, t, del)) flow+=df;
// Then if you want to extract a min cut: for (int e = 0; e < m; ++e)
// if (par[ep[e]] != -1 && par[ep[e^1]] == -1) cut.push_back(e);
// If you want to recover flow paths: get set of edges with flo[e] > 0.
// E^2logC in general, E*flow on integer capacity graphs
ll mf_update(int s, int t, ll del=1) {
  ll df[N]; memset(df, 0, sizeof df); memset(par, -1, sizeof par);
  queue<int> q; q.push(s); par[s] = -2; df[s] = INF;
  while (!q.empty()) { ll cf; int u = q.front(); q.pop();
    for (int v, e = first[u]; e != -1; e = nxt[e])
      if (par[v=ep[e^1]] == -1 && (cf = cap[e]-flo[e]) >= del)
        q.push(v), par[v] = e, df[v] = min(df[u], cf); }
  if (par[t] == -1) return 0;
  for (int e, i = t; i != s; i = ep[e])
    e = par[i], flo[e] += df[t], flo[e^1] -= df[t];
  return df[t]; }
 
// Dinic's fast maximum flow: tested on NAIPC 2015 F but not theoretically
// proven to be floating-point-safe.
// USAGE: 1) init(); 2) add edges
// 3) ll flow=0; while (bfs(S, T)) flow += dfs(S, T, INF);
// V^2E in general, min(V^(2/3),sqrt(E))E on unit caps, sqrt(V)E on bipartite
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
 
// Minimum cost maximum flow, assuming there are no negative cost cycles
// USAGE: 1) init(); 2) add edges, 3) mcf_pot_init(numV) and 4)
// ll price=0,flow=0; while (ll df = mcf_update(s, t, price, numV)) flow += df;
//! for sparse graphs, may help to change Dijkstra from O(N^2) to O(M*lgN)
//! code is provided in comments

int q[N], inq[N];
#define BUBL { \
    t = q[i]; q[i] = q[j]; q[j] = t; \
    t = inq[q[i]]; inq[q[i]] = inq[q[j]]; inq[q[j]] = t; }

bool vis[N]; ll pot[N], dist[N];
void mcf_pot_init(int n) { memset(pot, 0, sizeof pot);
  // if all edge costs >= 0, we can safely return before the Bellman-Ford here
  for (int k = 1; k < n; ++k) for (int e = 0; e < m; ++e)
    if (cap[e]) pot[ep[e^1]] = min(pot[ep[e^1]], pot[ep[e]] + cost[e]); }
ll mcf_update(int s, int t, ll& price, int n) {
  memset(vis, 0, sizeof vis); memset(dist, INF, sizeof dist); dist[s] = 0;
  
  memset(inq, -1, sizeof inq);
  int qs = 0; inq[q[qs++] = s] = 0;
  while (qs) {
    int u = q[0]; inq[u] = -1;
    q[0] = q[--qs];
    if( qs ) inq[q[0]] = 0;
    for( int i = 0, j = 2*i + 1, t; j < qs; i = j, j = 2*i + 1 ) {
      if( j + 1 < qs && dist[q[j + 1]] < dist[q[j]] ) j++;
      if( dist[q[j]] >= dist[q[i]] ) break;
      BUBL; }
    if (vis[u] == 1) continue; vis[u] = 1;
    for (int e = first[u]; e != -1; e = nxt[e]) { int v = ep[e^1];
      if (flo[e] < cap[e] && dist[v] > dist[u] + pot[u] - pot[v] + cost[e]) {
        dist[v] = dist[u] + pot[u] - pot[v] + cost[e], par[v] = e;
        if( inq[v] < 0 ) { inq[q[qs] = v] = qs; qs++; }
          for( int i = inq[v], j = ( i - 1 )/2, t;
            dist[q[i]] < dist[q[j]]; i = j, j = ( i - 1 )/2 )
              BUBL;
      }
    }
  }
  /*
  //! replaces the below section
  for (int u = s; u != -1; ) { vis[u] = true; // do Dijkstra
    for (int e = first[u]; e != -1; e = nxt[e]) { int v = ep[e^1];
      if (flo[e] < cap[e] && dist[v] > dist[u] + pot[u] - pot[v] + cost[e])
        dist[v] = dist[u] + pot[u] - pot[v] + cost[e], par[v] = e; }
    u = -1; ll best = INF;
    for (int i = 0; i < n; ++i) if (!vis[i] && best>dist[i]) best=dist[u=i]; }
  //!*/
  if (dist[t] >= INF) return 0; ll df = INF;
  for (int e, i = t; i != s; i = ep[e])
    e = par[i], df = min(df, cap[e] - flo[e]);
  for (int e, i = t; i != s; i = ep[e])
    e = par[i], flo[e] += df, flo[e^1] -= df, price += df*cost[e];
  for (int i = 0; i < n; ++i) pot[i] = min(INF, dist[i] + pot[i]);
  return df; }
//*!
}

unordered_map<string,vector<string>> tree;
unordered_map<string,double> speed;
unordered_map<string,int> id;

unordered_set<string> leftn;
void build_graph(string curr) {
  for (string child : tree[curr]) {
    if (!leftn.count(curr)) {
      FLOW::add_edge(0, id[child], 1, 0);
      if (curr != "CEO") {
        FLOW::add_edge(id[child], id[curr], 1, 20000-1000*min(speed[curr], speed[child]));
      }
      leftn.insert(child);
    } else {
      FLOW::add_edge(id[child], 1002, 1, 0);
      FLOW::add_edge(id[curr], id[child], 1, 20000-1000*min(speed[curr], speed[child]));
    }
    build_graph(child);
  }
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  FLOW::init();

  string name, sup;
  double spd;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> name >> spd >> sup;
    tree[sup].push_back(name);
    speed[name] = spd;
    id[name] = i+1;
  }
  build_graph("CEO");

  ll numV = 1003;
  int s = 0, t = 1002;
  FLOW::mcf_pot_init(numV);
  ll price=0,flow=0; 
  while (ll df = FLOW::mcf_update(s, t, price, numV)) 
    flow += df;
  cout << flow << " " << setprecision(10) << 20 - (price/1000.0)/flow << endl;

  return 0;
}
