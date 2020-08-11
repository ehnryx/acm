//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "bw"

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

ostream& operator << (ostream& os, const pair<ll,ll>& v) {
  return os << v.first << " " << v.second;
}

void operator += (pair<ll,ll>& a, const pair<ll,ll>& b) {
  a.first += b.first;
  a.second += b.second;
}

void operator -= (pair<ll,ll>& a, const pair<ll,ll>& b) {
  a.first -= b.first;
  a.second -= b.second;
}

pair<ll,ll> calc(int l, int r, int h) {
  if(h < 0) {
    auto [a, b] = calc(l, r, -h);
    return make_pair(-b, -a);
  }

  ll all = (ll) (r-l) * h;
  assert(all >= 0);
  if(all % 2 == 0) {
    return make_pair(all/2, all/2);
  } else if(l%2 == 0) {
    return make_pair(all/2+1, all/2);
  } else {
    return make_pair(all/2, all/2+1);
  }
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<pair<int,int>> v;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    v.emplace_back(x, y);
  }

  pair<ll,ll> ans;
  for(int i=n-1, j=0; j<n; i=j++) {
    if(v[i].second == v[j].second) {
      if(v[i].first < v[j].first) {
        ans -= calc(v[i].first, v[j].first, v[i].second);
      } else {
        ans += calc(v[j].first, v[i].first, v[i].second);
      }
    }
  }
  cout << ans << nl;

  return 0;
}
