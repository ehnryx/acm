#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

namespace ubc {
ll egcd(ll a, ll b, ll& x, ll &y) { if (!b) {x=1; y=0; return a;}
  // to ensure d>=0: x=sgn(a);y=0;return abs(a);       ^^^^^^^^
  ll d = egcd(b, a%b, y, x); y -= x * (a/b); return d; }

// Assuming a != 0, find smallest y >= 0 such that ax+by=c (if possible)
bool canon_egcd(ll a, ll b, ll c, ll& x, ll& y) {
  ll d = egcd(a, b, x, y), z = abs(a/d); if (c%d) return false;
  y = (y*(c/d)%z + z)%z, x = (c - b*y)/a; return true; }

bool chin_rem(ll a1, ll m1, ll a2, ll m2, ll& A, ll& M) {
  ll X1, X2, d = egcd(m1, m2, X1, X2); if (a1 % d != a2 % d) return 0;
  M = m1/d*m2, A = ((X1*(a2/d)%m2*m1 + X2*(a1/d)%m1*m2 + a1%d)%M + M)%M;
  return 1; }
}

constexpr int SMALL = 15;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    int m = n;
    //cerr << "SOLVE " << n << endl;

    vector<int> pps;
    for(int d=2; d*d<=n; d++) {
      if(n % d) continue;
      pps.push_back(1);
      while(n % d == 0) {
        n /= d;
        pps.back() *= d;
      }
    }
    pps.push_back(n);

    vector<ll> ans;
    ans.push_back(m);

    if(size(pps) < SMALL) {
      n = size(pps);
      for(int bm=0; bm<1<<n; bm++) {
        ll k = 0;
        ll mod = 1;
        for(int i=0; i<n; i++) {
          bool ok = ubc::chin_rem(k, mod, bm >> i & 1, pps[i], k, mod);
          assert(ok);
        }
        assert(mod == m);
        if((k - (ll)k*k) % m == 0) {
          ll x = (ll)k*(m-1) + 1;
          if(1 < x && x < (ll)m*(m-1)) {
            ans.push_back(x);
          }
        }
      }
    }

    else {
      int pp = *max_element(begin(pps), end(pps));
      //cerr << "pp: " << pp << endl;

      for(int i=1; i*pp<=m; i++) {
        if(int k = i*pp; (k - (ll)k*k) % m == 0) {
          ll x = (ll)k*(m-1) + 1;
          if(1 < x && x < (ll)m*(m-1)) {
            ans.push_back(x);
          }
        }
        if(int k = i*pp + 1; (k - (ll)k*k) % m == 0) {
          ll x = (ll)k*(m-1) + 1;
          if(1 < x && x < (ll)m*(m-1)) {
            ans.push_back(x);
          }
        }
      }
    }

    sort(begin(ans), end(ans));
    ans.resize(unique(begin(ans), end(ans)) - begin(ans));
    for(ll x : ans) {
      cout << x << " ";
    }
    cout << nl;
  }

  return 0;
}
