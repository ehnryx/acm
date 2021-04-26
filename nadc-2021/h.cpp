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

template <ll P, ll M>
struct Hasher {
  vector<ll> h, ip;
  Hasher(const string& s) {
    h.resize(size(s) + 1);
    ip.resize(size(s) + 1, 1);
    ll mul = 1;
    ll invp = inverse(P, M);
    for(int i=0; i<size(s); i++) {
      h[i+1] = (h[i] + s[i] * mul) % M;
      ip[i+1] = ip[i] * invp % M;
      mul = mul * P % M;
    }
  }
  ll get(int l, int r) const {
    return (h[r+1] + M - h[l]) * ip[l] % M;
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

  int n;
  cin >> n;
  vector<tuple<ll,ll,int>> have;
  // should split into |s| vectors to be faster
  // std::set is ~4x slower!!!
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    Hasher<101,(int)1e9+7> h1(s);
    Hasher<1789,998244353> h2(s);
    vector<tuple<ll,ll,int>> cur;
    for(int j=0; j<size(s); j++) {
      for(int k=0; k<=j; k++) {
        cur.emplace_back(h1.get(k, j), h2.get(k, j), j - k + 1);
      }
    }
    sort(begin(cur), end(cur));
    if(i == 0) {
      have = move(cur);
    } else {
      auto it = set_intersection(
          begin(have), end(have),
          begin(cur), end(cur),
          begin(have));
      have.resize(it - begin(have));
    }
  }

  int ans = 0;
  for(auto it : have) {
    ans = max(ans, get<2>(it));
  }
  cout << ans << nl;

  return 0;
}
