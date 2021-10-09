#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/data_structure/segment_tree.h"

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct node {
  ll a, b;
  node(): a(INFLL), b(INFLL) {}
  void put(ll _a, ll _b) {
    a = _a;
    b = _b;
  }
  const node& get() const { return *this; }
  const node& pull(const node& left, const node& right) {
    a = min(left.a, right.a);
    b = min(left.b, right.b);
    return *this;
  }
  static node default_value() { assert(false); }
  static node merge(const node& a, const node& b) {
    return node().pull(a, b);
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

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;

    vector<ll> ev;
    map<ll, ll> match;
    set<ll> is_point;
    vector<int> pts(n);
    for(int i=0; i<n; i++) {
      cin >> pts[i];
      ev.push_back(pts[i]);
      is_point.insert(pts[i]);
    }
    vector<pair<int, int>> segs(m);
    for(int i=0; i<m; i++) {
      cin >> segs[i].first >> segs[i].second;
      ev.push_back(segs[i].first);
      ev.push_back(segs[i].second);
      if(match.count(segs[i].first)) {
        match[segs[i].first] = min(match[segs[i].first], (ll)segs[i].second);
      } else {
        match[segs[i].first] = segs[i].second;
      }
    }

    ev.push_back(-INFLL); // start
    ev.push_back(INFLL); // end
    is_point.insert(-INFLL);
    is_point.insert(INFLL);
    match[-INFLL] = -INFLL;
    match[INFLL] = INFLL;

    sort(begin(ev), end(ev));
    ev.resize(unique(begin(ev), end(ev)) - begin(ev));

    int len = size(ev);
    map<ll, int> remap;
    for(int i=0; i<len; i++) {
      remap[ev[i]] = i;
    }

    vector<int> s(len);
    for(int i=len-1, to=len, last=len; i>=0; i--) {
      s[i] = min(to, last);
      if(match.count(ev[i])) {
        to = min(to, remap[match[ev[i]]]);
      }
      if(is_point.count(ev[i])) {
        last = i;
      }
    }

    vector<int> d(len);
    for(int i=0, to=-1; i<len; i++) {
      if(is_point.count(ev[i])) {
        to = remap[ev[i]];
      }
      d[i] = to;
    }

    vector<ll> dp(len, 0);
    segment_tree<node, node, false> st(len);
    assert(s[0] < len);
    st.update_point(0, 0 - ev[s[0]], 0 - 2*ev[s[0]]);
    for(int i=1; i<len; i++) {
      if(d[i] <= 0) continue; // can't
      auto [a, b] = st.query(0, d[i] - 1);
      dp[i] = min(a + 2*ev[i] - ev[d[i]], b + ev[i] + ev[d[i]]);
      if(i + 1 < len) {
        st.update_point(i, dp[i] - ev[s[i]], dp[i] - 2*ev[s[i]]);
      }
    }
    cout << dp[len - 1] << nl;
  }

  return 0;
}
