#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/strongly_connected.h"

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
  vector<vector<int>> adj(n);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a-1].push_back(b-1);
  }
  strongly_connected scc(adj);

  if(scc.size() == 1) {
    cout << 0 << nl;
    return;
  }

  vector<int> in(scc.size()), out(scc.size());
  for(int i=0; i<n; i++) {
    for(int j : adj[i]) {
      if(scc[i] != scc[j]) {
        out[scc[i]]++;
        in[scc[j]]++;
      }
    }
  }

  int ins = 0;
  int outs = 0;
  for(int i=0; i<scc.size(); i++) {
    ins += (in[i] == 0);
    outs += (out[i] == 0);
  }
  cout << max(ins, outs) << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
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
