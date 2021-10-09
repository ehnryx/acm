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

const int N = 5e5+1;
vector<int> adj[N];
int ans[N];

void init() {
  memset(ans, -1, sizeof ans);
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
  init();

  int n, m, k, a, b;
  cin >> n >> m;

  for (int i=0; i<m; i++) {
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  queue<int> bfs;

  cin >> k;
  for (int i=0; i<k; i++) {
    cin >> a;
    ans[a] = 0;
    bfs.push(a);
  }

  while (!bfs.empty()) {
    int cur = bfs.front();
    bfs.pop();

    for (int x : adj[cur]) {
      if (ans[x] == -1) {
        ans[x] = ans[cur]+1;
        bfs.push(x);
      }
    }
  }

  for (int i=1; i<=n; i++) {
    cout << ans[i] << ' ';
  }
  cout << nl;

  return 0;
}
