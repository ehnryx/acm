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
  vector cnt(1, vector<ll>(9));
  cnt[0][8] = 1;
  while(true) {
    vector cur = {
      cnt.back()[0]
        + cnt.back()[1] * 1  // A
        + cnt.back()[2] * 2  // AT
        + cnt.back()[3] * 3  // ATE
        + cnt.back()[4] * 2  // ATEL
        + cnt.back()[5] * 1  // ATELL
        + cnt.back()[6] * 1  // ATELLI
        + cnt.back()[7] * 1  // ATELLIT
        + cnt.back()[8] * 1, // ATELLITE
      cnt.back()[1]
        + cnt.back()[2] * 2  // T
        + cnt.back()[3] * 3  // TE
        + cnt.back()[4] * 2  // TEL
        + cnt.back()[5] * 1  // TELL
        + cnt.back()[6] * 1  // TELLI
        + cnt.back()[7] * 1  // TELLIT
        + cnt.back()[8] * 1, // TELLITE
      cnt.back()[2]
        + cnt.back()[3] * 2  // E
        + cnt.back()[4] * 2  // EL
        + cnt.back()[5] * 1  // ELL
        + cnt.back()[6] * 1  // ELLI
        + cnt.back()[7] * 1  // ELLIT
        + cnt.back()[8] * 1, // ELLITE
      cnt.back()[3]
        + cnt.back()[4] * 2  // L
        + cnt.back()[5] * 1  // LL
        + cnt.back()[6] * 1  // LLI
        + cnt.back()[7] * 1  // LLIT
        + cnt.back()[8] * 1, // LLITE
      cnt.back()[4]
        + cnt.back()[5] * 2  // L
        + cnt.back()[6] * 2  // LI
        + cnt.back()[7] * 2  // LIT
        + cnt.back()[8] * 2, // LITE
      cnt.back()[5]
        + cnt.back()[6] * 1  // I
        + cnt.back()[7] * 1  // IT
        + cnt.back()[8] * 1, // ITE
      cnt.back()[6]
        + cnt.back()[7] * 2  // T
        + cnt.back()[8] * 3, // TE
      cnt.back()[7]
        + cnt.back()[8] * 2, // E
      cnt.back()[8],
    };
    if(cur[0] > 1e18) break;
    cnt.push_back(cur);
  }

  ll n;
  cin >> n;
  string ans;
  for(int i=size(cnt)-1; i>0; i--) {
    auto put = n / cnt[i][0];
    ans += string(put, 'S');
    ans += "ATELLITE";
    n -= put * cnt[i][0];
  }
  cout << ans << nl;
  cerr << "length: " << size(ans) << endl;
  assert(size(ans) <= 5000);
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
