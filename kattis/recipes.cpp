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


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(1);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T;
  cin >> T;
  for(int tt=1; tt<=T; tt++) {
    int n, s, t;
    cin >> n >> s >> t;
    double one;
    vector<tuple<string, double>> all;
    for(int i=0; i<n; i++) {
      string name;
      cin >> name;
      double w, p;
      cin >> w >> p;
      all.emplace_back(name, p);
      if(p == 100) {
        one = w;
      }
    }
    one = one * t / s;

    cout << "Recipe # " << tt << nl;
    for(auto [name, p] : all) {
      cout << name << " " << one * (p / 100) << nl;
    }
    cout << string(40, '-') << nl;
  }

  return 0;
}
