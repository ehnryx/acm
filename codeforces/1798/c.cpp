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
  static auto primes = []{
    static constexpr int N = 4e4;
    vector is_prime(N, true);
    for(int i=2; i<N; i++) {
      if(not is_prime[i]) continue;
      for(int j=i*i; j<N; j+=i) {
        is_prime[j] = false;
      }
    }
    vector<int> p;
    for(int i=2; i<N; i++) {
      if(is_prime[i]) {
        p.push_back(i);
      }
    }
    return p;
  }();

  auto factor = [&](auto&& self, int n, int i=0) -> vector<int> {
    vector<int> f;
    for(; i < size(primes); i++) {
      int p = primes[i];
      if(p * p > n) break;
      int cnt = 0;
      while(n % p == 0) {
        cnt++;
        n /= p;
      }
      if(cnt) {
        auto subf = self(self, n, i+1);
        f = subf;
        for(int j=1; j<=cnt; j++) {
          for(int& v : subf) {
            v *= p;
          }
          f.insert(end(f), begin(subf), end(subf));
        }
        return f;
      }
    }
    if(n == 1) {
      return { 1 };
    } else {
      return { 1, n };
    }
  };

  int n;
  cin >> n;
  vector<int> a(n), b(n);
  for(int i=0; i<n; i++) {
    cin >> a[i] >> b[i];
  }

  unordered_map<int, int> dp;
  dp[-1] = 0;
  int ans = 0;
  for(int i=0; i<n; i++) {
    unordered_map<int, int> ndp;
    int nxt = n;
    for(int f : factor(factor, a[i])) {
      if(f > 1e5) continue;
      int cost = f * b[i];
      auto it = dp.find(cost);
      if(it == end(dp)) {
        ndp[cost] = ans + 1;
        nxt = min(nxt, ans + 1);
      } else {
        ndp[cost] = it->second;
        nxt = min(nxt, it->second);
      }
    }
    dp = move(ndp);
    ans = nxt;
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
