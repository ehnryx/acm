#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e5+1;
int a[N], b[N];

void solve() {
  int n;
  cin >> n;

  for (int i=1; i<=n; i++) {
    cin >> a[i];
  }

  vector<pii> zero;
  vector<int> cycle;
  for (int i=1; i<=n; i++) {
    cin >> b[i];
    if (b[i] == 0) {
      zero.push_back(pii(a[i],i));
    } else {
      cycle.push_back(i);
    }
  }
  if (cycle.size() == 1) {
    cout << -1 << nl;
    return;
  }

  int m = cycle.size();
  int k = zero.size();
  sort(zero.begin(), zero.end());
  vector<pii> edges;
  for (int i=0; i<m; i++) {
    int v = cycle[i];
    if (b[v] >= m) {
      cout << -1 << nl;
      return;
    }
    for (int j=1; j<=b[v]; j++) {
      edges.push_back(pii(cycle[(i+j)%m], v));
    }
    a[v] -= b[v];
    if (a[v] > k) {
      cout << -1 << nl;
      return;
    }
    for (int j=0; j<a[v]; j++) {
      edges.push_back(pii(zero[j].second, v));
    }
  }

  for (int i=0; i<k; i++) {
    int v = zero[i].second;
    if (a[v] > i) {
      cout << -1 << nl;
      return;
    }
    for (int j=0; j<a[v]; j++) {
      edges.push_back(pii(zero[j].second, v));
    }
  }

  cout << edges.size() << nl;
  for (const pii& it : edges) {
    cout << it.first << " " << it.second << nl;
  }

}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#define FILENAME "topo"
  cerr << "File IO: " << FILENAME << nl;
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
#endif

  int T;
  cin >> T;
  while (T--) {
    solve();
  }

  return 0;
}
