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
  int n;
  cin >> n;
  vector<int> a(n), d(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  for(int i=0; i<n; i++) {
    cin >> d[i];
    //d[i] -= a[i];
  }

  int K, L;
  cin >> K >> L;

  set<pair<int, int>> unused, used;
  ll sum = 0;
  for(int i=0; i<K; i++) {
    sum += a[n-1 - i];
    unused.emplace(d[n-1 - i], n-1 - i);
  }
  for(int i=0; i<L; i++) {
    auto [dj, j] = *rbegin(unused);
    sum += dj;
    unused.erase(prev(end(unused)));
    used.emplace(dj, j);
  }

  ll ans = sum;
  for(int i=0; i<K; i++) {
    int r = n - K + i;
    sum -= a[r];
    sum += a[i];
    if(used.count(pair(d[r], r))) {
      sum -= d[r];
      used.erase(pair(d[r], r));
      sum += d[i];
      used.emplace(d[i], i);
    } else {
      unused.erase(pair(d[r], r));
      unused.emplace(d[i], i);
    }
    assert(not empty(used));
    assert(size(used) == L);
    assert(size(used) + size(unused) == K);
    while(not empty(unused) and begin(used)->first < rbegin(unused)->first) {
      auto from = *begin(used);
      auto to = *rbegin(unused);
      used.erase(from);
      unused.erase(to);
      used.insert(to);
      unused.insert(from);
      sum -= from.first;
      sum += to.first;
    }
    ans = max(ans, sum);
  }
  cout << ans << nl;
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
