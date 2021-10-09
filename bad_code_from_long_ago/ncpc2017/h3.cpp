#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
#define USE_MAGIC_IO

#define ll int
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble double
#define nl '\n'
typedef complex<ldouble> pt;
/*
const ll MOD = 1e9+7;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;*/
const int INF = 0x3f3f3f3f;
const double EPS = 1e-9;

////////////////////////////////////////////////////////////////////////////////
// Maximum flow
////////////////////////////////////////////////////////////////////////////////
//*!
namespace FLOW {
const int N = 400002;
const int M = 800001;
//*/
// data structures and helper functions common to all flow routines
int par[N], first[N], nxt[2*M], ep[2*M], m;
ll flo[2*M], cap[2*M], cost[2*M];
void init() { m = 0; memset(first,-1,sizeof first); memset(flo,0,sizeof flo); }
void add_edge(int a, int b, ll c=1, ll p=0) { //a,b - nodes, c, p - cap, price
  nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, cost[m] =  p, ++m;
  nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m; }
 
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
}

// MAGIC IO
#ifdef USE_MAGIC_IO
inline char get(void) {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
inline void read(int &x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
  if (sgn) x = -x;
}
#else
#define get() getchar()
#define read(x) scanf("%d",&x)
#endif
void readchar(char& c) {
  while (isspace(c = get()));
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  FLOW::init();

  int n, m; read(n); read(m);
  vector<pt> people(n);
  for (int i = 0; i < n; i++) {
    int x, y; read(x); read(y);
    people[i] = {x, y};
  }

  set<ldouble> lines;
  unordered_map<ldouble, int> dumb;
  int cap[m];
  for (int i = 0; i < m; i++) {
    int x, y; read(x); read(y); read(cap[i]);
    lines.insert(arg(pt(x, y)));
    dumb[arg(pt(x,y))] = i+1;
    FLOW::add_edge(200000+i+1, 400001, cap[i]);
  }

  for (int i = 0; i < n; i++) {
    ldouble a = arg(people[i]);
    auto it = lines.lower_bound(a);
    auto it2 = it;
    FLOW::add_edge(0, i+1);
    if (it == lines.begin()) {
      it2 = --lines.end();
      if (abs((*it - a) - (a - (*it2 - 2*M_PI))) < EPS)
        FLOW::add_edge(i+1, 200000+dumb[*it]), FLOW::add_edge(i+1, 200000+dumb[*it2]);
      else if ((*it - a) < (a - (*it2 - 2*M_PI)))
        FLOW::add_edge(i+1, 200000+dumb[*it]);
      else FLOW::add_edge(i+1, 200000+dumb[*it2]);
    } else if (it == lines.end()) {
      it = lines.begin(), --it2;
      if (abs((*it - a + 2*M_PI) - (a - (*it2))) < EPS)
        FLOW::add_edge(i+1, 200000+dumb[*it]), FLOW::add_edge(i+1, 200000+dumb[*it2]);
      else if ((*it - a + 2*M_PI) < (a - (*it2)))
        FLOW::add_edge(i+1, 200000+dumb[*it]);
      else FLOW::add_edge(i+1, 200000+dumb[*it2]);
    }
    else {
      --it2;
      if (abs((*it - a) - (a - (*it2))) < EPS)
        FLOW::add_edge(i+1, 200000+dumb[*it]), FLOW::add_edge(i+1, 200000+dumb[*it2]);
      else if ((*it - a) < (a - (*it2)))
        FLOW::add_edge(i+1, 200000+dumb[*it]);
      else FLOW::add_edge(i+1, 200000+dumb[*it2]);
    }
  }

  int S = 0, T = 400001;
  ll flow=0; 
  while (FLOW::bfs(S, T))
    flow += FLOW::dfs(S, T, INF);

  using namespace FLOW;
  cout << flow << nl;
  for (int u = 1; u <= n; u++) {
    for (int e = first[u]; e != -1; e = nxt[e]) {
      int v = ep[e^1];
      if (v && flo[e]) cout << u-1 << " " << v - 200001 << nl;
    }
  }

  return 0;
}
