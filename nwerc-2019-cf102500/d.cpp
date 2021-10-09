#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const ll INFLL = 0x3f3f3f3f3f3f3f3f;

const int N = 2e3 + 1;
vector<pair<int,ll>> adj[N];
ll dist[N][N]; // edges, vertex
bool vis[N][N];
bool good[N];

pair<ll,ll> intersect(const pair<ll,ll>& a, const pair<ll,ll>& b) {
  if(a.first == -1 || b.first == -1) return make_pair(0, 1);
  ll top = a.second - b.second;
  ll bot = b.first - a.first;
  ll g = __gcd(top, bot);
  top /= g;
  bot /= g;
  if(bot < 0) {
    top = -top;
    bot = -bot;
  }
  return make_pair(top, bot);
}

bool smaller(const pair<ll,ll>& a, const pair<ll,ll>& b) {
  return (__int128)a.first*b.second < (__int128)a.second*b.first;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n, m;
  cin >> n >> m;
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
  }

  memset(dist, 0x3f, sizeof dist);
  dist[0][1] = 0;
  for(int i=1; i<=n; i++) {
    for(int u=1; u<=n; u++) {
      for(auto [v, c] : adj[u]) {
        dist[i][u] = min(dist[i][u], dist[i-1][v] + c);
      }
    }
  }

  vector<pair<ll,ll>> lines; // y=mx+b -> (m,b)
  lines.emplace_back(-1, -1); // scary
  for(int i=n; i>0; i--) {
    if(dist[i][n] == INFLL) continue;
    pair<ll,ll> cur(i, dist[i][n]);
    while(lines.size() > 1) {
      pair<ll,ll> last = intersect(lines.back(), cur);
      pair<ll,ll> pre = intersect(lines[lines.size()-2], cur);
      if(smaller(last, pre)) {
        lines.pop_back();
      } else {
        break;
      }
    }
    lines.emplace_back(i, dist[i][n]);
  }

  queue<pair<int,int>> bfs;
  for(int i=1; i<lines.size(); i++) {
    bfs.emplace(lines[i].first, n);
    vis[lines[i].first][n] = true;
  }

  int cnt = 0;
  while(!bfs.empty()) {
    auto [i, u] = bfs.front();
    bfs.pop();
    cnt += 1 - good[u];
    good[u] = true;
    if(i == 0) continue;
    for(auto [v, c] : adj[u]) {
      if(!vis[i-1][v] && dist[i-1][v] + c == dist[i][u]) {
        bfs.emplace(i-1, v);
        vis[i-1][v] = true;
      }
    }
  }

  cout << n - cnt << nl;
  for(int i=1; i<=n; i++) {
    if(!good[i]) {
      cout << i << " ";
    }
  }
  cout << nl;

  return 0;
}
