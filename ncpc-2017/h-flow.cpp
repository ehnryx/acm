#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

using ld = long double;

const int INF = 0x3f3f3f3f;

namespace Flow {
  //using ll = long long;
  using ll = int;
  const int N = 4e5 + 2;
  struct Edge { int v, r; ll f, c/*, p*/; };
  vector<Edge> adj[N]; int sz[N]; //ll mc;
  //vector<Edge> mcf_edges; // for mcf on large graphs with negative costs
  //void init(int n=N) {
    //mc=0; fill(sz,sz+n,0); fill(adj,adj+n,vector<Edge>()); }
  void add_edge(int a, int b, ll c=1/*, ll p=0*/) { //mc = max(mc,c); // scaling
  // mcf_edges.push_back({b,a,0,c,p});
	adj[a].push_back({b,sz[b]++,0,c/*,p*/});
	adj[b].push_back({a,sz[a]++,0,0/*,-p*/}); }
  int L[N], cur[N], Q[N];
  bool bfs(int s, int t, ll lim=1) {
    memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
    int f,b; Q[f=b=0] = s; L[s] = 0;
    while(f<=b && L[t]==INF) { int u = Q[f++];
      for(const Edge& e:adj[u]) if(L[e.v] == INF && e.c-e.f >= lim) {
        Q[++b] = e.v; L[e.v] = L[u]+1; } } return L[t] < INF; }
  ll dfs(int u, int t, ll f) { if (u == t || !f) return f;
    for (int i = cur[u]; i < sz[u]; cur[u] = ++i) { Edge& e = adj[u][i];
      if(e.f<e.c && L[e.v]==L[u]+1) {
        if(ll cf = dfs(e.v, t, min(e.c-e.f, f))) {
          e.f += cf; adj[e.v][e.r].f -= cf; return cf; } } } return 0; }
  ll flow(int s, int t/*, bool scaling=0*/) {ll inf=numeric_limits<ll>::max();
    ll res = 0; /*for(ll lim=(scaling?mc:1); lim; lim/=2)*/ {
      while(bfs(s,t/*,lim*/))while(ll cf=dfs(s,t,inf))res += cf;} return res;}
}

const ld EPS = 1e-13;
const ld PI = acos((ld) -1);

ld sub(ld a, ld b) {
  ld s = a - b;
  if(s < 0) s += 2 * PI;
  return s;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  const int S = n+m;
  const int T = n+m+1;

  vector<ld> ppl;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    ppl.push_back(atan2l(y, x));
  }

  map<ld, int> lines;
  vector<int> cap(m), want(m);
  for(int i=0; i<m; i++) {
    int x, y;
    cin >> x >> y >> cap[i];
    lines[atan2l(y, x)] = i;
  }

  for(int i=0; i<n; i++) {
    auto upper = lines.lower_bound(ppl[i]);
    if(upper == lines.end()) upper = lines.begin();
    auto lower = upper;
    if(lower == lines.begin()) lower = prev(lines.end());
    else lower = prev(lower);

    Flow::add_edge(S, i);
    if(sub(upper->first, ppl[i]) < sub(ppl[i], lower->first) - EPS) {
      want[upper->second]++;
      Flow::add_edge(i, n + upper->second);
    } else if(sub(ppl[i], lower->first) < sub(upper->first, ppl[i]) - EPS) {
      want[lower->second]++;
      Flow::add_edge(i, n + lower->second);
    } else {
      want[upper->second]++;
      want[lower->second]++;
      Flow::add_edge(i, n + upper->second);
      Flow::add_edge(i, n + lower->second);
    }
  }

  for(int i=0; i<m; i++) {
    for(int j=0; j<min(want[i],cap[i]); j++) {
      Flow::add_edge(n + i, T);
    }
  }

  int flow = Flow::flow(S, T);
  cout << flow << nl;
  for(int i=0; i<n; i++) {
    for(const auto& e : Flow::adj[i]) {
      if(e.v >= n && e.f > 0) {
        cout << i << " " << e.v - n << nl;
      }
    }
  }

  return 0;
}
