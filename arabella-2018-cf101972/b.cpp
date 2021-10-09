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
vector<int> adj[N];
int val[N], ans[N], height[N];
int idx[N], cmax[N];
unordered_map<int,int> match[2][N]; // inc,dec

// return linear?
bool solve(int cur, int par) {
  bool linear = true;
  vector<int> child;
  for (int x : adj[cur]) {
    if (x != par) {
      child.push_back(x);
      linear &= solve(x, cur);
    }
  }
  int children = child.size();

  //cerr << "solve " << cur << nl;
  // leaf
  if (children == 0) {
    //cerr << "  leaf" << nl;
    idx[cur] = cur;
    cmax[cur] = match[0][cur][val[cur]] = match[1][cur][val[cur]] = 1;
    height[cur] = 1;
    ans[cur] = 0;
  }
  else if (linear && children == 1) {
    height[cur] = height[child[0]]+1;
    int id = idx[cur] = idx[child[0]];
    cmax[id] = max(cmax[id], ++match[0][id][val[cur]-height[child[0]]]);
    cmax[id] = max(cmax[id], ++match[1][id][val[cur]+height[child[0]]]);
    ans[cur] = height[cur] - cmax[id];
    //cerr << "  line: " << height[cur] << " " << cmax[id] << "  upd " << val[cur]-height[child[0]] << " " << val[cur]+height[child[0]] << nl;
  }
  else if (linear && children == 2) {
    vector<int> a = { idx[child[0]], idx[child[1]] };
    int len = height[child[0]] + height[child[1]] + 1;
    //cerr << "  children: " << a[0] << " " << a[1] << " -> h " << height[child[0]] << " " << height[child[1]] << nl;
    ans[cur] = INF;
    for (int r=0; r<2; r++) {
      for (const pii& it : match[0][a[r]]) {
        int v = it.first + height[child[r]];
        int tot = it.second + match[1][a[r^1]][v+height[child[r^1]]] + (v==val[cur]);
        ans[cur] = min(ans[cur], len-tot);
      }
      for (const pii& it : match[1][a[r]]) {
        int v = it.first - height[child[r]];
        int tot = it.second + match[0][a[r^1]][v-height[child[r^1]]] + (v==val[cur]);
        ans[cur] = min(ans[cur], len-tot);
      }
    }
    linear = false;
  }
  else {
    ans[cur] = -1;
    linear = false;
  }
  return linear;
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

  int T;
  cin >> T;
  while (T--) {
    //cerr << nl << "NEW TEST CASE" << nl << nl;
    int n;
    cin >> n;
    int a, b;
    for (int i=1; i<=n; i++) {
      cin >> val[i];
      adj[i].clear();
      match[0][i].clear();
      match[1][i].clear();
    }
    for (int i=1; i<n; i++) {
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }

    solve(1, 0);
    for (int i=1; i<=n; i++) {
      cout << ans[i] << " ";
    }
    cout << nl;
  }

  return 0;
}
