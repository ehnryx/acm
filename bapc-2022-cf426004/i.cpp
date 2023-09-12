#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector adj(2*n, vector(2*n, 0.L));
  vector vis(2*n, vector(2*n, false));

  unordered_map<string, int> remap;
  for(int i=0, rid=0; i<n; i++) {
    ld a, b;
    string s, t, _;
    cin >> a >> s >> _ >> b >> t;
    if(not remap.count(s)) remap[s] = rid++;
    if(not remap.count(t)) remap[t] = rid++;
    int sid = remap[s];
    int tid = remap[t];
    adj[sid][tid] = log(b) - log(a);
    adj[tid][sid] = log(a) - log(b);
    vis[sid][tid] = true;
    vis[tid][sid] = true;
  }

  for(int k=0; k<2*n; k++) {
    for(int i=0; i<2*n; i++) {
      for(int j=0; j<2*n; j++) {
        if(not vis[i][k] or not vis[k][j]) continue;
        vis[i][j] = true;
        adj[i][j] = adj[i][k] + adj[k][j];
      }
    }
  }

  while(m--) {
    ld v;
    string s, t, _;
    cin >> v >> s >> _ >> t;
    if(not remap.count(s) or not remap.count(t)) {
      cout << "impossible" << nl;
      continue;
    }
    int sid = remap[s];
    int tid = remap[t];
    if(not vis[sid][tid]) {
      cout << "impossible" << nl;
    } else {
      cout << exp(log(v) + adj[sid][tid]) << nl;
    }
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << /*fixed <<*/ setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
