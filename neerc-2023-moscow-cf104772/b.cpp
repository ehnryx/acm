#define MULTI_TEST
%:include "main.h"
SOLVE() {
  ll n;
  cin >> n;
  int best = 0;
  vector<ll> ans;

  static vector<int> primes = [] {
    vector<int> ps;
    static constexpr int M = 1e6;
    vector<bool> np(M);
    for (int i = 2; i * i < M; i++) {
      if (np[i]) continue;
      for (int j = i * i; j < M; j += i) {
        np[j] = true;
      }
    }
    for (int i = 2; i < M; i++) {
      if (not np[i]) ps.push_back(i);
    }
    return ps;
  }();

  static constexpr int B = 2e4;
  for (int b = 2; b <= B; b++) {
    int cnt = 0;
    for (ll cur = n; cur;) {
      cnt += (cur % b == 0);
      cur /= b;
    }
    if (cnt > best) {
      best = cnt;
      ans.clear();
    }
    if (cnt == best) {
      ans.push_back(b);
    }
  }

  // assume answer is small because i have no ideas left
  if (best == 1) {
    vector<ll> factors;
    for (int p : primes) {
      ll f = n / p;
      if (f > p and f > B and f * p == n) {
        factors.push_back(f);
      }
    }
    ans.insert(end(ans), rbegin(factors), rend(factors));
    if (n > B) ans.push_back(n);
  }

  cout << best << " " << size(ans) << nl;
  for (ll v : ans) {
    cout << v << " ";
  }
  cout << nl;
}
