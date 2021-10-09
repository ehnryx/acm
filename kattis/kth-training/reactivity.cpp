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

const int N = 1e3+1;
vector<int> adj[N];
int deg[N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;

  int a, b;
  for (int i=0; i<m; i++) {
    cin >> a >> b;
    adj[a].push_back(b);
    deg[b]++;
  }

  queue<int> topo;
  auto push = [&] (int i) {
    if (!topo.empty()) return false;
    topo.push(i);
    return true;
  };

  for (int i=0; i<n; i++) {
    if (deg[i]==0) {
      if (!push(i)) {
        cout << "back to the lab" << nl;
        return 0;
      }
    }
  }

  vector<int> ans;
  while (!topo.empty()) {
    int cur = topo.front();
    topo.pop();
    ans.push_back(cur);
    for (int x : adj[cur]) {
      deg[x]--;
      if (deg[x] == 0) {
        if (!push(x)) {
          cout << "back to the lab" << nl;
          return 0;
        }
      }
    }
  }

  for (int it : ans) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
