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
  int n, k;
  cin >> n >> k;
  vector<int> a(n), b(n);
  vector<pair<int, int>> order;
  for(int i=0; i<n; i++) {
    cin >> a[i] >> b[i];
    order.emplace_back(a[i] + b[i], i);
  }

  if(k > a[0] + b[0]) {
    return void(cout << "NO" << nl);
  }

  sort(begin(order) + 1, end(order), greater<>());

  priority_queue<pair<int, int>> usable;
  usable.emplace(b[0], 0);
  int at = 1;
  while(not empty(usable)) {
    int u = usable.top().second;
    usable.pop();
    if(k <= a[u]) {
      return void(cout << "YES" << nl);
    }
    k -= b[u];
    while(at < n and k <= order[at].first) {
      int i = order[at].second;
      usable.emplace(b[i], i);
      at++;
    }
  }

  cout << "NO" << nl;
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
