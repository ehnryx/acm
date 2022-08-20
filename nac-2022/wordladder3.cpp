#include <bits/stdc++.h>
using namespace std;

//%:include "utility/defines.h"
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

  int n;
  cin >> n;
  vector<string> have;
  have.emplace_back(10, 'a');
  while(size(have) < n) {
    int idx = rng() % 10;
    int to = rng() % 26;
    string nxt = have.back();
    nxt[idx] = to + 'a';
    bool ok = true;
    for(int i=0; i+1<size(have); i++) {
      int diff = 0;
      for(int j=0; j<10; j++) {
        diff += (have[i][j] != nxt[j]);
      }
      if(diff <= 1) {
        ok = false;
        break;
      }
    }
    if(ok) {
      have.push_back(nxt);
    }
  }

  for(const string& s : have) {
    cout << s << nl;
  }

  return 0;
}
