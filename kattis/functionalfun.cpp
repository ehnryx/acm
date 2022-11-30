#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  for(string s,t; s=cin.getline(), t=cin.getline(), !s.empty(); ) {
    set<string> from, to;
    for(istringstream in(s.substr(6)); in>>s; ) {
      from.insert(s);
    }
    for(istringstream in(t.substr(8)); in>>t; ) {
      to.insert(t);
    }

    int n;
    cin >> n;
    bool ok = true;
    bool injective = true;
    for(int i=0; i<n; i++) {
      string x, _, y;
      cin >> x >> _ >> y;
      ok &= from.erase(x);
      injective &= to.erase(y);
    }

    if(!ok) {
      cout << "not a function" << nl;
    } else if(injective && to.empty()) {
      cout << "bijective" << nl;
    } else if(injective) {
      cout << "injective" << nl;
    } else if(to.empty()) {
      cout << "surjective" << nl;
    } else {
      cout << "neither injective nor surjective" << nl;
    }
  }

  return 0;
}
