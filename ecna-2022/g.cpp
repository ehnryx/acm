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
  vector<int> order(n);
  iota(begin(order), end(order), 1);
  while(m--) {
    char _;
    int a, b;
    cin >> _ >> a >> _ >> b;
    int ai = find(begin(order), end(order), a) - begin(order);
    int bi = find(begin(order), end(order), b) - begin(order);
    if(ai > bi) {
      for(int i=bi; i<ai; i++) {
        swap(order[i], order[i+1]);
      }
    }
  }
  for(int i=0; i<n; i++) {
    cout << "T" << order[i] << " ";
  }
  cout << nl;
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
