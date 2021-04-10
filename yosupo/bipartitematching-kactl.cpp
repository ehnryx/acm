#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

using ll = long long;
using vi = vector<int>;
#define rep(i,s,e) for(int i=(s); i<(e); i++)
#define sz(a) (int)size(a)

struct Dinic {
  struct Edge {
    int to, rev;
    ll c, oc;
    ll flow() const { return max(oc - c, 0LL); } // if you need flows
  };
  vi lvl, ptr, q;
  vector<vector<Edge>> adj;
  Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
  void add_edge(int a, int b, ll c, ll rcap = 0) {
    adj[a].push_back({b, sz(adj[b]), c, c});
    adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
  }
  ll dfs(int v, int t, ll f) {
    if (v == t || !f) return f;
    for (int& i = ptr[v]; i < sz(adj[v]); i++) {
      Edge& e = adj[v][i];
      if (lvl[e.to] == lvl[v] + 1)
        if (ll p = dfs(e.to, t, min(f, e.c))) {
          e.c -= p, adj[e.to][e.rev].c += p;
          return p;
        }
    }
    return 0;
  }
  ll calc(int s, int t) {
    ll flow = 0; q[0] = s;
    rep(L,0,31) do { // 'int L=30' maybe faster for random data
      lvl = ptr = vi(sz(q));
      int qi = 0, qe = lvl[s] = 1;
      while (qi < qe && !lvl[t]) {
        int v = q[qi++];
        for (Edge e : adj[v])
          if (!lvl[e.to] && e.c >> (30 - L))
            q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
      }
      while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
    } while (lvl[t]);
    return flow;
  }
  bool leftOfMinCut(int a) { return lvl[a] != 0; }
};


int main() {
  cin.tie(0)->sync_with_stdio(0);

  int L, R, M;
  cin >> L >> R >> M;
  Dinic dinic(L+R+2);
  for(int i=0; i<M; i++) {
    int a, b;
    cin >> a >> b;
    dinic.add_edge(a, b + L, 1);
  }
  int source = L + R;
  int sink = source + 1;
  for(int i=0; i<L; i++) {
    dinic.add_edge(source, i, 1);
  }
  for(int i=0; i<R; i++) {
    dinic.add_edge(i + L, sink, 1);
  }

  cout << dinic.calc(source, sink) << nl;
  for(int i=0; i<L; i++) {
    for(const auto& e : dinic.adj[i]) {
      if(e.flow() > 0) {
        cout << i << " " << e.to - L << nl;
      }
    }
  }

  return 0;
}
