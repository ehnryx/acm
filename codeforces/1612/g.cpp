#include <bits/stdc++.h>
using namespace std;

#include "../../../lca/number/mod_int.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  constexpr int M = 1e6;
  constexpr int O = 1e6;
  vector<int> cnt(2*M+1);
  for(int i=1; i<=n; i++) {
    int v;
    cin >> v;
    if(v % 2) cnt[O] += 1;
    if(v > 1) {
      cnt[O + -v+1] += 1;
      cnt[O +  v-1] += 1;
    }
  }

  for(int i=M; i>0; i--) {
    if(i+2 <= M) {
      cnt[O + i] += cnt[O + i + 2];
      cnt[O - i] += cnt[O - i - 2];
    }
  }

  vector<Int> fact(M+1);
  fact[0] = 1;
  for(int i=1; i<=M; i++) {
    fact[i] = fact[i-1] * i;
  }

  ll have = 0;
  Int ans = 0;
  Int num = 1;
  for(int i=-M; i<=M; i++) {
    if (cnt[O + i] == 0) continue;
    num *= fact[cnt[O + i]];
    Int cur = Int(have) * cnt[O + i] + Int((ll)cnt[O + i] * (cnt[O + i] + 1) / 2);
    ans += cur * i;
    have += cnt[O + i];
  }

  cout << ans << " " << num << nl;

  return 0;
}
