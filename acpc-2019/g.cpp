#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e5+1;
int val[N], par[N];
vector<int> adj[N];

int solve(int u, int add) {
  add += val[u];
  int res = (add > 0);
  for (int v:adj[u]) {
    res += solve(v, add);
  }
  add -= val[u];
  return res;
}

int g[N];
int find(int i) {
  if(g[i] == -1) return i;
  return g[i] = find(g[i]);
}
int link(int i, int j) {
  if(find(i) == find(j)) return 0;
  g[find(i)] = find(j);
  return 1;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n,m;
  cin >> n >> m;
  memset(g,-1,sizeof g);
  for (int i=1;i<n;i++) {
    cin >> par[i];
    adj[par[i]].push_back(i);
    if(par[i] < 0 || par[i] >= n) for(;;);
    assert(link(i, par[i]));
  }
  for(int i=0;i<m;i++) {
    int v;
    cin >> v;
    val[v]++;
  }

  int d = solve(0, 0);
  if(d > n-d) {
    cout << "We are NYC." << nl;
  } else if(d < n-d) {
    cout << "We are High Table." << nl;
  } else {
    cout << "I'd say the odds are about even." << nl;
  }

  return 0;
}
