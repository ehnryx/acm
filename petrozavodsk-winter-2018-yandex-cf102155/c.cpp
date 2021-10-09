#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e3+2;
const int M = 2*(1e4+N) + 7;

vector<int> adj[N];

namespace Dinic {
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

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;

  For(i,m) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  FOR(i,1,n) {
    //cerr << "Choose " << i << nl;

    unordered_set<int> left;
    unordered_map<int,int> right, rrev;
    for (int j : adj[i]) {
      left.insert(j);
      //cerr << "add to left " << j << nl;
    }

    Dinic::init();
    int lid = 0;
    int rid = left.size();
    for (int it : left) {
      for (int j : adj[it]) {
        if (j != i && !left.count(j)) {
          //cerr << "add_Edge " << it << " -> " << j << nl;
          if (right.count(j)) {
            Dinic::add_edge(lid, right[j]);
          } else {
            rrev[rid] = j;
            Dinic::add_edge(lid, right[j] = rid++);
          }
        }
      }
      lid++;
    }

    if (left.size() + right.size() + 1 != n) {
      continue;
    }

    int s = rid;
    int t = s+1;
    For(it,left.size()) {
      Dinic::add_edge(s, it);
    }
    for (const pii& it : right) {
      Dinic::add_edge(it.second, t);
    }

    int flow = 0;
    while (Dinic::bfs(s, t)) {
      flow += Dinic::dfs(s, t, INF);
    }

    //cerr << "flow: " << flow << nl;

    if (flow == right.size()) {
      cout << "Yes" << nl;
      cout << i << " " << left.size() << nl;
      lid = 0;
      for (int it : left) {
        using namespace Dinic;
        int other = -1;
        for (int e=first[lid]; e!=-1; e=nxt[e]) {
          if (flo[e] > 0) {
            other = rrev[ep[e^1]];
            break;
          }
        }
        cout << it << " " << other << nl;
        lid++;
      }
      return 0;
    }
  }

  cout << "No" << nl;

  return 0;
}
