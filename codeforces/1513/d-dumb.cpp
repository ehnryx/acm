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

struct SegmentTree {
  int n;
  vector<int> st;
  SegmentTree(int _n) {
    n = 1 << (32 - __builtin_clz(max(1, _n-1)));
    st.resize(2 * n);
  }
  void insert(int i, int v) {
    st[i += n] = v;
    for(i/=2; i; i/=2) {
      st[i] = gcd(st[2*i], st[2*i+1]);
    }
  }
  int query(int l, int r) {
    int res = 0;
    for(l+=n, r+=n+1; l<r; l/=2, r/=2) {
      if(l&1) res = gcd(res, st[l++]);
      if(r&1) res = gcd(res, st[--r]);
    }
    return res;
  }

  int search_left(int x, int v) {
    int l = 0;
    int r = x;
    while(l < r) {
      int m = (l+r) / 2;
      if(query(m, r) % v) {
        l = m+1;
      } else {
        r = m;
      }
    }
    return r;
  }
  int search_right(int x, int v) {
    int l = x;
    int r = n-1;
    while(l < r) {
      int m = (l+r+1) / 2;
      if(query(l, m) % v) {
        r = m-1;
      } else {
        l = m;
      }
    }
    return r;
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
    int n, cost;
    cin >> n >> cost;
    vector<int> a(n);
    vector<pair<int,int>> order;
    SegmentTree st(n);
    for(int i=0; i<n; i++) {
      cin >> a[i];
      order.emplace_back(a[i], i);
      st.insert(i, a[i]);
    }
    sort(begin(order), end(order));

    vector<tuple<int,int,int>> segs;
    for(auto [v, i] : order) {
      int l = st.search_left(i, v);
      int r = min(n-1, st.search_right(i, v));
      segs.emplace_back(l, r, v);
    }
    segs.emplace_back(0, n-1, cost);
    segs.emplace_back(n-1, n-1, INF);
    sort(begin(segs), end(segs));

    multiset<int> have;
    vector<vector<int>> rem(n);
    int pos = 0;
    ll ans = 0;
    for(auto [l, r, v] : segs) {
      //cerr << l << " " << r << " " << v << nl;
      while(pos < l) {
        // pos -> pos + 1
        for(int j : rem[pos]) {
          have.erase(have.find(j));
        }
        ans += *have.begin();
        pos++;
      }
      rem[r].push_back(v);
      have.insert(v);
    }

    cout << ans << nl;
  }

  return 0;
}
