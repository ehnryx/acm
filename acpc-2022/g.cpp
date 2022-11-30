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

string get_path(int n, ll v) {
  const ll mod = 1ll << n;
  string path;
  while(v) {
    ll p = v * 2 % mod;
    if(v * 2 == p) {
      path.push_back('L');
    } else {
      path.push_back('R');
    }
    v = p;
  }
  reverse(begin(path), end(path));
  return path;
}

int get_dist(const string& a, const string& b) {
  for(int i=0; i<min(size(a), size(b)); i++) {
    if(a[i] != b[i]) {
      return size(a) + size(b) - 2*i;
    }
  }
  return size(a) + size(b) - 2*min(size(a), size(b));
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<string> path;
  int ans = 0;
  for(int i=0; i<m; i++) {
    ll v;
    cin >> v;
    path.push_back(get_path(n, v));
    if(i) {
      ans += get_dist(path[i], path[i-1]);
    }
  }
  cout << ans << nl;
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
