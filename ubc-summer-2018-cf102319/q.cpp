%:include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"
#include "../../lca/number/mod_int.h"
#include "../../lca/misc/fast_input.h"

static const int input_buf_size = 10000;
fast_input<input_buf_size> fast_cin;

//#define FILENAME sadcactus

using ll = uint64_t;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct bit_mask <%
  static constexpr ll sink = 1ULL << 63;
  ll v;
  bit_mask(ll _v = sink): v(_v) <%%>
  friend ll operator | (ll a, bit_mask b) <% return a | b.v; %>
  bool operator < (const bit_mask& o) const <%
    if (v == o.v) return false;
    if ((v & o.v) == v && (v & -v) > (v ^ o.v)) return true;
    if ((v & o.v) == o.v && (o.v & -o.v) > (v ^ o.v)) return false;
    return v > o.v;
  %>
  bool is_sink() const <% return v == sink; %>
%>;

struct node <%
  bit_mask first, second, lazy;
  ll res;
  node(ll v = 0): first(v), second(), lazy(), res(0) <%%>

  ll get() const <% return res | first; %>

  void put(bit_mask x) <%
    first = x;
    lazy = x;
  %>

  void pull(const node& l, const node& r) <%
    res = l.res | r.res;
    first = max(l.first, r.first);
    second = max(l.second, r.second);
    if (l.first < first) <%
      res = res | l.first;
      second = max(second, l.first);
    %>
    if (r.first < first) <%
      res = res | r.first;
      second = max(second, r.first);
    %>
  %>

  void push(node& l, node& r) <%
    if (!lazy.is_sink()) <%
      if (l.second < lazy && lazy < l.first) l.put(lazy);
      if (r.second < lazy && lazy < r.first) r.put(lazy);
      lazy = bit_mask();
    %>
  %>

  bool break_condition(bit_mask x) const <%
    return !(x < first);
  %>

  bool put_condition(bit_mask x) const <%
    return second < x;
  %>

  static ll merge(ll a, ll b) <% return a | b; %>
%>;

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

  static const int M = 300;
  vector<int> primes;
  for(int i=2; i<M; i++) {
    bool np = false;
    for(int j=2; j<i; j++) {
      np |= (i % j == 0);
    }
    if(!np) {
      primes.push_back(i);
    }
  }

  function<ll(int)>to_bits = [=](int n) {
    ll bm = 1ULL << 62;
    for(int i=0; i<size(primes); i++) {
      if (n % primes[i] == 0) {
        bm |= 1ULL << (size(primes) - 1 - i);
      }
    }
    return bm;
  };

  int n;
  fast_cin >> n;
  vector<ll> a(n+1);
  for(int i=1; i<=n; i++) {
    int v;
    fast_cin >> v;
    a[i] = to_bits(v);
  }

  segment_tree<node, ll> st(a);
  int q;
  fast_cin >> q;
  while(q--) {
    int t;
    fast_cin >> t;
    if(t == 1) {
      int l, r, x;
      fast_cin >> l >> r >> x;
      st.update_range(l, r, to_bits(x));
    } else {
      int l, r;
      fast_cin >> l >> r;
      ll bm = st.query(l, r);
      mod_int<MOD> ans = 1;
      for(int i=0; i<size(primes); i++) {
        if (bm & 1ULL << (size(primes) - 1 - i)) {
          ans *= primes[i];
        }
      }
      cout << ans.v << nl;
    }
  }

  return 0;
}
