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

const int N = 1e4+1;
unordered_multiset<int> adj[N];
int deg[N];

bool dfs(int u, list<int>& ans, int goal = -1) {
  ans.push_back(u);
  if (adj[u].empty()) {
    if (goal == -1) return true;
    else return (goal == u);
  }

  auto cur = prev(ans.end());
  int nxt = *adj[u].begin();
  adj[u].erase(adj[u].begin());
  if (!dfs(nxt, ans, goal)) {
    return false;
  }

  if (!adj[u].empty()) {
    list<int> loop;
    int v = *adj[u].begin();
    adj[u].erase(adj[u].begin());
    if (!dfs(v, loop, u)) {
      return false;
    }
    ans.insert(next(cur), loop.begin(), loop.end());
  }

  return true;
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

  for (int n,m; cin>>n>>m && n; ) {
    for (int i=0; i<n; i++) {
      adj[i].clear();
      deg[i] = 0;
    }
    for (int i=0; i<m; i++) {
      int a, b;
      cin >> a >> b;
      adj[a].insert(b);
      deg[a]++;
      deg[b]--;
    }

    int s = 0;
    for (int i=0; i<n; i++) {
      if (deg[i] == 1) s = i;
    }

    list<int> ans;
    if (!dfs(s, ans) || ans.size() != m+1) {
      cout << "Impossible" << nl;
    } else {
      for (int it : ans) {
        cout << it << " ";
      } cout << nl;
    }
  }

  return 0;
}
