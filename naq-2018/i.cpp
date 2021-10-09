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
int parent[N], idx[N];
vector<int> adj[N];
set<int> vals[N];

int solve(int cur) {
  idx[cur] = cur;
  int res = 0;
  for (int x : adj[cur]) {
    res += solve(x);
    if (vals[idx[cur]].size() < vals[idx[x]].size()) {
      for (int it : vals[idx[cur]]) {
        vals[idx[x]].insert(it);
      }
      idx[cur] = idx[x];
    } else {
      for (int it : vals[idx[x]]) {
        vals[idx[cur]].insert(it);
      }
      idx[x] = idx[cur];
    }
  }

  if (vals[idx[cur]].count(cur)) {
    res += 1;
    vals[idx[cur]].clear();
  }

  return res;
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

  int n, k, m, a, b;
  cin >> n >> k >> m;

  for (int i=0; i<k; i++) {
    cin >> a >> b;
    adj[a].push_back(b);
    parent[b] = a;
  }

  for (int i=0; i<m; i++) {
    cin >> a >> b;
    vals[b].insert(a);
  }

  int ans = 0;
  for (int i=1; i<=n; i++) {
    if (!parent[i]) {
      ans += solve(i);
    }
  }
  cout << ans << nl;

  return 0;
}
