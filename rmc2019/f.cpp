//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 100 + 1;
vector<int> adj[N];
ld a[N], b[N], na[N], nb[N];
bool x[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    cin >> a[i] >> b[i];
    x[i] = (a[i] != -1);
  }
  for(int i=0; i<m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  while(clock() < 1.789*CLOCKS_PER_SEC) {
    for(int i=1; i<=n; i++) {
      if(!x[i]) {
        na[i] = nb[i] = 0;
        for(int j : adj[i]) {
          na[i] += a[j] / adj[i].size();
          nb[i] += b[j] / adj[i].size();
        }
      } else {
        na[i] = a[i];
        nb[i] = b[i];
      }
    }
    swap(na, a);
    swap(nb, b);
  }

  for(int i=1; i<=n; i++) {
    cout << a[i] << " " << b[i] << nl;
  }

  return 0;
}
