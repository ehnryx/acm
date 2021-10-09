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

bitset<10000> vis;
vector<int> path;
bool dfs(vector<int> adj[], int s, int t) {
  if (s == t) {
    path.clear();
    path.push_back(s);
    return true;
  }

  if (vis[s]) return false;
  vis[s] = true;

  for (int x : adj[s]) {
    if (dfs(adj, x, t)) {
      path.push_back(s);
      return true;
    }
  }
  return false;
}

void print(vector<int> adj[], int s, int t) {
  vis.reset();
  if (dfs(adj, s, t)) {
    for (int it : path) cout << it << " ";
    cout << nl;
  } else {
    cout << "NO" << nl;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  vector<int> adj[m+1][n+1];

  int a, b;
  for (int c=0; c<m; c++) {
    for (int i=1; i<n; i++) {
      cin >> a >> b;
      adj[c][a].push_back(b);
      adj[c][b].push_back(a);
    }
  }

  for (int i=1; i<=n; i++) {
    for (int j=1; j<i; j++) {
      cout << j << " " << i << ": " << nl;
      for (int c=0; c<m; c++) {
        print(adj[c], j, i);
      }
      cout << nl;
    }
  }

  return 0;
}
