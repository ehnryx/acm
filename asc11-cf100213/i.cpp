//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "radio"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld sqr(ld x) { return x*x; }
ld distance(const pair<int,int>& a, const pair<int,int>& b) {
  return sqrt(sqr(a.first-b.first) + sqr(a.second-b.second));
}

const int N = 1200;
vector<int> adj[N];
int ans[N];

bool dfs(int u, int p) {
  if(p == -1 || ans[p] == 1) ans[u] = 2;
  else ans[u] = 1;
  for(int v : adj[u]) {
    if(!ans[v]) {
      if(!dfs(v, u)) {
        return false;
      }
    } else if(ans[v] == ans[u]) {
      return false;
    }
  }
  return true;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<pair<int,int>> v;
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    v.emplace_back(a, b);
  }

  ld l = 0;
  ld r = 5e4;
  while(r-l > 1e-7) {
    ld m = (l + r) / 2;
    for(int i=0; i<n; i++) {
      adj[i].clear();
      ans[i] = 0;
    }

    for(int i=0; i<n; i++) {
      for(int j=0; j<i; j++) {
        if(distance(v[i], v[j]) < m) {
          adj[i].push_back(j);
          adj[j].push_back(i);
        }
      }
    }

    bool ok = true;
    for(int i=0; i<n && ok; i++) {
      if(!ans[i]) {
        ok &= dfs(i, -1);
      }
    }

    if(ok) {
      l = m;
    } else {
      r = m;
    }
  }

  cout << r/2 << nl;

  for(int i=0; i<n; i++) {
    adj[i].clear();
    ans[i] = 0;
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<i; j++) {
      if(distance(v[i], v[j]) < l) {
        adj[i].push_back(j);
        adj[j].push_back(i);
      }
    }
  }
  for(int i=0; i<n; i++) {
    if(!ans[i]) {
      dfs(i, -1);
    }
  }
  for(int i=0; i<n; i++) {
    cout << ans[i] << " ";
  }
  cout << nl;

  return 0;
}
