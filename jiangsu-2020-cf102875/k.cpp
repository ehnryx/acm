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

ll modpow(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2, n = n*n % m) {
    if(e&1) r = r*n % m;
  }
  return r;
}

template <int Prime, int Mod>
struct Hasher {
  static const int P = Prime;
  static const int M = Mod;
  vector<int> h, ip;
  Hasher(const vector<bool>& s): h(size(s) + 1), ip(size(s) + 1, 1) {
    int mul = 1;
    int inv = modpow(P, M - 2, M);
    for(int i=0; i<size(s); i++) {
      h[i+1] = (h[i] + (ll)s[i] * mul) % M;
      ip[i+1] = (ll)ip[i] * inv % M;
      mul = (ll)mul * P % M;
    }
  }
  int get(int l, int r) const {
    return (ll)(h[r] + M - h[l]) * ip[l] % M;
  }
};
using H = Hasher<97, 1'000'000'009>;

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

  int n;
  cin >> n;
  vector<vector<bool>> s(n);
  vector<pair<int,int>> order;
  for(int i=0; i<n; i++) {
    string bits;
    cin >> bits;
    transform(begin(bits), end(bits), back_inserter(s[i]),
        [](char c) { return c == '1'; });
    order.emplace_back(size(s[i]), i);
  }
  sort(begin(order), end(order));

  int len = size(s[order.back().second]);
  vector<bool> all(len);
  for(int i=0, j=0; i<len; i++) {
    while(size(s[order[j].second]) <= i) {
      j++;
      assert(j < n);
    }
    for(int k=j; k<n; k++) {
      all[i] = all[i] ^ s[order[k].second][i];
    }
  }

  H hall(all);
  int ans = 0;
  for(int i=0; i<n; i++) {
    H hcur(s[i]);
    int have = hall.get(0, len);
    for(int j=(int)size(s[i])-1; j>0; j--) {
      if(s[i][j]) {
        int mul = modpow(H::P, j, H::M);
        if(all[j]) {
          have = (have + H::M - mul) % H::M;
        } else {
          have = (have + mul) % H::M;
        }
      }
      if(have == hcur.get(j, size(s[i]))) {
        ans++;
        //cerr << i << " " << j << nl;
      }
    }
  }
  cout << ans << nl;

  return 0;
}
