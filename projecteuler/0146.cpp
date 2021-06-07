#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';
using ll = long long;

ll mod_mul(ll a, ll b, ll m) {
  return (__int128)a * b % m;
}

ll mod_pow(ll n, ll e, ll m) {
  ll r = 1;
  for (; e; e /= 2, n = n = mod_mul(n, n, m)) {
    if (e & 1) r = mod_mul(r, n, m);
  }
  return r;
}

/**
 * Author: brandonzhang
 * Description: Deterministic Miller-Rabin primality test.
 * For $n < 2 \cdot 10^9$, use \texttt{wit[] = \{2, 7, 61\}}. For $n > 2^{64}$, use random witnesses.
 * Trial division on small primes ($<50$) can lead to $>2\times$ speedup.
 * Status: tested SPOJ PRIC, FACT2, CF100956C
 * Time: 7 times the complexity of $a^b \mod c$.
 */
const ll wit[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
bool is_prime(ll n) { if (n<2) return 0; if (n%2 == 0) return n == 2;
  ll r = __builtin_ctzll(n-1), d = (n-1)>>r;
  for (ll a : wit) { a %= n; if (!a) return 1;
    if (a == 1 || a == n-1) continue;
    ll x = mod_pow(a,d,n), y;
    for (int i = 0; i < r; i++) { y = mod_mul(x,x,n);
      if (y == 1 && x != 1 && x != n-1) return 0; x = y; }
    if (x != 1) return 0; } return 1;
}

bool check(ll s) {
  return (is_prime(s + 1) && is_prime(s + 3) // prime
    && !is_prime(s + 5)
    && is_prime(s + 7) && is_prime(s + 9) // prime
    && !is_prime(s + 11)
    && is_prime(s + 13) // prime
    && !is_prime(s + 15) && !is_prime(s + 17) && !is_prime(s + 19)
    && !is_prime(s + 21) && !is_prime(s + 23) && !is_prime(s + 25)
    && is_prime(s + 27) // prime
  );
}

const int M = 10000;
ll solve(int l, int r) {
  ll ans = 0;
  if (r - l < M) {
    for (int i = l; i <= r; i++) {
      ll n = 2 * i;
      if (check(n * n)) {
        ans += n;
      }
    }
  } else {
    int m = (l + r) / 2;
    auto left = async(launch::async, solve, l, m);
    ans += solve(m + 1, r);
    ans += left.get();
  }
  return ans;
}

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  cout << solve(1, n/2) << nl;
  /*
  ll ans = 0;
  for (int i = 2; i < n; i += 2) {
    ll s = (ll)i*i;
    if (is_prime(s + 1) && is_prime(s + 3) // prime
      && !is_prime(s + 5)
      && is_prime(s + 7) && is_prime(s + 9) // prime
      && !is_prime(s + 11)
      && is_prime(s + 13) // prime
      && !is_prime(s + 15) && !is_prime(s + 17) && !is_prime(s + 19)
      && !is_prime(s + 21) && !is_prime(s + 23) && !is_prime(s + 25)
      && is_prime(s + 27)) { // prime
      ans += i;
    }
  }
  cout << ans << nl;
  */

  return 0;
}
