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
random_device _rd; mt19937 rng(_rd());

ll inverse(ll n, ll m) {
  ll r = 1;
  for(ll e=m-2; e; e/=2, n = n*n % m) {
    if(e&1) r = r*n % m;
  }
  return r;
}

template <int P, int M>
struct Hash {
  vector<int> v, ip;
  Hash(const string& s): v(size(s) + 1), ip(size(s) + 1, 1) {
    ll inv = inverse(P, M);
    ll mul = 1;
    for(int i=0; i<size(s); i++) {
      v[i+1] = (v[i] + s[i] * mul) % M;
      ip[i+1] = ip[i] * inv % M;
      mul = mul * P % M;
    }
  }
  int get(int s, int len) const {
    return (v[s + len] + M - v[s]) * (ll)ip[s] % M;
  }
};

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

  string s;
  cin >> s;
  int n = size(s);

  Hash<101,(int)1e9+7> h1(s);
  //Hash<1789,(int)1e9+9> h2(s);
  //Hash<37,998244353> h3(s);
  function<int(int,int)> query = [=](int a, int b) {
    int l = 0;
    int r = n - b;
    while(l < r) {
      int m = (l+r+1) / 2;
      if(h1.get(a, m) == h1.get(b, m)) {
          //&& h2.get(a, m) == h2.get(b, m)
          //&& h3.get(a, m) == h3.get(b, m)) {
        l = m;
      } else {
        r = m-1;
      }
    }
    return r;
  };

  for(int d=1; d<=n/3; d++) {
    int len1 = query(0, d) / d * d;
    int b = d + len1;
    int len2 = query(b, b+d) / d * d;
    int c = b+d + len2;
    int len3 = query(c, c+d);
    if(len3 == n - (c+d)) {
      cout << s.substr(0, d) << " " << s.substr(b, d) << nl;
      return 0;
    }
  }
  assert(false);

  return 0;
}
