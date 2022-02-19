#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

int inverse(int n, int mod) {
  int res = 1;
  for(int e=mod-2; e>0; e/=2) {
    if(e&1) res = (ll)res * n % mod;
    n = (ll)n * n % mod;
  }
  return res;
}

template <int mod, int prime>
struct Hasher {
  vector<int> h, invp;
  Hasher(const string& s): h(size(s) + 1), invp(size(s) + 1) {
    int ip = inverse(prime, mod);
    invp[0] = 1;
    for(int i=0, mul=1; i<size(s); i++) {
      h[i+1] = (h[i] + (ll)mul * s[i]) % mod;
      invp[i+1] = (ll)invp[i] * ip % mod;
      mul = (ll)mul * prime % mod;
    }
  }
  int query(int i, int len) {
    return (ll)(h[i+len] + mod - h[i]) * invp[i] % mod;
  }
};

template <int mod, int prime, int... others>
struct MultiHasher : MultiHasher<others...>, Hasher<mod, prime> {
  MultiHasher(const string& s): MultiHasher<others...>(s), Hasher<mod, prime>(s) {}
  auto query(int i, int len) {
    return tuple_cat(
        tuple(Hasher<mod, prime>::query(i, len)),
        MultiHasher<others...>::query(i, len));
  }
};

template <int mod, int prime>
struct MultiHasher<mod, prime> : Hasher<mod, prime> {
  MultiHasher(const string& s): Hasher<mod, prime>(s) {}
  auto query(int i, int len) {
    return tuple(Hasher<mod, prime>::query(i, len));
  }
};

using FancyHasher = MultiHasher<
  (int)1e9+7, 31,
  (int)1e9+9, 37,
  (int)1e9+123, 97,
  (int)1e9+321, 101>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while(T--) {
    string s;
    cin >> s;
    int n = size(s);
    FancyHasher ha(s);
    reverse(begin(s), end(s));
    FancyHasher hb(s);

    int take = 0;
    for(int i=1; 2*i<=n && s[i-1] == s[n-i]; i++) {
      take++;
    }

    pair<int, int> mid(0, 0);
    for(int i=1; i+2*take<=n; i++) {
      if(ha.query(take, i) == hb.query(n - take - i, i)) {
        mid = max(mid, pair(i, n - take - i));
      }
      if(ha.query(n - take - i, i) == hb.query(take, i)) {
        mid = max(mid, pair(i, take));
      }
    }

    cout << s.substr(0, take) + s.substr(mid.second, mid.first) + s.substr(n - take, take) << nl;
  }

  return 0;
}
