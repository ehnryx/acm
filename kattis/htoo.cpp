#include <bits/stdc++.h>
using namespace std;

//%:include "io/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

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

  map<char, int> cnt;
  while(true) {
    char c = getchar();
    if(!isalnum(c)) break;
    int d = 1;
    char f = getchar();
    ungetc(f, stdin);
    if(isdigit(f)) {
      scanf("%d", &d);
    }
    cnt[c] += d;
  }

  int multiplier;
  scanf("%d\n", &multiplier);

  map<char, int> want;
  while(true) {
    char c = getchar();
    if(!isalnum(c)) break;
    int d = 1;
    char f = getchar();
    ungetc(f, stdin);
    if(isdigit(f)) {
      scanf("%d", &d);
    }
    want[c] += d;
  }

  int ans = numeric_limits<int>::max();
  for(auto [c, v] : want) {
    ans = min(ans, cnt[c] * multiplier / v);
  }
  cout << ans << nl;

  return 0;
}
