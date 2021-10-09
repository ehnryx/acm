#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll modpow(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*n % m;
    n = n*n % m;
  }
  return r;
}

template <ll M, ll R, bool dit = 0> void ntt(vector<ll>& a) {
  static vector<ll> w(2, 1); int n = a.size();
  for (static int k = 2; k < n; k *= 2) {
    w.resize(n, 1); ll c = modpow(R, M/2/k * (dit ? M-2 : 1), M);
    for (int i = k+1; i < 2*k; i++) w[i] = w[i-1]*c % M; }
  for (int t = 1; t < n; t *= 2) {
    int k = (dit ? t : n/2/t);
    for (int i = 0; i < n; i += k*2) for (int j = 0; j < k; j++) {
      ll &c = a[i+j], &d = a[i+j+k], e = w[j+k], f = d;
      d = (dit ? c - (f = f*e % M) : (c-f)*e % M); if (d < 0) d += M;
      if ((c += f) >= M) c -= M;
    }
  }
}
template <ll M = (119<<23)+1, ll R = 31>
vector<ll> conv(vector<ll> a, vector<ll> b, int cut = INF) {
  if(a.empty() || b.empty()) return {};
  int len = a.size() + b.size() - 1, n = 1 << (32 - __builtin_clz(len));
  ll inv = modpow(n, M-2, M);
  a.resize(n); b.resize(n); ntt<M,R>(a); ntt<M,R>(b);
  for(int i=0; i<n; i++) a[i] = a[i]*b[i] % M * inv % M;
  ntt<M,R,1>(a); a.resize(min(len, cut)); return a;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  static const int M = 26;
  vector<int> p(M);
  for(int i=0; i<M; i++) {
    cin >> p[i];
    p[i]--;
  }

  string S, T;
  cin >> S >> T;
  int n = S.size();
  int m = T.size();
  vector<int> s(n), t(m);
  for(int i=0; i<n; i++) s[i] = S[i] - 'a';
  for(int i=0; i<m; i++) t[i] = T[i] - 'a';
  reverse(s.begin(), s.end());

  vector<ll> res(n+m-1);
  vector<ll> a(n), b(m), c;
  ll sum = 0;

  // (s^2 * p^2) * t^0
  for(int i=0; i<n; i++) {
    sum += s[i]*s[i] * p[s[i]]*p[s[i]];
  }

  // -2 * (s^2 * p + s * p^2) * t^1
  for(int i=0; i<n; i++) {
    a[i] = s[i]*s[i] * p[s[i]] + s[i] * p[s[i]]*p[s[i]];
  }
  for(int i=0; i<m; i++) {
    b[i] = t[i];
  }
  c = conv(a, b);
  for(int i=0; i<n+m-1; i++) {
    assert(c[i] >= 0 && c[i] < INF);
    res[i] += -2 * c[i];
  }

  // (4*s*p + s^2 + p^2) * t^2
  for(int i=0; i<n; i++) {
    a[i] = 4*s[i]*p[s[i]] + s[i]*s[i] + p[s[i]]*p[s[i]];
  }
  for(int i=0; i<m; i++) {
    b[i] = t[i]*t[i];
  }
  c = conv(a, b);
  for(int i=0; i<n+m-1; i++) {
    assert(c[i] >= 0 && c[i] < INF);
    res[i] += c[i];
  }

  // -2 * (s + p) * t^3
  for(int i=0; i<n; i++) {
    a[i] = s[i] + p[s[i]];
  }
  for(int i=0; i<m; i++) {
    b[i] = t[i]*t[i]*t[i];
  }
  c = conv(a, b);
  for(int i=0; i<n+m-1; i++) {
    assert(c[i] >= 0 && c[i] < INF);
    res[i] += -2 * c[i];
  }

  // 1 * t^4
  vector<ll> pref(m+1);
  for(int i=0; i<m; i++) {
    pref[i+1] = pref[i] + t[i]*t[i]*t[i]*t[i];
  }

  // output
  for(int i=n-1; i<m; i++) {
    ll val = (res[i] + sum + pref[i+1] - pref[i-n+1]) % MOD;
    cout << !val;
  }
  cout << nl;

  return 0;
}
