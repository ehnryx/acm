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

const int N = 3e5+1;
vector<int> adj[N];
int parent[N];
int deg[N], cnt[N], vis[N];

bool solve(int u, int p = 0, bool add = false) {
  if (vis[u]) return add;
  vis[u] = true;
  parent[u] = p;
  cnt[u] ^= add;
  if (deg[u]) add ^= 1;

  for (int v : adj[u]) {
    add = solve(v, u, add);
  }
  cnt[u] ^= add;

  return add;
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

  int n, m, k, a, b;
  cin >> n >> m >> k;

  for (int i=0; i<m; i++) {
    cin >> a >> b;
    deg[a] ^= 1;
    deg[b] ^= 1;
  }

  for (int i=0; i<k; i++) {
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  for (int i=1; i<=n; i++) {
    if (solve(i)) {
      cout << "NO" << nl;
      return 0;
    }
  }

  vector<int> ans;
  for (int i=1; i<=n; i++) {
    if (cnt[i]) {
      ans.push_back(i);
    }
  }
  cout << "YES" << nl;
  cout << ans.size() << nl;
  for (int it : ans) {
    cout << it << " " << parent[it] << nl;
  }

  return 0;
}
