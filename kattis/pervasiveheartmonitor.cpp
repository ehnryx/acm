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
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  for(string s; getline(cin, s); ) {
    int first = -1, last;
    for(int i=0; i<size(s); i++) {
      if(isalpha(s[i])) {
        if(first == -1) first = i;
        last = i;
      }
    }
    auto name = s.substr(first, last - first + 1);
    istringstream in(s.substr(0, first) + " " + s.substr(last + 1));
    double sum = 0;
    int count = 0;
    for(double x; in >> x; ) {
      sum += x;
      count++;
    }
    cout << sum / count << " " << name << nl;
  }

  return 0;
}
