#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

namespace Flow {
  const int N = 2e3 + 2;
  struct Edge { int v, r, f, c, p; };
  vector<Edge> adj[N]; int sz[N];
  vector<pair<int,int>> memo;
  void add_edge(int a, int b, int c, int p, bool rem=false) {
    if(rem) memo.emplace_back(a, sz[a]);
    adj[a].push_back({b,sz[b]++,0,c, p});
    adj[b].push_back({a,sz[a]++,0,0,-p});
  }

  bool vis[N]; int par[N]; int pot[N], dist[N];
  int mcf(int s, int t, int& price, int n) {
    fill(vis, vis+n, 0); fill(dist, dist+n, INF); dist[s] = 0;
    priority_queue<pair<ll,int>> dk; dk.push({0,s}); while(!dk.empty()) {
      int u=dk.top().second; dk.pop(); if(vis[u]) continue;
      vis[u] = true;
      for(const Edge& e:adj[u]) {
        if(e.f < e.c && dist[e.v] > dist[u] + pot[u] - pot[e.v] + e.p) {
          dist[e.v] = dist[u] + pot[u] - pot[e.v] + e.p; par[e.v] = e.r;
          dk.push({-dist[e.v], e.v});
        }
      }
    }
    /*
    for(int u=s; u!=-1; ) { vis[u]=1; for(const Edge& e:adj[u]) {
      if(e.f < e.c && dist[e.v] > dist[u] + pot[u] - pot[e.v] + e.p) {
        dist[e.v] = dist[u] + pot[u] - pot[e.v] + e.p; par[e.v] = e.r; } }
      u = -1; int best = INF;
      for(int i=0; i<n; i++) if(!vis[i] && dist[i]<best) best = dist[u=i];
    }
    */
    if(dist[t] >= INF) { return 0; } int df = INF;
    for(int u=t; u!=s; ) { const Edge& r = adj[u][par[u]];
      df = min(df, adj[r.v][r.r].c - adj[r.v][r.r].f); u = r.v; }
    for(int u=t; u!=s; ) { Edge& r=adj[u][par[u]], &e = adj[r.v][r.r];
      e.f += df; r.f -= df; price += df*e.p; u = r.v; }
    for(int i=0; i<n; i++) { pot[i] = min(INF, dist[i] + pot[i]); } return df;
  }
  int min_cost_flow(int s, int t, int& price, int n=N) {
    int flow = price = 0;
    while(int df=mcf(s,t,price,n)) { flow += df; } return flow;
  }
}

const int N = 1e2 + 1;
int x[N], y[N];
vector<pii> adj[N];
vector<int> graph[N];

const int M = 2e3 + 7;
vector<pii> dual[M];
int dsu[M];

vector<int> dist[M];
vector<int> pre[M];

int find(int i) {
  if(dsu[i] == -1) return i;
  return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
  i = find(i); j = find(j);
  if(i != j) {
    dsu[i] = j;
  }
}

struct Node {
  int i, d, p;
  bool operator < (const Node& o) const {
    return d > o.d;
  }
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  memset(dsu, -1, sizeof dsu);

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    cin >> x[i] >> y[i];
  }

  int total = 0;
  vector<tuple<int,int,int>> edges;
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
    edges.emplace_back(a, b, c);
    total += c;
  }

  //cerr<<"done input, total = "<<total<<endl;

  int fid = 0;
  map<pii,int> face;
  for(int i=1; i<=n; i++) {
    function<bool(pii,pii)> cmp = [=](const pii& a, const pii& b) {
      int ai = a.first;
      int bi = b.first;
      return atan2(y[ai]-y[i], x[ai]-x[i]) < atan2(y[bi]-y[i], x[bi]-x[i]);
    };
    sort(adj[i].begin(), adj[i].end(), cmp);
    for(int j=0; j<adj[i].size(); j++) {
      face[make_pair(i, j)] = fid++;
    }
  }

  for(int i=1; i<=n; i++) {
    int sz = adj[i].size();
    for(int j=0; j<sz; j++) {
      int id = face[make_pair(i, j)];
      int o = adj[i][j].first;
      int osz = adj[o].size();
      for(int k=0; k<osz; k++) {
        if(adj[o][k].first == i) {
          int oid = face[make_pair(o, (k + osz-1) % osz)];
          link(id, oid);
          break;
        }
      }
    }
  }

  map<pair<int,int>,pair<int,int>> done;
  for(int i=1; i<=n; i++) {
    int sz = adj[i].size();
    for(int j=0; j<sz; j++) {
      pii cur(i, adj[i][j].first), rev(adj[i][j].first, i);
      if(done.count(cur)) continue;
      int before = find(face[make_pair(i, (j + sz-1) % sz)]);
      int after = find(face[make_pair(i, j)]);
      dual[before].emplace_back(after, adj[i][j].second);
      dual[after].emplace_back(before, adj[i][j].second);
      done[cur] = done[rev] = make_pair(before, after);
    }
  }

  const int S = fid;
  const int T = S+1;
  int odd = 0;
  for(int i=0; i<fid; i++) {
    if(dual[i].size() % 2 == 0) continue;
    odd++;
    dist[i].resize(fid, INF);
    pre[i].resize(fid, -1);
    priority_queue<Node> dijk;
    dijk.push({i, 0, -1});
    dist[i][i] = 0;
    while(!dijk.empty()) {
      auto [u, d, p] = dijk.top();
      dijk.pop();
      if(d != dist[i][u]) continue;
      pre[i][u] = p;
      for(auto [v, c] : dual[u]) {
        if(d+c < dist[i][v]) {
          dist[i][v] = d+c;
          dijk.push({v, d+c, u});
        }
      }
    }

    Flow::add_edge(S, i, 1, 0);
    Flow::add_edge(i+fid, T, 1, 0);
    for(int j=0; j<fid; j++) {
      if(i == j || dist[i][j] == INF) continue;
      Flow::add_edge(i, j+fid, 1, dist[i][j], true);
    }
  }

  int match = 0;
  int flow = Flow::min_cost_flow(S, T, match);
  assert(flow == odd);
  assert(match % 2 == 0);
  cout << total - match/2 << nl;
  //cerr<<"done flow"<<endl;

  vector<int> to(fid, -1), mat(fid, -1);
  for(auto [u, e] : Flow::memo) {
    if(Flow::adj[u][e].f <= 0) continue;
    int v = Flow::adj[u][e].v - fid;
    to[u] = v;
  }

  for(int i=0; i<fid; i++) {
    if(to[i] == -1 || mat[i] != -1) continue;
    vector<int> cyc;
    cyc.push_back(i);
    for(int u = to[i]; u != i; u = to[u]) {
      assert(u != -1);
      cyc.push_back(u);
    }
    //cerr<<"cyc.size: "<<cyc.size()<<endl;
    if(cyc.size() % 2) for(;;);
    for(int j=0; j<cyc.size(); j+=2) {
      mat[cyc[j]] = cyc[j+1];
      mat[cyc[j+1]] = cyc[j];
    }
  }

  vector<bool> bad(m);
  for(int u=0; u<fid; u++) {
    if(mat[u] == -1 || mat[u] < u) continue;
    int v = mat[u];
    if(u == v) exit(0);
    // path from u -> v
    while(pre[u][v] != -1) {
      // remove dual edge pre[u][v] -> v
      int s = min(v, pre[u][v]);
      int t = max(v, pre[u][v]);
      for(int i=0; i<m; i++) {
        if(bad[i]) continue;
        auto [a, b, c] = edges[i];
        auto [before, after] = done[make_pair(a, b)];
        if(before > after) swap(before, after);
        if(s == before && t == after && c == dist[u][v]-dist[u][pre[u][v]]) {
          bad[i] = true;
          break;
        }
      }
      v = pre[u][v];
    }
  }

  int rest = 0;
  for(int i=0; i<m; i++) {
    if(bad[i]) continue;
    auto [a, b, c] = edges[i];
    graph[a].push_back(b);
    graph[b].push_back(a);
    rest += c;
  }
  assert(rest == total - match/2);

  vector<int> val(n+1, -1);
  for(int i=1; i<=n; i++) {
    if(val[i] != -1) continue;
    val[i] = 0;
    stack<int> stk;
    stk.push(i);
    while(!stk.empty()) {
      int u = stk.top();
      stk.pop();
      for(int v : graph[u]) {
        if(val[v] != -1) {
          assert(val[v] == (val[u] ^ 1));
          continue;
        }
        val[v] = val[u] ^ 1;
        stk.push(v);
      }
    }
  }

  for(int i=1; i<=n; i++) {
    cout << val[i] << " ";
  }
  cout << nl;

  return 0;
}
