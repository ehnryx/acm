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

const int N = 1e4 + 1;
vector<int> adj[N];
pair<int,int> ans[N];

void solve(int u, int p, int& id) {
  ans[u].first = ans[p].second;
  ans[u].second = id++;
  int children = 0;
  for(int v : adj[u]) {
    if(v == p) continue;
    solve(v, u, id);
    children++;
  }
  if(children == 0) {
    ans[u].second = ans[p].first;
  }
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  int id = 3;
  ans[0] = make_pair(1, 2);
  for(int i=1; i<=n; i++) {
    if(adj[i].size() == 1) {
      solve(i, 0, id);
      break;
    }
  }

  for(int i=1; i<=n; i++) {
    cout << ans[i].first << " " << ans[i].second << nl;
  }

  return 0;
}
