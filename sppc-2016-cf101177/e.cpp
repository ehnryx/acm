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

const int N = 2e5+1;
unordered_set<int> adj[N];
unordered_set<int> out[N];
bool complement[N];
int deg[N];
int root[N];
int ans[N];

void init() {
  memset(root, -1, sizeof root);
  memset(ans, -1, sizeof ans);
}

int find(int i) {
  if (root[i] == -1) return i;
  return root[i] = find(root[i]);
}

bool link(int i, int j) {
  if (find(i) == find(j)) return false;
  root[find(i)] = find(j);
  return true;
}

void dfs(int cur, int val = 0) {
  if (ans[cur] != -1) return;

  ans[cur] = val;
  for (int x : adj[cur]) {
    dfs(x, val^1);
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  init();

  int n;
  cin >> n;

  for (int i=1; i<=n; i++) {
    char t;
    int k, a;
    cin >> t >> k;
    if (t == 'C') {
      deg[i] = k;
    } else {
      deg[i] = n-1-k;
      complement[i] = true;
    }
    if (deg[i] == 0) {
      cout << "Impossible" << nl;
      return 0;
    }

    for (int j=0; j<k; j++) {
      cin >> a;
      if (t == 'C') {
        adj[i].insert(a);
        adj[a].insert(i);
        link(i,a);
      } else {
        out[i].insert(a);
      }
    }
  }

  const int cap = sqrt(n);
  for (int i=1; i<=n; i++) {
    if (complement[i]) {
      if (deg[i] <= cap) {
        for (int j=1; j<=n; j++) {
          if (i == j) continue;
          if (!out[i].count(j) && link(i,j)) {
            adj[i].insert(j);
            adj[j].insert(i);
          }
        }
      }
      else {
        for (int j=1; j<=max(420,cap); j++) {
          int a = 1 + rng()%n;
          if (i == a) continue;
          if (!out[i].count(a) && link(i,j)) {
            adj[i].insert(a);
            adj[a].insert(i);
          }
        }
      }
    }
  }

  for (int i=1; i<=n; i++) {
    dfs(i);
  }

  for (int i=1; i<=n; i++) {
    assert(ans[i] != -1);
    cout << (ans[i] ? 'S' : 'V');
  }
  cout << nl;

  return 0;
}
