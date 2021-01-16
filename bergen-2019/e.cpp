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
vector<int> adj[N], dag[N];
int in[N];

void solve(int u, int p, int bit=0) {
  for(int v : adj[u]) {
    if(v == p) continue;
    solve(v, u, bit);
    if(bit) {
      dag[u].push_back(v);
      in[v]++;
    } else {
      dag[v].push_back(u);
      in[u]++;
    }
    bit ^= 1;
  }
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

  int n;
  cin >> n;
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  solve(0, -1);

  queue<int> bfs;
  for(int i=0; i<n; i++) {
    if(in[i] == 0) {
      bfs.push(i);
    }
  }
  vector<int> ans;
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    ans.push_back(u);
    for(int v : dag[u]) {
      if(--in[v] == 0) {
        bfs.push(v);
      }
    }
  }

  for(int it : ans) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
