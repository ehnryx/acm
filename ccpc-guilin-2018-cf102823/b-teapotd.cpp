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
template <ll M = (119<<23)+1, ll R = 62>
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

  int T;
  cin >> T;
  for(int testnum=1; testnum<=T; testnum++) {
    int n, l, m;
    cin >> n >> l >> m;
    vector<ll> a(n);
    for(int i=0; i<n; i++) {
      cin >> a[i];
    }

    vector<ll> base(l, 1), res(1, 1);
    for( ; m; m/=2) {
      if(m & 1) {
        res = conv(res, base, n);
      }
      base = conv(base, base, n);
    }

    reverse(a.begin(), a.end());
    a = conv(res, a, n);
    cout << "Case " << testnum << ":";
    for(int i=n-1; i>=0; i--) {
      cout << " " << a[i];
    }
    cout << nl;
  }

  return 0;
}
