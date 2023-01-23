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
  int n;
  cin >> n;
  vector<int> to(2*n, -1);
  unordered_map<string, int> remap;
  for(int i=0, rid=0; i<n; i++) {
    string s, a, b;
    cin >> s >> a >> b;
    if(not remap.count(a)) remap[a] = rid++;
    if(not remap.count(b)) remap[b] = rid++;
    to[remap[a]] = remap[b];
  }

  int ans = 0;
  vector<bool> vis(n);
  for(int i=0; i<n; i++) {
    if(vis[i]) continue;
    int u = i;
    int len = 0;
    while(not vis[u] and u != -1) {
      vis[u] = true;
      len++;
      u = to[u];
    }
    if(u != -1) {
      ans = max(ans, len);
    }
  }
  if(ans) {
    cout << ans << nl;
  } else {
    cout << "No trades possible" << nl;
  }
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
