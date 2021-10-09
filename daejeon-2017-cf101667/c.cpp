#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e5+1;
int degree[N];
int indeg[N];
int res[N];
vector<int> adj[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  vector<pii> edges;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    edges.push_back(pii(a,b));
    degree[a]++;
    degree[b]++;
  }

  for (const pii& e : edges) {
    if (degree[e.first] < degree[e.second]) {
      adj[e.first].push_back(e.second);
      indeg[e.second]++;
    }
    if (degree[e.second] < degree[e.first]) {
      adj[e.second].push_back(e.first);
      indeg[e.first]++;
    }
  }

  queue<int> topo;
  for (int i = 0; i < n; i++) {
    if (indeg[i] == 0) {
      topo.push(i);
      res[i] = 1;
    }
  }

  int ans = 1;
  while (!topo.empty()) {
    int cur = topo.front(); topo.pop();
    for (int x : adj[cur]) {
      res[x] = max(res[x], res[cur]+1);
      ans = max(ans, res[x]);
      indeg[x]--;
      if (indeg[x] == 0) {
        topo.push(x);
      }
    }
  }

  cout << ans << nl;

  return 0;
}
