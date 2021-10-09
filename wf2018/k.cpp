#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  int deg[n]; memset(deg, 0, sizeof deg);

  int a, b;
  for (int i = 0; i < m; i++) {
    cin >> a >> b;
    deg[a]++;
    deg[b]++;
  }

  if (n == 2) {
    cout << (deg[0] != 1) + (deg[1] != 1) << nl;
    cout << 2 << " " << 1 << nl;
    cout << 0 << " " << 1 << nl;
    return 0;
  }

  vector<int> leaves;
  vector<pii> vertices;
  for (int i = 0; i < n; i++) {
    if (deg[i] == 1) {
      leaves.push_back(i);
    } else { 
      vertices.push_back(pii(deg[i], i));
    }
  }
  sort(vertices.begin(), vertices.end());

  vector<pii> edges;

  queue<int> internal;
  for (const pii& it : vertices) {
    if (!internal.empty()) {
      edges.push_back(pii(it.second, internal.front()));
      deg[it.second]--;
      if (--deg[internal.front()] == 0) {
        internal.pop();
      }
    }
    internal.push(it.second);
  }

  for (int leaf : leaves) {
    edges.push_back(pii(leaf, internal.front()));
    if (--deg[internal.front()] == 0) {
      internal.pop();
    }
  }

  int res = 0;
  while (!internal.empty()) {
    internal.pop();
    res++;
  }

  cout << res << nl;
  cout << n << " " << n-1 << nl;
  for (const pii& e : edges) {
    cout << e.first << " " << e.second << nl;
  }

  return 0;
}
