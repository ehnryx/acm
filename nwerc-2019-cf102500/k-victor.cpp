#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using pll = pair<ll,ll>;
const char nl = '\n';

const int N = 550*6;
ll s, d, t, n;
vector<ll> l, r;
set<ll> node;
ll pos[N]; //position of node
int total = 0; //# nodes
vector<pll> adj[N];

bool island_between(ll xpos, ll ypos) {
  auto it = lower_bound(l.begin(), l.end(), xpos);
  if (it == l.end()) return false;
  return *it < ypos;
}

bool in_island(ll xpos) {
  auto it = upper_bound(r.begin(), r.end(), xpos);
  if (it == r.end()) return false;
  int idx = it - r.begin();
  bool ans = l[idx] < xpos;
//  cerr << "wrapper " << l[idx] << " " << r[idx] << nl;
//  cerr << x << " bad " << ans << nl;
  return ans;
}

void add_node(int x) {
  if (x < 0 || x > s) return;
  if (in_island(x)) return;
  node.insert(x);
}

void add_edge(ll u, ll v) {
  assert(u < v);
  const ll dist = pos[v] - pos[u];
  ll w = -1;
  if (island_between(pos[u], pos[v])) {
    if (dist <= d) {
      w = t;
    }
  } else {
    w = min(
      min(
        (dist/d)*t + dist % d,
        ((dist-1)/d+1)*t
      ),
      dist
    );
  }
  if (w != -1) {
    //cerr << "add edge " << u << " to " << v << " w=" << w << nl;
    adj[u].emplace_back(v, w);
  }
}

ll dij() {
  priority_queue<pll, vector<pll>, greater<pll>> q;
  //first is dist, second is node
  q.emplace(0, 0);
  ll dist, u;
  vector<bool> seen(N);
  while (q.size()) {
    tie(dist, u) = q.top(); q.pop();
    if (seen[u]) continue;
    seen[u] = true;
    if (pos[u] == s) return dist;
    for (pll e : adj[u]) {
      ll v, w;
      tie(v, w) = e;
      q.emplace(dist + w, v);
    }
  }
  while(1);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> s >> d >> t >> n;
  l.resize(n);
  r.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> l[i] >> r[i];
  }
  add_node(0);
  add_node(s);
  for (int i = 0; i < n; ++i) {
    for (int m = -1; m <= 1; ++m) {
      add_node(l[i] + m*d);
      add_node(r[i] + m*d);
    }
  }
  for (int u : node) {
    pos[total++] = u;
  }
//  cerr << "nodes:";
//  for (int v : node) {
//    cerr << " " << v;
//  }
//  cerr << nl;
  for (int u = 0; u < total; ++u) {
    for (int v = u+1; v < total; ++v) {
      add_edge(u, v);
    }
  }
  ll ans = dij();
  cout << ans << nl;

  return 0;
}

