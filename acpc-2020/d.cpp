//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

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

const int N = 1e5 + 1;
int par[N], pre[N], post[N];
vector<int> adj[N];

int preid = 0, postid = 0;
void build(int u) {
  pre[u] = preid++;
  for(int v : adj[u]) {
    build(v);
  }
  post[u] = postid++;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;
  for(int i=2; i<=n; i++) {
    cin >> par[i];
    adj[par[i]].push_back(i);
  }
  build(1);

  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    if(pre[b] < pre[a] && post[b] > post[a]) {
      cout << "No" << nl;
    } else {
      cout << "Yes" << nl;
    }
  }

  return 0;
}
