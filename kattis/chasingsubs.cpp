//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll power(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*n % m;
    n = n*n % m;
  }
  return r;
}

ll inverse(ll n, ll m) {
  return power(n, m-2, m);
}

const ll P = 1789;
const ll M = 1e9+9;

struct Hasher {
  vector<ll> h[26], p, invp;

  Hasher(const string& s) {
    int n = s.size();
    p.resize(n+1);
    invp.resize(n+1);
    p[0] = invp[0] = 1;
    for(int i=1; i<=n; i++) {
      p[i] = p[i-1] * P % M;
      invp[i] = inverse(p[i], M);
    }
    for(int j=0; j<26; j++) {
      h[j].resize(n+1);
      for(int i=0; i<n; i++) {
        h[j][i+1] = (h[j][i] + (s[i]-'a' == j) * p[i]) % M;
      }
    }
  }

  ll get_hash(int j, int l, int r) {
    return (h[j][r] + M - h[j][l]) * invp[l] % M;
  }

  vector<ll> get_all(int l, int r) {
    vector<ll> out(26);
    for(int j=0; j<26; j++) {
      out[j] = get_hash(j, l, r);
    }
    return out;
  }
};

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  string s, t;
  cin >> s >> t;
  Hasher ss(s), tt(t);

  auto all = tt.get_all(0, t.size());
  vector<int> ans;
  for(int i=0; i+t.size()<=s.size(); i++) {
    bool ok = true;
    for(int j=0; j<26; j++) {
      auto cur = ss.get_hash(j, i, i+t.size());
      bool found = false;
      for(int k=0; k<26; k++) {
        found |= (cur == all[k]);
      }
      ok &= found;
    }
    if(ok) {
      ans.push_back(i);
    }
  }

  if(ans.size() == 1) {
    cout << s.substr(ans[0], t.size()) << nl;
  } else {
    cout << ans.size() << nl;
  }

  return 0;
}
