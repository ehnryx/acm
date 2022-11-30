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


#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, p;
  cin >> n >> p;
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  reverse(begin(a), end(a));

  auto have = set(begin(a), end(a));
  int need = -1;
  for(int i=p-1; i>=0; i--) {
    if(not have.contains(i)) {
      need = i;
      break;
    }
  }
  if(need == -1) {
    return void(cout << 0 << nl);
  }

  int ans = 0;
  if(a.front() < need) {
    ans += need - a.front();
    int at = need;
    need = -1;
    for(int i=a.front()-1; i>=0; i--) {
      if(not have.contains(i)) {
        need = i;
        break;
      }
    }
    if(need == -1) {
      return void(cout << ans << nl);
    }
    ans += p-1 - at;
  } else {
    ans += p-1 - a.front();
  }

  // roll
  ans++;
  a.front() = p-1;
  for(int i=0; i<n; i++) {
    if(++a[i] < p) {
      break;
    }
    a[i] = 0;
    if(i+1 == n) {
      a.resize(n+1, 1);
    }
  }
  have.insert(begin(a), end(a));

  while(have.contains(need)) {
    need--;
  }
  if(need == -1) {
    cout << ans << nl;
  } else {
    cout << ans + need << nl;
  }
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
