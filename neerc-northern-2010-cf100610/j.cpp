#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
typedef long long ll;
typedef long double ld;
const int INF = 0x3f3f3f3f;
const char nl = '\n';

#define FILE "journey"

struct Edge {
  int a, b, c;
};

const int N = 2e3+1;
ll dist[N]; int in[N]; bool vis[N], done[N];
vector<Edge> adj[N], dag[N];

const int M = 2e5+1;
Edge edges[M];

int get(int g, int a) {
  return 2*a + g;
}

int main() {
  if (fopen(FILE ".in", "r")) {
    freopen(FILE ".in", "r", stdin);
    freopen(FILE ".out", "w", stdout);
  }

  int n, s, t;
  cin >> n >> s >> t;

  for(int g=0; g<2; g++) {
    int m;
    cin >> m;
    for(int i=0; i<m; i++) {
      int a, b, c;
      cin >> a >> b >> c;
      edges[i] = {a,b,c};
    }
    memset(dist, INF, sizeof dist);
    dist[t] = 0;
    for(int i=1; i<n; i++) {
      for(int j=0; j<m; j++) {
        auto [a,b,c] = edges[j];
        dist[a] = min(dist[a], dist[b]+c);
        dist[b] = min(dist[b], dist[a]+c);
      }
    }
    for(int j=0; j<m; j++) {
      auto [a,b,c] = edges[j];
      if(dist[b] > dist[a]) swap(a,b);
      if(dist[a] > dist[b]) {
        a = get(g, a);
        b = get(g^1, b);
        adj[a].push_back({a,b,c});
      }
    }
  }

  queue<int> bfs;
  bfs.push(get(0, s));
  vis[get(0, s)] = true;
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    for(auto [a,b,c] : adj[u]) {
      dag[u].push_back({a,b,c});
      in[b]++;
      if(!vis[b]) {
        vis[b] = true;
        bfs.push(b);
      }
    }
  }

  if(in[get(0, s)] > 0) {
    cout << -1 << nl;
    return 0;
  }

  memset(dist, -1, sizeof dist);
  bfs.push(get(0, s));
  dist[get(0, s)] = 0;
  assert(in[get(0, s)] == 0);
  while(!bfs.empty()) {
    int u = bfs.front();
    done[u] = true;
    bfs.pop();
    for(auto [a,b,c] : dag[u]) {
      dist[b] = max(dist[b], dist[a] + c);
      in[b]--;
      if(in[b] == 0) {
        bfs.push(b);
      }
    }
  }

  for(int i=2; i<=2*n+1; i++) {
    if(vis[i] && !done[i]) {
      cout << -1 << nl;
      return 0;
    }
  }
  ll ans = max(dist[get(0, t)], dist[get(1, t)]);
  assert(ans > 0);
  cout << ans << nl;

  return 0;
}
