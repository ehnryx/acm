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
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Dinic {
  int vertices;
  int edges;
  // indices
  vector<map<int,int>> edgenum;
  vector<int> first;
  vector<int> nxt;
  vector<int> ep;
  // edges
  int ecnt;
  vector<ll> flo;
  vector<ll> cap;
  // bfs and dfs
  vector<int> dist;
  vector<int> cur;
  // init
  Dinic(int vertices, int edges, bool dup=false) {
    this->vertices = vertices;
    this->edges = edges;
    first.resize(vertices);
    nxt.resize(2*edges);
    ep.resize(2*edges);
    flo.resize(2*edges);
    cap.resize(2*edges);
    dist.resize(vertices);
    cur.resize(vertices);

    ecnt = 0;
    memset(&first[0], -1, vertices*sizeof(first[0]));
    clear_flow();

    if (dup) edgenum.resize(vertices);
  }
  void clear_flow() {
    memset(&flo[0], 0, 2*edges*sizeof(flo[0]));
  }

  // only use one of add_edge or add_edge_dup
  void add_edge(int a, int b, ll c) { 
    nxt[ecnt] = first[ep[ecnt]=a]; first[ep[ecnt]] = ecnt; cap[ecnt] = c; ++ecnt;
    nxt[ecnt] = first[ep[ecnt]=b]; first[ep[ecnt]] = ecnt; cap[ecnt] = 0; ++ecnt; 
  }
  void add_edge_dup(int a, int b, ll c) {
    if (edgenum[a].count(b)) {
      cap[edgenum[a][b]] += c;
    }
    else {
      ep[ecnt] = a;
      edgenum[a].insert(pair<int,int>(b, ecnt));
      nxt[ecnt] = first[a]; first[a] = ecnt; 
      cap[ecnt] = c; ++ecnt;
      ep[ecnt] = b;
      edgenum[b].insert(pair<int,int>(a, ecnt));
      nxt[ecnt] = first[b]; first[b] = ecnt; 
      cap[ecnt] = 0; ++ecnt;
    }
  }

  bool bfs(int s, int t) {
    memset(&dist[0], INF, vertices*sizeof(dist[0]));
    queue<int> nextq;
    nextq.push(s); 
    dist[s] = 0;
    while (!nextq.empty()) {
      int u = nextq.front(); 
      nextq.pop();
      cur[u] = first[u];
      cur[u] = first[u];
      for (int e = first[u]; e != -1; e = nxt[e]) {
        int v = ep[e^1];
        if (dist[v] == INF && flo[e] < cap[e]) {
          nextq.push(v);
          dist[v] = dist[u]+1;
        }
      }
    }
    return dist[t] < INF;
  }
  ll dfs(int u, int t, ll f) {
    if (u == t) {
      return f;
    }
    ll pushed, total;
    total = 0;
    for (int e = cur[u]; e != -1 && total < f; e = cur[u] = nxt[e]) {
      int v = ep[e^1];
      if (dist[v] == dist[u]+1 && flo[e] < cap[e]) {
        pushed = dfs(v, t, min(cap[e]-flo[e], f-total));
        flo[e] += pushed; 
        flo[e^1] -= pushed; 
        total += pushed;
      }
    }
    return total; 
  }

  ll max_flow(int s, int t) {
    ll flow = 0;
    while (bfs(s, t)) {
      flow += dfs(s, t, INFLL);
    }
    return flow;
  }
};

struct Bear {
  int x, y;
  int r;
  int val;
};

int sqr(int x) { return x*x; }

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n, m;
  cin >> n >> m;
  Dinic graph(2552, 2500*50 + 50 + 2500);

  int sum = 0;
  // add edges
  pii berry[n];
  for (int i = 0; i < n; i++) {
    cin >> berry[i].first >> berry[i].second;
    graph.add_edge(50+i+1, 2551, 1);
  }
  Bear bear[m];
  for (int i = 0; i < m; i++) {
    cin >> bear[i].x >> bear[i].y >> bear[i].r >> bear[i].val;
    sum += bear[i].val;
    graph.add_edge(0, i+1, bear[i].val);
    for (int j = 0; j < n; j++)
      if (sqr(berry[j].first-bear[i].x) + sqr(berry[j].second-bear[i].y) <= sqr(bear[i].r))
        graph.add_edge(i+1, 50+j+1, 1);
  }
  int ans = -1;
  for (int i = 0; i < m; i++) {
    graph.clear_flow();
    graph.max_flow(0, i+1);
    int flow = graph.max_flow(0, 2551);
    if (flow == sum - bear[i].val) {
      ans = max(ans, n-flow);
    }
  }
  cout << ans << nl;

  return 0;
}
