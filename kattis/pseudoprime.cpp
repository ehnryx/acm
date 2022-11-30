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
  static auto primes = [] {
    static constexpr int M = 1e5 + 1;
    vector<bool> np(M);
    for(int i=2; i*i<M; i++) {
      if(np[i]) continue;
      for(int j=i*i; j<M; j+=i) {
        np[j] = true;
      }
    }
    vector<int> p;
    for(int i=2; i<M; i++) {
      if(not np[i]) {
        p.push_back(i);
      }
    }
    return p;
  }();

  auto is_prime = [primes=as_const(primes)](int n) {
    for(int p : primes) {
      if(p*p > n) return true;
      if(n % p == 0) {
        return false;
      }
    }
    assert(false);
  };

  for(int a, p; cin >> p >> a and p; ) {
    if(is_prime(p)) {
      cout << "no" << nl;
      continue;
    }

    int r = 1;
    for(int n=a, e=p; e; e/=2) {
      if(e & 1) {
        r = ll(r) * n % p;
      }
      n = (ll)n * n % p;
    }
    cout << (r == a ? "yes" : "no") << nl;
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
