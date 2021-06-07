#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/number/mod_int.h"

constexpr int MOD = 1e9 + 7;
constexpr char nl = '\n';

using ll = long long;
using Int = mod_int<MOD>;

// the modular square root exists iff legendre(a, p) >= 0
namespace modular {
  ll modpow(ll n, ll e, ll m) {
    ll r = 1;
    for(;e;e/=2, n = n*n % m) {
      if(e&1) r = r*n % m;
    }
    return r;
  }

  int legendre(ll a, ll p) {
    return (a%p)?(modpow(a, (p-1)/2, p)==1?1:-1):0; }

  ll sqrt(ll a, ll p) {
    a %= p; if (a < 0) a += p;
    if (a == 0) return 0;
    if (legendre(a, p) != 1) throw invalid_argument("no sqrt");
    if (p % 4 == 3) return modpow(a, (p+1)/4, p);
    // a^(n+3)/8 or 2^(n+3)/8 * 2^(n-1)/4 works if p % 8 == 5
    ll s = p - 1, n = 2;
    int r = 0, m;
    while (s % 2 == 0)
      ++r, s /= 2;
    /// find a non-square mod p
    while (modpow(n, (p - 1) / 2, p) != p - 1) ++n;
    ll x = modpow(a, (s + 1) / 2, p);
    ll b = modpow(a, s, p), g = modpow(n, s, p);
    for (;; r = m) {
      ll t = b;
      for (m = 0; m < r && t != 1; ++m)
        t = t * t % p;
      if (m == 0) return x;
      ll gs = modpow(g, 1LL << (r - m - 1), p);
      g = gs * gs % p;
      x = x * gs % p;
      b = b * g % p;
    }
  }
}

const int K = 1000 + 1;
Int ncr[K][K];

// 1 + r + ... + r^n
Int geometric(Int r, ll n) {
  if (n == 0) return Int(1);
  if (r == 1) return Int(n + 1);
  return (r.pow(n + 1) - 1) / (r - 1);
}

void solve() {
  Int a, b, x, y; ll n; int k;
  cin >> a >> b >> x >> y >> n >> k;

  if (k == 0) {
    cout << Int(n + 1) << nl;
    return;
  }

  if (n == 0) {
    cout << x.pow(k) << nl;
    return;
  }

  if (n == 1) {
    cout << x.pow(k) + y.pow(k) << nl;
    return;
  }

  if (a == 0 && b == 0) {
    cout << x.pow(k) + y.pow(k) << nl;
    return;
  }

  if (b == 0) {
    cout << x.pow(k) + y.pow(k) * geometric(a.pow(k), n - 1) << nl;
    return;
  }

  if (a == 0) {
    ll num_x = n / 2;
    ll num_y = (n - 1) / 2;
    cout << x.pow(k) * geometric(b.pow(k), num_x) + y.pow(k) * geometric(b.pow(k), num_y) << nl;
    return;
  }

  Int s2 = a*a + b*4;
  try {
    Int s = modular::sqrt(s2.v, MOD);
    Int u = (a + s) / 2;
    Int v = (a - s) / 2;
    //assert(u != v);
    Int c = (y - x*v) / (u - v);
    Int d = (x*u - y) / (u - v);
    Int ans = 0;
    for(int j=0; j<=k; j++) {
      ans += ncr[k][j] * c.pow(j) * d.pow(k-j) * geometric(u.pow(j) * v.pow(k-j), n);
    }
    cout << ans << nl;
    return;
  } catch(const invalid_argument& e) {
    //cerr << e.what() << nl;
  }

  Int u_plus_v = a;
  Int u_times_v = -b;
  Int c_plus_d = x;
  Int c_times_d = (x*x - (a*x - y*2).pow(2) / s2) / 4;
  Int cu_plus_dv = y;
  Int vc_plus_ud = c_plus_d * u_plus_v - cu_plus_dv;
  Int cduv = c_times_d * u_times_v;

  vector<Int> ur_plus_vr(k + 1), cr_plus_dr(k + 1), cur_plus_dvr(k + 1), vcr_plus_udr(k + 1);
  ur_plus_vr[0] = cr_plus_dr[0] = cur_plus_dvr[0] = vcr_plus_udr[0] = 2;
  ur_plus_vr[1] = u_plus_v;
  cr_plus_dr[1] = c_plus_d;
  cur_plus_dvr[1] = cu_plus_dv;
  vcr_plus_udr[1] = vc_plus_ud;
  for(int i=2; i<=k; i++) {
    ur_plus_vr[i] = ur_plus_vr[i-1] * u_plus_v - u_times_v * ur_plus_vr[i-2];
    cr_plus_dr[i] = cr_plus_dr[i-1] * c_plus_d - c_times_d * cr_plus_dr[i-2];
    cur_plus_dvr[i] = cur_plus_dvr[i-1] * cu_plus_dv - cduv * cur_plus_dvr[i-2];
    vcr_plus_udr[i] = vcr_plus_udr[i-1] * vc_plus_ud - cduv * vcr_plus_udr[i-2];
  }

  queue<ll> generator;
  generator.push(n+1);
  generator.push(n);
  vector<ll> indices;
  while(!generator.empty()) {
    ll u = generator.front();
    generator.pop();
    if(!indices.empty() && u >= indices.back()) continue;
    indices.push_back(u);
    if(u > 1) {
      generator.push((u+1)/2);
      generator.push(u/2);
    }
  }
  reverse(indices.begin(), indices.end());
  int isz = indices.size();

  Int ans = 0;
  if (k % 2 == 0) {
    int j = k / 2;
    ans = ncr[k][j] * c_times_d.pow(j) * geometric(u_times_v.pow(j), n);
  }

  for(int j=0; 2*j<k; j++) {
    int r = k - 2*j;
    vector<Int> u_v(isz), cu_dv(isz), uv_prod(isz);
    u_v[0] = ur_plus_vr[r];
    cu_dv[0] = cur_plus_dvr[r];
    uv_prod[0] = u_times_v.pow(r);
    for(int i=1, h=0; i<isz; i++) {
      while(indices[h] != indices[i]/2) {
        h++;
      }
      if(2*indices[h] == indices[i]) {
        cu_dv[i] = cu_dv[h] * u_v[h] - uv_prod[h] * cr_plus_dr[r];
        u_v[i] = u_v[h] * u_v[h] - uv_prod[h] * 2;
        uv_prod[i] = uv_prod[h] * uv_prod[h];
      } else {
        assert(indices[h+1] == indices[h] + 1);
        cu_dv[i] = cu_dv[h] * u_v[h+1] - uv_prod[h] * vcr_plus_udr[r];
        u_v[i] = u_v[h] * u_v[h+1] - uv_prod[h] * ur_plus_vr[r];
        uv_prod[i] = uv_prod[h] * uv_prod[h] * uv_prod[0];
      }
    }

    Int bot = u_times_v.pow(k) - u_times_v.pow(j) * ur_plus_vr[r] + 1;
    Int top = cr_plus_dr[r]
      + u_times_v.pow(n*j + k) * cu_dv[isz-2]
      - u_times_v.pow((n+1)*j) * cu_dv[isz-1]
      - u_times_v.pow(j) * vcr_plus_udr[r];
    ans += ncr[k][j] * c_times_d.pow(j) * top / bot;
  }

  cout << ans << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for(int i=0; i<K; i++) {
    ncr[i][0] = ncr[i][i] = 1;
    for(int j=1; j<i; j++) {
      ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
    }
  }

  int T;
  cin >> T;
  while (T--) {
    solve();
  }

  return 0;
}
