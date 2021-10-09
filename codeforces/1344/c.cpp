//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  vector<int> in(n+1);
  vector<vector<int>> adj(n+1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[b].push_back(a);
    in[a]++;
  }

  queue<int> bfs;
  vector<bool> ans(n+1);
  int res = 0;
  for(int i=1; i<=n; i++) {
    if(in[i] == 0) {
      bfs.push(i);
      ans[i] = true;
      res++;
    }
  }

  int cnt = 0;
  while(!bfs.empty()) {
    cnt++;
    int u = bfs.front();
    bfs.pop();
    for(int v : adj[u]) {
      if(--in[v] == 0) {
        bfs.push(v);
      }
    }
  }

  if(cnt == n) {
    cout << n - res << nl;
    for(int i=1; i<=n; i++) {
      if(ans[i]) cout << 'E';
      else cout << 'A';
    }
    cout << nl;
  } else {
    cout << -1 << nl;
  }

  return 0;
}
