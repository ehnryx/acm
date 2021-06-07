#pragma GCC optimize("O3")
//#pragma GCC target("fma,sse4,avx2")
//#pragma GCC target("tune=native")

#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;
constexpr char nl = '\n';

using ll = long long;

// the modular square root exists iff legendre(a, p) >= 0
namespace modular {
  int add(int a, int b) {
    //assert(0 <= a && 0 <= b);
    //assert(a+b < 2*MOD);
    return a + b < MOD ? a + b : a + b - MOD;
  }
  int mul(int a, int b) {
    return (ll)a * b % MOD;
  }
  int modpow(int n, ll e, int m = MOD) {
    //assert(0<=n && n<2*MOD);
    if (e == 0) return 1;
    //if (n % MOD == 0) return 0;
    if (e >= MOD - 1) e %= MOD - 1;
    int r = 1;
    for(;e;e/=2, n = mul(n, n)) {
      if(e&1) r = mul(r, n);
    }
    return r;
  }
  int inverse(int n) {
    //assert(n % MOD);
    return modpow(n, MOD - 2);
  }

  int legendre(ll a, ll p) {
    return (a%p)?(modpow(a, (p-1)/2, p)==1?1:-1):0; }

  ll sqrt(ll a, ll p) {
    a %= p; if (a < 0) a += p;
    if (a == 0) return 0;
    if (legendre(a, p) != 1) return -1; //throw invalid_argument("no sqrt");
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
using namespace modular;

const int K = 1000 + 1;
int ncr[K][K];

// TODO could r be zero?
// 1 + r + ... + r^n
int geometric(int r, ll n) {
  //assert(0 <= r && r < MOD);
  if (n == 0) return 1;
  if (r == 1) return (n + 1) % MOD;
  return mul(modpow(r, n + 1) + MOD - 1, inverse(r + MOD - 1));
}

void solve() {
  static const int inv2 = inverse(2);
  static const int inv4 = mul(inv2, inv2);

  int a, b, x, y; ll n; int k;
  cin >> a >> b >> x >> y >> n >> k;

  if (k == 0) {
    cout << (n + 1) % MOD << nl;
    return;
  }

  if (n == 0) {
    cout << modpow(x, k) << nl;
    return;
  }

  if (n == 1) {
    cout << add(modpow(x, k), modpow(y, k)) << nl;
    return;
  }

  if (a == 0 && b == 0) {
    cout << add(modpow(x, k), modpow(y, k)) << nl;
    return;
  }

  if (b == 0) {
    cout << add(modpow(x, k), mul(modpow(y, k), geometric(modpow(a, k), n - 1))) << nl;
    return;
  }

  if (a == 0) {
    ll num_x = n / 2;
    ll num_y = (n - 1) / 2;
    cout << add(
        mul(modpow(x, k), geometric(modpow(b, k), num_x)),
        mul(modpow(y, k), geometric(modpow(b, k), num_y))) << nl;
    return;
  }

  int s2 = a*a + b*4;
  int s = modular::sqrt(s2, MOD);
  if (s != -1) {
    int u = mul(a + s, inv2);
    int v = mul(a + MOD - s, inv2);
    //assert(u != v);
    int inv_uv = inverse(u + MOD - v);
    int c = mul(y + MOD - mul(x, v), inv_uv);
    int d = mul(mul(x, u) + MOD - y, inv_uv);
    int ans = 0;
    for(int j=0; j<=k; j++) {
      ans = add(ans,
          mul(mul(mul(ncr[k][j], modpow(c, j)), modpow(d, k-j)),
            geometric(mul(modpow(u, j), modpow(v, k-j)), n)));
    }
    cout << ans << nl;
    return;
  }/* catch(const invalid_argument& e) {
    //cerr << e.what() << nl;
  }*/

  int u_plus_v = a;
  int u_times_v = MOD - b;
  int c_plus_d = x;
  //int c_times_d = (x*x - (a*x - y*2).pow(2) / s2) / 4;
  int delta = mul(a, x) - add(y, y);
  int c_times_d = mul(mul(x, x) + MOD - mul(mul(delta, delta), inverse(s2)), inv4);
  int cu_plus_dv = y;
  int vc_plus_ud = add(mul(c_plus_d, u_plus_v), MOD - cu_plus_dv);
  int cduv = mul(c_times_d, u_times_v);

  vector<int> ur_plus_vr(k + 1);
  ur_plus_vr[0] = 2;
  ur_plus_vr[1] = u_plus_v;
  vector<int> cr_plus_dr(k + 1);
  cr_plus_dr[0] = 2;
  cr_plus_dr[1] = c_plus_d;
  vector<int> cur_plus_dvr(k + 1);
  cur_plus_dvr[0] = 2;
  cur_plus_dvr[1] = cu_plus_dv;
  vector<int> vcr_plus_udr(k + 1);
  vcr_plus_udr[0] = 2;
  vcr_plus_udr[1] = vc_plus_ud;
  for(int i=2; i<=k; i++) {
    ur_plus_vr[i] = add(mul(ur_plus_vr[i-1], u_plus_v), MOD - mul(u_times_v, ur_plus_vr[i-2]));
    cr_plus_dr[i] = add(mul(cr_plus_dr[i-1], c_plus_d), MOD - mul(c_times_d, cr_plus_dr[i-2]));
    cur_plus_dvr[i] = add(mul(cur_plus_dvr[i-1], cu_plus_dv), MOD - mul(cduv, cur_plus_dvr[i-2]));
    vcr_plus_udr[i] = add(mul(vcr_plus_udr[i-1], vc_plus_ud), MOD - mul(cduv, vcr_plus_udr[i-2]));
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

  int ans = 0;
  if (k % 2 == 0) {
    int j = k / 2;
    ans = mul(mul(ncr[k][j], modpow(c_times_d, j)), geometric(modpow(u_times_v, j), n));
  }

  for(int j=0; 2*j<k; j++) {
    int r = k - 2*j;
    vector<int> u_v(isz), cu_dv(isz), uv_prod(isz);
    u_v[0] = ur_plus_vr[r];
    cu_dv[0] = cur_plus_dvr[r];
    uv_prod[0] = modpow(u_times_v, r);
    for(int i=1, h=0; i<isz; i++) {
      while(indices[h] != indices[i]/2) {
        h++;
      }
      if(2*indices[h] == indices[i]) {
        cu_dv[i] = add(mul(cu_dv[h], u_v[h]), MOD - mul(uv_prod[h], cr_plus_dr[r]));
        u_v[i] = add(mul(u_v[h], u_v[h]), MOD - add(uv_prod[h], uv_prod[h]));
        uv_prod[i] = mul(uv_prod[h], uv_prod[h]);
      } else {
        //assert(indices[h+1] == indices[h] + 1);
        cu_dv[i] = add(mul(cu_dv[h], u_v[h+1]), MOD - mul(uv_prod[h], vcr_plus_udr[r]));
        u_v[i] = add(mul(u_v[h], u_v[h+1]), MOD - mul(uv_prod[h], ur_plus_vr[r]));
        uv_prod[i] = mul(mul(uv_prod[h], uv_prod[h]), uv_prod[0]);
      }
    }

    int bot = add(modpow(u_times_v, k), MOD - mul(modpow(u_times_v, j), ur_plus_vr[r])) + 1;
    int top = add(add(cr_plus_dr[r], mul(modpow(u_times_v, n*j + k), cu_dv[isz-2])),
        MOD - add(
          mul(modpow(u_times_v, (n+1)*j), cu_dv[isz-1]),
          mul(modpow(u_times_v, j), vcr_plus_udr[r])));
    ans = add(ans,
        mul(mul(mul(ncr[k][j], modpow(c_times_d, j)), top), inverse(bot)));
  }

  cout << ans << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for(int i=0; i<K; i++) {
    ncr[i][0] = ncr[i][i] = 1;
    for(int j=1; j<i; j++) {
      ncr[i][j] = add(ncr[i-1][j], ncr[i-1][j-1]);
    }
  }

  int T;
  cin >> T;
  while (T--) {
    solve();
  }

  return 0;
}
