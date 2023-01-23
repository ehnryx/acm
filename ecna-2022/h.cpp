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
  int s, n;
  cin >> s >> n;
  vector<int> all, tp;
  for(int i=0; i<n; i++) {
    int a; char y;
    cin >> a >> y;
    if(y == 'y') {
      tp.push_back(a);
    } else {
      all.push_back(a);
    }
  }

  sort(begin(tp), end(tp), greater<>());
  for(int i=1; i<size(tp); i++) {
    tp[i] = min(tp[i], tp[i-1] - 1);
  }
  all.insert(end(all), begin(tp), end(tp));
  sort(begin(all), end(all));

  for(int i=0; i<size(all); i++) {
    if(i+1 > (ll)all[i] * s) {
      return void(cout << "No" << nl);
    }
  }

  cout << "Yes" << nl;
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
